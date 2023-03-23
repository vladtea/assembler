#ifndef MACROMAN_H
#define MACROMAN_H

/* A joke: Its importent to read the name of the file like in the song "the village people - Macho Man*/

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

Macro* find_macros(const char* filename, int* num_macros);/*takes a filename and a pointer to an integer and returns an array of Macro structs, with the number of 
                                                            macros found stored in the integer pointed to by num_macros. This function reads the file and looks for macro 
                                                                definitions, and creates an array of Macro structs for each macro found.*/

void replace_macros(const char* filename, Macro* macros, int num_macros);/*takes a filename, an array of Macro structs, and the number of macros in the array, and writes a new file
                                                                         with macro definitions replaced by their contents. This function reads the original file and writes a new file 
                                                                         with macro contents in place of macro definitions.*/

void delete_macros(const char* filename, const char* new_filename);/*takes a filename and a new filename, and writes a new file with all macro definitions removed. This function reads
                                                                   the original file and writes a new file without macro definitions.*/

#endif /* MACROMAN_H */
