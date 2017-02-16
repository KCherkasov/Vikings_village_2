#include "Item.h"

Item::Item(const ItemTemplate& data, const std::vector<GameObject*>& pool): GameObject(data._own_id) {
  _name = data._name;
  _description = data._description;
  _kind = data._kind;
  _rarity = data._rarity;
  _cost.clear();
  _cost = data._cost;
  for (size_t i = 0; i < data._parts.size(); ++i) {
    for (size_t j = 0; pool.size(); ++j) {
      if (pool[j] != NULL && data._parts[i] != FREE_ID) {
        if (pool[j]->id() == data._parts[i]) {
          _parts.push_back(dynamic_cast<ItemPart*>(pool[j]));
          break;
        }
      }
    }
  }
}

std::vector<ssize_t> Item::bonuses() const {
  std::vector<ssize_t> result;
  if (!_parts.empty()) {
    for (size_t i = 0; i < CS_SIZE; ++i) {
      result.push_back(SSIZE_T_DEFAULT_VALUE);
    }
    for (size_t i = 0; i < _parts.size(); ++i) {
      if (_parts[i] != NULL) {
        for (size_t j = 0; j < result.size(); ++j) {
          result[j] += _parts[i]->bonuses(j);
        }
      }
    }
  }
  return result;
}

ssize_t Item::bonuses(const size_t& index) const {
  ssize_t result = SSIZE_T_DEFAULT_VALUE;
  if (!_parts.empty() && index < CS_SIZE) {
    for (size_t i = 0; i < _parts.size(); ++i) {
      if (_parts[i] != NULL) {
        result += _parts[i]->bonuses(index);
      }
    }
  }
  return result;
}

std::vector<size_t> Item::cost() const {
  std::vector<size_t> result;
  if (!_parts.empty()) {
    for (size_t i = 0; i < RI_SIZE; ++i) {
      result.push_back(SIZE_T_DEFAULT_VALUE);
    }
    for (size_t i = 0; i < _parts.size(); ++i) {
      if (_parts[i] != NULL) {
        for (size_t j = 0; j < result.size(); ++j) {
          result[j] += _parts[i]->cost(j);
        }
      }
    }
  }
  return result;
}

size_t Item::cost(const size_t& index) const {
  size_t result = SIZE_T_DEFAULT_VALUE;
  if (!_parts.empty() && index < RI_SIZE) {
    for (size_t i = 0; i < _parts.size(); ++i) {
      if (_parts[i] != NULL) {
        result += _parts[i]->cost(index);
      }
    }
  }
  return result;
}

std::string Item::what() const {
  std::string result;
  if (_manager != NULL) {
    
  }
  return result;
}

std::string Item::short_what() const {
  std::string result;
  if (_manager != NULL) {
    
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
  data._parts.clear();
  for (size_t i = 0; i < _parts.size(); ++i) {
    data._parts.push_back(FREE_ID);
    if (_parts[i] != NULL) {
      data._parts[data._parts.size() - 1] = _parts[i]->id();
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
