#include "../handler.h"

Handler::HandLoan::HandLoan(const Handler& thisHandler)
    : handler(const_cast<Handler&>(thisHandler)) {
}