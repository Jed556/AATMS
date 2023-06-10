#include "../generator.h"

void Generator::randomizeSeed() {
    this->seed = seed;
    srand(static_cast<unsigned>(time(0)));
}