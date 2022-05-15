#ifndef CONSTITUENCY_H

struct Constituency {
    char *name;
    unsigned int *neighbours;
    unsigned int numNeighbours;
};

// void constructConstituency(struct Constituency *the_struct, char *name_input, int *arr[], int num_neighbours);
// void destructConstituency(struct Constituency *the_struct);
// void printConstituency(struct Constituency *the_struct);

void constructConstituency(struct Constituency * const obj,
                            char const *name, 
                            unsigned int* const neighbours, 
                            unsigned int const numNeighbours);
void printConstituency(struct Constituency * const obj);
void destructConstituency(struct Constituency * const obj);


#endif