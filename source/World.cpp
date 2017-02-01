#include "World.h"

size_t World::cleanup() {
  _storage.clear();
  for (size_t i = 0; i < _character_pool.size(); ++i) {
    delete _character_pool[i];
  }
  _character_pool.clear();
  return RC_OK;
}

size_t World::new_game(const std::string& player_name) {
  
  return RC_OK;
}

size_t World::save_game(const std::string& fname) const {
  
  return RC_OK;
}

size_t World::load_game(const std::string& fname) {
  
  return RC_OK;
}

size_t World::update() {
  size_t j = SIZE_T_DEFAULT_VALUE;
  while (!_character_pool.empty() && j < _character_pool.size()) {
    if (_character_pool[j] != NULL) {
      _character_pool[j]->update();
      if (_character_pool[j]->to_delete()) {
        delete _character_pool[j];
        _character_pool.erase(_character_pool.begin() + j);
      } else {
        ++j;
      }
    } else {
      _character_pool.erase(_character_pool.begin() + j);
    }
  }
  return RC_OK;
}

std::string World::character_what(const size_t& index) const {
  std::string result;
  if (index < _character_pool.size()) {
    if (_character_pool[index] != NULL) {
      result = _character_pool[index]->what();
    }
  }
  return result;
}

std::string World::character_what(const ssize_t& id) const {
  std::string result;
  for (size_t i = 0; i < _character_pool.size(); ++i) {
    if (_character_pool[i] != NULL) {
      if (_character_pool[i]->id() == id) {
        result = _character_pool[i]->what();
        break;
      }
    }
  }
  return result;
}

std::string World::character_short_what(const size_t& index) const {
  std::string result;
  if (index < _character_pool.size()) {
    if (_character_pool[index] != NULL) {
      result = _character_pool[index]->short_what();
    }
  }
  return result;
}

std::string World::character_short_what(const ssize_t& id) const {
  std::string result;
  for (size_t i = 0; i < _character_pool.size(); ++i) {
    if (_character_pool[i] != NULL) {
      if (_character_pool[i]->id() == id) {
        result = _character_pool[i]->short_what();
        break;
      }
    }
  }
  return result;
}
