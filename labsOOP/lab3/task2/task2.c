// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// 
// (c) Martin Porcheron
//     m.a.w.porcheron@swansea.ac.uk
// -----------------------------------------------------

#include <stdio.h>

#include "constituency.h"

int main() {
  const int numConstituencies = 5;
  struct Constituency constituencies[numConstituencies];
  constructConstituency(
    &constituencies[0], 
    "Swansea East",
    (unsigned int[]){1, 2, 3, 4}, 
    4);

  constructConstituency(
    &constituencies[1], 
    "Swansea West",
    (unsigned int[]){0, 2}, 
    2);

  constructConstituency(
    &constituencies[2], 
    "Gower",
    (unsigned int[]){0, 1, 3}, 
    3);

  constructConstituency(
    &constituencies[3], 
    "Neath",
    (unsigned int[]){0, 2, 4},
    3);

  constructConstituency(
    &constituencies[4], 
    "Aberavon",
    (unsigned int[]){0 , 3},
     2);

  int i;

  int min = 1000;
  int minIndex = 0;
  int maxIndex = 0;
  int max = 0;

  for (i = 0; i < numConstituencies; i++) {

    int currentNumNeighbours = (&constituencies[i])->numNeighbours;

    if(min > currentNumNeighbours) {
      min = currentNumNeighbours;
      minIndex = i;
    }

    if(max < currentNumNeighbours) {
      max = currentNumNeighbours;
      maxIndex = i;
    }

      printConstituency(&constituencies[i]);
      printf("\n");
  }


  printf("\n%s has the most bordering constituencies \n", (&constituencies[maxIndex])->name);

  for (i = 0; i < (&constituencies[maxIndex])->numNeighbours; i++) {
    printf("   %s \n", (&constituencies[(&constituencies[maxIndex])->neighbours[i]])->name);
  }

  printf("\n%s has the fewest bordering constituencies \n", (&constituencies[minIndex])->name);

  for (i = 0; i < (&constituencies[minIndex])->numNeighbours; i++) {
    printf("   %s \n", (&constituencies[(&constituencies[maxIndex])->neighbours[i]])->name);
  }


  for (i = 0; i < numConstituencies; i++) {
      destructConstituency(&constituencies[i]);
  }

  // struct Constituency test;
  // constructConstituency(
  //   &test,
  //   "Swansea East",
  //   (unsigned int[]){1, 2, 3, 4},
  //   4);
  // printConstituency(&test);
  
  // printf("\n");
  
  // destructConstituency(&test);
  
  return 0;
}