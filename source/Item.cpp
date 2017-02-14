#include "Item.h"

Item::Item(const ItemTemplate& data): GameObject(data._own_id) {
  _name = data._name;
  _description = data._description;
  _kind = data._kind;
  _rarity = data._rarity;
  _cost.clear();
  _cost = data._cost;
  _bonuses.clear();
  _bonuses = data._bonuses;
}

std::string Item::what() const {
  std::string result;
  if (_manager == NULL) {
    return result;
  }
  return result;
}

std::string Item::short_what() const {
  std::string result;
  if (_manager == NULL) {
    return result;
  }
  return result;
}

size_t Item::update() const {
  return RC_OK;
}