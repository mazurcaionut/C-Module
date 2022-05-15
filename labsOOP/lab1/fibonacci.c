#include "fibonacci.h"


int fibonacci(int n) {
    switch (n)
    {
    case 0:
        return 0;
        break;
    case 1:
        return 1;
        break;
    default:
        return fibonacci(n-1) + fibonacci(n-2);
        break;
    }
}
