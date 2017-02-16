#include "ItemPart.h"

ItemPart::ItemPart(const ItemPartTemplate& data): GamObject(data._own_id) {
  _name = data._name;
  _description =  data._description;
  _kind = data._kind;
  _rarity = data._rarity;
  _place = data._place;
  _cost.clear();
  _cost = data._cost;
  _bonuses.clear();
  _bonuses = data._bonuses;  
}

std::string ItemPart::what() const {
  std::string result;
  if (_manager != NULL) {
    
  }
  return result;
}

std::string ItemPart::short_what() const {
  std::string result;
  if (_manager != NULL) {
    
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
  data._rarity = _rarity;
  data._place = _place;
  data._cost.clear();
  data._cost = _cost;
  data._bonuses.clear();
  data._bonuses = _bonuses;
  return data;
}
