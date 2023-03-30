
#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 256
#define MAX_LABELS 1000
#define MAX_SYMBOLS 1000
#define MAX_ENTRIES 100

struct counter {
    int ic;
    int dc;
};

void add_label(char* label) {
    strcpy(labels[label_count], label);
    label_count++;
}

void add_symbol(char* symbol) {
    strcpy(symbols[symbol_count], symbol);
    symbol_count++;
}

void add_entry(int ic) {
    entry_table[entry_count] = ic;
    entry_count++;
}

int is_label(char* word) {
    int i;
    for (i = 0; i < label_count; i++) {
        if (strcmp(labels[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}


void finalPassage(char* fileName, char** labels) {
    
    struct counter cnt = { 100,0 };
    FILE* fp;
    char line[MAX_LINE_LENGTH];

    fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("Error: cannot open input file\n");
        return 1;
    }

    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        // Remove newline character from line
        line[strcspn(line, "\n")] = '\0';

        // Parse line to get first word
        char* word = strtok(line, " ");

        // Check if word is a label
        if (is_label(word)) {
            continue; // skip label
        }

        // Check if word is .string, .data or .extern
        if (strcmp(word, ".string") == 0 ||
            strcmp(word, ".data") == 0 ||
            strcmp(word, ".extern") == 0) {
            cnt.ic = cnt.ic + 1;
            continue; // skip line
        }

        // Check if word is .entry
        if (strcmp(word, ".entry") == 0) {
            // Mark ic in entry table
            add_entry(ic);
            cnt.ic = cnt.ic + 1;
            continue;
        }

        // Complete operand coding
        // ...

        // Increment ic
        ic++;

        // Going back to step 2 and repeating the reading line
    }

    fclose(fp);

    // Save file with .o extension
    // ...

    return 0;
}
