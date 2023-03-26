#ifndef LABELING_H
#define LABELING_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


enum opcode get_opcode(const char* opcode_name);
void extract_labels(const char* fileName, char* labels[], int max_labels);
#endif 

