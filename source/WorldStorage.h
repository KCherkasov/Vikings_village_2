#ifndef WORLD_STORAGE_H
#define WORLD_STORAGE_H

#include "TemplateStorage.h"
#include "GameCharacter.h"
#include "Battle.h"

#include "UITextStorage.h"

#include "TagManager.h"

class WorldStorage {
  public:
    WorldStorage() {}
    WorldStorage(const std::string& templates_db_name, const std::string& ui_texts_db_name);
    ~WorldStorage() {}
    
    bool is_filled() const;
    size_t fill(const std::string& templates_db_name, const std::string& ui_texts_db_name);
    size_t clear();
    
    size_t make_character(GameCharacter*& result, const ssize_t& level = START_LEVEL) const;
    size_t make_character(GameCharacter*& result, const GameCharacterTemplate& data) const;
    
    size_t make_battle(Battle*& result, const std::vector<GameCharacter*>& character_pool, const std::vector<ssize_t>& viking_ids, const std::vector<ssize_t>& enemy_ids) const;
    
    UITextStorage* dictionary() const { return const_cast<UITextStorage*>(&_ui_dictionary); }
    TagManager* manager(const size_t& index) const { if(index < _managers.size()) { return const_cast<TagManager*>(&_managers[index]); } else { return NULL; } }
    
  private:
    TemplateStorage _templates;
    UITextStorage _ui_dictionary;
    // Need to spawn several managers, each responsible for different scopes. Maybe shall spawn a vector of them and add an enum to designate them in misc.h
    std::vector<TagManager> _managers;
    
    size_t fill_managers();
};

#endif
