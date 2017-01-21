#include "LevelableObject.h"

size_t LevelableObject::set_level(const ssize_t& value) {
  _level = std::max(START_LEVEL, std::min(MAX_LEVEL, value));
  return RC_OK;
}

size_t LevelableObject::increase_level(const ssize_t& shift) {
  _level = std::min(MAX_LEVEL, _level + shift);
  return RC_OK;
}

size_t LevelableObject::decrease_level(const ssize_t& shift) {
  _level = std::max(START_LEVEL, _level - shift);
  return RC_OK;
}
