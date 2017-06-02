#ifndef VIKINGS_GET_OR_PARSE_COMMAND_H
#define VIKINGS_GET_OR_PARSE_COMMAND_H

#include "BaseCommands.h"
#include "FrontendPackages.h"

class GetOrParseCommand: public BackendCommand {
  public:
    GetOrParseCommand(Collection<BasePackage>& parsed, ssize_t target_id = FREE_ID): BackendCommand(), _parsed(parsed), _target_id(target_id) {}
    virtual GetOrParseCommand() {}
    virtual ssize_t execute(World* world);
  private:
    Collection<BasePackage>& _parsed;
    ssize_t _target_id;

    ssize_t get_or_parse(World* world);
    BasePackage* parse(World* world);
};

#endif
