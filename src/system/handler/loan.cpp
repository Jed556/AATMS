#include "../handler.h"

Handler::HandLoan::HandLoan(const Handler& thisHandler)
    : thisHandler(const_cast<Handler&>(thisHandler)) {
}