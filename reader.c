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


void fileManipulate(const char* fileName) {
    FILE* file = fopen(fileName, "r");
    char line[100];
    char opcode[4];
    char operand1[100];
    char operand2[100];
    int success = 0;
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    while (fgets(line, sizeof(line), file)) {
        success = sscanf(line, "%s %[^,]%[, ]%s", opcode, operand1, operand2);
        if (success >= 2) {
            // Parse opcode enum
            enum OpCode opcodeEnum;
            if (strcmp(opcode, "ADD") == 0) {
                opcodeEnum = ADD;
            }
            else if (strcmp(opcode, "SUB") == 0) {
                opcodeEnum = SUB;
            }
            else if (strcmp(opcode, "MUL") == 0) {
                opcodeEnum = MUL;
            }
            else if (strcmp(opcode, "DIV") == 0) {
                opcodeEnum = DIV;
            }
            else {
                printf("Unknown opcode: %s\n", opcode);
                continue;
            }

            // Check if operand1 is an immediate or a register
            char* comma_ptr = strchr(operand1, ',');
            if (comma_ptr == NULL) {
                // Operand1 is an immediate
                printf("Opcode: %d, Immediate: %s\n", opcodeEnum, operand1);
            }
            else {
                // Operand1 is a register, operand2 may be an immediate or a register
                *comma_ptr = '\0'; // Replace comma with null character to separate operands
                char* rest_ptr = comma_ptr + 1; // Pointer to the rest of the string after the comma
                if (rest_ptr[0] == '\0') {
                    // Operand2 is missing
                    printf("Invalid instruction: %s", line);
                    continue;
                }
                if (rest_ptr[0] >= '0' && rest_ptr[0] <= '9') {
                    // Operand2 is an immediate
                    printf("Opcode: %d, Register 1: %s, Immediate: %s\n", opcodeEnum, operand1, rest_ptr);
                }
                else {
                    // Operand2 is a register
                    printf("Opcode: %d, Register 1: %s, Register 2: %s\n", opcodeEnum, operand1, rest_ptr);
                }
            }
        }
        else {
            printf("Invalid instruction: %s", line);
        }
    }

    fclose(file);

}





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






