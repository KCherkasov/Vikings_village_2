#include <iostream>

#include "UITextStorage.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
  UITextStorage storage;
  std::string db_name("UITexts.db");
  std::cout << "loading data from " << db_name << " database...";
  storage.fill_storage(db_name);
  std::cout << "success" << std::endl;
  std::cout << std::endl << "character_field_names table contents:" << std::endl << std::endl;
  for (size_t i = 0; i < storage.character_field_names_count(); ++i) {
    std::cout << i+1 << " " << storage.character_field_name(i) << std::endl;
  }
  std::cout << std::endl << "stat_names table contents:" << std::endl << std::endl;
  for (size_t i = 0; i < storage.stat_names_count(); ++i) {
    std::cout << i+1 << " " << storage.stat_name(i) << std::endl;
  }
  storage.clear_storage();
  return 0;
}
