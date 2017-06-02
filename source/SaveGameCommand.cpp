#include "SaveGameCommand.h"

ssize_t SaveGameCommand::execute(World* world) {
  if (world == NULL || this->_fname.empty()) {
    return RC_BAD_INPUT;
  }
  if (std::ifstream(this->_fname, std::ios::in | std::ios::nocreate) != NULL && !this->_overwrite_permission) {
    return RC_BAD_INPUT;
  }
  world->save_game(this->_fname);
  return RC_OK;
}
