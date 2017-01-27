#include <iostream>

#include "UITextStorage.h"

ssize_t main() {
  UITextStorage storage;
  std::string db_name("UITexts.db");
  storage.fill_storage(db_name);
  for (size_t i = 0; i < storage.character_field_names_count(); ++i) {
    std::cout << i << " " << storage.character_field_name(i) << std::endl;
  }
  std::cout << std::endl;
  for (size_t i = 0; i < storage.stat_names_count(); ++i) {
    std::cout << i << " " << storage.stat_name(i) << std::endl;
  }
  storage.clear_storage();
  return 0;
}
