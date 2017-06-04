#ifndef VIKINGS_START_NEW_GAME_COMMAND_H
#define VIKINGS_END_NEW_GAME_COMMAND_H

#include "BaseCommands.h"

class StartNewGameCommand: public FrontendCommand {
  public:
    StartNewGameCommand(const std::string& village_name): FrontendCommand(), _village_name(village_name) {}
    virtual ~StartNewGameCommand() {}

    virtual ssize_t execute(World* world) { if (world == NULL) { return RC_BAD_INPUT; }  return world->new_game(this->_village_name); }

  private:
    std::string _village_name;
};

#endif
