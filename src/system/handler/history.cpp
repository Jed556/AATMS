#include "../handler.h"

Handler::HandHistory::HandHistory(const Handler& thisHandler)
    : handler(const_cast<Handler&>(thisHandler)) {
}