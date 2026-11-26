#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum { WORD_LIMIT = 45, BUCKETS = 4096, FAMILY_DEPTH = 3 };

typedef struct Entry
{
    char text[WORD_LIMIT + 1];
    struct Entry *next;
} Entry;

typedef struct
{
    Entry *buckets[BUCKETS];
    size_t count;
} Dictionary;

typedef struct Relative
{
    struct Relative *parent[2];
    char gene[2];
} Relative;

typedef enum { INPUT_END, INPUT_OK, INPUT_LONG } InputStatus;

static InputStatus read_line(char *buffer, size_t capacity)
{
    if (fgets(buffer, (int) capacity, stdin) == NULL)
    {
        return INPUT_END;
    }

    char *newline = strchr(buffer, '\n');
    if (newline != NULL)
    {
        *newline = '\0';
        return INPUT_OK;
    }

    int character = getchar();
    if (character == '\n' || character == EOF)
    {
        return INPUT_OK;
    }

    while ((character = getchar()) != '\n' && character != EOF)
    {
    }
    return INPUT_LONG;
}

static void normalize(char *destination, const char *source)
{
    do
    {
        *destination++ = (char) tolower((unsigned char) *source);
    }
    while (*source++ != '\0');
}

static size_t bucket_for(const char *text)
{
    uint32_t value = UINT32_C(2166136261);
    while (*text != '\0')
    {
        value ^= (unsigned char) *text++;
        value *= UINT32_C(16777619);
    }
    return value % BUCKETS;
}

static bool dictionary_add(Dictionary *dictionary, const char *text)
{
    if (text[0] == '\0' || strlen(text) > WORD_LIMIT)
    {
        return false;
    }

    Entry *entry = malloc(sizeof(*entry));
    if (entry == NULL)
    {
        return false;
    }

    normalize(entry->text, text);
    size_t bucket = bucket_for(entry->text);
    entry->next = dictionary->buckets[bucket];
    dictionary->buckets[bucket] = entry;
    dictionary->count++;
    return true;
}

static bool dictionary_contains(const Dictionary *dictionary, const char *text)
{
    if (strlen(text) > WORD_LIMIT)
    {
        return false;
    }

    char key[WORD_LIMIT + 1];
    normalize(key, text);

    for (const Entry *entry = dictionary->buckets[bucket_for(key)];
         entry != NULL; entry = entry->next)
    {
        if (strcmp(entry->text, key) == 0)
        {
            return true;
        }
    }
    return false;
}

static void dictionary_clear(Dictionary *dictionary)
{
    for (size_t bucket = 0; bucket < BUCKETS; bucket++)
    {
        while (dictionary->buckets[bucket] != NULL)
        {
            Entry *entry = dictionary->buckets[bucket];
            dictionary->buckets[bucket] = entry->next;
            free(entry);
        }
    }
    dictionary->count = 0;
}

static void word_demo(void)
{
    const char *examples[] = {
        "apple", "banana", "cat", "algorithm", "recursion"
    };
    Dictionary dictionary = {0};

    for (size_t i = 0; i < sizeof(examples) / sizeof(examples[0]); i++)
    {
        if (!dictionary_add(&dictionary, examples[i]))
        {
            fprintf(stderr, "Could not load the dictionary.\n");
            dictionary_clear(&dictionary);
            return;
        }
    }

    printf("Word count: %zu\n", dictionary.count);
    for (;;)
    {
        char input[WORD_LIMIT + 1];
        printf("Enter word (or 'exit'): ");
        fflush(stdout);
        InputStatus status = read_line(input, sizeof(input));
        if (status == INPUT_END)
        {
            break;
        }
        if (status == INPUT_LONG)
        {
            puts("Word is too long.");
            continue;
        }
        if (strcmp(input, "exit") == 0)
        {
            break;
        }
        puts(dictionary_contains(&dictionary, input) ? "Found" : "Not found");
    }
    dictionary_clear(&dictionary);
}

static void destroy_family(Relative *member)
{
    if (member != NULL)
    {
        for (size_t side = 0; side < 2; side++)
        {
            destroy_family(member->parent[side]);
        }
        free(member);
    }
}

static Relative *build_family(unsigned int depth)
{
    if (depth == 0)
    {
        return NULL;
    }

    Relative *member = calloc(1, sizeof(*member));
    if (member == NULL)
    {
        return NULL;
    }

    static const char alleles[] = {'A', 'B', 'O'};
    for (size_t side = 0; side < 2; side++)
    {
        if (depth == 1)
        {
            member->gene[side] = alleles[rand() % 3];
            continue;
        }

        member->parent[side] = build_family(depth - 1);
        if (member->parent[side] == NULL)
        {
            destroy_family(member);
            return NULL;
        }
        member->gene[side] = member->parent[side]->gene[rand() % 2];
    }
    return member;
}

static void display_family(const Relative *member, unsigned int level)
{
    if (member == NULL)
    {
        return;
    }
    printf("%*sGen %u: %c%c\n", (int) (level * 4), "",
           level, member->gene[0], member->gene[1]);
    for (size_t side = 0; side < 2; side++)
    {
        display_family(member->parent[side], level + 1);
    }
}

static void family_demo(void)
{
    Relative *root = build_family(FAMILY_DEPTH);
    if (root == NULL)
    {
        fprintf(stderr, "Could not create the family.\n");
        return;
    }
    display_family(root, 0);
    destroy_family(root);
}

int main(void)
{
    srand((unsigned int) time(NULL));
    for (;;)
    {
        char selection[32];
        printf("\n1. Dictionary\n2. Family tree\n0. Exit\nSelect: ");
        fflush(stdout);
        InputStatus status = read_line(selection, sizeof(selection));
        if (status == INPUT_END)
        {
            return EXIT_SUCCESS;
        }
        if (status == INPUT_LONG)
        {
            puts("Enter 0, 1 or 2.");
            continue;
        }

        if (strcmp(selection, "0") == 0)
        {
            return EXIT_SUCCESS;
        }
        else if (strcmp(selection, "1") == 0)
        {
            word_demo();
        }
        else if (strcmp(selection, "2") == 0)
        {
            family_demo();
        }
        else
        {
            puts("Enter 0, 1 or 2.");
        }
    }
}