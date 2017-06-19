#include "Battle.h"

size_t Battle::random_character_index(const std::vector<GameCharacter*>& character_pool, const std::vector<size_t>& keys) const {
  while(true) {
    if (character_pool.empty()) {
      return SIZE_T_DEFAULT_VALUE;
    }
    size_t index = roll_dice(character_pool.size());
    if (!vector_has(keys, index) && character_pool[index] != NULL) {
      if (!character_pool[index]->to_delete()) {
        return index;
      }
    }
  }
}

size_t Battle::make_pairs(std::vector<size_t>& vikings_queue, std::vector<size_t>& enemies_queue) const {
  vikings_queue.clear();
  enemies_queue.clear();
  size_t pairs_count = std::min(this->_vikings.size(), this->_enemies.size());
  for (size_t i = 0; i < pairs_count; ++i) {
    vikings_queue.push_back(this->random_character_index(this->_vikings, vikings_queue));
    enemies_queue.push_back(this->random_character_index(this->_enemies, enemies_queue));
  }
  size_t extra_pairs = std::max(this->_vikings.size(), this->_enemies.size()) - pairs_count;
  for (size_t i = 0; i < extra_pairs; ++i) {
    if (this->_vikings.size() < this->_enemies.size()) {
      vikings_queue.push_back(roll_dice(this->_vikings.size()));
      enemies_queue.push_back(this->random_character_index(this->_enemies, enemies_queue));
    } else {
      vikings_queue.push_back(random_character_index(this->_vikings, vikings_queue));
      enemies_queue.push_back(roll_dice(this->_enemies.size()));
    }
  }
  return RC_OK;
}

size_t Battle::clean_dead(std::vector<GameCharacter*>& character_pool) {
  size_t j = SIZE_T_DEFAULT_VALUE;
  while (!character_pool.empty() && j < character_pool.size()) {
    if (character_pool[j] != NULL) {
      if (character_pool[j]->to_delete()) {
        if (this->_turn > START_TURN) {
          this->_log += character_pool[j]->name();
          this->_log.append(" ");
          this->_log += this->_manager->tag(BT_DEATH);
          this->_log.append(";\n");
        }
        character_pool.erase(character_pool.begin() + j);
      } else {
        ++j;
      }
    } else {
      character_pool.erase(character_pool.begin() + j);
    }
  }
  if (this->_turn > START_TURN) {
    this->_log.append("\n");
  }
  return RC_OK;
}

size_t Battle::cleanup() {
  if (this->_turn > START_TURN) {
    this->_log.append("Observing the battlefield after ");
    this->_log += convert_to_string<size_t>(this->_turn - 1);
    this->_log.append(" round of fight:\n");
    this->_log.append("Vikings squad:\n");
    clean_dead(this->_vikings);
    this->_log.append("Enemies squad:\n");
    clean_dead(this->_enemies);
  }
  return RC_OK;
}

size_t Battle::update_fighters() {
  for (size_t i = 0; i < this->_vikings.size(); ++i) {
    if (this->_vikings[i] != NULL) {
      this->_vikings[i]->update();
    }
  }
  for (size_t i = 0; i < this->_enemies.size(); ++i) {
    if (this->_enemies[i] != NULL) {
      this->_enemies[i]->update();
    }
  }
  return RC_OK;
}

size_t Battle::write_log_entry(const size_t& viking_index, const size_t& enemy_index) {
  if (viking_index >= this->_vikings.size() || enemy_index >= this->_enemies.size()) {
    return RC_BAD_INDEX;
  }
  if (this->_vikings[viking_index] == NULL || this->_enemies[enemy_index] == NULL) {
    return RC_BAD_INPUT;
  }
  this->_log += this->_vikings[viking_index]->name();
  this->_log.append(" versus ");
  this->_log += this->_enemies[enemy_index]->name();
  this->_log.append(":\n");
  return RC_OK;
}

size_t Battle::write_log_entry(const size_t& viking_index, const size_t& enemy_index, const size_t& stat_id, const size_t& is_hit, const size_t& is_wounded, const bool& viking_strikes) {
  if (viking_index >= this->_vikings.size() || enemy_index >= this->_enemies.size() || stat_id > CS_DEFENSE) {
    return RC_BAD_INDEX;
  }
  if (this->_vikings[viking_index] == NULL || this->_enemies[enemy_index] == NULL || this->_manager == NULL) {
    return RC_BAD_INPUT;
  }
  if (viking_strikes) {
    this->_log += this->_vikings[viking_index]->name();
  } else {
    this->_log += this->_enemies[enemy_index]->name();
  }
  this->_log.append(" ");
  if (stat_id == CS_MELEE) {
    this->_log += this->_manager->tag(BT_MELEE_ATTACK_ATTEMPT);
  }
  if (stat_id == CS_RANGED) {
    this->_log += this->_manager->tag(BT_RANGED_ATTACK_ATTEMPT);
  }
  this->_log.append(" ");
  if (viking_strikes) {
    this->_log += this->_enemies[enemy_index]->name();
  } else {
    this->_log += this->_vikings[viking_index]->name();
  }
  this->_log.append(".\n");
  if (viking_strikes) {
    this->_log += this->_vikings[viking_index]->name();
    this->_log.append(" ");
    if (is_hit == TO_FIRST_WON) {
      if (stat_id == CS_MELEE) {
        this->_log += this->_manager->tag(BT_MELEE_ATTACK_SUCCESS);
      }
      if (stat_id == CS_RANGED) {
        this->_log += this->_manager->tag(BT_RANGED_ATTACK_SUCCESS);
      }
      this->_log.append(" ");
      this->_log += this->_enemies[enemy_index]->name();
      this->_log.append(".\n");
      this->_log += this->_enemies[enemy_index]->name();
      this->_log.append(" ");
      if (is_wounded == TO_FIRST_WON) {
        this->_log += this->_manager->tag(BT_WOUND_MADE);
      } else {
        this->_log += this->_manager->tag(BT_WOUND_AVOID);
      }
    } else {
      if (stat_id == CS_MELEE) {
        this->_log += this->_manager->tag(BT_MELEE_ATTACK_FAILURE);
      }
      if (stat_id == CS_RANGED) {
        this->_log += this->_manager->tag(BT_RANGED_ATTACK_FAILURE);
      }
      this->_log.append(" ");
      this->_log += this->_enemies[enemy_index]->name();
    }
  } else {
    this->_log += this->_enemies[enemy_index]->name();
    this->_log.append(" ");
    if (is_hit == TO_FIRST_WON) {
      if (stat_id == CS_MELEE) {
        this->_log += this->_manager->tag(BT_MELEE_ATTACK_FAILURE);
      }
      if (stat_id == CS_RANGED) {
        this->_log += this->_manager->tag(BT_RANGED_ATTACK_FAILURE);
      }
      this->_log.append(" ");
      this->_log += this->_vikings[viking_index]->name();
    } else {
      if (stat_id == CS_MELEE) {
        this->_log += this->_manager->tag(BT_MELEE_ATTACK_SUCCESS);
      }
      if (stat_id == CS_RANGED) {
        this->_log += this->_manager->tag(BT_RANGED_ATTACK_SUCCESS);
      }
      this->_log.append(" ");
      this->_log += this->_vikings[viking_index]->name();
      this->_log.append(".\n");
      this->_log += this->_vikings[viking_index]->name();
      this->_log.append(" ");
      if (is_wounded == TO_FIRST_WON) {
        this->_log += this->_manager->tag(BT_WOUND_AVOID);
      } else {
        this->_log += this->_manager->tag(BT_WOUND_MADE);
      }
    }
  }
  this->_log.append(".\n\n");
  return RC_OK;
}

size_t Battle::strike(const size_t& viking_index, const size_t& enemy_index, const size_t& stat_id, const bool& viking_strikes) {
  // strike has two stages - hit and wound.
  // First is the comparative test if attacker hitted the defender.
  // If it's successful, then we test the defender on being wounded by that hit.
  // If defender is wounded, he takes one wound.

  // stat_id argument added for future usage to process ranged fight through this method too.
  size_t is_hit = TO_DRAW;
  size_t is_wounded = TO_DRAW;
  //defender stat_indices. Vary depend on stat_id value (see comments below)
  size_t defender_hit_stat = CS_SIZE;
  size_t defender_wound_stat = CS_SIZE;
  // for melee fight it is: hit - attacker's melee vs defender's melee; wound - attacker's melee vs defender's defense
  if (stat_id == CS_MELEE) {
    defender_hit_stat = CS_MELEE;
    defender_wound_stat = CS_DEFENSE;
  }
  // for ranged fight: hit - attacker's ranged vs defender's defense; wound - the same.
  if (stat_id == CS_RANGED) {
    defender_hit_stat = CS_DEFENSE;
    defender_wound_stat = CS_DEFENSE;
  }
  if (viking_strikes) {
    is_wounded = TO_SECOND_WON;
  } else {
    is_wounded = TO_FIRST_WON;
  }
  if (viking_strikes) {
    is_hit = stats_test(this->_vikings[viking_index]->stats(stat_id), this->_enemies[enemy_index]->stats(defender_hit_stat), viking_strikes);
  } else {
    is_hit = stats_test(this->_vikings[viking_index]->stats(defender_hit_stat), this->_enemies[enemy_index]->stats(stat_id), viking_strikes);
  }
  if (is_hit != is_wounded) {
    if (viking_strikes) {
      is_wounded = stats_test(this->_vikings[viking_index]->stats(stat_id), this->_enemies[enemy_index]->stats(defender_wound_stat), viking_strikes);
    } else {
      is_wounded = stats_test(this->_vikings[viking_index]->stats(defender_wound_stat), this->_enemies[enemy_index]->stats(stat_id), viking_strikes);
    }
    if (is_hit == is_wounded) {
      if (viking_strikes) {
        this->_enemies[enemy_index]->add_wounds();
      } else {
        this->_vikings[viking_index]->add_wounds();
      }
    }
  }
  write_log_entry(viking_index, enemy_index, stat_id, is_hit, is_wounded, viking_strikes);
  return RC_OK;
}

size_t Battle::duel(const size_t& viking_index, const size_t& enemy_index) {
  if (viking_index >= this->_vikings.size() || enemy_index >= this->_enemies.size()) {
    return RC_BAD_INDEX;
  }
  if (this->_vikings[viking_index] == NULL || this->_enemies[enemy_index] == NULL) {
    return RC_BAD_INPUT;
  }
  if (this->_vikings[viking_index]->to_delete() || this->_enemies[enemy_index]->to_delete()) {
    return RC_BAD_INPUT;
  }
  // following code possible needs further revision and modification in terms of fight mechanics tuning
  bool viking_strikes = roll_dice() % 2 == 0; // this shall be changed to an initiative test when this stat'll be added to GameCharacter class
  // during the duel, both warriors make their strike (if they're not dead)
  bool viking_alive = this->_vikings[viking_index]->wounds() <= this->_vikings[viking_index]->wounds_cap();
  bool enemy_alive = this->_enemies[enemy_index]->wounds() <= this->_enemies[enemy_index]->wounds_cap();
  write_log_entry(viking_index, enemy_index);
  strike(viking_index, enemy_index, CS_MELEE, viking_strikes);
  strike(viking_index, enemy_index, CS_MELEE, !viking_strikes);
  this->_log.append("\n");
  return RC_OK;
}

size_t Battle::fight_round() {
  this->_log.append("\n\n");
  this->_log += this->_manager->tag(BT_TURN);
  this->_log.append(" ");
  this->_log += convert_to_string<size_t>(this->_turn);
  this->_log.append(":\n");
  this->_log += this->_manager->tag(BT_VIKINGS_COUNT);
  this->_log.append(": ");
  this->_log += convert_to_string<size_t>(this->_vikings.size());
  this->_log.append("; ");
  this->_log += this->_manager->tag(BT_ENEMIES_COUNT);
  this->_log.append(": ");
  this->_log += convert_to_string<size_t>(this->_enemies.size());
  this->_log.append(".\n\n");
  std::vector<size_t> vikings_queue;
  std::vector<size_t> enemies_queue;
  make_pairs(vikings_queue, enemies_queue);
  for (size_t i = 0; i < vikings_queue.size(); ++i) {
    duel(vikings_queue[i], enemies_queue[i]);
    this->_log.append("\n");
  }
  ++this->_turn;
  return RC_OK;
}

std::vector<size_t> Battle::generate_reward() const {
  std::vector<size_t> result;
  seed();
  for (size_t i = 0; i < RI_SIZE; ++i) {
    result.push_back(SIZE_T_DEFAULT_VALUE);
    result[result.size() - 1] += roll_dice(PERCENT_CAP / 4);
  }
  return result;
}

Battle::Battle(const BattleTemplate& data, std::unordered_map<ssize_t, GameEntity*>& pool): GameEntity(data._own_id) {
  this->_turn = START_TURN;
  this->_vikings.clear();
  for (size_t i = 0; i < data._vikings.size(); ++i) {
    GameCharacter* to_add = dynamic_cast<GameCharacter*>(pool[data._vikings[i]]);
    if (to_add != NULL) {
      this->_vikings.push_back(to_add);
    }
  }
  this->_enemies.clear();
  for (size_t i = 0; i < data._enemies.size(); ++i) {
    GameCharacter* to_add = dynamic_cast<GameCharacter*>(pool[data._enemies[i]]);
    if (to_add != NULL) {
      this->_enemies.push_back(to_add);
    }
  }
}

std::string Battle::what() const {
  std::string result;
  if (this->_manager == NULL) {
    return result;
  }
  result += this->_manager->tag(BT_TURN);
  result += convert_to_string<size_t>(this->_turn);
  result += this->_manager->tag(BT_TURN);
  return result;
}

std::string Battle::short_what() const {
  std::string result;
  if (this->_manager == NULL) {
    return result;
  }
  result += this->_manager->tag(BT_TURN);
  result += convert_to_string<size_t>(this->_turn);
  result += this->_manager->tag(BT_TURN);
  return result;
}

size_t Battle::update() {
  while (true) {
    this->cleanup();
    if (this->is_victory() || this->is_defeat()) {
      break;
    }
    this->fight_round();
    this->update_fighters();
  }
  this->_log.append("\n\n");
  if (this->is_victory()) {
    // code here to process victory
    this->_log.append("Vikings won!");
  } else {
    // code here to process defeat
    this->_log.append("Enemies won!");
  }
  this->_to_delete = true;
  return RC_OK;
}
