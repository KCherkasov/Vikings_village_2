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

ssize_t UITextStorage::read_battle_log_parts(sqlite3*& connection) {
  _melee_attack_attempts.clear();
  _ranged_attack_attempts.clear();
  _melee_attack_success.clear();
  _ranged_attack_success.clear();
  _melee_attack_failure.clear();
  _ranged_attack_failure.clear();
  _wound_made.clear();
  _wound_avoid.clear();
  sqlite3_stmt* statement;
  ssize_t response =  sqlite3_prepare(connection, "select count(id) from 'battle'", -1, &statement, 0);
  sqlite3_step(statement);
  size_t counter = sqlite3_column_int(statement, 0);
  sqlite3_finalize(statement);
  response = sqlite3_prepare(connection, "select id, melee_attempt, ranged_attempt, melee_success, ranged_success, melee_failure, ranged_failure, wound_made, wound_avoid from 'battle'", -1, &statement, 0);
  for (size_t i = 0; i < counter; ++i) {
    sqlite3_step(statement);
    _melee_attack_attempts.push_back(std::string());
    _melee_attack_attempts[_melee_attack_attempts.size() - 1].append((const char*)(sqlite3_column_text(statement, 1)));
    _ranged_attack_attempts.push_back(std::string());
    _ranged_attack_attempts[_ranged_attack_attempts.size() - 1].append((const char*)(sqlite3_column_text(statement, 2)));
    _melee_attack_success.push_back(std::string());
    _melee_attack_success[_melee_attack_success.size() - 1].append((const char*)(sqlite3_column_text(statement, 3)));
    _ranged_attack_success.push_back(std::string());
    _ranged_attack_success[_ranged_attack_success.size() - 1].append((const char*)(sqlite3_column_text(statement, 4)));
    _melee_attack_failure.push_back(std::string());
    _melee_attack_failure[_melee_attack_failure.size() - 1].append((const char*)(sqlite3_column_text(statement, 5)));
    _ranged_attack_failure.push_back(std::string());
    _ranged_attack_failure[_ranged_attack_failure.size() - 1].append((const char*)(sqlite3_column_text(statement, 6)));
    _wound_made.push_back(std::string());
    _wound_made[_wound_made.size() - 1].append((const char*)(sqlite3_column_text(statement, 7)));
    _wound_avoid.push_back(std::string());
    _wound_avoid[_wound_avoid.size() - 1].append((const char*)(sqlite3_column_text(statement, 8)));
  }
  sqlite3_finalize(statement);
  return response;
}

bool UITextStorage::is_filled() const {
  return !_stat_names.empty() && !_character_field_names.empty() && !_gender_names.empty() && !_melee_attack_attempts.empty() && !_ranged_attack_attempts.empty() && !_melee_attack_success.empty() && !_ranged_attack_success.empty() && !_melee_attack_failure.empty() && !_ranged_attack_failure.empty() && !_wound_made.empty() && !_wound_avoid.empty();
}

size_t UITextStorage::fill_storage(const std::string& db_name) {
  sqlite3* database = NULL;
  open_connection(db_name, database);
  read_character_field_names(database);
  read_stat_names(database);
  read_manager_tags(database);
  read_gender_names(database);
  read_battle_log_parts(database);
  close_connection(database);
  return RC_OK;
}

size_t UITextStorage::clear_storage() {
  _character_field_names.clear();
  _stat_names.clear();
  _gender_names.clear();
  _character_manager_tags.clear();
  _battle_manager_tags.clear();
  _ui_manager_tags.clear();
  _melee_attack_attempts.clear();
  _ranged_attack_attempts.clear();
  _melee_attack_success.clear();
  _ranged_attack_success.clear();
  _melee_attack_failure.clear();
  _ranged_attack_failure.clear();
  _wound_made.clear();
  _wound_avoid.clear();
  return RC_OK;
}
