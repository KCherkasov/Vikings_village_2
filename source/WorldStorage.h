#ifndef WORLD_STORAGE_H
#define WORLD_STORAGE_H

#include <unordered_map>

#include "ItemPart.h"
#include "Item.h"
#include "GameCharacter.h"
#include "Battle.h"

#include "TemplateStorage.h"
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

    size_t make_item_part(ItemPart*& result, const size_t& group, const size_t& place, const size_t& rarity = IR_SIZE) const;
    size_t make_item_part(ItemPart*& result, const ItemPartTemplate& data) const;

    size_t make_item(Item*& result, const size_t& blueprint_index) const;
    size_t make_item(Item*& result, const ItemTemplate& data, std::unordered_map<ssize_t, GameEntity*>& pool) const;

    size_t make_character(GameCharacter*& result, const ssize_t& level = START_LEVEL) const;
    size_t make_character(GameCharacter*& result, const GameCharacterTemplate& data) const;

    size_t make_battle(Battle*& result, std::unordered_map<ssize_t, GameEntity*>& pool, const std::vector<ssize_t>& viking_ids, const std::vector<ssize_t>& enemy_ids) const;

    UITextStorage* dictionary() const { return const_cast<UITextStorage*>(&(this->_ui_dictionary)); }
    TagManager* manager(const size_t& index) const { if(index < this->_managers.size()) { return const_cast<TagManager*>(&(this->_managers[index])); } else { return NULL; } }

  private:
    TemplateStorage _templates;
    UITextStorage _ui_dictionary;
    std::vector<TagManager> _managers;

    size_t fill_managers();
};

#endif
