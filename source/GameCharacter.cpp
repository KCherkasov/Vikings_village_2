#include "GameCharacter.h"


size_t GameCharacter::level_up() {
  increase_level();
  _stat_points += STAT_POINTS_PER_LEVEL;
  return RC_OK;
}

size_t GameCharacter::wounds_cap() const {
  size_t total_wounds = BASIC_WOUNDS_CAP; 
  // processing the traits here
  return total_wounds;
}

GameCharacter::GameCharacter(const GameCharacterTemplate& data): LevelableObject(data._own_id, data._level), _stat_points(data._stat_points), _wounds(data._wounds), _gender(data._gender), _experience(data._experience), _stats(data._stats) {
  _name = data._name;
  _description = data._description;
}

size_t GameCharacter::add_wounds(const size_t& amount) {
  _wounds += amount;
  return RC_OK;
}

size_t GameCharacter::remove_wounds(const size_t& amount) {
  if (amount > _wounds) {
    _wounds = SIZE_T_DEFAULT_VALUE;
  } else {
    _wounds -= amount;
  }
  return RC_OK;
}

size_t GameCharacter::melee_skill() const {
  size_t skill = SIZE_T_DEFAULT_VALUE;
  skill += _stats[CS_MELEE];
  return skill;
}

size_t GameCharacter::ranged_skill() const {
  size_t skill = SIZE_T_DEFAULT_VALUE;
  skill += _stats[CS_RANGED];
  return skill;
}

size_t GameCharacter::defense() const {
  size_t defense = SIZE_T_DEFAULT_VALUE;
  defense += _stats[CS_DEFENSE];
  return defense;
}

std::string GameCharacter::what() const {
  std::string result;
  if (_manager == NULL) {
    return result;
  }
  std::string buffer;
  result += _manager->tag(CT_NAME);
  result += _name;
  result += _manager->tag(CT_NAME);
  result += _manager->tag(CT_DESCRIPTION);
  result += _description;
  result += _manager->tag(CT_DESCRIPTION);
  result += _manager->tag(CT_LEVEL);
  buffer = convert_to_string<ssize_t>(_level);
  result += buffer;
  buffer.clear();
  result += _manager->tag(CT_LEVEL);
  result += _manager->tag(CT_STAT_POINTS);
  buffer = convert_to_string<ssize_t>(_stat_points);
  result += buffer;
  buffer.clear();
  result += _manager->tag(CT_STAT_POINTS);
  result += _manager->tag(CT_WOUNDS);
  buffer = convert_to_string<size_t>(_wounds);
  result += buffer;
  buffer.clear();
  result += _manager->tag(CT_WOUNDS);
  result += _manager->tag(CT_WOUNDS_CAP);
  buffer = convert_to_string<size_t>(wounds_cap());
  result += buffer;
  buffer.clear();
  result += _manager->tag(CT_WOUNDS_CAP);
  result += _manager->tag(CT_GENDER);
  buffer = convert_to_string<bool>(_gender);
  result += buffer;
  buffer.clear();
  result += _manager->tag(CT_GENDER);
  for (size_t i = 0; i < _experience.size(); ++i) {
    result += _manager->tag(CT_EXPERIENCE);
    buffer = convert_to_string<size_t>(_experience[i]);
    result += buffer;
    buffer.clear();
    result += _manager->tag(CT_EXPERIENCE);
  }
  for (size_t i = 0; i < _stats.size(); ++i) {
    result += _manager->tag(CT_STATS);
    buffer = convert_to_string<ssize_t>(_stats[i]);
    result += buffer;
    result += _manager->tag(CT_STATS);
  }
  return result;
}

std::string GameCharacter::short_what() const {
  std::string result;
  if (_manager == NULL) {
    return result;
  }
  result += _manager->tag(CT_NAME);
  result += _name;
  result += _manager->tag(CT_NAME);
  result += _manager->tag(CT_LEVEL);
  std::string buffer = convert_to_string<ssize_t>(_level);
  result += buffer;
  buffer.clear();
  result += _manager->tag(CT_LEVEL);
  return result;
}

std::string GameCharacter::talk() const {
  std::string result;
  result += _manager->tag(CT_NAME);
  result += _name;
  result += _manager->tag(CT_NAME);
  result += _manager->tag(CT_SPEECH);
  // code to place character's speech there
  result += _manager->tag(CT_SPEECH);
  return result;
}

size_t GameCharacter::update() {
  if (_wounds >= wounds_cap()) {
    _to_delete = true;
    return RC_OK;
  }
  if (_experience[PI_CURRENT] >= _experience[PI_MAX]) {
    level_up();
  }
  return RC_OK;
}

GameCharacterTemplate GameCharacter::save_data() const {
  GameCharacterTemplate data;
  data._own_id = _own_id;
  data._name.clear();
  data._name = _name;
  data._description.clear();
  data._description = _description;
  data._level = _level;
  data._stat_points = _stat_points;
  data._wounds = _wounds;
  data._gender = _gender;
  data._experience.clear();
  data._experience = _experience;
  data._stats.clear();
  data._stats = _stats;
  return data;
}

size_t GameCharacter::increase_stat(const size_t& index, const ssize_t& shift) {
  if (index >= _stats.size()) {
    return RC_BAD_INDEX;
  }
  if (_stat_points > SSIZE_T_DEFAULT_VALUE) {
    _stats[index] += shift;
  }
  return RC_OK;
}
