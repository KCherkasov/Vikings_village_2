#include "ItemPart.h"

ItemPart::ItemPart(const ItemPartTemplate& data): GamObject(data._own_id) {
  _name = data._name;
  _description =  data._description;
  _kind = data._kind;
  _group = data._group;
  _rarity = data._rarity;
  _place = data._place;
  _cost.clear();
  _cost = data._cost;
  _bonuses.clear();
  _bonuses = data._bonuses;  
}

// add proper manager tags mark-up
std::string ItemPart::what() const {
  std::string result;
  if (_manager != NULL) {
    result += _name;
    result += _description;
    result += convert_to_string<size_t>(_kind);
    result += convert_to_string<size_t>(_group);
    result += convert_to_string<size_t>(_rarity);
    result += convert_to_string<size_t>(_place);
    for (size_t i = 0; i < _cost.size(); ++i) {
      result += convert_to_string<size_t>(_cost[i]);
    }
    for (size_t i = 0; i < _bonuses.size(); ++i) {
      result += convert_to_string<ssize_t>(_bonuses[i]);
    }
  }
  return result;
}

// add proper manager tag mark-up
std::string ItemPart::short_what() const {
  std::string result;
  if (_manager != NULL) {
    result += _name;
    result += convert_to_string<size_t>(_rarity);
  }
  return result;
}

size_t ItemPart::update() {
  return RC_OK;
}

ItemPartTemplate ItemPart::save_data() {
  ItemPartTemplate data;
  data._own_id = _own_id;
  data._name.clear();
  data._name = _name;
  data._description.clear();
  data._description = _description;
  data._kind = _kind;
  data._group = _group;
  data._rarity = _rarity;
  data._place = _place;
  data._cost.clear();
  data._cost = _cost;
  data._bonuses.clear();
  data._bonuses = _bonuses;
  return data;
}
