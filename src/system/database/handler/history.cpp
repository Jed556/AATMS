#include "../handler.h"

Handler::History::History(const Handler& handler)
    : handler(const_cast<Handler&>(handler)) {
}