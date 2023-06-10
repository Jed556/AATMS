#include "../handler.h"

Handler::Handler()
    : account(*this), history(*this), loan(*this) {
}

void Handler::setDB(sqlite3* db) {
    this->db = db;
}