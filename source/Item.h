#ifndef VIKINGS_ITEM_H
#define VIKINGS_ITEM_H

#include "ItemPart.h"

class Item: public GameObject {
  public:
    Item(const ItemTemplate& data, const std::vector<GameObject*>& pool);
    ~Item() {}
    std::vector<ssize_t> bonuses() const;
    size_t bonuses(const ssize_t& index) const;
    std::vector<size_t> cost() const;
    size_t cost(const size_t& index) const;
    std::string what() const;
    std::string short_what() const;
    size_t update();
    ItemTemplate save_data() const;
    size_t dispose();
  protected:
    size_t _kind;
    size_t _rarity;
    std::vector<ItemPart*> _parts;
};

#endif
