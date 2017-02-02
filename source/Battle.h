#ifndef VIKINGS_BATTLE_H
#define VIKINGS_BATTLE_H

#include "GameCharacter.h"

class Battle: public GameEntity {
  public:
    Battle(const BattleTemplate& data, const std::vector<GameCharacter*>& character_pool);
    virtual ~Battle() {}
    std::string what() const;
    std::string short_what() const;
    size_t update();
  protected:
    size_t _turn;
    std::vector<GameCharacter*> _vikings;
    std::vector<GameCharacter*> _enemies;
    
    GameCharacter* get_by_id(const ssize_t& id, const std::vector<GameCharacter*>& character_pool);
    size_t make_pairs(std::vector<std::vector<size_t> >& pairs) const;
    size_t clean_dead(std::vector<GameCharacter*>& character_pool);
    size_t cleanup();
};

#endif