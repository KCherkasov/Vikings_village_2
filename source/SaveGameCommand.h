#ifndef VIKINGS_SAVE_GAME_COMMAND_H
#define VIKINGS_SAVE_GAME_COMMAND_H

#include "BaseCommands.h"

class SaveGameCommand: public FrontendCommand {
  public:
    SaveGameCommand(const std::string& fname, bool overwrite_permission = false): FrontendCommand(), _fname(fname), _overwrite_permission(overwrite_permission) {}
    virtual ~SaveGameCommand() {}

    virtual ssize_t execute(World* world);

  private:
    std::string _fname;
    bool _overwrite_permission;
};

#endif
