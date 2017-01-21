#ifndef VIKINGS_MISC_H
#define VIKINGS_MISC_H

#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <stdlib>

//-- global constants declaration --//

// default values to initialize variables and class fields
const bool BOOL_DEFAULT_VALUE = true;
const size_t SIZE_T_DEFAULT_VALUE = 0;
const ssize_t SSIZE_T_DEFAULT_VALUE = 0;

const ssize_t FREE_ID = -1; // instance identifier representing an obscence of the object (when object id is used instead of reference/pointer to object)

const ssize_t START_LEVEL = 1;
const ssize_t MAX_LEVEL = 100;

//-- global constants declaration end --//

//-- enumerations declaration --//

enum ResponseCodes { RC_OK, RC_SIZE };

//-- enumerations declaration end --//

#endif
