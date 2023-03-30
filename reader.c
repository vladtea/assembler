#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct counter {
    int ic;
    int dc;
};

typedef enum {
    r0,
    r1,
    r2,
    r3,
    r4,
    r5,
    r6,
    r7
} Register;

Register register_from_string(const char* reg_string) {
    if (strcmp(reg_string, "r0") == 0) return r0;
    if (strcmp(reg_string, "r1") == 0) return r1;
    if (strcmp(reg_string, "r2") == 0) return r2;
    if (strcmp(reg_string, "r3") == 0) return r3;
    if (strcmp(reg_string, "r4") == 0) return r4;
    if (strcmp(reg_string, "r5") == 0) return r5;
    if (strcmp(reg_string, "r6") == 0) return r6;
    if (strcmp(reg_string, "r7") == 0) return r7;
    // Invalid register name
    return -1;
}



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

enum opcode_type {
    INVALID_OPCODE = -1,
    mov = 0,
    cmp = 1,
    add = 2,
    sub = 3,
    not = 4,
    clr = 5,
    lea = 6,
    inc = 7,
    dec = 8,
    jmp = 9,
    bne = 10,
    red = 11,
    prn = 12,
    jst = 13,
    rts = 14,
    stop = 15,

};
/* the struct is  OpCode,the number, number of operands*/
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

/*type , num of DC*/
struct operand operands[] = {
    {"#imm", 2},
    {"reg", 2},
    {"[reg]", 4},
    {"[#imm+reg]", 3},
    {"[reg+reg]", 2},
};





enum opcode_type get_opcode(const char* opcode_name) {
    for (int i = 0; i < num_opcodes; i++) {
        if (strcmp(opcode_name, opcodes[i].name) == 0) {
            return (enum opcode_type)opcodes[i].opcode;
        }
    }
    return INVALID_OPCODE;
}





struct counter cnt = { 100,0 };
int numline = 0;
char line[256];
struct symbol symtab[256];
int symtab_size = 0;
int has_symbol = 0;
void reader(const char* fileName, const char* fileName1, const char* fileName2) {
    FILE* entry_file = NULL;
    FILE* extern_file = NULL;
    FILE* src_file = fopen(fileName, "r");
    if (!src_file) {
        printf("Error opening source file\n");

    }

    while (fgets(line, 256, src_file)) {
        char* newline; /*used for triming to append the lines to .ent and .ext*/
        char symbol[256];
        char opcode[256];
        char operand1[256];
        char operand2[256];
        int bytes = 0;
        has_symbol = 0;
        numline++;
        if (sscanf(line, "%255[^:]:%s %s %s", symbol, opcode, operand1, operand2) >= 2) {
            // Line has a symbol
            cnt.dc = 4;
            cnt.ic = cnt.ic + cnt.dc;
            
        }
        else if (sscanf(line, "%s %s %s", opcode, operand1, operand2) >= 1) {
            // Line has no symbol
            Register reg1 = register_from_string(operand1);
            /* if reg1 is not a reg it is an immidiate*/
            if (reg1 == -1) {
                cnt.dc = 3;
                cnt.ic = cnt.ic + cnt.dc;
            }
            /* operan1 and operand2 are registers*/
            else {
                cnt.dc = 2;
                cnt.ic = cnt.ic + cnt.dc;
            }
           
        }
        else if (sscanf(line, opcode, operand1) >= 1) {
            

        }
        else if (sscanf(line, "%s", opcode) < 1) {
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
        if (strstr(line, ".data") != NULL) {
            /* .data command without label */
            int count = 0;
            int cruiser = 0;
            while (line[cruiser] != '\n') {
                if (line[cruiser] == ',') {
                    cruiser++;
                }
                cruiser++;
            }
            count++;
            
            int x = count;
            char* token = strtok(line, "\"");
            token = strtok(NULL, " ");
            if (x > 1) {
                token = strtok(token, ",");
            }
            while (token != NULL) {
                (cnt.dc)++;
                count--;
                if (x == 1) {
                    token = strtok(NULL, " ");
                }
                else {
                    token = strtok(NULL, ",");
                }
            }
            if (count != 0) {
                printf("Insufficient commas in .data command. Line number %d.\n", numline);
                cnt.dc = (cnt.dc) - x;
            }
            continue;
        }

		if (strstr(line, ".string") != NULL) {
			/* .string command without label */
			int count = 0;
			int cruiser = 0;
			while (line[cruiser] != '\n') {
				if (line[cruiser] == '"') {
					count++;
				}
				cruiser++;
			}
			if (count >= 2) {
				char* token = strtok(line, "\"");
					token = strtok(NULL, "\"");
						if (strlen(token) == 0) {
							printf(".string command needs to have two arguments. Line number %d.\n", numline);
						}
						else {
							int lengthOfString = strlen(token);
							cnt.dc = (cnt.dc) + lengthOfString + 1; // +1 for the null terminator at the end of the string
						}
			}
			else {
				printf(".string command needs to have at least two quotation marks. Line number %d.\n", numline);
			}
			continue;
		}




            // Check if line contains an entry or extern instruction
            if (strstr(opcode, ".entry")) {
                // Create new file for .entry directive
                if (entry_file) {
                    fclose(entry_file);
                }
                char entry_filename[256];
                sprintf(entry_filename, "%s.ent", fileName1);
                entry_file = fopen(entry_filename, "a");

                if (!entry_file) {
                    entry_file = fopen(entry_filename, "w"); // Create the file if it doesn't exist
                    if (!entry_file) {
                        printf("Error creating entry file\n");
                        return;
                    }
                }

                // Write the rest of the line to the entry file
                memmove(line, line + 6, strlen(line));
                newline = strtok(line, "\n");
                newline = strtok(line, " ");
                fprintf(entry_file, "%s %d\n", newline, cnt.ic);
                
                cnt.dc = 1;
                cnt.ic += cnt.dc;
                continue;

            }
            else if (strstr(opcode, ".extern")) {
                // Create new file for .extern directive
                if (extern_file) {
                    fclose(extern_file);
                }
                char extern_filename[256];
                sprintf(extern_filename, "%s.ext", fileName2);


                extern_file = fopen(extern_filename, "a");
                if (!extern_file) {
                    extern_file = fopen(extern_filename, "w"); // Create the file if it doesn't exist
                    if (!extern_file) {
                        printf("Error creating extern file\n");
                        return;
                    }
                }

                // Write the rest of the line to the extern file
                memmove(line, line + 7, strlen(line));
                newline = strtok(line, "\n");
                newline = strtok(line, " ");
                fprintf(extern_file, "%s %d\n", newline, cnt.ic);
                cnt.dc = 1;
                cnt.ic += cnt.dc;
                continue;
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


                    cnt.ic=(cnt.ic) + bytes;





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




    printf("ic=%d\n", cnt.ic);
    printf("dc=%d\n", cnt.dc);

}












