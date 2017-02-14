#ifndef VIKINGS_EQUIPMENT_H
#define VIKINGS_EQUIPMENT_H

#include "Item.h"

class Equipment: public Item {
  public:
    Equipment(const ItemTemplate& data);
    ~Equipment() {}
    std::vector<size_t> bonuses() const { return _bonuses; }
    size_t bonuses(const size_t& index) const { return _bonuses[index]; }
    size_t cost() const { return _cost; }
    size_t cost(const size_t& index) const { return _cost[index]; }
    std::string what() const;
    std::string short_what() const;
    size_t update();
    ItemTemplate save_data() const;
    size_t dispose() { _to_delete = true; return RC_OK; }
  protected:
    size_t _kind;
    size_t _rarity;
    std::vector<size_t> _cost;
    std::vector<size_t> _bonuses;  
};

#endif
