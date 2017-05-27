#ifndef VIKINGS_BASE_COMMANDS_H
#define VIKINGS_BASE_COMMANDS_H

//----------------------------------------------------------------------------//
//--              Core classes for Command pattern realization              --//
//----------------------------------------------------------------------------//
//-- > BaseCommand: basic class for every command;                          --//
//-- > FrontendCommand: base class for commands sent from GUI to backend;   --//
//-- > BackendCommand: base class for commands sent to backend from inside. --//
//----------------------------------------------------------------------------//

#include "misc.h"
#include "World.h"

//-- BaseCommand class --//

class BaseCommand {
  public:
    BaseCommand() {}
    virtual ~BaseCommand() {}
    virtual ssize_t execute(World* world) { return RC_OK; }
};

//-- BaseCommand class end --//

//-- FrontendCommand class --//

class FrontendCommand: public BaseCommand {
  public:
    FrontendCommand(): BaseCommand() {}
    virtual ~FrontendCommand() {}
};

//-- FrontendCommand class end --//

//-- BackendCommand class --//

class BackendCommand: public BaseCommand {
  public:
    BackendCommand(): BaseCommand() {}
    virtual ~BackendCommand() {}
};

//-- BackendCommand class end --//

#endif
