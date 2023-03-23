#include <stdio.h>


enum Opcode {
    mov = 0b0000,
    cmp = 0b0001,
    add = 0b0010,
    sub = 0b0011,
    not = 0b0100,
    clr = 0b0101,
    lea = 0b0110,
    inc = 0b0111,
    dec = 0b1000,
    jmp = 0b1001,
    bne = 0b1010,
    red = 0b1011,
    prn = 0b1100,
    jsr = 0b1101,
    rts = 0b1110,
    stop = 0b1111
};

while (currentChar != EOF) {
    // ignore whitespace
    if (isspace(currentChar)) {
        currentChar = fgetc(inputFile);
        continue;
    }

switch (my_OpCode) {
    case mov:
        printf("The color is red");
        break;
    case cmp:
        printf("The color is green");
        break;
    case add:
        printf("The color is blue");
        break;
    case sub:
        printf("The color is blue");
        break;
    case not:
        printf("The color is blue");
        break;
    case clr:
        printf("The color is blue");
        break;
    case lea:
        printf("The color is blue");
        break;
    case inc:
        printf("The color is blue");
        break;
    case dec:
        printf("The color is blue");
        break;
    case jmp:
        printf("The color is blue");
        break;
    case bne:
        printf("The color is blue");
        break;
    case red:
        printf("The color is blue");
        break;
    case prn:
        printf("The color is blue");
        break;
    case jsr:
        printf("The color is blue");
        break;
    case rts:
        printf("The color is blue");
        break;
    case stop:
        printf("The color is blue");
        break;

    }




void reader() {


}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MACRO_SIZE 1000
#define MAX_NAME_SIZE 50
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
    char line[MAX_MACRO_SIZE];
    while (fgets(line, MAX_MACRO_SIZE, file)) {
        for (int i = 0; i < num_macros; i++) {
            if (strstr(line, macros[i].name)) {
                printf("%s", macros[i].content);
                break;
            }
        }
        if (!strstr(line, "mcr ")) {
            printf("%s", line);
        }
    }
    fclose(file);
}

int main() {
    int num_macros = 0;
    Macro* macros = find_macros("asmb.txt", &num_macros);
    if (!macros) {
        printf("Error finding macros.\n");
        return 1;
    }
    replace_macros("asmb.txt", macros, num_macros);
    free(macros);
    return 0;
}
