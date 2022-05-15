// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// 
// (c) Martin Porcheron
//     m.a.w.porcheron@swansea.ac.uk
// -----------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "timestables.h"

int main(int argc , char *argv[]) {
    int *ptr[MAX_TABLE_SIZE];
    //  = {NULL};

    for(int i = 0; i < MAX_TABLE_SIZE; i++) {
        ptr[i] = (int*) malloc(MAX_TABLE_SIZE * sizeof(int));
        generateTable(i, ptr[i]);
    }


    // for(int i = 0; i < MAX_TABLE_SIZE; i++) {
    // }

    printTables(ptr);

    for(int i = 0; i < MAX_TABLE_SIZE; i++) {
        free(ptr[i]);
        ptr[i] = NULL;
    }


	return 0;
}
