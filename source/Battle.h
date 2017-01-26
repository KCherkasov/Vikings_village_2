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
};

#endif