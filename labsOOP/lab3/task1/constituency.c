#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constituency.h"


void constructConstituency(struct Constituency * const obj,
                            char const *name, 
                            unsigned int* const neighbours, 
                            unsigned int const numNeighbours) {
    obj->name   = NULL;
    obj->neighbours = NULL;
    obj->numNeighbours = 0;

    int nameLength = strlen(name);

    obj->name = (char*) malloc(nameLength * sizeof(char));
    obj->neighbours = (int*) malloc(numNeighbours * sizeof(int));

    obj->numNeighbours = numNeighbours;

    memcpy(obj->name, name, nameLength * sizeof(char));

    memcpy(obj->neighbours, neighbours, numNeighbours * sizeof(int));
}


void printConstituency(struct Constituency * const obj) {

    printf("%s | %d neighbours | ", obj->name, obj->numNeighbours);

    printf("[ ");
    int i;
    for (i = 0; i < obj->numNeighbours; i++) {
        printf("%d ", obj->neighbours[i]);
    }
    printf("]");
}

void destructConstituency(struct Constituency * const obj) {

    if(obj->name != NULL) {
        free(obj->name);
        obj->name = NULL;
    }

    if(obj->neighbours != NULL) {
        free(obj->neighbours);
        obj->neighbours = NULL;
    }  

    obj->numNeighbours = 0;
}