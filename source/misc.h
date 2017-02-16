#ifndef VIKINGS_MISC_H
#define VIKINGS_MISC_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cmath>
#include <cstdlib>

//-- global constants declaration --//

// default values to initialize variables and class fields
const bool BOOL_DEFAULT_VALUE = false;
const size_t SIZE_T_DEFAULT_VALUE = 0;
const ssize_t SSIZE_T_DEFAULT_VALUE = 0;

const ssize_t FREE_ID = -1; // instance identifier representing an obscence of the object (when object id is used instead of reference/pointer to object)

// min and max level value for levalble objects
const ssize_t START_LEVEL = 1;
const ssize_t MAX_LEVEL = 100;

//gender designations
const bool MALE_GENDER = true;
const bool FEMALE_GENDER = false;

// level-up experience point cap for gaining level 2. Other level-up caps are calculated basing on this one.
const size_t FIRST_LEVEL_UP_CAP = 100;

// percentage increasement of experience cap per each level-up
const size_t EXP_CAP_INCREASEMENT = 110;

// basic wounds cap without any traits giving extra wounds
const size_t BASIC_WOUNDS_CAP = 1;

// initial stats value on level 1 for both genders
const size_t INITIAL_MALE_STATS_VALUE = 20;
const size_t INITIAL_FEMALE_STATS_VALUE = 15;

const size_t STAT_MAX_VALUE = 200;

// stat points granted per each level-up
const ssize_t STAT_POINTS_PER_LEVEL = 5;

// percent range cap
const size_t PERCENT_CAP = 100;

// basic seed for stats randomization
const size_t BASIC_SEED = 15;

// start turn number
const size_t START_TURN = 1;

// fight chances plank values in percents. Used to initialize and limit chance values
const size_t MIN_PLANK_VALUE = 10;
const size_t BASE_PLANK_VALUE = 50;
const size_t MAX_PLANK_VALUE = 90;

// items cost and bonuses rise per quality grade in percents
const size_t BASIC_RISE = 75; // basic stats and cost rise used for IK_TRASH rarity items
const size_t RISE_PER_GRADE = 25; // bonus per each grade above IK_TRASH

//-- global constants declaration end --//

//-- enumerations declaration --//

// used for marking functions and methods ending and future error handling
enum ResponseCodes { RC_OK, RC_BAD_INPUT, RC_BAD_INDEX, RC_NO_MANAGER, RC_HAS_MANAGER, RC_SIZE };

// two-elements array indices and size, used to designated current state and max value of some stats
enum PairIndices { PI_CURRENT, PI_MAX, PI_SIZE };

// character stat list enumeration
// WARNING: altering this one will cause the necessity of rebuilding db structure and data retrieval algorithms
enum CharacterStats { CS_MELEE, CS_RANGED, CS_DEFENSE, CS_SIZE };

// item rarities enumeration
enum ItemRarity { IR_TRASH, IR_COMMON, IR_GOOD, IR_RARE, IR_EPIC, IR_LEGENDARY, IR_SIZE };

// item kinds enumeration
enum ItemKinds { IK_HELMET, IK_CHEST, IK_HANDS, IK_BOOTS, IK_MAIN_HAND, IK_OFF_HAND, IK_RANGED, IK_SIZE }

// resources enumeration
// WARNING: altering this one will cause the necessity of rebuilding db structure and data retrieval algorithms
enum ResourceIndices { RI_GOLD, RI_FOOD, RI_WOOD, RI_IRON, RI_LEATHER, RI_SIZE };

// item parts enumeration
enum ItempartsList { IL_FIRST, IL_SECOND, IL_THIRD, IL_SIZE };

// test outcome variants
enum TestOutcomes { TO_FIRST_WON, TO_SECOND_WON, TO_DRAW, TO_SIZE };

// tag managers list

enum TagManagers { TM_CHARACTER, TM_BATTLE, TM_UI, TM_SIZE };

// tag lists for tag manager class
enum CharacterTags { CT_NAME, CT_DESCRIPTION, CT_LEVEL, CT_STAT_POINTS, CT_WOUNDS, CT_WOUNDS_CAP, CT_GENDER, CT_EXPERIENCE, CT_STATS, CT_SPEECH, CT_SIZE };
enum BattleTags { BT_TURN, BT_VIKINGS_COUNT, BT_ENEMIES_COUNT, BT_MELEE_ATTACK_ATTEMPT, BT_RANGED_ATTACK_ATTEMPT, BT_MELEE_ATTACK_SUCCESS, BT_RANGED_ATTACK_SUCCESS, BT_MELEE_ATTACK_FAILURE, BT_RANGED_ATTACK_FAILURE, BT_WOUND_MADE, BT_WOUND_AVOID, BT_DEATH, BT_SIZE };
enum UiTags { UT_GENDER_NOMINATIVE, UT_GENDER_POSESSIVE, UT_SIZE };

//-- enumerations declaration end --//

//-- functions declaration --//

// functions for random digits generation
void seed();
size_t roll_dice(const size_t& dice = PERCENT_CAP);

// functions for making some char stats tests
size_t stats_test(const size_t& first_char_stat, const size_t& second_char_stat, const bool& first_strikes);
bool stats_test(const size_t& stat, const size_t& difficulty = BASE_PLANK_VALUE);

template<class T>
std::string convert_to_string(const T& value) {
  std::ostringstream into;
  into << value;
  return into.str();
}

template<class T>
size_t convert_from_string(const std::string& from, T& result) {
  std::istringstream out(from);
  out >> result;
  return RC_OK;
}

template<class T>
bool vector_has(const std::vector<T>& vect, const T& value) {
  for (size_t i = 0; i < vect.size(); ++i) {
    if (vect[i] == value) {
      return true;
    }
  }
  return false;
}

//-- functions declaration end --//

#endif
