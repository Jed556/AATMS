#include "../handler.h"

Handler::HandHistory::HandHistory(const Handler& thisHandler)
    : thisHandler(const_cast<Handler&>(thisHandler)) {
}