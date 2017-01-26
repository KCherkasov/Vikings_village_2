#ifndef VIKINGS_LEVELABLE_OBJECT_H
#define VIKINGS_LEVELABLE_OBJECT_H

#include "GameObject.h"

class LevelableObject: public GameObject {
  public:
    LevelableObject(const ssize_t id = FREE_ID, const ssize_t& level = START_LEVEL): GameObject(id) { _level = level; }
    virtual ~LevelableObject() {}
    ssize_t level() const { return _level; }
    size_t set_level(const ssize_t& value);
  protected:
    size_t increase_level(const ssize_t& shift = 1);
    size_t decrease_level(const ssize_t& shift = 1);
    size_t virtual level_up() { increase_level(); return RC_OK; }
    
    ssize_t _level;
};

#endif
