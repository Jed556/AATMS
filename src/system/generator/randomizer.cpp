#include "../handler.h"

void Generator::randomizeSeed() {
    srand(static_cast<unsigned>(time(0)));
}