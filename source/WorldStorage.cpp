#include "WorldStorage.h"

size_t WorldStorage::fill_managers() {
  if (!_ui_dictionary.is_filled()) {
    return RC_BAD_INPUT;
  }
  for(size_t i = 0; i < TM_SIZE; ++i) {
    _managers.push_back(TagManager());
  }
  for (size_t i = 0; i < _ui_dictionary.character_tags_count(); ++i) {
    _managers[TM_CHARACTER].add_tag(_ui_dictionary.character_tag(i));
  }
  for (size_t i = 0; i < _ui_dictionary.battle_tags_count(); ++i) {
    _managers[TM_BATTLE].add_tag(_ui_dictionary.battle_tag(i));
  }
  for (size_t i = 0; i < _ui_dictionary.ui_tags_count(); ++i) {
    _managers[TM_UI].add_tag(_ui_dictionary.ui_tag(i));
  }
  _ui_dictionary.clear_manager_tags();
  return RC_OK;
}

WorldStorage::WorldStorage(const std::string& templates_db_name, const std::string& ui_db_name) {
  _templates.fill_storage(templates_db_name);
  _ui_dictionary.fill_storage(ui_db_name);
  fill_managers();
}

bool WorldStorage::is_filled() const {
  if (!_templates.is_filled() || !_ui_dictionary.is_filled()) {
    return false;
  }
  for (size_t i = 0; i < _managers.size(); ++i) {
    if (!_managers[i].is_filled()) {
      return false;
    }
  }
  return true;
}

size_t WorldStorage::fill(const std::string& templates_db_name, const std::string& ui_db_name) {
  _templates.fill_storage(templates_db_name);
  _ui_dictionary.fill_storage(ui_db_name);
  fill_managers();
  return RC_OK;
}

size_t WorldStorage::clear() {
  _templates.clear_storage();
  _ui_dictionary.clear_storage();
  for (size_t i = 0; i < _managers.size(); ++i) {
    _managers[i].clear_tags();
  }
  _managers.clear();
  return RC_OK;
}

size_t WorldStorage::make_character(GameCharacter*& result, const ssize_t& level) const {
  GameCharacterTemplate data = _templates.make_character_template(level);
  result = new GameCharacter(data);
  result->set_manager(const_cast<TagManager*>(&_managers[TM_CHARACTER]));
  return RC_OK;
}

size_t WorldStorage::make_character(GameCharacter*& result, const GameCharacterTemplate& data) const {
  result = new GameCharacter(data);
  result->set_manager(const_cast<TagManager*>(&_managers[TM_CHARACTER]));
  return RC_OK;
}

size_t WorldStorage::make_battle(Battle*& result, const std::vector<GameCharacter*>& character_pool, const std::vector<ssize_t>& viking_ids, const std::vector<ssize_t>& enemy_ids) const {
  BattleTemplate data;
  data._own_id = FREE_ID;
  data._turn = START_TURN;
  data._vikings = viking_ids;
  data._enemies = enemy_ids;
  result = new Battle(data, character_pool);
  result->set_manager(const_cast<TagManager*>(&_managers[TM_BATTLE]));
  return RC_OK;
}

