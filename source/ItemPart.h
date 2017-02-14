#ifndef VIKINGS_ITEM_PART_H
#define VIKINGS_ITEM_PART_H

#include "StorageEntities.h"
#include "GameObject.h"

class ItemPart: public GameObject {
  public:
    ItemPart(const ItemPart& data);
    virtual ~ItemPart() {}
    size_t kind() const { return _kind; }
    size_t place() const { return _place; }
    size_t rarity() const { return _rarity; }
    std::vector<size_t> cost() { return _cost; }
    size_t cost(const size_t& index) { return _cost[index]; }
    std::vector<size_t> bonuses() { return _bonuses; }
    size_t bonuses(const size_t& index) { return _bonuses[index]; }
    std::string what() const;
    std::string short_what() const;
    size_t update();
    ItemPartTemplate save_data() const;
  protected:
    size_t _kind;
    size_t _place;
    size_t _rarity;
    std::vector<size_t> _cost;
    std::vector<size_t> _bonuses;
};

#endif
