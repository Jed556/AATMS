#include "../handler.h"

Handler::Handler(Database& database, int UTC)
    : database(database), account(*this), transact(*this), history(*this), loan(*this), UTC(UTC), generate(database, UTC) {
}
