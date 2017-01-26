#ifndef VIKINGS_GAME_ENTITY_H
#define VIKINGS_GAME_ENTITY_H

#include "misc.h"
#include "TagManager.h"

class GameEntity {
  public:
    GameEntity(const ssize_t& id = FREE_ID) { if (id != FREE_ID) { if (id > _id) { _id = id + 1; } _own_id = id; } else { _own_id = ++_id; }  }
    virtual ~GameEntity() {}
    ssize_t id() const { return _own_id; }
    bool to_delete() const { return _to_delete; }
    size_t set_manager(TagManager* manager) { if (_manager != NULL) { return RC_HAS_MANAGER; } if (manager == NULL) { return RC_BAD_INPUT; } _manager = manager; return RC_OK; }
    virtual std::string what() const = 0;
    virtual std::string short_what() const = 0;
    virtual size_t update() { return RC_OK; }
  protected:
    static ssize_t _id;
    ssize_t _own_id;
    bool _to_delete;
    TagManager* _manager;
};

#endif