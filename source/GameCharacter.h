#ifndef VIKINGS_GAME_CHARACTER_H
#define VIKINGS_GAME_CHARACTER_H

#include "LevelableObject.h"
#include "StorageEntities.h"

class GameCharacter: public LevelableObject {
  public:
    GameCharacter(const GameCharacterTemplate& data);
    virtual ~GameCharacter() {}
    ssize_t stat_points() const { return _stat_points; }
    size_t wounds() const { return _wounds; }
    size_t add_wounds(const size_t& amount = 1);
    size_t remove_wounds(const size_t& amount = 1);
    bool gender() const { return _gender; }
    size_t melee_skill() const;
    size_t ranged_skill() const;
    size_t defense() const;
    std::vector<size_t> experience() const { return _experience; }
    size_t experience(const size_t& index) { return _experience[index]; }
    std::vector<size_t> stats() const { return _stats; }
    size_t stats(const size_t& index) const { return _stats[index]; }
    std::string what() const;
    std::string short_what() const;
    std::string talk() const; // method for getting character replies on various situations (think about args, we shall somehow tell the character about the situation he/she'll talk about)
    size_t update();
    size_t increase_stat(const size_t& index, const size_t& shift = 1);
  protected:
    ssize_t _stat_points;
    size_t _wounds; // amount of damage TAKEN by the character. Healthy character has 0 wounds.
    bool _gender;
    std::vector<size_t> _experience;
    std::vector<size_t> _stats;
    
    size_t level_up();
    size_t wounds_cap() const;
};

#endif