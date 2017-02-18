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
  if (stream.is_open()) {
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
  }
  return stream;
}

std::ifstream& operator >> (std::ifstream& stream, GameCharacterTemplate& data) {
  if (stream.is_open()) {
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
  }
  return stream;
}

//-- GameCharacter template end --//

//-- ItemPart template --//

bool operator == (const ItemPartTemplate& lhs, const ItemPartTemplate& rhs) {
  if (lhs._own_id != rhs._own_id) {
    return false;
  }
  if (lhs._name != rhs._name) {
    return false;
  }
  if (lhs._description != rhs._description) {
    return false;
  }
  if (lhs._kind != rhs._kind) {
    return false;
  }
  if (lhs._group != rhs._group) {
    return false;
  }
  if (lhs._place != rhs._place) {
    return false;
  }
  if (lhs._rarity != rhs._rarity) {
    return false;
  }
  if (lhs._cost != rhs._cost) {
    return false;
  }
  if (lhs._bonuses != rhs._bonuses) {
    return false;
  }
  return true;
}

bool operator < (const ItemPartTemplate& lhs, const ItemPartTemplate& rhs) {
  return lhs._own_id < rhs._own_id;
}

bool operator > (const ItemPartTemplate& lhs, const ItemPartTemplate& rhs) {
  return lhs._own_id > rhs._own_id;
}

std::ofstream& operator << (std::ofstream& stream, const ItemPartTemplate& data) {
  if (stream.is_open()) {
    stream << data._own_id;
    stream << data._name;
    stream << data._description;
    stream << data._kind;
    stream << data._place;
    stream << data._rarity;
    stream << data._cost.size();
    for (size_t i = 0; i < data._cost.size(); ++i) {
      stream << data._cost[i];
    }
    stream << data._bonuses.size();
    for (size_t i = 0; i < data._bonuses.size(); ++i) {
      stream << data._bonuses[i];
    }
  }
  return stream;
}

std::ifstream& operator >> (std::ifstream& stream, ItemPartTemplate& data) {
  if (stream.is_open()) {
    stream >> data._own_id;
    stream >> data._name;
    stream >> data._description;
    stream >> data._kind;
    stream >> data._place;
    stream >> data._rarity;
    size_t counter = SIZE_T_DEFAULT_VALUE;
    stream >> counter;
    data._cost.clear();
    for (size_t i = 0; i < counter; ++i) {
      size_t buffer = SIZE_T_DEFAULT_VALUE;
      stream >> buffer;
      data._cost.push_back(buffer);
    }
    stream >> counter;
    data._bonuses.clear();
    for (size_t i = 0; i < counter; ++i) {
      size_t buffer = SIZE_T_DEFAULT_VALUE;
      stream >> buffer;
      data._bonuses.push_back(buffer);
    }
  }
  return stream;
}

//-- ItemPart template end --//

//-- Item template --//

bool operator == (const ItemTemplate& lhs, const ItemTemplate& rhs) {
  if (lhs._own_id != rhs._own_id) {
    return false;
  }
  if (lhs._name != rhs._name) {
    return false;
  }
  if (lhs._description != rhs._description) {
    return false;
  }
  if (lhs._kind != rhs._kind) {
    return false;
  }
  if (lhs._rarity != rhs._rarity) {
    return false;
  }
  if (lhs._parts != rhs._parts) {
    return false;
  }
  return true;
}

bool operator < (const ItemTemplate& lhs, const ItemTemplate& rhs) {
  return lhs._own_id < rhs._own_id;
}

bool operator > (const ItemTemplate& lhs, const ItemTemplate& rhs) {
  return lhs._own_id > rhs._own_id;
}

std::ofstream& operator << (std::ofstream& stream, const ItemTemplate& data) {
  if (stream.is_open()) {
    stream << data._own_id;
    stream << data._name;
    stream << data._description;
    stream << data._kind;
    stream << data._rarity;
    stream << data._parts.size();
    for (size_t i = 0; i < data._parts.size(); ++i) {
      stream << data._parts[i];
    }
  }
  return stream;
}

std::ifstream& operator >> (std::ifstream& stream, ItemTemplate& data) {
  if (stream.is_open()) {
    stream >> data._own_id;
    stream >> data._name;
    stream >> data._description;
    stream >> data._kind;
    stream >> data._rarity;
    size_t counter = SIZE_T_DEFAULT_VALUE;
    stream >> counter;
    data._parts.clear();
    for (size_t i = 0; i < counter; ++i) {
      ssize_t buffer = SSIZE_T_DEFAULT_VALUE;
      stream >> buffer;
      data._parts.push_back(buffer);
    }
  }
  return stream;
}

//-- Item template end --//

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
  if (stream.is_open()) {
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
  }
  return stream;
}

std::ifstream& operator >> (std::ifstream& stream, BattleTemplate& data) {
  if (stream.is_open()) {
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
  }
  return stream;
}

//-- Battle template end --//
