#ifndef VIKINGS_UI_TEXT_STORAGE_H
#define VIKINGS_UI_TEXT_STORAGE_H

#include "misc.h"
#include "BaseStorage.h"

enum CharacterFieldnames { CF_ID, CF_NAME, CF_DESCRIPTION, CF_LEVEL, CF_STAT_POINTS, CF_WOUNDS, CF_GENDER, CF_EXPERIENCE, CF_STATS, CF_SIZE };

class UITextStorage: public BaseStorage {
  public:
    UITextStorage(): BaseStorage() {}
    virtual ~UITextStorage() {}
    size_t fill_storage(const std::string& db_name);
    size_t clear_storage();
    size_t character_field_names_count() const { return _character_field_names.size(); }
    std::string character_field_name(const size_t& index) { return _character_field_names[index]; }
    size_t stat_names_count() const { return _stat_names.size(); }
    std::string stat_name(const size_t& index) const { return _stat_names[index]; }
  private:
    std::vector<std::string> _character_field_names;
    std::vector<std::string> _stat_names;
    
    ssize_t read_character_field_names(sqlite3*& connection);
    ssize_t read_stat_names(sqlite3*& connection);
};


#endif
