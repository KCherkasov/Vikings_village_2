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

size_t Battle::random_character_index(const std::vector<GameCharacter*>& character_pool, const std::vector<size_t>& keys) const {
  while(true) {
    if (character_pool.empty()) {
      return SIZE_T_DEFAULT_VALUE;
    }
    size_t index = roll_dice(character_pool.size());
    if (!vector_has(keys, index) && character_pool[index] != NULL) {
      if (!character_pool[index]->to_delete()) {
        return index;
      }
    }
  }  
}

size_t Battle::make_pairs(std::vector<size_t>& vikings_queue, std::vector<size_t>& enemies_queue) const {
  vikings_queue.clear();
  enemies_queue.clear();
  size_t pairs_count = std::min(_vikings.size(), _enemies.size());
  for (size_t i = 0; i < pairs_count; ++i) {
    vikings_queue.push_back(random_character_index(_vikings, vikings_queue));
    enemies_queue.push_back(random_character_index(_enemies, enemies_queue));
  }
  size_t extra_pairs = std::max(_vikings.size(), _enemies.size()) - pairs_count;
  for (size_t i = 0; i < extra_pairs; ++i) {
    if (_vikings.size() < _enemies.size()) {
      vikings_queue.push_back(roll_dice(_vikings.size()));
      enemies_queue.push_back(random_character_index(_enemies, enemies_queue));
    } else {
      vikings_queue.push_back(random_character_index(_vikings, vikings_queue));
      enemies_queue.push_back(roll_dice(_enemies.size()));
    }
  }
  return RC_OK;
}

size_t Battle::clean_dead(std::vector<GameCharacter*>& character_pool) {
  size_t j = SIZE_T_DEFAULT_VALUE;
  while (!character_pool.empty() && j < character_pool.size()) {
    if (character_pool[j] != NULL) {
      if (character_pool[j]->to_delete()) {
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

size_t Battle::update_fighters() {
  for (size_t i = 0; i < _vikings.size(); ++i) {
    if (_vikings[i] != NULL) {
      _vikings[i]->update();
    }
  }
  for (size_t i = 0; i < _enemies.size(); ++i) {
    if (_enemies[i] != NULL) {
      _enemies[i]->update();
    }
  }
  return RC_OK;
}

size_t Battle::duel(const size_t& viking_index, const size_t& enemy_index) {
  if (viking_index >= _vikings.size() || enemy_index >= _enemies.size()) {
    return RC_BAD_INDEX;
  }
  if (_vikings[viking_index] == NULL || _enemies[enemy_index] == NULL) {
    return RC_BAD_INPUT;
  }
  if (_vikings[viking_index]->to_delete() || _enemies[enemy_index]->to_delete()) {
    return RC_BAD_INPUT;
  }
  
  return RC_OK;
}

size_t Battle::fight_round() {
  std::vector<size_t> vikings_queue;
  std::vector<size_t> enemies_queue;
  make_pairs(vikings_queue, enemies_queue);
  for (size_t i = 0; i < vikings_queue.size(); ++i) {
    duel(vikings_queue[i], enemies_queue[i]);  
  }
  ++_turn;
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
  while (!is_victory() && !is_defeat()) {
    cleanup();
    play_fight_round();
    update_fighters();
  }
  if (is_victory()) {
    // code here to process victory
  } else {
    // code here to process defeat
  }
  _to_delete = true;
  return RC_OK;
}
