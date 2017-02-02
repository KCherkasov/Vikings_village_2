#include "StorageEntities.h"

//-- GameCharacter template --//

bool operator == (const GameCharacterTemplate& lhs, const GameCharacterTemplate& rhs) {
  if (lhs._own_id != rhs._own_id) {
    return false;
  }
  if (lhs._name != rhs._name) {
    return false;
  }
  if (lhs._description != rhs._description) {
    return false;
  }
  if (lhs._level != rhs._level) {
    return false;
  }
  if (lhs._stat_points != rhs._stat_points) {
    return false;
  }
  if (lhs._wounds != rhs._wounds) {
    return false;
  }
  if (lhs._gender != rhs._gender) {
    return false;
  }
  if (lhs._experience != rhs._experience) {
    return false;
  }
  if (lhs._stats != rhs._stats) {
    return false;
  }
  return true;
}

bool operator < (const GameCharacterTemplate& lhs, const GameCharacterTemplate& rhs) {
  return lhs._own_id < rhs._own_id;
}

bool operator > (const GameCharacterTemplate& lhs, const GameCharacterTemplate& rhs) {
  return lhs._own_id > rhs._own_id;
}

std::ofstream& operator << (std::ofstream& stream, const GameCharacterTemplate& data) {
  if (!stream.is_open()) {
    return stream;
  }
  stream << data._own_id;
  stream << data._name;
  stream << data._description;
  stream << data._level;
  stream << data._stat_points;
  stream << data._wounds;
  stream << data._gender;
  stream << data._experience.size();
  for (size_t i = 0; i < data._experience.size(); ++i) {
    stream << data._experience[i];
  }
  stream << data._stats.size();
  for (size_t i = 0; i < data._stats.size(); ++i) {
    stream << data._stats[i];
  }
  return stream;
}

std::ifstream& operator >> (std::ifstream& stream, GameCharacterTemplate& data) {
  if (!stream.is_open()) {
    return stream;
  }
  stream >> data._own_id;
  stream >> data._name;
  stream >> data._description;
  stream >> data._level;
  stream >> data._stat_points;
  stream >> data._wounds;
  stream >> data._gender;
  size_t counter = SIZE_T_DEFAULT_VALUE;
  stream >> counter;
  data._experience.clear();
  for (size_t i = 0; i < counter; ++i) {
    size_t buffer = SIZE_T_DEFAULT_VALUE;
    stream >> buffer;
    data._experience.push_back(buffer);
  }
  stream >> counter;
  data._stats.clear();
  for (size_t i = 0; i < counter; ++i) {
    size_t buffer = SIZE_T_DEFAULT_VALUE;
    stream >> buffer;
    data._stats.push_back(buffer);
  }
  return stream;
}

//-- GameCharacter template end --//

//-- Battle template --//

bool operator == (const BattleTemplate& lhs, const BattleTemplate& rhs) {
  if (lhs._own_id != rhs._own_id) {
    return false;
  }
  if (lhs._turn != rhs._turn) {
    return false;
  }
  if (lhs._vikings != rhs._vikings) {
    return false;
  }
  if (lhs._enemies != rhs._enemies) {
    return false;
  }
  return true;
}

bool operator < (const BattleTemplate& lhs, const BattleTemplate& rhs) {
  return lhs._own_id < rhs._own_id;
}

bool operator > (const BattleTemplate& lhs, const BattleTemplate& rhs) {
  return lhs._own_id > rhs._own_id;
}

std::ofstream& operator << (std::ofstream& stream, const BattleTemplate& data) {
  if (!stream.is_open()) {
    return stream;
  }
  stream << data._own_id;
  stream << data._turn;
  stream << data._vikings.size();
  for (size_t i = 0; i < data._vikings.size(); ++i) {
    stream << data._vikings[i];
  }
  stream << data._enemies.size();
  for (size_t i = 0; i < data._enemies.size(); ++i) {
    stream << data._enemies[i];
  }
  return stream;
}

std::ifstream& operator >> (std::ifstream& stream, BattleTemplate& data) {
  if (!stream.is_open()) {
    return stream;
  }
  stream >> data._own_id;
  stream >> data._turn;
  size_t counter = SIZE_T_DEFAULT_VALUE;
  stream >> counter;
  data._vikings.clear();
  ssize_t buffer = SSIZE_T_DEFAULT_VALUE;
  for (size_t i = 0; i < counter; ++i) {
    stream >> buffer;
    data._vikings.push_back(buffer);
  }
  stream >> counter;
  data._enemies.clear();
  for (size_t i = 0; i < counter; ++i) {
    stream >> buffer;
    data._enemies.push_back(buffer);
  }
  return stream;
}

//-- Battle template end --//
