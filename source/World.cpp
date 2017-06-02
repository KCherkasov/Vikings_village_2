#include "World.h"

size_t World::cleanup(bool burn_storage) {
  if (burn_storage) {
    this->_storage.clear();
  }
  for (std::pair<ssize_t, GameObject*> object : this->_objects.map()) {
    delete object.second();
  }
  this->_objects.clear();
  return RC_OK;
}

ssize_t World::make_item_part(size_t group, size_t place, size_t rarity) {
  ItemPart* tmp = NULL;
  this->_storage.make_item_part(tmp, group, place, rarity);
  this->_objects.add(dynamic_cast<GameEntity*>(tmp));
  return tmp->id();
}

ssize_t World::make_item_part(const ItemPartTemplate& data) {
  ItemPart* tmp = NULL;
  this->_storage.make_item_part(tmp, data);
  this->_objects.add(dynamic_cast<GameEntity*>(tmp));
  return tmp->id();
}

ssize_t World::make_item(size_t blueprint) {
  Item* tmp = NULL;
  this->_storage->make_item(tmp, blueprint);
  for (size_t i = 0; i < ITEM_PARTS_PER_ITEM; ++i) {
    this->_objects.add(dynamic_cast<GameEntity*>(tmp->part(i)));
  }
  this->_objects.add(dynamic_cast<GameEntity*>(tmp));
  return tmp->id();
}

ssize_t World::make_item(const ItemTemplate& data) {
  Item* tmp = NULL;
  this->_storage.make_item(tmp, data, this->_objects.map());
  this->_objects.add(dynamic_cast<GameEntity*>(tmp));
  return tmp->id();
}

ssize_t World::make_character(ssize_t level) {
  GameCharacter* tmp = NULL;
  this->_storage->make_character(tmp, level);
  /* add inventory registering here */
  this->_objects.add(dynamic_cast<GameEntity*>(tmp));
  return tmp->id();
}

ssize_t World::make_character(const GameCharacterTemplate& data) {
  GameCharacter* tmp = NULL;
  this->_storage->make_character(tmp, data);
  this->_objects.add(dynamic_cast<GameEntity*>(tmp));
  return tmp->id();
}

ssize_t World::make_battle(Collecion<GameEntity>& raiders) {
  if (raiders.empty()) {
    return FREE_ID;
  }
  Battle* tmp = NULL;
  std::vector<ssize_t> viking_ids;
  ssize_t average_level = SSIZE_T_DEFAULT_VALUE;
  for (auto object = raiders.map().begin(); object != raiders.map().end(); ++object) {
    if (object->second != NULL) {
      viking_ids.push_back(object->second->id());
    }
    average_level += object->second->level();
  }
  average_level /= viking_ids.size();
  // generating enemies
  std::vector<ssize_t> enemy_ids;
  seed();
  size_t enemies_count = roll(viking_ids.size() + viking_ids.size() / 2);
  for (size_t i = 0; i < enemies_count; ++i) {
    ssize_t id = this->make_character(average_level);
    enemy_ids.push_back(id);
  }
  this->_storage->make_battle(tmp, this->_objects.map(), viking_ids, enemy_ids);
  this->_objects.add(dynamic_cast<GameEntity*>(tmp));
  return tmp->id();
}

size_t World::new_game(const std::string& player_name) {
  if (player_name.empty()) {
    return RC_BAD_INPUT;
  }
  this->cleanup();
  return RC_OK;
}

size_t World::save_game(const std::string& fname) const {
  std::ofstream save_file;
  save_file.open(fname, std::oftream::out | std::ofstream::trunc);
  if (!save_file.is_open()) {
    return RC_BAD_INPUT;
  }
  save_file << this->_turn;
  Collection<ItemPart> item_parts = this->get_all_instances<ItemPart>();
  item_parts.clear_null();
  this->write_collection<ItemPart>(save_file, item_parts);
  item_parts.clear();
  Collection<Item> items = this->get_all_instances<Item>();
  items.clear_null();
  this->write_collection<Item>(save_file, items);
  items.clear();
  Collection<GameCharacter> characters = this->get_all_instances<GameCharacter>();
  characters.clear_null();
  this->write_collection<GameCharacter>(save_file, characters);
  characters.clear();
  save_file.close();
  return RC_OK;
}

size_t World::load_game(const std::string& fname) {
  std::ofstream load_file;
  load_file.open(fname);
  if (!load_file.is_open()) {
    return RC_FILE_ERROR;
  }
  this->cleanup();
  load_file >> this->_turn;
  size_t obj_counter = SIZE_T_DEFAULT_VALUE;
  load_file >> obj_counter;
  for (size_t i = 0; i < obj_counter; ++i) {
    ItemPartTemplate data;
    load_file >> data;
    this->make_item_part(data);
  }
  load_file >> obj_counter;
  for (size_t i = 0; i < obj_counter; ++i) {
    ItemTemplate data;
    load_file >> data;
    this->make_item(data);
  }
  return RC_OK;
}

size_t World::update() {
  this->_objects.update();
  /* some code to do pre-deleting stuff with objects that gonna be deleted (like loot dropping, gravestone making and message sending) */
  this->_objects.clear_to_delete(true);
  this->_objects.clear_null();
  return RC_OK;
}
