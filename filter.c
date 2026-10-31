#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <cstdint>
#include <string>

#pragma pack(push, 1)
struct BMPFileHeader {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
};

struct BMPInfoHeader {
    uint32_t biSize;
    int32_t  biWidth;
    int32_t  biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t  biXPelsPerMeter;
    int32_t  biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};

struct RGBTRIPLE {
    uint8_t rgbtBlue;
    uint8_t rgbtGreen;
    uint8_t rgbtRed;
};
#pragma pack(pop)

void grayscale(int height, int width, std::vector<std::vector<RGBTRIPLE>>& image) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int average = std::round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
}

void sepia(int height, int width, std::vector<std::vector<RGBTRIPLE>>& image) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int r = image[i][j].rgbtRed;
            int g = image[i][j].rgbtGreen;
            int b = image[i][j].rgbtBlue;

            int sepiaRed = std::round(.393 * r + .769 * g + .189 * b);
            int sepiaGreen = std::round(.349 * r + .686 * g + .168 * b);
            int sepiaBlue = std::round(.272 * r + .534 * g + .131 * b);

            image[i][j].rgbtRed = std::min(255, sepiaRed);
            image[i][j].rgbtGreen = std::min(255, sepiaGreen);
            image[i][j].rgbtBlue = std::min(255, sepiaBlue);
        }
    }
}

void reflect(int height, int width, std::vector<std::vector<RGBTRIPLE>>& image) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width / 2; j++) {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
}

void blur(int height, int width, std::vector<std::vector<RGBTRIPLE>>& image) {
    std::vector<std::vector<RGBTRIPLE>> copy = image;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            float sumRed = 0, sumGreen = 0, sumBlue = 0;
            int counter = 0;

            for (int r = -1; r <= 1; r++) {
                for (int c = -1; c <= 1; c++) {
                    int nextI = i + r;
                    int nextJ = j + c;

                    if (nextI >= 0 && nextI < height && nextJ >= 0 && nextJ < width) {
                        sumRed += copy[nextI][nextJ].rgbtRed;
                        sumGreen += copy[nextI][nextJ].rgbtGreen;
                        sumBlue += copy[nextI][nextJ].rgbtBlue;
                        counter++;
                    }
                }
            }

            image[i][j].rgbtRed = std::round(sumRed / counter);
            image[i][j].rgbtGreen = std::round(sumGreen / counter);
            image[i][j].rgbtBlue = std::round(sumBlue / counter);
        }
    }
}

int main() {
    std::string inputFile = "input.bmp";
    std::string outputFile = "output.bmp";

    std::ifstream in(inputFile, std::ios::binary);
    if (!in) {
        std::cerr << "Error: Could not open " << inputFile << std::endl;
        return 1;
    }

    BMPFileHeader fileHeader;
    BMPInfoHeader infoHeader;

    in.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    in.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    if (fileHeader.bfType != 0x4D42 || infoHeader.biBitCount != 24 || infoHeader.biCompression != 0) {
        std::cerr << "Error: Only 24-bit uncompressed BMP files are supported." << std::endl;
        return 1;
    }

    int height = std::abs(infoHeader.biHeight);
    int width = infoHeader.biWidth;
    int padding = (4 - (width * sizeof(RGBTRIPLE)) % 4) % 4;

    std::vector<std::vector<RGBTRIPLE>> image(height, std::vector<RGBTRIPLE>(width));

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            in.read(reinterpret_cast<char*>(&image[i][j]), sizeof(RGBTRIPLE));
        }
        in.seekg(padding, std::ios::cur);
    }
    in.close();

    blur(height, width, image);

    std::ofstream out(outputFile, std::ios::binary);
    if (!out) {
        std::cerr << "Error: Could not create output file." << std::endl;
        return 1;
    }

    out.write(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    out.write(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            out.write(reinterpret_cast<char*>(&image[i][j]), sizeof(RGBTRIPLE));
        }
        for (int k = 0; k < padding; k++) {
            out.put(0);
        }
    }
    out.close();

    std::cout << "Success: Filter applied. Saved as " << outputFile << std::endl;
    return 0;
}