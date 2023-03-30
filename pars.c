// Opcode table
enum Opcode {
   /*first group of instructions getting 2 operans*/
    mov = 0b0000,/*0*/
    cmp = 0b0001,/*1*/
    add = 0b0010,/*2*/
    sub = 0b0011,/*3*/
    lea = 0b0110,/*6*/
    /*second group of instructions that needs only one operand, have only dec operand 4 - 5 always zero*/
    not = 0b0100,/*4*/
    clr = 0b0101,/*5*/
    inc = 0b0111,/*7*/
    dec = 0b1000,/*8*/
    jmp = 0b1001,/*9*/
    bne = 0b1010,/*10*/
    red = 0b1011,/*11*/
    prn = 0b1100,/*12*/
    jsr = 0b1101,/*13*/
    /*third group of instructions*/
    rts = 0b1110,/*14*/
    stop = 0b1111/*15*/
};



if (strcmp(opcode, ".entry") == 0) {
    // TODO: Handle entry directive
}
else if (strcmp(opcode, ".extern") == 0) {
    // TODO: Handle extern directive
    if (has_symbol) {
        // Insert symbol into symbol table with undefined value and type
        strcpy(symtab[symtab_size].name, symbol);
        symtab[symtab_size].type = -2; // Set symbol type to external
        symtab[symtab_size].value = 0;
        symtab_size++;
    }

    // Insert operand symbols into symbol table with undefined value and type
    char* token = strtok(operand1, ",");
    while (token != NULL) {
        if (strlen(token) > 0) {
            strcpy(symtab[symtab_size].name, token);
            symtab[symtab_size].type = -2; // Set symbol type to external
            symtab[symtab_size].value = 0;
            symtab_size++;
        }
        token = strtok(NULL, ",");
    }
}
else {
    // Instruction found, check number of operands
    int num_operands = 0;
    int operand_modes[2] = { 0 };
    if (operand1[0] != '\0') {
        num_operands++;
        for (int j = 0; j < num_operands; j++) {
            for (int k = 0; k < num_operands; k++) {
                if (operand1[0] == '#' || operand1[0] == '-') {
                    operand_modes[k] = 0;
                }
                else if (operand1[0] == 'r' && strlen(operand1) == 2) {
                    operand_modes[k] = 3;
                }
                else if (operand1[0] == '&' && has_symbol) {
                    operand_modes[k] = 1;
                }
                else if (has_symbol) {
                    operand_modes[k] = 2;
                }
            }
        }
    }
    if (operand2[0] != '\0') {
        num_operands++;
        for (int j = 0; j < num_operands; j++) {
            for (int k = 0; k < num_operands; k++) {
                if (operand2[0] == '#' || operand2[0] == '-') {
                    operand_modes[k] = 0;
                }
                else if (operand2[0] == 'r' && strlen(operand2) == 2) {
                    operand_modes[k] = 3;
                }
                else if (operand2[0] == '&' && has_symbol) {
                    operand_modes[k] = 1;
                }
                else if (has_symbol) {
                    operand_modes[k] = 2;
                }
            }
        }
    }
    for (int i = 0; i < num_opcodes; i++) {
        if (strcmp(opcode, opcodes[i].name) == 0) {
            // Encode instruction and update instruction counter (IC)
            int opcode_value = opcodes[i].opcode;
            int bytes = 1; // Opcode always takes up one byte
            bytes += num_operands; // Add one byte for each operand
            int operand_encoding = 0;
            for (int j = 0; j < num_operands; j++) {
                operand_encoding <<= 2;
                operand_encoding |= operand_modes[j];
            }
            int instruction = (opcode_value << 12) | operand_encoding;

            IC += bytes;
        }
    }




    //enum OpCodeEnum {
//    mov = 0b0000,
//    cmp = 0b0001,
//    add = 0b0010,
//    sub = 0b0011,
//    not = 0b0100,
//    clr = 0b0101,
//    lea = 0b0110,
//    inc = 0b0111,
//    dec = 0b1000,
//    jmp = 0b1001,
//    bne = 0b1010,
//    red = 0b1011,
//    prn = 0b1100,
//    jsr = 0b1101,
//    rts = 0b1110,
//    stop = 0b1111
//};


    void process_data_directive(const char* operand1) {
        // Parse and count the number of elements in the data directive
        char* token = strtok(operand1, ",");
        int num_elements = 0;
        while (token != NULL) {
            num_elements++;
            token = strtok(NULL, ",");
        }

        // TODO: encode data directive in memory and update data counter (DC)

        DC += num_elements;
    }

    void process_string_directive(const char* operand1) {
        // Count the number of characters in the string
        int num_chars = strlen(operand1) - 2; // Subtract two for the enclosing quotes
        for (int i = 0; i < num_chars; i++) {
            if (operand1[i] == '\\') {
                // Escape character, skip next character
                i++;
            }
        }

        // TODO: encode string directive in memory and update data counter (DC)

        DC += num_chars;
    }

    void process_entry_directive(FILE** entry_file, const char* fileName1, const char* operand1) {
        // Create a new file for the .entry directive
        if (*entry_file) {
            fclose(*entry_file);
        }
        char entry_filename[256];
        sprintf(entry_filename, "%s.ent", fileName1);
        *entry_file = fopen(entry_filename, "a");
        if (!*entry_file) {
            printf("Error creating entry file\n");
            return;
        }

        // TODO: handle entry directive
    }

    void process_extern_directive(FILE** extern_file, const char* fileName2, const char* operand1) {
        // Create a new file for the .extern directive
        if (*extern_file) {
            fclose(*extern_file);
        }
        char extern_filename[256];
        sprintf(extern_filename, "%s.ext", fileName2);
        *extern_file = fopen(extern_filename, "a");
        if (!*extern_file) {
            printf("Error creating extern file\n");
            return;
        }

        // TODO: handle extern directive
    }

    void process_instruction(const char* opcode, const char* operand1, const char* operand2, const char* symbol) {
        // TODO: encode instruction in memory and update instruction counter (IC)
        //       if a symbol is provided, store it in the symbol table

        IC += 1; // Assuming one instruction takes one memory cell
    }

    void finalize() {
        // TODO: Finalize the encoding of data and instructions in memory
        //       This might include updating the symbol table, resolving external symbols, etc.
    }



    // Update symbol table entry for instruction
    if (has_symbol) {
        for (int j = 0; j < symtab_size; j++) {
            if (strcmp(symbol, symtab[j].name) == 0) {
                if (symtab[j].type != -1) {
                    printf("Error: symbol %s already defined\n", symbol);
                    break;
                }
                symtab[j].type = IC - bytes; // Value is address of instruction
                break;s
            }
        }
    }