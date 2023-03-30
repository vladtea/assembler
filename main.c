#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "macroman.h"
#include "labeling.h"
#include "reader.h"
#include "secondpassage.h"



#define MAX_MACRO_SIZE 10000
#define MAX_LABELS 100

int main(int argc, char* argv[]) {
    /*------------------------------          MACRO opening         -------------------------------------*/
    /*input file name*/
    char fileName[100] = "C:/Users/MPC/source/repos/hello/hello/"; /*add desired path for the file*/
    char amFileName[100] = "C:/Users/MPC/source/repos/hello/hello/";
    strcat(fileName, argv[1]);
    strcat(fileName, ".as");
    strcat(amFileName, argv[1]);
    strcat(amFileName, ".am");
    int num_macros = 0;
    
    /* run through the file and finds all the macros in it */
    Macro* macros = find_macros(fileName, &num_macros);
    if (!macros) {
        printf("Error finding macros.\n");
        return 1;
    }
    
    /*Deploys all the macro in the .am file*/
    replace_macros(fileName, macros, num_macros);
    
    delete_macros("asmbnew.txt" , amFileName);  
    
    remove("asmbnew.txt");
    free(macros);
    
    
    /*------------------------------          labeling code         -------------------------------------*/
    
    
    char** labels = malloc(MAX_LABELS * sizeof(char*)); // allocate memory for array of pointers to labels
    
    // check if memory allocation was successful
    if (labels == NULL) {
        perror("Error allocating memory");
        exit(1);
    }

    // set all pointers in the array to NULL
    for (int i = 0; i < MAX_LABELS; i++) {
        labels[i] = NULL;
    }

    // call extract_labels function to populate the labels array
    extract_labels(amFileName , labels, MAX_LABELS);

    // print out all the labels found
    for (int i = 0; i < MAX_LABELS; i++) {
        if (labels[i] != NULL) {
            printf("%s\n", labels[i]);
            free(labels[i]); // free memory for each label after using it
        }
        else {
            break;
        }
    }
    // free memory for the array of pointers to labels
    
    /*free(labels);*/
    /*------------------------------          OpCode and the first passage         -------------------------------------*/
    
    reader(amFileName, argv[1], argv[1]);
    

    /*------------------------------         final passage         -------------------------------------*/

    finalPassage(argv[1], labels);
    
    
    
    
    
    
    
    
    
    return 0;


}
