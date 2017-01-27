#include "BaseStorage.h"

ssize_t BaseStorage::open_connection(const std::string& db_name, sqlite3*& connection) {
  return sqlite3_open(db_name.data(), &connection);
}

ssize_t BaseStorage::close_connection(sqlite3*& connection) {
  return sqlite3_close(connection);
}
