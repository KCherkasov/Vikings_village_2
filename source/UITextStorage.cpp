#include "UITextStorage.h"

ssize_t UITextStorage::read_character_field_names(sqlite3*& connection) {
  _character_field_names.clear();
  sqlite3_stmt* statement;
  ssize_t response = sqlite3_prepare(connection, "select id, field_name from 'character_fieldnames'", -1, &statement, 0);
  for (size_t i = 0; i < CF_SIZE; ++i) {
    response = sqlite3_step(statement);
    _character_field_names.push_back();
    _character_field_names[_character_field_names.size() - 1].append(sqlite3_column_text(statement, 1));
  }
  response = sqlite3_finalize(statement);
  return response;
}

ssize_t UITextStorage::read_stat_names(sqlite3*& connection) {
  _stat_names.clear();
  sqlite3_stmt* statement;
  ssize_t response = sqlite3_prepare(connection, "select id, stat_name from 'stat_names'", -1, &statement, 0);
  for (size_t i = 0; i < CF_SIZE; ++i) {
    response = sqlite3_step(statement);
    _stat_names.push_back();
    _stat_names[_stat_names.size() - 1].append(sqlite3_column_text(statement, 1));
  }
  response = sqlite3_finalize(statement);
  return response;  
}

size_t UITextStorage::fill_storage(const std::string& db_name) {
  sqlite3* database = NULL;
  open_connection(db_name, database);
  read_character_field_names(database);
  read_stat_names(database);
  close_connection(database);
  return RC_OK;
}

size_t UITextStorage::clear_storage() {
  _character_field_names.clear();
  _stat_names.clear();
  return RC_OK;
}