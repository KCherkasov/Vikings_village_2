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
    _manager[TM_BATTLE].add_tag(_ui_dictionary.battle_tag(i));
  }
  for (size_t i = 0; i < _ui_dictionary.ui_tags_count(); ++i) {
    _manager[TM_UI].add_tag(_ui_dictionary.ui_tag(i));
  }
  _ui_dictionary.clear_manager_tags();
  return RC_OK;
}

WorldStorage::WorldStorage(const std::string& templates_db_name, const std::string& ui_db_name) {
  _templates.fill_storage(templates_db_name);
  _ui_dictionary.fill_storage(ui_db_name);
  fill_managers();
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
  result->set_manager(const_cast<TagManager*>(&_manager[TM_CHARACTER]));
  return RC_OK;
}

size_t WorldStorage::make_character(GameCharacter*& result, const GameCharacterTemplate& data) const {
  result = new GameCharacter(data);
  result->set_manager(const_cast<TagManager*>(&_manager[TM_CHARACTER]));
  return RC_OK;
}
