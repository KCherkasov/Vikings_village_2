#ifndef VIKINGS_BATTLE_H
#define VIKINGS_BATTLE_H

#include "GameCharacter.h"

class Battle: public GameEntity {
  public:
    Battle(const BattleTemplate& data, const std::vector<GameCharacter*>& character_pool);
    virtual ~Battle() {}
    std::string what() const;
    std::string short_what() const;
    std::string log() const { return _log; }
    size_t update();
  protected:
    size_t _turn;
    std::vector<GameCharacter*> _vikings;
    std::vector<GameCharacter*> _enemies;
    std::string _log;
    
    GameCharacter* get_by_id(const ssize_t& id, const std::vector<GameCharacter*>& character_pool);
    
    size_t random_character_index(const std::vector<GameCharacter*>& character_pool, const std::vector<size_t>& keys) const;
    size_t make_pairs(std::vector<std::vector<size_t> >& pairs) const;
    
    size_t clean_dead(std::vector<GameCharacter*>& character_pool);
    size_t cleanup();
    size_t update_fighters();
    
    size_t write_log_names(const size_t& viking_index, const size_t& enemy_index);
    size_t write_log_entry(const size_t& viking_index, const size_t& enemy_index, const size_t& stat_id, const size_t& is_hit, const size_t& is_wounded, const bool& viking_strikes);
    
    size_t strike(const size_t& viking_index, const size_t& enemy_index, const size_t& stat_id, const bool& viking_strikes);
    size_t duel(const size_t& viking_index, const size_t& local_index);
    size_t fight_round();
    
    bool is_victory() const { return _enemies.empty(); }
    bool is_defeat() const { return _vikings.empty(); }
};

#endif