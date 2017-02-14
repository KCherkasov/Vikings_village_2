#ifndef VIKINGS_TEMPLATE_STORAGE_H
#define VIKINGS_TEMPLATE_STORAGE_H

#include "StorageEntities.h"
#include "BaseStorage.h"

class TemplateStorage: public BaseStorage {
  public:
    TemplateStorage(): BaseStorage() {}
    virtual ~TemplateStorage() {}
    
    bool is_filled() const;
    size_t fill_storage(const std::string& db_name);
    size_t clear_storage();
    
    GameCharacterTemplate make_character_template(const ssize_t& level = START_LEVEL) const;
    GameCharacterTemplate make_character_template(const bool& gender, const ssize_t& level = START_LEVEL) const;
    
    ItemTemplate make_item_template(const size_t& rarity = IR_COMMON) const;
  
  private:
    std::vector<std::string> _male_nameparts_begin;
    std::vector<std::string> _male_nameparts_end;

    std::vector<ItemTemplate> _item_templates;

    std::vector<std::string> _surname_suffixes;
    
    ssize_t read_male_names(sqlite3*& connection);
    ssize_t read_surname_suffixes(sqlite3*& connection);
    
    ssize_t read_item_part_generals(sqlite3*& connection);
    ssize_t read_item_part_costs(sqlite3*& connection);
    ssize_t read_item_part_bonuses(sqlite3*& connection);
    
    ssize_t read_item_parts(sqlite3*& connection);
    
    std::string male_name() const;
    std::string female_name() const;
    std::string surname(const bool& gender) const;
};

#endif
