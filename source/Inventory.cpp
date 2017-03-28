#include "Inventory.h"

Inventory::Inventory(const InventoryTemplate& data, const std::vector<GameObject*>& item_pool): GameEntity(data._own_id), _items(std::vector<Item*>(data._item_ids.size(), NULL)) {
  for (size_t i = 0; i < _items.size(); ++i) {
    _items[i] = dynamic_cast<Item*>(get_by_id<GameObject>(item_pool));
  }
}

Inventory::~Inventory() {
  for (size_t i = 0; i < _items.size(); ++i) {
    _items[i] = NULL;
  }
}

std::vector<ssize_t> Inventory::bonuses() const {
  std::vector<ssize_t> bonuses(CS_SIZE, SSIZE_T_DEFAULT_VALUE);
  for (size_t i = 0; i < bonuses.size(); ++i) {
    for (size_t j = 0; j < _items.size(); ++j) {
      if (_items[j] != NULL) {
        bonuses[i] += _items[j]->bonuses(i);
      }
    }
  }
  return bonuses;
}

ssize_t Inventory::bonuses(const size_t& index) const {
  ssize_t bonus = SSIZE_T_DEFAULT_VALUE;
  for (size_t i = 0; i < _items.size(); ++i) {
    if (_items[i] != NULL) {
      bonus += _items[i]->bonuses[index];
    }
  }
  return bonus;
}

size_t Inventory::equip(Item*& item) {
  if (item != NULL) {
    Item* tmp = _items[item->kind()];
    _items[item->kind()] = item;
    item = tmp;
    tmp = NULL;
  }
  return RC_OK;
}


Item* Inventory::unequip(const size_t& index) {
  if (index >= _items.size()) {
    return NULL;
  }
  Item* tmp = _items[index];
  _items[index] = NULL;
  return tmp;
}

InventoryTemplate Inventory::save_data() const {
  InventoryTemplate data;
  data._own_id = _own_id;
  for (size_t i = 0; i < _items.size(); ++i) {
    if (_items[i] != NULL) {
      data._item_ids.push_back(_items[i]->id();
    } else {
      data._item_ids.push_back(FREE_ID);
    }
  }
  return data;
}

std::string Inventory::what() const {
  std::string result;
  for (size_t i = 0; i < _items.size(); ++i) {
    result += _manager->tag(IT_SLOT);
    if (_items[i] != NULL) {
      result += _items[i]->short_what();
    } else {
      result += _manager->tag(IT_EMPTY_SLOT);
    }
    result += _manager->tag(IT_SLOT);
  }
  result += short_what();
  return result;
}

std::string Inventory::short_what() const {
  std::string result;
  std::vector<ssize_t> bonuses = bonuses();
  result += _manager->tag(IT_BONUSES);
  for (size_t i = 0; i < bonuses.size(); ++i) {
    result += convert_to_string<ssize_t>(bonuses[i]);
  }
  result += _manager->tag(IT_BONUSES);
  return result;
}
