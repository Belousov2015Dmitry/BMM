#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Matrix/Matrix.h"
#include "Experiment/Experiment.h"
#include "Helpers/Stack.h"


//type of matrix elements
#ifdef type
#undef type
#endif
#define type double

//type of stack elements
#ifdef stype
#undef stype
#endif
#define stype unsigned

//custom random generator
#ifdef randValue
#undef randValue
#endif
#define randValue() rand() % 1024 * 1.0 / pow(10, rand() % 5)

int main() {
    srand(time(0));

    start(1024);
    //TODO: analytics

    getchar();
    return 0;
}