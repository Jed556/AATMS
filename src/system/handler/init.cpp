#include "../handler.h"

Handler::Handler(Database& database)
    : database(database), account(*this), history(*this), loan(*this) {
}
