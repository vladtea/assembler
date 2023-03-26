#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum Register {
    r0,
    r1,
    r2,
    r3,
    r4,
    r5,
    r6,
    r7
};

enum OpCodeEnum {
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

struct symbol {
    char name[256];
    int type;
    int value;
};

struct opcode {
    char name[256];
    int opcode;
    int operands;
};

struct operand {
    char name[256];
    int address_mode;
};

struct opcode opcodes[] = {
        {"mov", 0, 2},
        {"cmp", 1, 2},
        {"add", 2, 2},
        {"sub", 3, 2},
        {"not", 4, 1},
        {"clr", 5, 1},
        {"lea", 6, 2},
        {"inc", 7, 1},
        {"dec", 8, 1},
        {"jmp", 9, 1},
        {"bne", 10, 1},
        {"red", 11, 1},
        {"prn", 12, 1},
        {"jsr", 13, 1},
        {"rts", 14, 0},
        {"stop", 15, 0}
};
int num_opcodes = sizeof(opcodes) / sizeof(struct opcode);


struct operand operands[] = {
        {"imm", 0},
        {"dir", 1},
        {"ind", 2},
        {"reg", 3}
};
int num_operands = sizeof(operands) / sizeof(struct operand);




int DC = 0;
int IC = 0;
char line[256];
struct symbol symtab[256];
int symtab_size = 0;
int has_symbol = 0;
void reader(const char* fileName) {
    FILE* src_file = fopen(fileName, "r");
    if (!src_file) {
        printf("Error opening source file\n");
        return 1;
    }

    while (fgets(line, 256, src_file)) {
        char symbol[256];
        char opcode[256];
        char operand1[256];
        char operand2[256];
        int bytes = 0;
        has_symbol = 0;

        // Parse line for symbol, opcode, and operands
        if (sscanf(line, "%s %s %s %s", symbol, opcode, operand1, operand2) >= 2) {
            has_symbol = 1;
        }
        else if (sscanf(line, "%s %s", opcode, operand1) < 1) {
            // Line is blank or contains only whitespace
            continue;
        }

        // Check if symbol is valid and insert into symbol table
        if (has_symbol) {
            // TODO: check if symbol is valid
            strcpy(symtab[symtab_size].name, symbol);
            symtab[symtab_size].type = -1; // Set symbol type to undefined for now
            symtab[symtab_size].value = 0;
            symtab_size++;
        }

        // Check if line contains a data storage directive
        if (strstr(opcode, ".data") || strstr(opcode, ".string")) {
            // TODO: implement data storage directive parsing and encoding
        }

        // Check if line contains an entry or extern instruction
        if (strstr(opcode, ".entry") || strstr(opcode, ".extern")) {
            // TODO: implement entry and extern instruction parsing and handling
        }

        // Check if line contains an instruction
        for (int i = 0; i < num_opcodes; i++) {
            if (strcmp(opcode, opcodes[i].name) == 0) {
                // Instruction found, check number of operands
                if ((opcodes[i].operands == 1 && operand2[0] != '\0') ||
                    (opcodes[i].operands == 2 && operand2[0] == '\0')) {
                    printf("Error: incorrect number of operands for %s\n", opcode);
                    break;
                }

                // Encode instruction and update instruction counter (IC)
                int opcode_value = opcodes[i].opcode;
                int addressing_mode1 = 0;
                int addressing_mode2 = 0;
                bytes = 1; // Opcode always takes up one byte

                for (int j = 0; j < num_operands; j++) {
                    if (strstr(operand1, operands[j].name)) {
                        addressing_mode1 = operands[j].address_mode;
                        bytes++;
                        break;
                    }
                }

                if (operand2[0] != '\0') {
                    for (int j = 0; j < num_operands; j++) {
                        if (strstr(operand2, operands[j].name)) {
                            addressing_mode2 = operands[j].address_mode;
                            bytes++;
                            break;
                        }
                    }
                }

                IC += bytes;

                // Update symbol table entry for instruction
                if (has_symbol) {
                    for (int j = 0; j < symtab_size; j++) {
                        if (strcmp(symbol, symtab[j].name) == 0) {
                            if (symtab[j].type != -1) {
                                printf("Error: symbol %s already defined\n", symbol);
                                break;
                            }
                            symtab[j].type = IC - bytes; // Value is address of instruction
                            break;
                        }
                    }
                }

                break;
            }
            else if (i == num_opcodes - 1) {
                printf("Error: invalid opcode %s\n", opcode);
            }
        }
    }

    fclose(src_file);


    // Print out symbol table for debugging purposes
    for (int i = 0; i < symtab_size; i++) {
        printf("Symbol: %s, Type: %d, Value: %d\n", symtab[i].name, symtab[i].type, symtab[i].value);
    }


}












