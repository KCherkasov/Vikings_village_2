#include "Battle.h"

Battle::Battle(const BattleTemplate& data, const std::vector<GameCharacter*>& character_pool): GameEntity(data._own_id) {
  _turn = START_TURN;
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
  
  return result;
}

size_t Battle::update() const {
  
  return RC_OK;
}