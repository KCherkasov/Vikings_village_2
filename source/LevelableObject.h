#ifndef VIKINGS_LEVELABLE_OBJECT_H
#define VIKINGS_LEVELABLE_OBJECT_H

#include "GameObject.h"

class LevelableObject: public GameObject {
  public:
    LevelableObject(): GameObject() { _level = START_LEVEL; }
    virtual ~LevelableObject() {}
    ssize_t level() const { return _level; }
    size_t set_level(const ssize_t& value);
    size_t increase_level(const ssize_t& shift = 1);
    size_t decrease_level(const ssize_t& shift = 1);
  protected:
    ssize_t _level;
};

#endif
