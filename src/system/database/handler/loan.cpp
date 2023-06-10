#include "../handler.h"

Handler::Loan::Loan(const Handler& handler)
    : handler(const_cast<Handler&>(handler)) {
}