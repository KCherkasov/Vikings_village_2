#ifndef VIKINGS_ITEM_PART_H
#define VIKINGS_ITEM_PART_H

#include "StorageEntities.h"
#include "GameObject.h"

class ItemPart: public GameObject {
  public:
    ItemPart(const ItemPartTemplate& data);
    virtual ~ItemPart() {}
    size_t kind() const { return this->_kind; }
    size_t group() const { return this->_group; }
    size_t place() const { return this->_place; }
    size_t rarity() const { return this->_rarity; }
    std::vector<size_t> cost() { return this->_cost; }
    size_t cost(const size_t& index) { return this->_cost[index]; }
    std::vector<ssize_t> bonuses() { return this->_bonuses; }
    ssize_t bonuses(const size_t& index) { return this->_bonuses[index]; }
    std::string what() const;
    std::string short_what() const;
    size_t update();
    ItemPartTemplate save_data() const;
    size_t dispose() { this->_to_delete = true; return RC_OK; }
  protected:
    size_t _kind;
    size_t _group;
    size_t _place;
    size_t _rarity;
    std::vector<size_t> _cost;
    std::vector<ssize_t> _bonuses;
};

#endif
