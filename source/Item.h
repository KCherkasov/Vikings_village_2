#ifndef VIKINGS_ITEM_H
#define VIKINGS_ITEM_H

#include "ItemPart.h"
#include <unordered_map>

class Item: public GameObject {
  public:
    Item(const ItemTemplate& data, std::unordered_map<ssize_t, GameEntity*>& pool);
    ~Item();
    std::vector<ssize_t> bonuses() const;
    ssize_t bonuses(const size_t& index) const;
    std::vector<size_t> cost() const;
    size_t cost(const size_t& index) const;
    size_t rarity() const;
    size_t kind() const { return this->_kind; }
    ItemPart* part(const size_t& index) const { return this->_parts[index]; }
    size_t parts_count() const { return this->_parts.size(); }
    std::string what() const;
    std::string short_what() const;
    size_t update();
    ItemTemplate save_data() const;
    size_t dispose();
  protected:
    size_t _kind;
    std::vector<ItemPart*> _parts;
};

#endif
