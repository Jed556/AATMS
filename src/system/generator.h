#ifndef GENERATOR_H
#define GENERATOR_H

#include <sys/time.h>
#include "database.h"

#include <ctime>
#include <string>
#include <vector>

class Generator {
   private:
    int seed;

   public:
    void randomizeSeed();
    std::string id();
    int expiryYear();
    std::string cvc();
    DateTime getDate();
} generate;

#endif  // GENERATOR_H