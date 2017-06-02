#include "GetOrParseCommand.h"

BasePackage* GetOrParseCommand::parse(World* world) {
  GameEntity* object = World->object(this->_target_id);
  if (object == NULL) {
    return NULL;
  }
  BasePackage* result = NULL;
  switch (typeid(*object)) {
    typeid(Battle) {
      result = new BattleData(dynamic_cast<Battle*>(object), world->storage()->dictionary(), this->_parsed);
      break;
    }
    typeid(GameCharacter) {
      result = new GameCharacterData(dynamic_cast<GameCharacter*>(object), world->storage()->dictionary());
      break;
    }
    typeid(Item) {
      result = new ItemData(dynamic_cast<Item*>(object), world->storage()->dictionary(), this->_parsed);
      break;
    }
    typeid(ItemPart) {
      result = new ItemPartData(dynamic_cast<ItemPart*>(object), world->storage()->dictionary());
      break;
    }
  }
  return result;
}

ssize_t GetOrParseCommand::get_or_parse(World* world) {
  if (this->has(this->_target_id)) {
    return RC_OK;
  }
  BasePackage* obj = this->parse(world);
  if (obj == NULL) {
    return RC_BAD_INPUT;
  }
  this->_parsed.add(obj);
  return RC_OK;
}

ssize_t GetOrParseCommand::execute(World* world) {
  if (world == NULL) {
    return RC_BAD_INPUT;
  }
  return this->get_or_parse(world);
}
