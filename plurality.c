#include <stdio.h>
#include <string.h>

struct Candidate {
    char name[50];
    int votes;
};

int main()
{
    struct Candidate candidates[3] = {
        {"Alice", 0},
        {"Bob", 0},
        {"Charlie", 0}
    };

    int candidate_count = 3;

char votes[5] [20] = {
        "Alice",
        "Bob",
        "Charlie",
        "Alice",
        "Bob"
    };

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < candidate_count; j++) {
            if (strcmp(votes[i], candidates[j].name) == 0) {
                candidates[j].votes++;
                break;
            }
        }
    }

    printf("Vote counts:\n");
    for (int i = 0; i < candidate_count; i++) {
        printf("%s: %d votes\n", candidates[i].name, candidates[i].votes);
    }

    return 0;
}