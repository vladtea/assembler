#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_MACRO_SIZE 10000
#define MAX_NAME_SIZE 81
#define MAX_CONTENT_SIZE 950

typedef struct Macro {
    char name[MAX_NAME_SIZE];
    char content[MAX_CONTENT_SIZE];
} Macro;

Macro* find_macros(const char* filename, int* num_macros) {
    Macro* macros = NULL;
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file.\n");
        return NULL;
    }
    int in_macro = 0;
    char line[MAX_MACRO_SIZE];
    char name[MAX_NAME_SIZE];
    char content[MAX_CONTENT_SIZE];
    int content_index = 0;
    while (fgets(line, MAX_MACRO_SIZE, file)) {
        if (in_macro) {
            if (strstr(line, "endmcr")) {
                in_macro = 0;
                Macro macro;
                strcpy(macro.name, name);
                strcpy(macro.content, content);
                (*num_macros)++;
                macros = (Macro*)realloc(macros, (*num_macros) * sizeof(Macro));
                macros[(*num_macros) - 1] = macro;
                memset(name, 0, MAX_NAME_SIZE);
                memset(content, 0, MAX_CONTENT_SIZE);
                content_index = 0;
            }
            else {
                strcat(content, line);
                content_index += strlen(line);
            }
        }
        else {
            char* macro_start = strstr(line, "mcr ");
            if (macro_start) {
                in_macro = 1;
                macro_start += strlen("mcr ");
                sscanf(macro_start, "%s", name);
            }
        }
    }
    fclose(file);
    return macros;
}

void replace_macros(const char* filename, Macro* macros, int num_macros) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }
    FILE* newfile = fopen("asmbnew.txt", "w"); // open new file for writing
    if (!newfile) {
        printf("Error creating new file.\n");
        fclose(file);
        return;
    }

    char line[MAX_MACRO_SIZE];
    while (fgets(line, MAX_MACRO_SIZE, file)) {
        char* line_pos = line;
        // loop through all macros
        for (int i = 0; i < num_macros; i++) {
            char* macro_pos = strstr(line_pos, macros[i].name);
            while (macro_pos != NULL) {
                // write line before the macro
                int before_macro_len = macro_pos - line_pos;
                fwrite(line_pos, sizeof(char), before_macro_len, newfile);
                // write macro content
                fwrite(macros[i].content, sizeof(char), strlen(macros[i].content), newfile);
                // advance line pointer past macro name
                line_pos += before_macro_len + strlen(macros[i].name);
                macro_pos = strstr(line_pos, macros[i].name);
            }
        }
        // check if line only contains line break character
        if (strlen(line) == 1 && line[0] == '\n') {
            continue;
        }
        fprintf(newfile, "%s", line_pos); // write remaining line to new file
    }

    fclose(file);
    fclose(newfile);
}


void delete_macros(const char* filename, const char* new_filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }
    FILE* new_file = fopen(new_filename, "w");
    if (!new_file) {
        printf("Error creating new file.\n");
        fclose(file);
        return;
    }

    char line[MAX_MACRO_SIZE];
    int in_macro = 0;
    while (fgets(line, sizeof(line), file)) {
        // remove newline character from line
        int len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
            len--;
        }

        // check if we are inside a macro definition
        if (in_macro) {
            if (strstr(line, "endmcr")) {
                in_macro = 0;
            }
        }
        else {
            // check if this line starts a macro definition
            if (strstr(line, "mcr ")) {
                in_macro = 1;
            }
            else if (len > 0 && !isspace(line[0])) {
                // write line to new file if not in macro definition and not a blank line
                fprintf(new_file, "%s\n", line);
            }
        }
    }

    fclose(file);
    fclose(new_file);
}
