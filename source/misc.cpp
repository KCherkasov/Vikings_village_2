#include "misc.h"

void seed() {
  srand(static_cast<size_t>(time(0)));
}

size_t roll_dice(const size_t& dice) {
  size_t roll = rand() % dice;
  return roll;   
}

size_t stats_test(const size_t& first_char_stat, const size_t& second_char_stat, const bool& first_strikes) {
  size_t result = TO_DRAW;
  size_t chance = BASE_PLANK_VALUE;
  if (std::max(first_char_stat, second_char_stat) - std::min(first_char_stat, second_char_stat) > MAX_PLANK_VALUE - BASE_PLANK_VALUE) {
    if (first_char_stat > second_char_stat && first_strikes) {
      chance = MAX_PLANK_VALUE;
    } else {
      chance = MIN_PLANK_VALUE;
    }    
  } else {
    if (first_char_stat > second_char_stat && first_strikes) {
      chance += std::max(first_char_stat, second_char_stat) - std::min(first_char_stat, second_char_stat);
    } else {
      chance -= std::max(first_char_stat, second_char_stat) - std::min(first_char_stat, second_char_stat);
    }
  }
  size_t roll = roll_dice();
  if (first_strikes) {
    if (roll <= chance) {
      result = TO_FIRST_WON;
    } else {
      result = TO_SECOND_WON;
    }
  } else {
    if (roll <= chance) {
      result = TO_SECOND_WON;
    } else {
      result = TO_FIRST_WON;
    }
  }
  return result;
}

bool stats_test(const size_t& stat, const size_t& difficulty) {
  size_t chance = std::min(MAX_PLANK_VALUE, std::max(MIN_PLANK_VALUE, difficulty));
  return roll_dice() <= chance;
}
