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
  for (size_t i = 0; i < _ui_dictionary.inv_item_tags_count(); ++i) {
    _managers[TM_INV_ITEM].add_tag(_ui_dictionary.inv_item_tag(i));
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
  this->_templates.fill_storage(templates_db_name);
  this->_ui_dictionary.fill_storage(ui_db_name);
  this->fill_managers();
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

size_t WorldStorage::make_item_part(ItemPart*& result, const size_t& group, const size_t& place, const size_t& rarity) const {
  ItemPartTemplate data = this->_templates.make_item_part_template(group, place, rarity);
  result = new ItemPart(data);
  result->set_manager(const_cast<TagManager*>(&(this->_managers[TM_INV_ITEM])));
  return RC_OK;
}

size_t WorldStorage::make_item_part(ItemPart*& result, const ItemPartTemplate& data) const {
  result = new ItemPart(data);
  result->set_manager(const_cast<TagManager*>(&(this->_managers[TM_INV_ITEM])));
  return RC_OK;
}

size_t WorldStorage::make_item(Item*& result, const size_t& blueprint_index) const {
  ItemTemplate data;
  std::vector<ssize_t> blueprint = this->_templates.make_item_blueprint(blueprint_index);
  data._own_id = FREE_ID;
  data._name.clear();
  data._description.clear();
  std::unordered_map<ssize_t, GameEntity*> map;
  data._kind = blueprint[IB_KIND];
  data._parts.clear();
  for (size_t i = 0; i < ITEM_PARTS_PER_ITEM; ++i) {
    ItemPart* part = NULL;
    this->make_item_part(part, blueprint[IB_GROUP], i, blueprint[IB_RARITY]);
    data._parts.push_back(part->id());
    map[part->id()] = dynamic_cast<GameEntity*>(part);
    data._name += part->name();
    if (i == 0) {
      data._name.append(" with ");
    }
    if (i == 1) {
      data._name.append(" and ");
    }
    data._description += part->description();
    data._description.append("\n\n");
  }
  result = new Item(data, map);
  result->set_manager(const_cast<TagManager*>(&(this->_managers[TM_INV_ITEM])));
  return RC_OK;
}

size_t WorldStorage::make_item(Item*& result, const ItemTemplate& data, std::unordered_map<ssize_t, GameEntity*>& pool) const {
  result = new Item(data, pool);
  result->set_manager(const_cast<TagManager*>(&(this->_managers[TM_INV_ITEM])));
  return RC_OK;
}

size_t WorldStorage::make_character(GameCharacter*& result, const ssize_t& level) const {
  GameCharacterTemplate data = this->_templates.make_character_template(level);
  result = new GameCharacter(data);
  result->set_manager(const_cast<TagManager*>(&(this->_managers[TM_CHARACTER])));
  return RC_OK;
}

size_t WorldStorage::make_character(GameCharacter*& result, const GameCharacterTemplate& data) const {
  result = new GameCharacter(data);
  result->set_manager(const_cast<TagManager*>(&(this->_managers[TM_CHARACTER])));
  return RC_OK;
}

size_t WorldStorage::make_battle(Battle*& result, std::unordered_map<ssize_t, GameEntity*>& pool, const std::vector<ssize_t>& viking_ids, const std::vector<ssize_t>& enemy_ids) const {
  BattleTemplate data;
  data._own_id = FREE_ID;
  data._turn = START_TURN;
  data._vikings = viking_ids;
  data._enemies = enemy_ids;
  result = new Battle(data, pool);
  result->set_manager(const_cast<TagManager*>(&(this->_managers[TM_BATTLE])));
  return RC_OK;
}
