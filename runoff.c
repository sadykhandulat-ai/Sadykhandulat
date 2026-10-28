#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

int preferences[MAX_VOTERS][MAX_CANDIDATES];

typedef struct {
    char name[50];
    int votes;
    bool eliminated;
} candidate;

candidate candidates[MAX_CANDIDATES];
int voter_count = 0;
int candidate_count = 0;

bool vote(int voter, int rank, char *name);
void tabulate(void);
int find_min(void);
void eliminate(int min);
bool print_winner(void);

int main(void) {
    printf("Enter number of candidates: ");
    if (scanf("%d", &candidate_count) != 1 || candidate_count > MAX_CANDIDATES || candidate_count < 1) {
        return 1;
    }

    for (int i = 0; i < candidate_count; i++) {
        printf("Candidate %d name: ", i + 1);
        scanf("%s", candidates[i].name);
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    printf("Enter number of voters: ");
    if (scanf("%d", &voter_count) != 1 || voter_count > MAX_VOTERS || voter_count < 1) {
        return 1;
    }

    for (int i = 0; i < voter_count; i++) {
        for (int j = 0; j < candidate_count; j++) {
            char name[50];
            printf("Voter %d, Rank %d: ", i + 1, j + 1);
            scanf("%s", name);

            if (!vote(i, j, name)) {
                printf("Invalid vote.\n");
                return 2;
            }
        }
        printf("\n");
    }

    while (true) {
        tabulate();

        bool won = print_winner();
        if (won) {
            break;
        }

        int min = find_min();
        
        bool tie = true;
        for (int i = 0; i < candidate_count; i++) {
            if (!candidates[i].eliminated && candidates[i].votes != min) {
                tie = false;
                break;
            }
        }

        if (tie) {
            for (int i = 0; i < candidate_count; i++) {
                if (!candidates[i].eliminated) {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        eliminate(min);

        for (int i = 0; i < candidate_count; i++) {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

bool vote(int voter, int rank, char *name) {
    for (int i = 0; i < candidate_count; i++) {
        if (strcmp(candidates[i].name, name) == 0) {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

void tabulate(void) {
    for (int i = 0; i < voter_count; i++) {
        for (int j = 0; j < candidate_count; j++) {
            int candidate_idx = preferences[i][j];
            if (!candidates[candidate_idx].eliminated) {
                candidates[candidate_idx].votes++;
                break;
            }
        }
    }
}

int find_min(void) {
    int min_votes = voter_count;
    for (int i = 0; i < candidate_count; i++) {
        if (!candidates[i].eliminated && candidates[i].votes < min_votes) {
            min_votes = candidates[i].votes;
        }
    }
    return min_votes;
}

void eliminate(int min) {
    for (int i = 0; i < candidate_count; i++) {
        if (!candidates[i].eliminated && candidates[i].votes == min) {
            candidates[i].eliminated = true;
        }
    }
}

bool print_winner(void) {
    int majority = voter_count / 2;
    for (int i = 0; i < candidate_count; i++) {
        if (!candidates[i].eliminated && candidates[i].votes > majority) {
            printf("\nWinner: %s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}
