#ifndef VIKINGS_WORLD_H
#define VIKINGS_WORLD_H

#include "WorldStorage.h"

class World {
  public:
    World() {}
    ~World() {}
    size_t fill_storage(const std::string& templates_db_name, const std::string& ui_db_name);
    size_t new_game(const std::string& player_name);
    size_t load_game(const std::string& fname); // think about args there
    size_t save_game(const std::string& fname) const;
    size_t update();
    
    std::string character_what(const size_t& index) const;
    std::string character_what(const ssize_t& id) const;
    
    std::string character_short_what(const size_t& index) const;
    std::string character_short_what(const ssize_t& id) const;
    
  private:
    WorldStorage _storage;
    
    size_t cleanup();
    size_t save_data() const; // prepares data for save
};

#endif
