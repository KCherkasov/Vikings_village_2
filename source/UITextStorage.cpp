#include "UITextStorage.h"

ssize_t UITextStorage::read_character_field_names(sqlite3*& connection) {
  _character_field_names.clear();
  sqlite3_stmt* statement;
  ssize_t response = sqlite3_prepare(connection, "select id, field_name from 'character_fieldnames'", -1, &statement, 0);
  for (size_t i = 0; i < CF_SIZE; ++i) {
    response = sqlite3_step(statement);
    _character_field_names.push_back(std::string());
    _character_field_names[_character_field_names.size() - 1].append((const char*)(sqlite3_column_text(statement, 1)));
  }
  response = sqlite3_finalize(statement);
  return response;
}

ssize_t UITextStorage::read_stat_names(sqlite3*& connection) {
  _stat_names.clear();
  sqlite3_stmt* statement;
  ssize_t response = sqlite3_prepare(connection, "select id, stat_name from 'stat_names'", -1, &statement, 0);
  for (size_t i = 0; i < CS_SIZE; ++i) {
    response = sqlite3_step(statement);
    _stat_names.push_back(std::string());
    _stat_names[_stat_names.size() - 1].append((const char*)(sqlite3_column_text(statement, 1)));
  }
  response = sqlite3_finalize(statement);
  return response;  
}

ssize_t UITextStorage::read_gender_names(sqlite3*& connection) {
  _gender_names.clear();
  sqlite3_stmt* statement;
  ssize_t response = sqlite3_prepare(connection, "select id, name from 'gender_names'", -1, &statement, 0);
  for (size_t i = 0; i < PI_SIZE; ++i) {
    response = sqlite3_step(statement);
    _gender_names.push_back(std::string());
    _gender_names[_gender_names.size() - 1].append((const char*)(sqlite3_column_text(statement, 1)));
  }
  response = sqlite3_finalize(statement);
  return response;
}

ssize_t UITextStorage::read_character_tags(sqlite3*& connection) {
  _character_manager_tags.clear();
  sqlite3_stmt* statement;
  ssize_t response = sqlite3_prepare(connection, "select id, tag from 'character_tags'", -1, &statement, 0);
  for (size_t i = 0; i < CT_SIZE; ++i) {
    response = sqlite3_step(statement);
    _character_manager_tags.push_back(std::string());
    _character_manager_tags[_character_manager_tags.size() - 1].append((const char*)(sqlite3_column_text(statement, 1)));
  }
  response = sqlite3_finalize(statement);
  return response;
}

ssize_t UITextStorage::read_battle_tags(sqlite3*& connection) {
  _battle_manager_tags.clear();
  sqlite3_stmt* statement;
  ssize_t response = sqlite3_prepare(connection, "select id, tag from 'battle_tags'", -1, &statement, 0);
  for (size_t i = 0; i < BT_SIZE; ++i) {
    response = sqlite3_step(statement);
    _battle_manager_tags.push_back(std::string());
    _battle_manager_tags[_battle_manager_tags.size() - 1].append((const char*)(sqlite3_column_text(statement, 1)));
  }
  response = sqlite3_finalize(statement);
  return response;
}

ssize_t UITextStorage::read_ui_tags(sqlite3*& connection) {
  _ui_manager_tags.clear();
  sqlite3_stmt* statement;
  ssize_t response = sqlite3_prepare(connection, "select id, tag from 'ui_tags'", -1, &statement, 0);
  for (size_t i = 0; i < UT_SIZE; ++i) {
    response = sqlite3_step(statement);
    _ui_manager_tags.push_back(std::string());
    _ui_manager_tags[_ui_manager_tags.size() - 1].append((const char*)(sqlite3_column_text(statement, 1)));
  }
  response = sqlite3_finalize(statement);
  return response;
}

ssize_t UITextStorage::read_manager_tags(sqlite3*& connection) {
  read_character_tags(connection);
  read_battle_tags(connection);
  read_ui_tags(connection);
  return RC_OK;
}

bool UITextStorage::is_filled() const {
  return !_stat_names.empty() && !_character_field_names.empty() && !_character_manager_tags.empty() && !_battle_manager_tags.empty() && !_ui_manager_tags.empty() && !_gender_names.empty();
}

size_t UITextStorage::fill_storage(const std::string& db_name) {
  sqlite3* database = NULL;
  open_connection(db_name, database);
  read_character_field_names(database);
  read_stat_names(database);
  read_manager_tags(database);
  read_gender_names(database);
  close_connection(database);
  return RC_OK;
}

size_t UITextStorage::clear_storage() {
  _character_field_names.clear();
  _stat_names.clear();
  _manager_tags.clear();
  _gender_names.clear();
  return RC_OK;
}
