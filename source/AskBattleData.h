#ifndef VIKINGS_ASK_BATTLE_DATA_H
#define VIKINGS_ASK_BATTLE_DATA_H

#include "BaseCommands.h"
#include "FrontendPackages.h"

class AskBattleData: public BackendCommand {
  public:
    AskBattleData(Collection<BasePackage>& responses, ssize_t battle_id = FREE_ID) : BackendCommand(), _battle_id(battle_id), _responses(responses) {}
    virtual ~AskBattleData() {}
    virtual size_t execute(World* world);

  private:
    ssize_t _battle_id;
    Collection<BasePackage>& _responses;
};

#endif
