#ifndef VIKINGS_TEXT_STORAGE_H
#define VIKINGS_TEXT_STORAGE_H

#include "misc.h"
#include "BaseStorage.h"

class TextStorage: public BaseStorage {
  public:
    TextStorage(): BaseStorage() {}
    virtual ~TextStorage() {}
    size_t fill_storage(const std::string& db_name);
    size_t clear_storage();
  private:
};

#endif