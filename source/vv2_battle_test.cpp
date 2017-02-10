#include <iostream>

#include "WorldStorage.h"

std::string get_replacement(const size_t& tag_id, const WorldStorage& storage) {
  std::string result;
  switch (tag_id) {
    case BT_TURN: {
      result.append("Turn");
      break;
    }
    case BT_VIKINGS_COUNT: {
      result.append("Vikings squad size");
      break;
    }
    case BT_ENEMIES_COUNT: {
      result.append("Enemies squad size");
      break;
    }
    case BT_MELEE_ATTACK_ATTEMPT: {
      result += storage.dictionary()->melee_attempt(roll_dice(storage.dictionary()->melee_attempts_count()));
      break;
    }
    case BT_RANGED_ATTACK_ATTEMPT: {
      result += storage.dictionary()->ranged_attempt(roll_dice(storage.dictionary()->ranged_attempts_count()));
      break;
    }
    case BT_MELEE_ATTACK_SUCCESS: {
      result += storage.dictionary()->melee_success(roll_dice(storage.dictionary()->melee_sucess_count()));
      break;
    }
    case BT_RANGED_ATTACK_SUCCESS: {
      result += storage.dictionary()->ranged_success(roll_dice(storage.dictionary()->ranged_success_count()));
      break;
    }
    case BT_MELEE_ATTACK_FAILURE: {
      result += storage.dictionary()->melee_failure(roll_dice(storage.dictionary()->melee_failures_count()));
      break;
    }
    case BT_RANGED_ATTACK_FAILURE: {
      result += storage.dictionary()->ranged_failure(roll_dice(storage.dictionary()->ranged_failures_count()));
      break;
    }
    case BT_WOUND_MADE: {
      result += storage.dictionary()->wound_made(roll_dice(storage.dictionary()->wound_made_count()));
      break;
    }
    case BT_WOUND_AVOID: {
      result += storage.dictionary()->wound_avoid(roll_dice(storage.dictionary()->wound_avoid_count()));
      break;
    }
    case BT_DEATH: {
      result.append("dies");
      break;
    }
  }
  return result;
}

void process_log(std::string& log, const WorldStorage& storage) {
  if (!storage.is_filled()) {
    return;
  }
  for (size_t i = 0; i < BT_SIZE; ++i) {
    size_t j = 0;
    while (j < log.size()) {
      j = storage.manager(TM_BATTLE)->replace_tag(i, j, log, get_replacement(i, storage));
    }
  }
}

int main(int argc, char** argv) {
  seed();
  const size_t CHARACTERS_PER_SQUAD = 15;
  
  std::string templates_db_name("Templates.db");
  std::string ui_db_name("UITexts.db");
  std::string log_name("battle_log.log");
  
  std::cout << "\nVikings village ver.0.1 battle mechanics test\n\nInitializing storage using " << templates_db_name << " and " << ui_db_name << " databases...";
  WorldStorage storage(templates_db_name, ui_db_name);
  if (storage.is_filled()) {
    std::cout << "success" << std::endl << std::endl;
  } else {
    std::cout << "faliure. Aborting test." << std::endl << std::endl;
    return 0;
  }
  size_t total_characters = 2 * (CHARACTERS_PER_SQUAD + roll_dice(BASIC_SEED) + 1);
  std::cout << "Initializing " << total_characters << " battle characters...\n";
  std::vector<GameCharacter*> pool;
  for (size_t i = 0; i < total_characters; ++i) {
    pool.push_back(NULL);
    storage.make_character(pool[pool.size() - 1], roll_dice(BASIC_SEED) + START_LEVEL);
    std::cout << i + 1 << "/" << total_characters << " (" << (i + 1) * PERCENT_CAP / total_characters << "\%)\n";
  }
  std::cout << "Done.\n\nDistributing characters between viking and enemy squads...\n\n";
  std::vector<ssize_t> viking_ids;
  std::vector<ssize_t> enemy_ids;
  std::cout << "Filling vikings squad...\n";
  for (size_t i = 0; i < total_characters / 2; ++i) {
    while (true) {
      size_t index = roll_dice(pool.size());
      if (pool[index] != NULL) {
        if (!vector_has(viking_ids, pool[index]->id())) {
          viking_ids.push_back(pool[index]->id());
          std::cout << i + 1 << "/" << total_characters / 2 << " (" << (i + 1) * PERCENT_CAP / (total_characters / 2) << "\%)\n";
          break;
        }
      }
    }
  }
  std::cout << "Done.\n\nFilling enemies squad...\n";
  for (size_t i = 0; i < total_characters - total_characters / 2; ++i) {
    while (true) {
      size_t index = roll_dice(pool.size());
      if (pool[index] != NULL) {
        if (!vector_has(viking_ids, pool[index]->id()) && !vector_has(enemy_ids, pool[index]->id())) {
          enemy_ids.push_back(pool[index]->id());
          std::cout << i + 1 << "/" << total_characters - total_characters / 2 << " (" << (i + 1) * PERCENT_CAP / (total_characters - total_characters / 2) << "\%)\n";
          break;
        }
      }
    }
  }
  std::cout << "Done.\n\nMaking Battle class object...";
  Battle* battle = NULL;
  storage.make_battle(battle, pool, viking_ids, enemy_ids);
  if (battle != NULL) {
    std::cout << "success." << std::endl << std::endl << "Simulating the battle...";
    battle->update();
    std::cout << "Done.\nProcessing battle log...";
    std::string processed = battle->log();
    process_log(processed, storage);
    std::cout << "Done.\nRedirecting battle log into " << log_name << " file...";
    std::ofstream log;
    log.open(log_name.data(), std::ios::out | std::ios::trunc);
    log << processed;
    log.close();
    // std::cout << "Done. Printing battle log...\n\n" << battle->log(); // deprecated for Windows version. uncomment when compiling for Linux
  } else {
    std::cout << "failure.\n" << std::endl;
  }
  std::cout << "Done.\n\nMaking cleanup...";
  for (size_t i = 0; i < pool.size(); ++i) {
    if (pool[i] != NULL) {
      delete pool[i];
    }
  }
  pool.clear();
  std::cout << "\ncharacter pool cleaning done...";
  delete battle;
  std::cout << "\nbattle cleaning done...";
  storage.clear();
  std::cout << "\nstorage cleaning done...\nFinishing the test.";
  system("pause");
	return 0;
}

