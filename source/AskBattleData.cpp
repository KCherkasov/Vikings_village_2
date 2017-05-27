#include "AskBattleData.h"

ssize_t AskBattleData::execute(World* world) {
  if (world == NULL) {
    return RC_BAD_INPUT;
  }
  Battle* battle = NULL;
  if (this->_battle_id > FREE_ID) {
    battle = dynamic_cast<Battle*>(world->object(this->_battle_id));
  } else {
    battle = world->first_instance();
  }
  if (battle != NULL) {
    BattleData* response = new BattleData(battle, world->storage()->dictionary(), this->_responses);
    this->_responses.add(dynamic_cast<BasePackage*>(response));
    return response->id();
  }
  return FREE_ID;
}
