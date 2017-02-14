#ifndef VIKINGS_GAME_OBJECT_H
#define VIKINGS_GAME_OBJECT_H

#include "GameEntity.h"

class GameObject: public GameEntity {
  public:
    GameObject(const ssize_t& id = FREE_ID): GameEntity(id) { _name.clear(); _description.clear(); }
    virtual ~GameObject() {}
    std::string name() const { return _name; }
    std::string description() const { return _description; }
  protected:
    std::string _name;
    std::string _description;
};

#endif
