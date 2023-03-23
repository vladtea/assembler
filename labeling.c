#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char saved_words[24][4] = {
    "mov",
    "cmp",
    "add",
    "sub",
    "not",
    "clr",
    "lea",
    "inc",
    "dec",
    "jmp",
    "bne",
    "red",
    "prn",
    "jsr",
    "rts",
    "stop"
    "r0",
    "r1",
    "r2",
    "r3",
    "r4",
    "r5",
    "r6",
    "r7"
};


void extract_labels(const char* fileName, char* labels[], int max_labels) {
    char line[1000]; // buffer to store input line
    int num_labels = 0; // number of labels found

    // open input file
    FILE* fp = fopen(fileName, "r");
    if (fp == NULL) {
        perror("Error opening file");
        exit(1);
    }

    // read file line by line
    while (fgets(line, sizeof(line), fp)) {
        // extract label from beginning of line
        char* label_end = strchr(line, ':');
        if (label_end != NULL) {
            // allocate memory for label and copy it to array
            int label_len = label_end - line + 1;
            char* label = malloc(label_len);
            strncpy(label, line, label_len);
            label[label_len - 1] = '\0';

            // check if label already exists
            for (int i = 0; i < num_labels; i++) {
                if (strcmp(labels[i], label) == 0) {
                    fprintf(stderr, "Error: label '%s' already exists\n", label);
                    exit(1);
                }
            }

            for (int j = 0; j < sizeof(saved_words); j++) {
                if (strcmp(saved_words[j], label) == 0) {
                    fprintf(stderr, "Error: label '%s' is a saved word in assembly\n", saved_words[j]);
                    
                }
            }

            for (int i = 0; i < num_labels; i++) {
                if (strcmp(labels[i], label) == 0) {
                    fprintf(stderr, "Error: label '%s' already exists\n", label);
                    
                }
            }

            labels[num_labels++] = label;

            if (num_labels == max_labels) {
                break;
            }
        }
    }

    // close file
    fclose(fp);
}
