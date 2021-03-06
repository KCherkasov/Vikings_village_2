#ifndef VIKINGS_GAME_CHARACTER_H
#define VIKINGS_GAME_CHARACTER_H

#include "LevelableObject.h"
#include "StorageEntities.h"
#include "Inventory.h"

class GameCharacter: public LevelableObject {
  public:
    GameCharacter(const GameCharacterTemplate& data);
    virtual ~GameCharacter() {}
    ssize_t stat_points() const { return _stat_points; }
    size_t wounds() const { return _wounds; }
    size_t wounds_cap() const;
    size_t add_wounds(const size_t& amount = 1);
    size_t remove_wounds(const size_t& amount = 1);
    bool gender() const { return _gender; }
    ssize_t melee_skill() const;
    ssize_t ranged_skill() const;
    ssize_t defense() const;
    std::vector<size_t> experience() const { return _experience; }
    size_t experience(const size_t& index) { return _experience[index]; }
    std::vector<ssize_t> stats() const { return _stats; }
    ssize_t stats(const ssize_t& index) const { return _stats[index]; }
    std::string what() const;
    std::string short_what() const;
    std::string talk() const; // method for getting character replies on various situations (think about args, we shall somehow tell the character about the situation he/she'll talk about)
    size_t update();
    GameCharacterTemplate save_data() const;
    size_t increase_stat(const size_t& index, const ssize_t& shift = 1);
    size_t increase_experience(const size_t& amount) { _experience[PI_CURRENT] += amount; return RC_OK; }
  protected:
    ssize_t _stat_points;
    size_t _wounds; // amount of damage TAKEN by the character. Healthy character has 0 wounds.
    bool _gender;
    std::vector<size_t> _experience;
    std::vector<ssize_t> _stats;
    
    size_t level_up();
};

#endif
