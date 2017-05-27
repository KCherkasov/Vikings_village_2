#ifndef VIKINGS_WORLD_H
#define VIKINGS_WORLD_H

#include "WorldStorage.h"
#include "Collection.h"
#include <typeinfo>

class World {
  public:
    World(): _turn(START_TURN) {}
    ~World() {}
    size_t fill(const std::string& templates_db_name, const std::string& ui_db_name) { _storage.fill(templates_db_name, ui_db_name); return RC_OK; }
    size_t new_game(const std::string& player_name);
    size_t load_game(const std::string& fname); // think about args there
    size_t save_game(const std::string& fname) const;
    size_t update();

    std::string object_short_what(ssize_t key) const { std::string what; if (this->_objects.has(key)) { if (this->_objects[key] != NULL) { what = this->_objects[key]->short_what(); } } }
    std::string object_what(ssize_t key) const { std::string what; if (this->_objects.has(key)) { if (this->_objects[key] != NULL) { what = this->_objects[key]->what(); } } }

    GameEntity* object(ssize_t id) { return this->_objects[id]; }
    template<class T> T* first_instance(size_t start_point = 0);

    WorldStorage* storage() { return const_cast<WorldStorage*>(&(this->_storage)); }

  private:
    size_t _turn;
    Collection<GameEntity> _objects;
    WorldStorage _storage;

    ssize_t make_item_part(size_t group, size_t place, size_t rarity = IR_SIZE);
    ssize_t make_item_part(const ItemPartTemplate& data);

    ssize_t make_item(size_t blueprint);
    ssize_t make_item(const ItemTemplate& data);

    ssize_t make_character(ssize_t level = START_LEVEL);
    ssize_t make_character(const GameCharacterTemplate& data);

    ssize_t make_battle(Collection<GameEntity>& raiders);

    size_t cleanup(bool burn_storage = false);

    template <class T> Collection<T> get_all_instances() const;
    template <class T> size_t write_collection(std::ofstream& file, const Collection<T>& collection) const;
};

template <class T>
Collection<T> World::get_all_instances() const {
  Collection<T> instances;
  for (auto instance = this->_objects.map().begin(); instance != this->_objects.map().end(); ++instance) {
    if (instance->second != NULL) {
      if (typeid(*(instance->second)) == typeid(T)) {
        instances.add(dynamic_cast<T*>(instance->second));
      }
    }
  }
  return instances;
}

template <class T>
size_t World::write_collection(std::ofstream& file, const Collection<T>& collection) {
  if (!file.is_open()) {
    return RC_FILE_ERROR;
  }
  if (collection.empty()) {
    return RC_BAD_INPUT;
  }
  file << collection.size();
  for (auto object = collection.map().begin(); object != collection.map().end(); ++object) {
    file << object->second->save_data();
  }
  return RC_OK;
}

template<class T>
T* World::first_instance(size_t start_point) {
  T* result = NULL;
  for (auto object = this->_objects.begin() + start_point; object != this->_objects.end(); ++object) {
    if (object->second != NULL) {
      if (typeid(*(object->second)) == typeid(T)) {
        result = object->second;
        break;
      }
    }
  }
  return result;
}

#endif
