#include "LoadGameCommand.h"

const std::string

ssize_t LoadGameCommand::execute(World* world) {
  if (world == NULL || this->_fname) {
    return RC_BAD_INPUT;
  }
  if (std::ifstream(fname, std::ios::in | std::ios::nocreate) == NULL) {
    return RC_BAD_INPUT;
  }
  return world->load_game(this->_fname);
}
