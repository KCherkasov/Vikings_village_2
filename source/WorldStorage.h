#ifndef WORLD_STORAGE_H
#define WORLD_STORAGE_H

#include "TemplateStorage.h"
#include "GameCharacter.h"

#include "UITextStorage.h"

#include "TagManager.h"

class WorldStorage {
  public:
    WorldStorage() {}
    WorldStorage(const std::string& templates_db_name, const std::string& ui_texts_db_name);
    ~WorldStorage() {}
    
    bool is_filled() const { return _templates.is_filled() && _ui_dictionary.is_filled() && _manager.is_filled(); }
    size_t fill(const std::string& templates_db_name, const std::string& ui_texts_db_name);
    size_t clear();
    
    size_t make_character(GameCharacter*& result, const ssize_t& level = START_LEVEL) const;
    size_t make_character(GameCharacter*& result, const GameCharacterTemplate& data) const;
    
    UITextStorage* dictionary() const { return const_cast<UITextStorage*>(&_ui_dictionary); }
    TagManager* manager() const { return const_cast<TagManager*>(&_manager); }
    
  private:
    TemplateStorage _templates;
    UITextStorage _ui_dictionary;
    // Need to spawn several managers, each responsible for different scopes. Maybe shall spawn a vector of them and add an enum to designate them in misc.h
    TagManager _manager;
};

#endif
