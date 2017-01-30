#include "WorldStorage.h"

WorldStorage::WorldStorage(const std::string& templates_db_name, const std::string& ui_db_name) {
  _templates.fill_storage(templates_db_name);
  _ui_dictionary.fill_storage(ui_db_name);
  for (size_t i = 0; i < _ui_dictionary.tags_count(); ++i) {
    _manager.add_tag(_ui_dictionary.tag(i));
  }
}

size_t WorldStorage::fill(const std::string& templates_db_name, const std::string& ui_db_name) {
  _templates.fill_storage(templates_db_name);
  _ui_dictionary.fill_storage(ui_db_name);
  for (size_t i = 0; i < _ui_dictionary.tags_count(); ++i) {
    _manager.add_tag(_ui_dictionary.tag(i));
  }
  return RC_OK;
}

size_t WorldStorage::make_character(GameCharacter*& result, const ssize_t& level) const {
  GameCharacterTemplate data = _templates.make_character_template(level);
  result = new GameCharacter(data);
  result->set_manager(_manager);
  return RC_OK;
}

size_t WorldStorage::make_character(GameCharacter*& result, const GameCharacterTemplate& data) const {
  result = new GameCharacter(data);
  result->set_manager(_manager);
  return RC_OK;
}