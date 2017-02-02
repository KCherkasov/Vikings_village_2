#ifndef VIKINGS_STORAGE_ENTITIES_H
#define VIKINGS_STORAGE_ENTITIES_H

#include "misc.h"

//-- XxxTemplate structs are used for serializing/deserializing tasks with Xxx class objects.       --//
//-- Xxx class must have an Xxx(const XxxTemplate& data) constructor for initializing objects       --//
//-- via prepared data and public size_t save_data(XxxTemplate& result) const method for prepping   --//
//-- an instance data to write in save file.                                                        --//
//-- XxxTemplate must have the same (or almost the same excluding some fields like _to_delete or    --//
//-- any static fields) fields as Xxx class and also have operators for comparisons and stream I/O. --//

//-- GameCharacter template --//

struct GameCharacterTemplate {
  ssize_t _own_id;
  std::string _name;
  std::string _description;
  ssize_t _level;
  size_t _stat_points;
  size_t _wounds;
  bool _gender;
  std::vector<size_t> _experience;
  std::vector<size_t> _stats;
  
  GameCharacterTemplate& operator = (const GameCharacterTemplate& rhs) {
    _own_id = rhs._own_id;
    _name.clear();
    _name = rhs._name;
    _description.clear();
    _description = rhs._description;
    _level = rhs._level;
    _stat_points = rhs._stat_points;
    _wounds = rhs._wounds;
    _gender = rhs._gender;
    _experience.clear();
    _experience = rhs._experience;
    _stats.clear();
    _stats = rhs._stats;
    return *this;
  }
  
  friend bool operator == (const GameCharacterTemplate& lhs, const GameCharacterTemplate& rhs);
  friend bool operator < (const GameCharacterTemplate& lhs, const GameCharacterTemplate& rhs);
  friend bool operator > (const GameCharacterTemplate& lhs, const GameCharacterTemplate& rhs);
  
  friend std::ofstream& operator << (std::ofstream& stream, const GameCharacterTemplate& data);
  friend std::ifstream& operator >> (std::ifstream& stream, GameCharacterTemplate& data);
};

//-- GameCharacter template end --//

//-- Battle template --//

struct BattleTemplate {
  ssize_t _own_id;
  size_t _turn;
  std::vector<ssize_t> _vikings; // stores ids of player's vikings involved in this fight
  std::vector<ssize_t> _enemies; // stores ids of generated enemies involved in this fight
  
  BattleTemplate& operator = (const BattleTemplate& rhs) {
    _own_id = rhs._own_id;
    _turn = rhs._turn;
    _vikings.clear();
    _vikings = rhs._vikings;
    _enemies.clear();
    _enemies = rhs._enemies;
    return *this;
  }
  
  friend bool operator == (const BattleTemplate& lhs, const BattleTemplate& rhs);
  friend bool operator < (const BattleTemplate& lhs, const BattleTemplate& rhs);
  friend bool operator > (const BattleTemplate& lhs, const BattleTemplate& rhs);
  
  friend std::ofstream& operator << (std::ofstream& stream, const BattleTemplate& data);
  friend std::ifstream& operator >> (std::ifstream& stream, const BattleTemplate& data);
};

//-- Battle template end --///

#endif
