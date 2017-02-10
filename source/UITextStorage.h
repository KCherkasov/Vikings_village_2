#ifndef VIKINGS_UI_TEXT_STORAGE_H
#define VIKINGS_UI_TEXT_STORAGE_H

#include "misc.h"
#include "BaseStorage.h"

enum CharacterFieldnames { CF_ID, CF_NAME, CF_DESCRIPTION, CF_LEVEL, CF_STAT_POINTS, CF_WOUNDS, CF_GENDER, CF_EXPERIENCE, CF_STATS, CF_SIZE };

class UITextStorage: public BaseStorage {
  public:
    UITextStorage(): BaseStorage() {}
    virtual ~UITextStorage() {}
    
    bool is_filled() const;
    size_t fill_storage(const std::string& db_name);
    size_t clear_storage();
    
    size_t character_field_names_count() const { return _character_field_names.size(); }
    std::string character_field_name(const size_t& index) { return _character_field_names[index]; }
    size_t stat_names_count() const { return _stat_names.size(); }
    std::string stat_name(const size_t& index) const { return _stat_names[index]; }
    size_t gender_names_count() const { return _gender_names.size(); }
    std::string gender_name(const size_t& index) const { return _gender_names[index]; }
    size_t character_tags_count() const { return _character_manager_tags.size(); }
    std::string character_tag(const size_t& index) const { return _character_manager_tags[index]; }
    size_t battle_tags_count() const { return _battle_manager_tags.size(); }
    std::string battle_tag(const size_t& index) const { return _battle_manager_tags[index]; }
    size_t ui_tags_count() const { return _ui_manager_tags.size(); }
    std::string ui_tag(const size_t& index) const { return _ui_manager_tags[index]; }
    size_t melee_attempts_count() const { return _melee_attack_attempts.size(); }
    std::string melee_attempt(const size_t& index) const { return _melee_attack_attempts[index]; }
    size_t ranged_attempts_count() const { return _ranged_attack_attempts.size(); }
    std::string ranged_attempt(const size_t& index) const { return _ranged_attack_attempts[index]; }
    size_t melee_sucess_count() const { return _melee_attack_success.size(); }
    std::string melee_success(const size_t& index) const { return _melee_attack_success[index]; }
    size_t ranged_success_count() const { return _ranged_attack_success.size(); }
    std::string ranged_success(const size_t& index) const { return _ranged_attack_success[index]; }
    size_t melee_failures_count() const { return _melee_attack_failure.size(); }
    std::string melee_failure(const size_t& index) const { return _melee_attack_failure[index]; }
    size_t ranged_failures_count() const { return _ranged_attack_failure.size(); }
    std::string ranged_failure(const size_t& index) const { return _ranged_attack_failure[index]; }
    size_t wound_made_count() const { return _wound_made.size(); }
    std::string wound_made(const size_t& index) const { return _wound_made[index]; }
    size_t wound_avoid_count() const { return _wound_avoid.size(); }
    std::string wound_avoid(const size_t& index) const { return _wound_avoid[index]; }
    size_t clear_manager_tags() { _character_manager_tags.clear(); _battle_manager_tags.clear(); _ui_manager_tags.clear(); return RC_OK; }
  private:
    std::vector<std::string> _character_field_names;
    std::vector<std::string> _stat_names;
    std::vector<std::string> _gender_names;
    
    std::vector<std::string> _character_manager_tags;
    std::vector<std::string> _battle_manager_tags;
    std::vector<std::string> _ui_manager_tags;

    std::vector<std::string> _melee_attack_attempts;
    std::vector<std::string> _ranged_attack_attempts;
    std::vector<std::string> _melee_attack_success;
    std::vector<std::string> _ranged_attack_success;
    std::vector<std::string> _melee_attack_failure;
    std::vector<std::string> _ranged_attack_failure;
    std::vector<std::string> _wound_made;
    std::vector<std::string> _wound_avoid;
        
    ssize_t read_character_field_names(sqlite3*& connection);
    ssize_t read_stat_names(sqlite3*& connection);
    ssize_t read_gender_names(sqlite3*& connection);

    ssize_t read_character_tags(sqlite3*& connection);
    ssize_t read_battle_tags(sqlite3*& connection);
    ssize_t read_ui_tags(sqlite3*& connection);
    ssize_t read_manager_tags(sqlite3*& connection);
    
    ssize_t read_battle_log_parts(sqlite3*& connection);
};


#endif
