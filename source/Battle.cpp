#include "Battle.h"

GameCharacter* Battle::get_by_id(const ssize_t& id, const std::vector<GameCharacter*>& character_pool) {
  for (size_t i = 0; i < character_pool.size(); ++i) {
    if (character_pool[i] != NULL) {
      if (character_pool[i]->id() == id) {
        return character_pool[i];
      }
    }
  }
  return NULL;
}

size_t Battle::make_pairs(std::vector<std::vector<size_t> >) const {
  
  return RC_OK;
}

size_t Battle::clean_dead(std::vector<GameCharacter*>& character_pool) {
  size_t j = SIZE_T_DEFAULT_VALUE;
  while (!character_pool.empty() && j < character_pool.size()) {
    if (character_pool[j] != NULL) {
      if (character_pool[j]->to_delete() || character_pool[j]->wounds() >= character_pool[j]->wounds_cap()) {
        character_pool.erase(character_pool.begin() + j);
      } else {
        ++j;
      }
    } else {
      character_pool.erase(character_pool.begin() + j);
    }
  }
  return RC_OK;
}

size_t Battle::cleanup() {
  clean_dead(_vikings);
  clean_dead(_enemies);
  return RC_OK;
}

Battle::Battle(const BattleTemplate& data, const std::vector<GameCharacter*>& character_pool): GameEntity(data._own_id) {
  _turn = START_TURN;
  _vikings.clear();
  for (size_t i = 0; i < data._vikings.size(); ++i) {
    GameCharacter* to_add = get_by_id(data._vikings[i], character_pool);
    if (to_add != NULL) {
      _vikings.push_back(to_add);
    }
  }
  _enemies.clear();
  for (size_t i = 0; i < data._enemies.size(); ++i) {
    GameCharacter* to_add = get_by_id(data._enemies[i], character_pool);
    if (to_add != NULL) {
      _enemies.push_back(to_add);
    }
  }
}

std::string Battle::what() const {
  std::string result;
  if (_manager == NULL) {
    return result;
  }
  result += _manager->tag(TL_TURN);
  std::string buffer;
  convert_to_string<size_t>(_turn, buffer);
  result += buffer;
  buffer.clear();
  result += _manager->tag(TL_TURN);
  return result;
}

std::string Battle::short_what() const {
  std::string result;
  if (_manager == NULL) {
    return result;
  }
  result += _manager->tag(TL_TURN);
  std::string buffer;
  convert_to_string<size_t>(_turn, buffer);
  result += buffer;
  buffer.clear();
  result += _manager->tag(TL_TURN);
  return result;
}

size_t Battle::update() const {
  cleanup();
  if (_vikings.empty()) {
    // code to process defeat here
  }
  if (_enemies.empty()) {
    // code to process victory here
  }
  return RC_OK;
}
