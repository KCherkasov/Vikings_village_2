#ifndef VIKINGS_INVENTORY_H
#define VIKINGS_INVENTORY_H

#include "Item.h"

class Inventory: public GameEntity {
  public:
    Inventory(const InventoryTemplate& data, const std::vector<GameObject*>& item_pool);
    virtual ~Inventory();
    std::vector<ssize_t> bonuses() const;
    ssize_t bonuses(const size_t& index) const;
    size_t equip(Item*& item);
    Item* unequip(const size_t& index);
    InventoryTemplate save_data() const;
    std::string what() const;
    std::string short_what() const;
    size_t update() { return RC_OK; }
  private:
    std::vector<Item*> _items;
}

#endif
