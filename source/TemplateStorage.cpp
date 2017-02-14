#include "TemplateStorage.h"

ssize_t TemplateStorage::read_male_names(sqlite3*& connection) {
  _male_nameparts_begin.clear();
  _male_nameparts_end.clear();
  sqlite3_stmt* statement;
  ssize_t response = sqlite3_prepare(connection, "select count(id) from 'male_nameparts'", -1, &statement, 0);
  sqlite3_step(statement);
  size_t count = sqlite3_column_int(statement, 0);
  sqlite3_finalize(statement);
  response = sqlite3_prepare(connection, "select id, first, second from 'male_nameparts'", -1, &statement, 0);
  for (size_t i = 0; i < count; ++i) {
    sqlite3_step(statement);
    _male_nameparts_begin.push_back(std::string());
    _male_nameparts_begin[_male_nameparts_begin.size() - 1].append((const char*)(sqlite3_column_text(statement, 1)));
    _male_nameparts_end.push_back(std::string());
    _male_nameparts_end[_male_nameparts_end.size() - 1].append((const char*)(sqlite3_column_text(statement, 2)));
  }
  sqlite3_finalize(statement);
  return response;
}

ssize_t TemplateStorage::read_surname_suffixes(sqlite3*& connection) {
  _surname_suffixes.clear();
  sqlite3_stmt* statement;
  ssize_t response = sqlite3_prepare(connection, "select count(id) from 'surname_suffixes'", -1, &statement, 0);
  sqlite3_step(statement);
  size_t count = sqlite3_column_int(statement, 0);
  sqlite3_finalize(statement);
  response = sqlite3_prepare(connection, "select id, name from 'surname_suffixes'", -1, &statement, 0);
  for (size_t i = 0; i < count; ++i) {
    sqlite3_step(statement);
    _surname_suffixes.push_back(std::string());
    _surname_suffixes[_surname_suffixes.size() - 1].append((const char*)(sqlite3_column_text(statement, 1)));
  }
  sqlite3_finalize(statement);
  return response;
}

ssize_t TemplateStorage::read_item_part_generals(sqlite3*& connection) {
  
}

ssize_t TemplateStorage::read_item_part_costs(sqlite3*& connection) {
  
}

ssize_t TemplateStorage::read_item_part_bonuses(sqlite3*& connection) {
  
}

ssize_t TemplateStorage::read_item_parts(sqlite3*& connection) {
  size_t generals_counter = SIZE_T_DEFAULT_VALUE;
  size_t costs_counter = SIZE_T_DEFAULT_VALUE;
  size_t bonuses_counter = SIZE_T_DEFAULT_VALUE;
  read_item_part_generals(connection);
  read_item_part_costs(connection);
  read_item_part_bonuses(connection);
  return RC_OK;
}

std::string TemplateStorage::male_name() const {
  std::string name;
  name += _male_nameparts_begin[roll_dice(_male_nameparts_begin.size())];
  name += _male_nameparts_end[roll_dice(_male_nameparts_end.size())];
  return name;
}

std::string TemplateStorage::female_name() const {
  std::string name("fem_name_here");
  
  return name;
}

std::string TemplateStorage::surname(const bool& gender) const {
  std::string surname;
  surname += _male_nameparts_begin[roll_dice(_male_nameparts_begin.size())];
  surname += _male_nameparts_end[roll_dice(_male_nameparts_end.size())];
  if (gender == MALE_GENDER) {
    surname += _surname_suffixes[0];
  } else {
    surname += _surname_suffixes[1];
  }
  return surname;
}

bool TemplateStorage::is_filled() const {
  return !_male_nameparts_begin.empty() && !_male_nameparts_end.empty() && !_surname_suffixes.empty();
}

size_t TemplateStorage::fill_storage(const std::string& db_name) {
  sqlite3* database = NULL;
  open_connection(db_name, database);
  read_male_names(database);
  read_surname_suffixes(database);
  close_connection(database);
  return RC_OK;
}

size_t TemplateStorage::clear_storage() {
  _male_nameparts_begin.clear();
  _male_nameparts_end.clear();
  _surname_suffixes.clear();
  return RC_OK;
}

GameCharacterTemplate TemplateStorage::make_character_template(const ssize_t& level) const {
  GameCharacterTemplate result;
  if (roll_dice() < PERCENT_CAP / 2) {
    result._gender = MALE_GENDER;
  } else {
    result._gender = FEMALE_GENDER;
  }
  result._own_id = FREE_ID;
  result._name.clear();
  if (result._gender == MALE_GENDER) {
    result._name += male_name();
  } else {
    result._name += female_name();
  }
  result._name.append(" ");
  result._name += surname(result._gender);
  result._description.clear();
  result._level = level;
  result._stat_points = (result._level - 1) * STAT_POINTS_PER_LEVEL;
  result._wounds = SIZE_T_DEFAULT_VALUE;
  result._experience.clear();
  result._experience.resize(PI_SIZE);
  result._experience[PI_CURRENT] = SIZE_T_DEFAULT_VALUE;
  result._experience[PI_MAX] = FIRST_LEVEL_UP_CAP;
  for (size_t i = 1; i < result._level; ++i) {
    result._experience[PI_CURRENT] = result._experience[PI_MAX] + 1;
    result._experience[PI_MAX] *= EXP_CAP_INCREASEMENT;
    result._experience[PI_MAX] /= PERCENT_CAP;
  }
  result._stats.clear();
  result._stats.resize(CS_SIZE);
  for (size_t i = 0; i < result._stats.size(); ++i) {
    if (result._gender == MALE_GENDER) {
      result._stats[i] = INITIAL_MALE_STATS_VALUE + roll_dice(BASIC_SEED) - floor((double)(BASIC_SEED / 2));
    } else {
      result._stats[i] = INITIAL_FEMALE_STATS_VALUE + roll_dice(BASIC_SEED) - floor((double)(BASIC_SEED / 2));
    }
  }
  while (result._stat_points > 0) {
    ++result._stats[roll_dice(result._stats.size())];
    --result._stat_points;
  }
  return result;
}

GameCharacterTemplate TemplateStorage::make_character_template(const bool& gender, const ssize_t& level) const {
  GameCharacterTemplate result;
  result._own_id = FREE_ID;
  result._name.clear();
  if (gender == MALE_GENDER) {
    result._name += male_name();
  } else {
    result._name += female_name();
  }
  result._name.append(" ");
  result._name += surname(gender);
  result._description.clear();
  result._level = level;
  result._stat_points = (result._level - 1) * STAT_POINTS_PER_LEVEL;
  result._wounds = SIZE_T_DEFAULT_VALUE;
  result._gender = gender;
  result._experience.clear();
  result._experience.resize(PI_SIZE);
  result._experience[PI_CURRENT] = SIZE_T_DEFAULT_VALUE;
  result._experience[PI_MAX] = FIRST_LEVEL_UP_CAP;
  for (size_t i = 1; i < result._level; ++i) {
    result._experience[PI_CURRENT] = result._experience[PI_MAX] + 1;
    result._experience[PI_MAX] *= EXP_CAP_INCREASEMENT;
    result._experience[PI_MAX] /= PERCENT_CAP;
  }
  result._stats.clear();
  result._stats.resize(CS_SIZE);
  for (size_t i = 0; i < result._stats.size(); ++i) {
    if (result._gender == MALE_GENDER) {
      result._stats[i] = INITIAL_MALE_STATS_VALUE + roll_dice(BASIC_SEED) - floor((double)(BASIC_SEED / 2));
    } else {
      result._stats[i] = INITIAL_FEMALE_STATS_VALUE + roll_dice(BASIC_SEED) - floor((double)(BASIC_SEED / 2));
    }
  }
  while (result._stat_points > 0) {
    size_t stat_id = roll_dice(result._stats.size());
    if (result._stats[stat_id] < STAT_MAX_VALUE) {
      ++result._stats[stat_id];
      --result._stat_points;
    }
  }
  return result;
}
