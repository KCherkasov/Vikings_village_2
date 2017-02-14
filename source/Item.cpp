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

ItemTemplate Item::save_data() const {
  ItemTemplate data;
  data._own_id = _own_id;
  data._name.clear();
  data._name = _name;
  data._description.clear();
  data._description = _description;
  data._kind = _kind;
  data._rarity = _rarity;
  data._cost.clear();
  data._cost = _cost;
  data._bonuses.clear();
  data._bonuses = _bonuses;
  return data;
}
