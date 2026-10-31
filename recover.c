#include <iostream>
#include <fstream>
#include <cstdint>
#include <iomanip>
#include <sstream>
#include <vector>

const int BLOCK_SIZE = 512;

int main() {
    std::ifstream in("card.raw", std::ios::binary);
    if (!in) {
        std::cerr << "Error: Could not open card.raw" << std::endl;
        return 1;
    }

    std::vector<uint8_t> buffer(BLOCK_SIZE);
    std::ofstream out;
    int fileCount = 0;
    bool isImgFound = false;

    while (in.read(reinterpret_cast<char*>(buffer.data()), BLOCK_SIZE) || in.gcount() > 0) {
        bool isJpegStart = (buffer == 0xff && 
                            buffer == 0xd8 && 
                            buffer == 0xff && 
                            (buffer & 0xf0) == 0xe0);

        if (isJpegStart) {
            if (isImgFound) {
                out.close();
            } else {
                isImgFound = true;
            }

            std::stringstream ss;
            ss << std::setw(3) << std::setfill('0') << fileCount << ".jpg";
            
            out.open(ss.str(), std::ios::binary);
            if (!out) {
                std::cerr << "Error: Could not create output image" << std::endl;
                return 1;
            }
            fileCount++;
        }

        if (isImgFound) {
            out.write(reinterpret_cast<char*>(buffer.data()), in.gcount());
        }
    }

    if (out.is_open()) {
        out.close();
    }
    in.close();

    std::cout << "Success: Recovered " << fileCount << " images." << std::endl;
    return 0;
}