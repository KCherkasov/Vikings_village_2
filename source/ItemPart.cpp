#include "ItemPart.h"

ItemPart::ItemPart(const ItemPartTemplate& data): GameObject(data._own_id), _kind(data._kind), _group(data._group), _rarity(data._rarity), _place(data._place), _cost(data._cost), _bonuses(data._bonuses) {
  this->_name = data._name;
  this->_description =  data._description;
}

// add proper manager tags mark-up
std::string ItemPart::what() const {
  std::string result;
  if (this->_manager != NULL) {
    result += this->_manager->tag(IT_NAME);
    result += this->_name;
    result += this->_manager->tag(IT_NAME);
    result += this->_manager->tag(IT_DESCRIPTION);
    result += this->_description;
    result += this->_manager->tag(IT_DESCRIPTION);
    result += this->_manager->tag(IT_KIND);
    result += convert_to_string<size_t>(this->_kind);
    result += this->_manager->tag(IT_KIND);
    result += this->_manager->tag(IT_GROUP);
    result += convert_to_string<size_t>(this->_group);
    result += this->_manager->tag(IT_GROUP);
    result += this->_manager->tag(IT_RARITY);
    result += convert_to_string<size_t>(this->_rarity);
    result += this->_manager->tag(IT_RARITY);
    result += this->_manager->tag(IT_PLACE);
    result += convert_to_string<size_t>(this->_place);
    result += this->_manager->tag(IT_PLACE);
    for (size_t i = 0; i < _cost.size(); ++i) {
      result += this->_manager->tag(IT_COST);
      result += convert_to_string<size_t>(this->_cost[i]);
      result += this->_manager->tag(IT_COST);
    }
    for (size_t i = 0; i < _bonuses.size(); ++i) {
      result += this->_manager->tag(IT_BONUSES);
      result += convert_to_string<ssize_t>(this->_bonuses[i]);
      result += this->_manager->tag(IT_BONUSES);
    }
  }
  return result;
}

// add proper manager tag mark-up
std::string ItemPart::short_what() const {
  std::string result;
  if (_manager != NULL) {
    result += this->_manager->tag(IT_NAME);
    result += _name;
    result += this->_manager->tag(IT_NAME);
    result += this->_manager->tag(IT_RARITY);
    result += convert_to_string<size_t>(_rarity);
    result += this->_manager->tag(IT_RARITY);
  }
  return result;
}

size_t ItemPart::update() {
  return RC_OK;
}

ItemPartTemplate ItemPart::save_data() const {
  ItemPartTemplate data;
  data._own_id = this->_own_id;
  data._name.clear();
  data._name = this->_name;
  data._description.clear();
  data._description = this->_description;
  data._kind = this->_kind;
  data._group = this->_group;
  data._rarity = this->_rarity;
  data._place = this->_place;
  data._cost.clear();
  data._cost = this->_cost;
  data._bonuses.clear();
  data._bonuses = this->_bonuses;
  return data;
}
