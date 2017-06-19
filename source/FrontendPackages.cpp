#include "FrontendPackages.h"

//-- related functions (mostly hardcoded stuff that'll be replaced with db tables) --//

std::string get_kind_name(size_t kind) {
  std::string result;
  switch (kind) {
    case IK_HELMET: {
      result.append("Helmet");
      break;
    }
    case IK_CHEST: {
      result.append("Chestpiece");
      break;
    }
    case IK_HANDS: {
      result.append("Gloves");
      break;
    }
    case IK_BOOTS: {
      result.append("Boots");
      break;
    }
    case IK_MAIN_HAND: {
      result.append("Main hand");
      break;
    }
    case IK_OFF_HAND: {
      result.append("Offhand")
      break;
    }
    case IK_RANGED: {
      result.append("Ranged weapon");
      break;
    }
  }
  return result;
}

std::string get_group_name(size_t group) {
  std::string result;
  switch (group) {
    case PG_HELMET: {
      break;
    }
    case PG_CHEST: {
      break;
    }
    case PG_HANDS: {
      break;
    }
    case PG_BOOTS: {
      break;
    }
    case PG_AXE: {
      result.append("axe");
      break;
    }
    case PG_SWORD: {
      result.append("sword");
      break;
    }
    case PG_SPEAR: {
      result.append("spear");
      break;
    }
    case PG_SHIELD: {
      result.append("shield");
      break;
    }
    case PG_BOW: {
      result.append("bow");
      break;
    }
  }
  return result;
}

std::string get_rarity_name(size_t rarity) {
  std::string result;
  switch (rarity) {
    case IR_TRASH: {
      result.append("Trash");
      break;
    }
    case IR_COMMON: {
      result.append("Common");
      break;
    }
    case IR_GOOD: {
      result.append("Good");
      break;
    }
    case IR_RARE: {
      result.append("Rare");
      break;
    }
    case IR_EPIC: {
      result.append("Epic");
      break;
    }
    case IR_LEGENDARY: {
      result.append("Legendary");
      break;
    }
  }
  return result;
}

std::string get_rarity_name(size_t index) {
  std::string result;
  switch (result) {
    case IR_GOLD: {
      result.append("Gold: ");
      break;
    }
    case IR_FOOD: {
      result.append("Food: ");
      break;
    }
    case IR_WOOD: {
      result.append("Wood: ");
      break;
    }
    case IR_IRON: {
      result.append("Iron: ");
      break;
    }
    case IR_LEATHER: {
      result.append("Leather: ");
      break;
    }
  }
  return result;
}

//-- related functions end --//

//-- BattleData class --//

std::string BattleData::get_tag_replacement(size_t tag_id) const {
  std::string result;
  switch (tag_id) {
    case BT_TURN: {
      result.append("Turn");
      break;
    }
    case BT_VIKINGS_COUNT: {
      result.append("Vikings squad size");
      break;
    }
    case BT_ENEMIES_COUNT: {
      result.append("Enemies squad size");
      break;
    }
    case BT_MELEE_ATTACK_ATTEMPT: {
      result += this->_dictionary->melee_attempt(roll_dice(this->_dictionary->melee_attempts_count()));
      break;
    }
    case BT_RANGED_ATTACK_ATTEMPT: {
      result += this->_dictionary->ranged_attempt(roll_dice(this->_dictionary->ranged_attempts_count()));
      break;
    }
    case BT_MELEE_ATTACK_SUCCESS: {
      result += this->_dictionary->melee_success(roll_dice(this->_dictionary->melee_sucess_count()));
      break;
    }
    case BT_RANGED_ATTACK_SUCCESS: {
      result += storage.dictionary()->ranged_success(roll_dice(storage.dictionary()->ranged_success_count()));
      break;
    }
    case BT_MELEE_ATTACK_FAILURE: {
      result += this->_dictionary->melee_failure(roll_dice(this->_dictionary->melee_failures_count()));
      break;
    }
    case BT_RANGED_ATTACK_FAILURE: {
      result += this->_dictionary->ranged_failure(roll_dice(this->_dictionary->ranged_failures_count()));
      break;
    }
    case BT_WOUND_MADE: {
      result += this->_dictionary->wound_made(roll_dice(this->_dictionary->wound_made_count()));
      break;
    }
    case BT_WOUND_AVOID: {
      result += this->_dictionary->wound_avoid(roll_dice(this->_dictionary->wound_avoid_count()));
      break;
    }
    case BT_DEATH: {
      result.append("dies");
      break;
    }
  }
  return result;
}

void BattleData::process_log(Battle* battle) {
  this->_battle_log = battle->log();
  for (size_t i = 0; i < BT_SIZE; ++i) {
    size_t j = 0;
    while (j < this->_battle_log.size()) {
      j = battle->manager()->replace_tag(i, j, this->_battle_log, this->get_tag_replacement(i));
    }
  }
}

void BattleData::get_survivors(Battle* battle, Collection<BasePackage>& responses) {
  for (size_t i = 0; i < battle->vikings().size(); ++i) {
    if (battle->vikings()[i] != NULL) {
      if (!battle->vikings()[i]->to_delete()) {
        if (!responses.has(battle->vikings()[i]->id())) {
          BasePackage* survivor = new GameCharacterData(battle->vikings()[i], this->_dictionary);
          responses.add(survivor);
        }
        this->_survivors_data.add(responses[battle->vikings()[i]->id()]);
      }
    }
  }
}

size_t BattleData::parse_object(Battle* battle, Collection<BasePackage>& responses) {
  this->process_log(battle);
  this->get_survivors(battle, responses);
  return RC_OK;
}

char* BattleData::to_packet() const {
  size_t pure_length = this->_battle_log.size() + sizeof(size_t) * 2 + sizeof(ssize_t);
  std::vector<char*> survivors_data;
  size_t survivors_data_length = 0;
  for (auto obj = this->_survivors_data.map().begin(); obj != this->_survivors_data.map().end(); ++obj) {
    if (obj->second != NULL) {
      survivors_data.push_back(obj->second->to_packet());
      survivors_data_length += strlen(survivors_data[survivors_data.size() - 1]);
    }
  }
  pure_length += survivors_data_length + survivors_data.size() * sizeof(size_t);
  char* message = new char[pure_length];
  memcpy(message, &(this->_battle_log.size()), sizeof(size_t));
  memcpy(message + sizeof(size_t), this->_id, sizeof(ssize_t));
  memcpy(message + sizeof(size_t) + sizeof(ssize_t), this->_battle_log.data(), this->_battle_log.size());
  memcpy(message + this->_battle_log.size() + sizeof(size_t) + sizeof(ssize_t), &(survivors_data.size()), sizeof(size_t));
  size_t shift = 0;
  for (size_t i = 0; i < survivors_data.size(); ++i) {
    memcpy(message + this->_battle_log.size() + sizeof(ssize_t) + sizeof(size_t) * (2 + i) + shift, &(strlen(survivors_data[i])), sizeof(size_t));
    memcpy(message + this->_battle_log.size() + sizeof(ssize_t) + sizeof(size_t) * (2 + i + 1) + shift, survivors_data[i], strlen(survivors_data[i]));
    shift += strlen(survivors_data[i]);
  }
  return message;
}

void BattleData::from_packet(char* packet) {
  if (packet == NULL) {
    return;
  }
  this->_battle_log.clear();
  size_t log_size = 0;
  memcpy(&log_size, packet, sizeof(size_t));
  memcpy(&(this->_id), packet + sizeof(size_t), sizeof(ssize_t));
  char* battle_log = new char[log_size];
  memcpy(battle_log, packet + sizeof(size_t) + sizeof(ssize_t), log_size);
  this->_battle_log.append(const_cast<const char*>(battle_log));
  delete[] battle_log;
  size_t survivors_count = 0;
  size_t shift = 0;
  memcpy(&survivors_count, packet + sizeof(size_t) + sizeof(ssize_t) + log_size, sizeof(size_t));
  for (size_t i = 0 ; i < survivors_count; ++i) {
    size_t survivor_data_size = 0;
    memcpy(&survivor_data_size, packet + log_size + sizeof(ssize_t) + sizeof(size_t) * (2 + i) + shift, sizeof(size_t));
    char* survivor_data = new char[survivor_data_size];
    memcpy(survivor_data, packet + log_size + sizeof(ssize_t) + sizeof(size_t) * (2 + i + 1) + shift, survivor_data_size);
    shift += survivor_data_size;
    BasePackage* survivor = new CharacterData(survivor_data);
    this->_survivors_data.add(survivor);
    delete[] survivor_data;
  }
}

//-- BattleData class end --//

//-- GameCharacterData class --//

std::string GameCharacterData::get_tag_replacement(size_t tag_id) const {
  std::string result;
  if (tag_id < CT_SIZE) {
    result += this->_dictionary.character_field_name(tag_id);
    result.append(" ");
  }
  return result;
}

void GameCharacterData::get_generals(GameCharacter* character) {
  this->_generals.clear();
  std::string buffer = this->get_tag_replacement(CF_NAME);
  buffer += character->name();
  this->_generals.push_back(buffer);
  buffer.clear();
  buffer = this->get_tag_replacement(CF_GENDER);
  buffer += this->_dictionary->gender_name(this->gender());
  this->_generals.push_back(buffer);
  buffer.clear();
  buffer = convert_to_string<ssize_t>(character->level());
  buffer.append(" ");
  buffer += this->get_tag_replacement(CF_LEVEL);
  buffer.append(" (");
  buffer += convert_to_string<size_t>(character->experience(PI_CURRENT));
  buffer.append("/");
  buffer += convert_to_string<size_t>(character->experience(PI_MAX));
  buffer.append(" exp)")
  this->_generals.push_back(buffer);
  buffer.clear();
}

void GameCharacterData::get_stats(GameCharacter* character) {
  std::string buffer = this->get_tag_replacement(CF_STATS);
  this->_stats.clear();
  this->_stats.push_back(buffer);
  buffer.clear();
  for (size_t i = 0; i < CS_SIZE; ++i) {
    buffer = this->stat_name(i);
    buffer.append(": ");
    buffer += convert_to_string<ssize_t>(character->stats(i));
    this->_stats.push_back(buffer);
    buffer.clear();
  }
}

size_t GameCharacterData::parse_object(GameCharacter* character) {
  this->get_generals(character);
  this->get_stats(character);
  // TO-DO: add inventory info when applied
  return RC_OK;
}

char* GameCharacterData::to_packet() const {
  size_t pure_length = sizeof(ssize_t);
  for (size_t i = 0; i < this->_generals.size(); ++i) {
    pure_length += this->_generals[i].size();
  }
  for (size_t i = 0; i < this->_stats.size(); ++i) {
    pure_length += this->_stats[i].size();
  }
  char* message = new char[pure_length];
  memcpy(message, &(this->_id), sizeof(ssize_t));
  size_t shift = 0;
  for (size_t i = 0; i < this->_generals.size(); ++i) {
    memcpy(message + sizeof(ssize_t) + sizeof(size_t) * (1 + i) + shift, &(this->_generals[i].size()), sizeof(size_t));
    memcpy(message + sizeof(ssize_t) + sizeof(size_t) * (2 + i) + shift, this->_generals[i].data(), this->_generals[i].size());
    shift += this->_generals[i].size();
  }
  for (size_t i = 0; i < this->_generals.size(); ++i) {
    memcpy(message + sizeof(ssize_t) + sizeof(size_t) * (1 + i + this->_generals.size()) + shift, &(this->_stats[i].size()), sizeof(size_t));
    memcpy(message + sizeof(ssize_t) + sizeof(size_t) * (2 + i + this->_generals.size()) + shift, &(this->_stats[i].size()), sizeof(size_t));
    shift += this->_stats[i].size();
  }
  return message;
}

void GameCharacterData::from_packet(char* packet) {
  if (packet == NULL) {
    return;
  }
  memcpy(&(this->_id), packet, sizeof(ssize_t));
  size_t shift = 0;
  this->_generals.clear();
  for (size_t i = 0; i < CP_SIZE; ++i) {
    size_t size = 0;
    memcpy(&size, packet + sizeof(ssize_t) + shift + sizeof(size_t) * i, sizeof(size_t));
    char* buffer = new char[size];
    memcpy(buffer, packet + sizeof(ssize_t) + shift + sizeof(size_t) * (1 + i), size);
    this->_generals.push_back(std::string());
    this->_generals[this->_generals.size() - 1].append(const_cast<const char*>(buffer));
    delete[] buffer;
    shift += size;
  }
  this->_stats.clear();
  for (size_t i = 0; i < SP_SIZE; ++i) {
    size_t size = 0;
    memcpy(&size, packet + sizeof(ssize_t) + shift + sizeof(size_t) * (this->_generals.size() + i), sizeof(size_t));
    char* buffer = new char[size];
    memcpy(buffer, packet + sizeof(ssize_t) + shift + sizeof(size_t) * (this->_generals.size() + i + 1), size);
    delete[] buffer;
    shift += size;
  }
}

//-- GameCharacterData class end --//

//-- ItemData class --//

std::string ItemData::get_tag_replacement(size_t tag_id) const {
  std::string result;
  switch (tag_id) {
    case IT_NAME: {
      result.append("Name: ");
      break;
    }
    case IT_DESCRIPTION: {
      result.append("Description: ");
      break;
    }
    case IT_KIND: {
      result.append("Kind: ");
      break;
    }
    case IT_GROUP: {
      result.append("Kind:  ");
      break;
    }
    case IT_PLACE: {
      result.append("Slot: ");
      break;
    }
    case IT_BONUSES: {
      result.append("Bonuses: ");
      break;
    }
    case IT_COST: {
      result.append("Cost: ");
      break;
    }
    case IT_EMPTY_SLOT {
      result.append("Nothing");
      break;
    }
  }
  return result;
}

void ItemData::get_generals(Item* item) {
  std::string buffer = this->get_tag_replacement(IT_NAME);
  buffer += item->name();
  this->_generals.push_back(buffer);
  buffer.clear();
  buffer = this->get_tag_replacement(IT_DESCRIPTION);
  buffer += item->description();
  this->_generals.push_back(buffer);
  buffer.clear();
  buffer = this->get_tag_replacement(IT_KIND);
  buffer += get_kind_name(item->kind());
  if (!get_group_name(item->part(0)->group()).empty()) {
    buffer.append(" (");
    buffer += get_group_name(item->part(0).group());
    buffer.append(")");
  }
  this->_generals.push_back(buffer);
  buffer.clear();
  buffer += this->get_tag_replacement(IT_RARITY);
  buffer += get_rarity_name(item->rarity());
  this->_generals.push_back(buffer);
  buffer.clear();
}

void ItemData::get_bonuses(Item* item) {
  std::string buffer = this->get_tag_replacement(IT_BONUSES);
  this->_bonuses.clear();
  this->_bonuses.push_back(buffer);
  buffer.clear();
  for (size_t i = 0; i < CS_SIZE; ++i) {
    buffer = this->_dictionary->stat_name(i);
    buffer.append(": ");
    buffer += convert_to_string<ssize_t>(item->bonuses(i));
    this->_bonuses.push_back(buffer);
    buffer.clear();
  }
}

void ItemData::get_costs(Item* item) {
  std::string buffer = this->get_tag_replacement(IT_COST);
  this->_costs.clear();
  this->_costs.push_back(buffer);
  buffer.clear();
  for (size_t i = 0; i < RI_SIZE; ++i) {
    buffer = get_resource_name(i);
    buffer += convert_to_string<size_t>(item->cost(i));
    this->_costs.push_back(buffer);
    buffer.clear();
  }
}

void ItemData::get_parts(Item* item, Collection<BasePackage>& responses) {
  this->_parts.clear();
  for (size_t i = 0; i < item->parts_count(); ++i) {
    if (item->part(i) != NULL) {
      if (!item->part(i)->to_delete()) {
        if (!responses.has(item->parts(i)->id())) {
          ItemPartData* data = new ItemPartData(item->part(i), this->_dictionary);
          responses.add(data);
        }
        this->_parts.push_back(responses[item->parts(i)->id()]);
      }
    }
  }
}

char* ItemData::to_packet() const {
  size_t pure_length = sizeof(ssize_t);
  for (size_t i = 0; i < this->_generals.size(); ++i) {
    pure_length += this->_generals[i].size();
  }
  for (size_t i = 0; i < this->_bonuses.size(); ++i) {
    pure_length += this->_bonuses[i].size();
  }
  for (size_t i = 0; i < this->_costs.size(); ++i) {
    pure_length += this->_costs[i].size();
  }
  std::vector<char*> parts;
  for (size_t i = 0; i < this->_parts.size(); ++i) {
    parts.push_back(NULL);
    parts[parts.size() - 1] = this->_parts[i]->to_packet();
    pure_length += strlen(parts[parts.size() - 1]);
  }
  char* message = new char[pure_length];
  memcpy(message, &(this->_id), sizeof(ssize_t));
  size_t shift = 0;
  for (size_t i = 0; i < this->_generals.size(); ++i) {
    memcpy(message + sizeof(ssize_t) + shift, &(this->_generals[i].size()), sizeof(size_t));
    shift += sizeof(size_t);
    memcpy(message + sizeof(ssize_t) + shift, this->_generals[i].data(), this->_generals[i].size());
    shift += this->_generals[i].size();
  }
  for (size_t i = 0; i < this->_bonuses.size(); ++i) {
    memcpy(message + sizeof(ssize_t) + shift, &(this->_bonuses[i].size()), sizeof(size_t));
    shift += sizeof(size_t);
    memcpy(message + sizeof(ssize_t) + shift, this->_bonuses[i].data(), this->_bonuses[i].size());
    shift += this->_bonuses[i].size();
  }
  for (size_t i = 0; i < this->_costs.size(); ++i) {
    memcpy(message + sizeof(ssize_t) + shift, &(this->_costs[i].size()), sizeof(size_t));
    shift += sizeof(size_t);
    memcpy(message + sizeof(ssize_t) + shift, this->_costs[i].data(), this->_costs[i].size());
    shift += this->_costs[i].size();
  }
  for (size_t i = 0; i < this->_parts.size(); ++i) {
    memcpy(message + sizeof(ssize_t) + shift, &(strlen(parts[i])), sizeof(size_t));
    shift += sizeof(size_t);
    memcpy(message + sizeof(ssize_t) + shift, parts[i], strlen(parts[i]));
    shift += strlen(parts[i]);
  }
  return message;
}

void ItemData::from_packet(char* packet) {
  if (packet == NULL) {
    return;
  }
  size_t shift = 0;
  memcpy(&(this->_id), packet, sizeof(size_t));
  shift += sizeof(size_t);
  this->_generals.clear();
  for (size_t i = 0; i < IG_SIZE; ++i) {
    size_t size = 0;
    memcpy(&size, packet + shift, sizeof(size_t));
    shift += sizeof(size_t);
    char* buffer = new char[size];
    memcpy(buffer, packet + shift, size);
    this->_generals.push_back(std::string());
    this->_generals[this->_generals.size()].append(const_cast<const char*>(buffer));
    delete[] buffer;
    shift += size;
  }
  this->_bonuses.clear();
  for(size_t i = 0; i < SP_SIZE; ++i) {
    size_t size = 0;
    memcpy(&size, packet + shift, sizeof(size_t));
    shift += sizeof(size_t);
    char* buffer = new char[size];
    memcpy(buffer, packet + shift, size);
    this->_bonuses.push_back(std::string());
    this->_bonuses[this->_bonuses.size()].append(const_cast<const char*>(buffer));
    delete[] buffer;
    shift += size;
  }
  this->_costs.clear();
  for (size_t i = 0; i < IC_SIZE; ++i) {
    size_t size = 0;
    memcpy(&size, packet + shift, sizeof(size_t));
    shift += sizeof(size_t);
    char* buffer = new char[size];
    memcpy(buffer, packet + shift, size);
    this->_costs.push_back(std::string());
    this->_costs[this->_costs.size()].append(const_cast<const char*>(buffer));
    delete[] buffer;
    shift += size;
  }
  this->_parts.map().clear();
  for (size_t i = 0; i < 3; ++i) {
    size_t size = 0;
    memcpy(&size, packet + shift, sizeof(size_t));
    shift += sizeof(size_t);
    char* buffer = new char[size];
    memcpy(buffer, packet + shift, size);
    shift += size;
    BasePackage* part = new ItemPartData(buffer);
    delete[] buffer;
    this->_parts.add(part);
    part = NULL;
  }
}

//-- ItemData class end --//

//-- ItemPartData class --//

//-- -!- NOTE: replace this hardcoded stuff with db table -!-
std::string ItemPartData::get_tag_replacement(size_t tag_id) const {
  std::string result;
  switch (tag_id) {
    case IT_NAME: {
      result.append("Name: ");
      break;
    }
    case IT_DESCRIPTION: {
      result.append("Description: ");
      break;
    }
    case IT_KIND: {
      result.append("Kind: ");
      break;
    }
    case IT_GROUP: {
      result.append("Kind:  ");
      break;
    }
    case IT_PLACE: {
      result.append("Slot: ");
      break;
    }
    case IT_BONUSES: {
      result.append("Bonuses: ");
      break;
    }
    case IT_COST: {
      result.append("Cost: ");
      break;
    }
    case IT_EMPTY_SLOT {
      result.append("Nothing");
      break;
    }
  }
  return result;
}

void ItemPartData::get_generals(ItemPartData* item_part) {
  std::string buffer = this->get_tag_replacement(IT_NAME);
  buffer += item_part->name();
  this->_generals.push_back(buffer);
  buffer.clear();
  buffer = this->get_tag_replacement(IT_DESCRIPTION);
  buffer += item_part->description();
  this->_generals.push_back(buffer);
  buffer.clear();
  buffer = this->get_tag_replacement(IT_KIND);
  buffer += get_kind_name(item_part->kind());
  if (!get_group_name(item_part->group()).empty()) {
    buffer.append(" (");
    buffer += get_group_name(item_part.group());
    buffer.append(")");
  }
  this->_generals.push_back(buffer);
  buffer.clear();
  buffer += this->get_tag_replacement(IT_PLACE);
  buffer += convert_to_string<size_t>(item_part->place() + 1);
  this->_generals.push_back(buffer);
  buffer.clear();
  buffer += this->get_tag_replacement(IT_RARITY);
  buffer += get_rarity_name(item_part->rarity());
  this->_generals.push_back(buffer);
  buffer.clear();
}

void ItemPartData::get_bonuses(ItemPart* item_part) {
  std::string buffer = this->get_tag_replacement(IT_BONUSES);
  this->_bonuses.clear();
  this->_bonuses.push_back(buffer);
  buffer.clear();
  for (size_t i = 0; i < CS_SIZE; ++i) {
    buffer = this->_dictionary->stat_name(i);
    buffer.append(": ");
    buffer += convert_to_string<ssize_t>(item_part->bonuses(i));
    this->_bonuses.push_back(buffer);
    buffer.clear();
  }
}

void ItemPartData::get_costs(ItemPart* item_part) {
  std::string buffer = this->get_tag_replacement(IT_COST);
  this->_costs.clear();
  this->_costs.push_back(buffer);
  buffer.clear();
  for (size_t i = 0; i < RI_SIZE; ++i) {
    buffer = get_resource_name(i);
    buffer += convert_to_string<size_t>(item_part->cost(i));
    this->_costs.push_back(buffer);
    buffer.clear();
  }
}

size_t ItemPartData::parse_object(ItemPart* item_part) {
  this->get_generals(item_part);
  this->get_bonuses(item_part);
  this->get_costs(item_part);
  return RC_OK;
}

char* ItemPartData::to_packet() const {
  size_t pure_length = sizeof(ssize_t);
  for (size_t i = 0; i < this->_generals.size(); ++i) {
    pure_length += this->_generals[i].size();
  }
  for (size_t i = 0; i < this->_bonuses.size(); ++i) {
    pure_length += this->_bonuses[i].size();
  }
  for (size_t i = 0; i < this->_costs.size(); ++i) {
    pure_length += this->_costs[i].size();
  }
  char* message = new char[pure_length];
  memcpy(message, &(this->_id), sizeof(ssize_t));
  size_t shift = 0;
  for (size_t i = 0; i < this->_generals.size(); ++i) {
    memcpy(message + sizeof(ssize_t) + shift, &(this->_generals[i].size()), sizeof(size_t));
    shift += sizeof(size_t);
    memcpy(message + sizeof(ssize_t) + shift, this->_generals[i].data(), this->_generals[i].size());
    shift += this->_generals[i].size();
  }
  for (size_t i = 0; i < this->_bonuses.size(); ++i) {
    memcpy(message + sizeof(ssize_t) + shift, &(this->_bonuses[i].size()), sizeof(size_t));
    shift += sizeof(size_t);
    memcpy(message + sizeof(ssize_t) + shift, this->_bonuses[i].data(), this->_bonuses[i].size());
    shift += this->_bonuses[i].size();
  }
  for (size_t i = 0; i < this->_costs.size(); ++i) {
    memcpy(message + sizeof(ssize_t) + shift, &(this->_costs[i].size()), sizeof(size_t));
    shift += sizeof(size_t);
    memcpy(message + sizeof(ssize_t) + shift, this->_costs[i].data(), this->_costs[i].size());
    shift += this->_costs[i].size();
  }
  return message;
}

void ItemPartData::from_packet(char* packet) {
  if (packet == NULL) {
    return;
  }
  size_t shift = 0;
  memcpy(&(this->_id), packet, sizeof(size_t));
  shift += sizeof(size_t);
  this->_generals.clear();
  for (size_t i = 0; i < IG_SIZE; ++i) {
    size_t size = 0;
    memcpy(&size, packet + shift, sizeof(size_t));
    shift += sizeof(size_t);
    char* buffer = new char[size];
    memcpy(buffer, packet + shift, size);
    this->_generals.push_back(std::string());
    this->_generals[this->_generals.size()].append(const_cast<const char*>(buffer));
    delete[] buffer;
    shift += size;
  }
  this->_bonuses.clear();
  for(size_t i = 0; i < SP_SIZE; ++i) {
    size_t size = 0;
    memcpy(&size, packet + shift, sizeof(size_t));
    shift += sizeof(size_t);
    char* buffer = new char[size];
    memcpy(buffer, packet + shift, size);
    this->_bonuses.push_back(std::string());
    this->_bonuses[this->_bonuses.size()].append(const_cast<const char*>(buffer));
    delete[] buffer;
    shift += size;
  }
  this->_costs.clear();
  for (size_t i = 0; i < IC_SIZE; ++i) {
    size_t size = 0;
    memcpy(&size, packet + shift, sizeof(size_t));
    shift += sizeof(size_t);
    char* buffer = new char[size];
    memcpy(buffer, packet + shift, size);
    this->_costs.push_back(std::string());
    this->_costs[this->_costs.size()].append(const_cast<const char*>(buffer));
    delete[] buffer;
    shift += size;
  }
}

//-- ItemPartData class end --//
