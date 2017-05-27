#include "Item.h"

Item::Item(const ItemTemplate& data, std::unordered_map<ssize_t, GameEntity*>& pool): GameObject(data._own_id), _kind(data._kind) {
  this->_name = data._name;
  this->_description = data._description;
  for (size_t i = 0; i < data._parts.size(); ++i) {
    this->_parts.push_back(dynamic_cast<ItemPart*>(pool[data._parts[i]]));
  }
}

Item::~Item() {
  for (size_t i = 0; i < _parts.size(); ++i) {
    this->_parts[i] = NULL;
  }
}

std::vector<ssize_t> Item::bonuses() const {
  std::vector<ssize_t> result;
  if (!this->_parts.empty()) {
    for (size_t i = 0; i < CS_SIZE; ++i) {
      result.push_back(SSIZE_T_DEFAULT_VALUE);
    }
    for (size_t i = 0; i < this->_parts.size(); ++i) {
      if (this->_parts[i] != NULL) {
        for (size_t j = 0; j < result.size(); ++j) {
          result[j] += this->_parts[i]->bonuses(j);
        }
      }
    }
  }
  return result;
}

ssize_t Item::bonuses(const size_t& index) const {
  ssize_t result = SSIZE_T_DEFAULT_VALUE;
  if (!this->_parts.empty() && index < CS_SIZE) {
    for (size_t i = 0; i < this->_parts.size(); ++i) {
      if (this->_parts[i] != NULL) {
        result += this->_parts[i]->bonuses(index);
      }
    }
  }
  return result;
}

std::vector<size_t> Item::cost() const {
  std::vector<size_t> result;
  if (!this->_parts.empty()) {
    for (size_t i = 0; i < RI_SIZE; ++i) {
      result.push_back(SIZE_T_DEFAULT_VALUE);
    }
    for (size_t i = 0; i < this->_parts.size(); ++i) {
      if (this->_parts[i] != NULL) {
        for (size_t j = 0; j < result.size(); ++j) {
          result[j] += this->_parts[i]->cost(j);
        }
      }
    }
  }
  return result;
}

size_t Item::cost(const size_t& index) const {
  size_t result = SIZE_T_DEFAULT_VALUE;
  if (!this->_parts.empty() && index < RI_SIZE) {
    for (size_t i = 0; i < this->_parts.size(); ++i) {
      if (this->_parts[i] != NULL) {
        result += this->_parts[i]->cost(index);
      }
    }
  }
  return result;
}

size_t Item::rarity() const {
  size_t rarity = IR_TRASH;
  for (size_t i = 0; i < this->_parts.size(); ++i) {
    if (this->_parts[i] != NULL) {
      rarity += this->_parts[i]->rarity();
    }
  }
  rarity /= this->_parts.size();
  return rarity;
}

std::string Item::what() const {
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
    result += convert_to_string<size_t>(this->rarity());
    for (size_t i = 0; i < RI_SIZE; ++i) {
      result += convert_to_string<size_t>(this->cost(i));
    }
    for (size_t i = 0; i < CS_SIZE; ++i) {
      result += convert_to_string<ssize_t>(this->bonuses(i));
    }
    for (size_t i = 0; i < this->_parts.size(); ++i) {
      if (this->_parts[i] != NULL) {
        result += this->_parts[i]->short_what();
      }
    }
  }
  return result;
}

std::string Item::short_what() const {
  std::string result;
  if (_manager != NULL) {
    result += _name;
    result += convert_to_string<size_t>(_kind);
    result += convert_to_string<size_t>(rarity());
    for (size_t i = 0; i < CS_SIZE; ++i) {
      result += convert_to_string<ssize_t>(bonuses(i));
    }
  }
  return result;
}

size_t Item::update() {
  return RC_OK;
}

ItemTemplate Item::save_data() const {
  ItemTemplate data;
  data._own_id = this->_own_id;
  data._name.clear();
  data._name = this->_name;
  data._description.clear();
  data._description = this->_description;
  data._kind = this->_kind;
  data._parts.clear();
  for (size_t i = 0; i < this->_parts.size(); ++i) {
    data._parts.push_back(FREE_ID);
    if (this->_parts[i] != NULL) {
      data._parts[data._parts.size() - 1] = this->_parts[i]->id();
    }
  }
  return data;
}

size_t Item::dispose() {
  _to_delete = true;
  for (size_t i = 0; i < _parts.size(); ++i) {
    if (_parts[i] != NULL) {
      _parts[i]->dispose();
    }
  }
  return RC_OK;
}
