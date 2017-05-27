#include "TemplateStorage.h"

ssize_t TemplateStorage::read_male_names(sqlite3*& connection) {
  this->_male_nameparts_begin.clear();
  this->_male_nameparts_end.clear();
  sqlite3_stmt* statement;
  ssize_t response = sqlite3_prepare(connection, "select count(id) from 'male_nameparts'", -1, &statement, 0);
  sqlite3_step(statement);
  size_t count = sqlite3_column_int(statement, 0);
  sqlite3_finalize(statement);
  response = sqlite3_prepare(connection, "select id, first, second from 'male_nameparts'", -1, &statement, 0);
  for (size_t i = 0; i < count; ++i) {
    sqlite3_step(statement);
    this->_male_nameparts_begin.push_back(std::string());
    this->_male_nameparts_begin[this->_male_nameparts_begin.size() - 1].append((const char*)(sqlite3_column_text(statement, 1)));
    this->_male_nameparts_end.push_back(std::string());
    this->_male_nameparts_end[this->_male_nameparts_end.size() - 1].append((const char*)(sqlite3_column_text(statement, 2)));
  }
  sqlite3_finalize(statement);
  return response;
}

ssize_t TemplateStorage::read_female_names(sqlite3*& connection) {
  this->_female_nameparts_begin.clear();
  this->_female_nameparts_end.clear();
  sqlite3_stmt* statement;
  ssize_t response = sqlite3_prepare(connection, "select count(id) from 'female_nameparts'", -1, &statement, 0);
  sqlite3_step(statement);
  size_t count = sqlite3_column_int(statement, 0);
  sqlite3_finalize(statement);
  response = sqlite3_prepare(connection, "select id, first, second from 'female_nameparts'", -1, &statement, 0);
  for (size_t i = 0; i < count; ++i) {
    sqlite3_step(statement);
    this->_female_nameparts_begin.push_back(std::string());
    this->_female_nameparts_begin[this->_female_nameparts_begin.size() - 1].append((const char*)(sqlite3_column_text(statement, 1)));
    this->_female_nameparts_end.push_back(std::string());
    this->_female_nameparts_end[this->_female_nameparts_end.size() - 1].append((const char*)(sqlite3_column_text(statement, 2)));
  }
  sqlite3_finalize(statement);
  return response;
}

ssize_t TemplateStorage::read_surname_suffixes(sqlite3*& connection) {
  this->_surname_suffixes.clear();
  sqlite3_stmt* statement;
  ssize_t response = sqlite3_prepare(connection, "select count(id) from 'surname_suffixes'", -1, &statement, 0);
  sqlite3_step(statement);
  size_t count = sqlite3_column_int(statement, 0);
  sqlite3_finalize(statement);
  response = sqlite3_prepare(connection, "select id, name from 'surname_suffixes'", -1, &statement, 0);
  for (size_t i = 0; i < count; ++i) {
    sqlite3_step(statement);
    this->_surname_suffixes.push_back(std::string());
    this->_surname_suffixes[this->_surname_suffixes.size() - 1].append((const char*)(sqlite3_column_text(statement, 1)));
  }
  sqlite3_finalize(statement);
  return response;
}

ssize_t TemplateStorage::read_item_part_generals(sqlite3*& connection) {
  if (this->_item_part_templates.empty()) {
    return RC_BAD_INPUT;
  }
  sqlite3_stmt* statement;
  ssize_t response = sqlite3_prepare(connection, "select count(id) from 'item_part_generals'", -1, &statement, 0);
  sqlite3_step(statement);
  size_t counter = sqlite3_column_int(statement, 0);
  sqlite3_finalize(statement);
  if (counter != this->_item_part_templates.size()) {
    return RC_BAD_INPUT;
  }
  response = sqlite3_prepare(connection, "select id, name, description from 'item_part_generals'", -1, &statement, 0);
  for (size_t i = 0; i < std::min(counter, this->_item_part_templates.size()); ++i) {
    sqlite3_step(statement);
    this->_item_part_templates[i]._own_id = FREE_ID;
    this->_item_part_templates[i]._name.clear();
    this->_item_part_templates[i]._name.append((const char*)(sqlite3_column_text(statement, 1)));
    this->_item_part_templates[i]._description.clear();
    this->_item_part_templates[i]._description.append((const char*)(sqlite3_column_text(statement, 2)));
  }
  sqlite3_finalize(statement);
  sqlite3_prepare(connection, "select id, kind, group, place, rarity from 'item_part_generals'", -1, &statement, 0);
  for (size_t i = 0; i < counter; ++i) {
    sqlite3_step(statement);
    this->_item_part_templates[i]._kind = sqlite3_column_int(statement, 1);
    this->_item_part_templates[i]._group = sqlite3_column_int(statement, 2);
    this->_item_part_templates[i]._place = sqlite3_column_int(statement, 3);
    this->_item_part_templates[i]._rarity = sqlite3_column_int(statement, 4);
  }
  sqlite3_finalize(statement);
  return response;
}

ssize_t TemplateStorage::read_item_part_costs(sqlite3*& connection) {
  if (_item_part_templates.empty()) {
    return RC_BAD_INPUT;
  }
  sqlite3_stmt* statement;
  ssize_t response = sqlite3_prepare(connection, "select count(id) from 'item_part_costs'", -1, &statement, 0);
  sqlite3_step(statement);
  size_t counter = sqlite3_column_int(statement, 0);
  sqlite3_finalize(statement);
  if (counter != this->_item_part_templates.size()) {
    return RC_BAD_INPUT;
  }
  response = sqlite3_prepare(connection, "select id, gold, food, wood, iron, leather from 'item_part_costs'", -1, &statement, 0);
  for (size_t i = 0; i < counter; ++i) {
    sqlite3_step(statement);
    this->_item_part_templates[i]._cost.clear();
    for (size_t j = 1; j <= RI_SIZE; ++j) {
      this->_item_part_templates[i]._cost.push_back(sqlite3_column_int(statement, j));
    }
  }
  sqlite3_finalize(statement);
  return response;
}

ssize_t TemplateStorage::read_item_part_bonuses(sqlite3*& connection) {
  if (this->_item_part_templates.empty()) {
    return RC_BAD_INPUT;
  }
  sqlite3_stmt* statement;
  ssize_t response = sqlite3_prepare(connection, "select count(id) from 'item_part_bonuses'", -1, &statement, 0);
  sqlite3_step(statement);
  size_t counter = sqlite3_column_int(statement, 0);
  sqlite3_finalize(statement);
  if (counter != this->_item_part_templates.size()) {
    return RC_BAD_INPUT;
  }
  response = sqlite3_prepare(connection, "select id, melee, ranged, defense from 'item_part_bonuses'", -1, &statement, 0);
  for (size_t i = 0; i < counter; ++i) {
    sqlite3_step(statement);
    this->_item_part_templates[i]._bonuses.clear();
    for (size_t j = 1; j <= CS_SIZE; ++j) {
      this->_item_part_templates[i]._bonuses.push_back(sqlite3_column_int(statement, j));
    }
  }
  sqlite3_finalize(statement);
  return response;
}

ssize_t TemplateStorage::read_item_parts(sqlite3*& connection) {
  this->_item_part_templates.clear();
  sqlite3_stmt* statement;
  sqlite3_prepare(connection, "select count(id) from 'item_part_generals'", -1, &statement, 0);
  sqlite3_step(statement);
  size_t counter = sqlite3_column_int(statement, 0);
  sqlite3_finalize(statement);
  this->_item_part_templates.resize(counter);
  this->read_item_part_generals(connection);
  this->read_item_part_costs(connection);
  this->read_item_part_bonuses(connection);
  return RC_OK;
}

ssize_t TemplateStorage::read_item_blueprints(sqlite3*& connection) {
  this->_item_blueprints.clear();
  sqlite3_stmt* statement;
  ssize_t response = sqlite3_prepare(connection, "select count(id) from 'item_blueprints'", -1, &statement, 0);
  response = sqlite3_step(statement);
  size_t counter = sqlite3_column_int(statement, 0);
  response = sqlite3_finalize(statement);
  response = sqlite3_prepare(connection, "select id, kind, group, rarity, first, second, third from 'item_blueprints'", -1, &statement, 0);
  for (size_t i = 0; i < counter; ++i) {
    response = sqlite3_step(statement);
    std::vector<ssize_t> blueprint;
    for (size_t j = 0; j < IB_SIZE; ++j) {
      blueprint.push_back(sqlite3_column_int(statement, j + 1));
    }
    this->_item_blueprints.push_back(blueprint);
  }
  response = sqlite3_finalize(statement);
  return response;
}

std::string TemplateStorage::male_name() const {
  std::string name;
  name += _male_nameparts_begin[roll_dice(_male_nameparts_begin.size())];
  name += _male_nameparts_end[roll_dice(_male_nameparts_end.size())];
  return name;
}

std::string TemplateStorage::female_name() const {
  std::string name;
  name += _female_nameparts_begin[roll_dice(_female_nameparts_begin.size())];
  name += _female_nameparts_end[roll_dice(_female_nameparts_end.size())];
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
  return !_male_nameparts_begin.empty() && !_male_nameparts_end.empty() && !_female_nameparts_begin.empty() && !_female_nameparts_end.empty() && !_surname_suffixes.empty();
}

size_t TemplateStorage::fill_storage(const std::string& db_name) {
  sqlite3* database = NULL;
  open_connection(db_name, database);
  read_male_names(database);
  read_female_names(database);
  read_surname_suffixes(database);
  read_item_parts(database);
  read_item_blueprints(database);
  close_connection(database);
  return RC_OK;
}

size_t TemplateStorage::clear_storage() {
  _male_nameparts_begin.clear();
  _male_nameparts_end.clear();
  _female_nameparts_begin.clear();
  _female_nameparts_end.clear();
  _surname_suffixes.clear();
  _item_part_templates.clear();
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

ItemPartTemplate TemplateStorage::make_item_part_template(const size_t& group, const size_t& place, const size_t& rarity) const {
  ItemPartTemplate result;
  result._own_id = FREE_ID;
  result._name.clear();
  result._description.clear();
  result._cost.clear();
  result._bonuses.clear();
  while (true) {
    size_t index = roll_dice(_item_part_templates.size());
    if (this->_item_part_templates[index]._group == group && this->_item_part_templates[index]._place == place) {
      result = this->_item_part_templates[index];
      if (rarity == IR_SIZE) {
        if (result._rarity == IR_SIZE) {
          size_t chance = roll_dice();
          if (chance <= LEGENDARY_CHANCE) {
            result._rarity = IR_LEGENDARY;
          } else if (chance <= EPIC_CHANCE) {
            result._rarity = IR_EPIC;
          } else if (chance <= RARE_CHANCE) {
            result._rarity = IR_RARE;
          } else if (chance <= GOOD_CHANCE) {
            result._rarity = IR_GOOD;
          } else if (chance <= COMMON_CHANCE) {
            result._rarity = IR_COMMON;
          } else {
            result._rarity = IR_TRASH;
          }
        }
      } else {
        if (result._rarity == IR_SIZE) {
          result._rarity = rarity;
        }
      }
      break;
    }
  }
  return result;
}

std::vector<ssize_t> TemplateStorage::make_item_blueprint(const size_t& index) const {
  std::vector<ssize_t> blueprint;
  if (index < this->_item_blueprints.size()) {
    blueprint = this->_item_blueprints[index];
  }
  return blueprint;
}
