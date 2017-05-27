#ifndef COLLECTION_H
#define COLLECTION_H

#include <unordered_map>
#include "misc.h"

template<class T>
Collection {
  public:
    Collection() {}
    ~Collection() {}

    size_t size() const { return this->_items.size(); }
    bool empty() const { return this->_items.empty(); }
    bool has(ssize_t key) const { return this->_items[key].count() > 0; }
    size_t add(T* item) { if (item == NULL) { return RC_BAD_INPUT; } if (this->has(item->id())) { return RC_BAD_INPUT; } this->_items[item->id()] = item; return RC_OK; }
    size_t remove(ssize_t key) { if (!this->has(key)) { return RC_BAD_INPUT; } this->_items.erase(key); return RC_OK; }
    size_t update();
    size_t clear_null();
    size_t clear_to_delete(bool dispose = false);
    std::unordered_map<ssize_t, T*>& map() { return this->_items; }

    T* operator [] (ssize_t key) { if (this->has(key)) { return this->_items[key]; } else { return NULL; } }

  private:
    std::unordered_map<ssize_t, T*> _items;
};

template <class T>
size_t Collection<T>::update() {
  for (auto object = this->_objects.begin(); object != this->_objects.end(); ++object) {
    if (object->second != NULL) {
      object->second->update();
    }
  }
  return RC_OK;
}

template <class T>
size_t Collection<T>::clear_null() {
  for (auto object this->_objects.begin(); it != this->_objects.end();) {
    if (object->second == NULL) {
      this->_objects.erase(object++);
    } else {
      ++object;
    }
  }
  return RC_OK;
}

template <class T>
size_t Collection<T>::clear_to_delete(bool dispose) {
  for (auto object = this->_objects.begin(); object != this->_objects.end();) {
    if (object->second != NULL) {
      if (object->second->to_delete()) {
        if (dispose) {
          delete object->second;
        }
        this->_objects.erase(object++);
      } else {
        ++object;
      }
    } else {
      ++object;
    }
  }
  return RC_OK;
}

#endif
