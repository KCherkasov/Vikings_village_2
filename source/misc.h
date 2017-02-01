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

//-- global constants declaration end --//

//-- enumerations declaration --//

// used for marking functions and methods ending and future error handling
enum ResponseCodes { RC_OK, RC_BAD_INPUT, RC_BAD_INDEX, RC_NO_MANAGER, RC_HAS_MANAGER, RC_SIZE };

// two-elements array indices and size, used to designated current state and max value of some stats
enum PairIndices { PI_CURRENT, PI_MAX, PI_SIZE };

// character stat list enumeration
// WARNING: altering this one will cause the necessity of rebuilding db structure and data retrieval algorithms
enum CharacterStats { CS_MELEE, CS_RANGED, CS_DEFENSE, CS_SIZE };

// tag list for tag manager class
enum TagList { TL_NAME, TL_DESCRIPTION, TL_LEVEL, TL_STAT_POINTS, TL_WOUNDS, TL_WOUNDS_CAP, TL_GENDER, TL_EXPERIENCE, TL_STATS, TL_SPEECH, TL_TURN, TL_SIZE };

//-- enumerations declaration end --//

//-- functions declaration --//

void seed();
size_t roll_dice(const size_t& dice = PERCENT_CAP);

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

//-- functions declaration end --//

#endif
