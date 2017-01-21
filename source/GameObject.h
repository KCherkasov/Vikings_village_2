#ifndef VIKINGS_GAME_OBJECT_H
#define VIKINGS_GAME_OBJECT_H

#include "misc.h"

class GameObject {
  public:
    GameObject() { _own_id = ++_id; }
    virtual ~GameObject() {}
    ssize_t id() const { return _own_id; }
    std::string name() const { return _name; }
    std::string description() const { return _description; }
  protected:
    static ssize_t _id;
    ssize_t _own_id;
    std::string _name;
    std::string _description;
};

#endif
