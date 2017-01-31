#include "misc.h"

void seed() { srand(static_cast<size_t>(time(0))); }

size_t roll_dice(const size_t& dice) {
  size_t roll = rand() % dice;
  return roll;   
}
