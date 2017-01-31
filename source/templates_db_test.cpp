#include <iostream>

#include "WorldStorage.h"

int main(int argc, char** argv) {
  const size_t CHARACTERS_TO_CREATE = 15;
  seed();
  std::string templates_db_name("Templates.db");
  std::string ui_db_name("UITexts.db");
  std::cout << "filling the storage using " << templates_db_name << " and " << ui_db_name << " databases...";
  WorldStorage storage;
  storage.fill(templates_db_name, ui_db_name);
  if (storage.is_filled()) {
    std::cout << "success" << std::endl;
  } else {
    std::cout << "failure. finishing the test" << std::endl;
    return 0;
  }
  std::cout << "\ncharacter creation test:\n\n";
  for (size_t i = 0; i < CHARACTERS_TO_CREATE; ++i) {
    GameCharacter* character = NULL;
    storage.make_character(character, roll_dice(MAX_LEVEL) + START_LEVEL);
    std::cout << "character " << i+1 << ": " << character->what() << std::endl << std::endl;
    delete character;
  }
  storage.clear();
  return 0;
}
