#ifndef GENERATOR_H
#define GENERATOR_H

#include <ctime>
#include <string>

class Generator {
   private:
    int seed;

   public:
    void randomizeSeed();
    std::string accountID();
    std::string expirationMonth();
    std::string expirationYear();
    std::string cvc();
} generate;

#endif  // GENERATOR_H