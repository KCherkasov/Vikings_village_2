#include "StorageEntities.h"

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
  if (lhs._wounds != rhs._wounds;) {
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

bool operator > const GameCharacterTemplate& lhs, const GameCharacterTemplate& rhs) {
  return lhs._own_id > rhs._own_id;
}

std::ofstream& operator << (std::ofstream& stream, const GameCharacterTemplate& data) {
  stream << data._own_id;
  stream << data._name;
  stream << data_description;
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
  stream >> data._own_id;
  stream >> data._name;
  stream >> data._description;
  stream >> data._level;
  stream >> data._stat_points;
  stream >> data._wounds;
  stream >> data._gender;
  size_t counter;
  stream >> counter;
  data._experience.clear();
  for (size_t i = 0; i < counter; ++i) {
    size_t buffer;
    stream >> buffer;
    data._experience.push_back(buffer);
  }
  stream >> counter;
  data._stats.clear();
  for (size_t i = 0; i < counter; ++i) {
    size_t buffer;
    stream >> buffer;
    data._stats.push_back(buffer);
  }
  return stream;
}
