#include <stdio.h>
#include <stdlib.h>
#include "fibonacci.h"

// const int FIBONACCI_NUM = 10;

int main(int argc, char* argv[]) {

    // argc > 0 ?  printf("its valid") : return 0;
    
    int num = atoi(argv[1]);
    int result = fibonacci(num);
    printf("Fibonacci of %d = %d\n", num, result);
    return 0;
}