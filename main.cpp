#include <iostream>
#include "linear.h"
#include "utils.h"

using namespace std;

int main() {
    measure(&testSolve);
    measure(&testParallelSolve);
    return 0;
}