#ifndef VIKINGS_FRONTEND_PACKAGES_H
#define VIKINGS_FRONTEND_PACKAGES_H

//-----------------------------------------------------------------------------//
//--  Classes performing objects parsing and prepping data for the frontend  --//
//-----------------------------------------------------------------------------//

#include "misc.h"
#include "Battle.h"
#include "GameCharacter.h"
#include "Item.h"
#include "ItemPart.h"
#include "UITextStorage.h"
#include "Collection.h"

#include <cstring>

//-- related functions --//

std::string get_kind_name(size_t kind);
std::string get_group_name(size_t group);
std::string get_rarity_name(size_t rarity);
std::string get_resource_name(size_t index);

//-- related functions end --//

//-- BasePackage class --//

class BasePackage {
  public:
    BasePackage(ssize_t id = FREE_ID, UITextStorage* dictionary): _id(id), _dictionary(dictionary) {}
    virtual ~BasePackage() {}
    ssize_t id() const { return this->_id; }
    virtual size_t clear() { return RC_OK; }
    virtual char* to_packet() const { RawPacket result; return result; }
    virtual void from_packet(char* packet) {}
  protected:
    ssize_t _id; // package id (similar with the source object's id)
    UITextStorage* _dictionary;

    virtual std::string get_tag_replacement(size_t tag_id) const { return std::string(); }
};

//-- BasePackage class end --//

//-- BattleData class --//

class BattleData: public BasePackage {
  public:
    BattleData(char* packet): _id(FREE_ID), _dictionary(NULL) { this->from_packet(packet); }
    BattleData(Battle* battle, UITextStorage* dictionary, Collection<BasePackage>& responses): BasePackage(battle->id(), dictionary) { this->parse_object(battle, responses); }
    virtual ~BattleData() {}

    virtual size_t clear() { this->_battle_log.clear(); }

    std::string log() const { return this->_battle_log; }
    GameCharacterData* survivor(ssize_t id) { return dynamic_cast<GameCharacterData*>(this->_survivors_data[id]); }
    size_t survivors_count() const { return this->_survivors_data.map().size(); }

    virtual char* to_packet() const;
    virtual void from_packet(char* packet);

  protected:
    virtual std::string get_tag_replacement(size_t tag_id) const;

  private:
    std::string _battle_log;
    Collection<BasePackage> _survivors_data;

    size_t parse_object(Battle* battle, Collection<BasePackage>& responses);
    void process_log(Battle* battle);
    void get_survivors(Battle* battle, Collection<BasePackage>& responses);
};

//-- BattleData class end --//

//-- CharacterData class --//

enum CharacerPackage { CP_NAME, CP_GENDER, CP_LEVEL, CP_SIZE };
enum StatsPackage { SP_TITLE, SP_MELEE, SP_RANGED, SP_DEFENSE, SP_SIZE };

class GameCharacterData: public BasePackage {
  public:
    GameCharacterData(char* packet): _id(FREE_ID), _dictionary(NULL) { this->from_packet(packet); }
    GameCharacterData(GameCharacter* character, UITextStorage* dictionary): BasePackage(character->id(), dictionary) { this->parse_object(character); }
    virtual ~GameCharacterData() {}

    std::string name() const { return this->_generals[CP_NAME]; }
    std::string gender() const { return this->_generals[CP_GENDER]; }
    std::string level() const { return this->_generals[CP_LEVEL]; }

    std::string generals(size_t index) const { if (index < this->_generals.size()) { return this->_generals[index]; } return std::string(); }

    std::string stats_title() const { return this->_stats[SP_TITLE]; }
    std::string melee() const { return this->_stats[SP_MELEE]; }
    std::string ranged() const { return this->_stats[SP_RANGED]; }
    std::string defense() const { return this->_stats[SP_DEFENSE]; }

    std::string stats(size_t index) const { if (index < this->_stats.size()) { return this->_generals[index]; } return std::string(); }

    virtual char* to_packet() const;
    virtual void from_packet(char* packet);

  protected:
    std::string get_tag_replacement(size_t tag_id) const;

  private:
    std::vector<std::string> _generals;
    std::vector<std::string> _stats;

    size_t parse_object(GameCharacter* character);
    void get_generals(GameCharacter* character);
    void get_stats(GameCharacter* character);
};

//-- CharacterData class end --//

//-- ItemData class --//

enum ItemGenerals { IG_NAME, IG_DESCRIPTION, IG_KIND, IG_PLACE, IG_RARITY, IG_SIZE };
enum ItemCosts { IC_TITLE, IC_GOLD, IC_FOOD, IC_WOOD, IC_IRON, IC_LEATHER, IC_SIZE };

class ItemData: public BasePackage {
  public:
    ItemData(char* packet): _id(FREE_ID), _dictionary(NULL) { this->from_packet(packet); }
    ItemData(Item* item, UITextStorage* dictionary, Collection<BasePackage>& responses): BasePackage(item->id(), dictionary) { this->parse_object(item, responses); }
    virtual ~ItemData();

    std::string name() const { return this->_generals[IG_NAME]; }
    std::string description() const { return this->_generals[IG_DESCRIPTION]; }
    std::string kind() const { return this->_generals[IG_KIND]; }
    std::string group() const { return this->_generals[IG_GROUP]; }
    std::string rarity() const { return this->_generals[IG_RARITY]; }

    std::string generals(size_t index) const { if (index < IG_SIZE) { return this->_generals[index]; } return std::string(); }

    std::string bonuses_title() const { return this->_bonuses[SP_TITLE]; }
    std::string melee_bonus() const { return this->_bonuses[SP_MELEE]; }
    std::string ranged_bonus() const { return this->_bonuses[SP_RANGED]; }
    std::string defense_bonus() const { return this->_bonuses[SP_DEFENSE]; }

    std::string bonuses(size_t index) const { if (index < this->_bonuses.size()) { return this->_bonuses[index]; }  return std::string(); }

    std::string cost_title() const { return this->_costs[IC_TITLE]; }
    std::string gold_cost() const { return this->_costs[IC_GOLD]; }
    std::string food_cost() const { return this->_costs[IC_FOOD]; }
    std::string wood_cost() const { return this->_costs[IC_WOOD]; }
    std::string iron_cost() const { return this->_costs[IC_IRON]; }
    std::string leather_cost() const { return this->_costs[IC_LEATHER]; }

    std::string costs(size_t index) const { if (index < this->_costs.size()) { return this->_costs[index]; } return std::string(); }

    ItemPartData* part(size_t index) { return dynamic_cast<ItemPartData*>(this->_parts[index]); }

    virtual char* to_packet() const;
    virtual void from_packet(char* packet);

  protected:
    std::string get_tag_replacement(size_t tag_id) const;

  private:
    std::vector<std::string> _generals;
    std::vector<std::string> _bonuses;
    std::vector<std::string> _costs;
    std::vector<BasePackage*> _parts;

    size_t parse_object(Item* item, Collection<BasePackage>& responses);
    void get_generals(Item* item);
    void get_bonuses(Item* item);
    void get_costs(Item* item);
    void get_parts(Item* item, Collection<BasePackage>& responses);
};

//-- ItemData class end --//

//-- ItemPartData class --//

class ItemPartData: public BasePackage {
  public:
    ItemPartData(ItemPart* item_part, UITextStorage* dictionary): BasePackage(item_part->id(), dictionary) { this->parse_object(item_part); }
    virtual ~ItemPartData() {}

    std::string name() const { return this->_generals[IG_NAME]; }
    std::string description() const { return this->_generals[IG_DESCRIPTION]; }
    std::string kind() const { return this->_generals[IG_KIND]; }
    std::string group() const { return this->_generals[IG_GROUP]; }
    std::string rarity() const { return this->_generals[IG_RARITY]; }

    std::string generals(size_t index) const { if (index < IG_SIZE) { return this->_generals[index]; } return std::string(); }

    std::string bonuses_title() const { return this->_bonuses[SP_TITLE]; }
    std::string melee_bonus() const { return this->_bonuses[SP_MELEE]; }
    std::string ranged_bonus() const { return this->_bonuses[SP_RANGED]; }
    std::string defense_bonus() const { return this->_bonuses[SP_DEFENSE]; }

    std::string bonuses(size_t index) const { if (index < this->_bonuses.size()) { return this->_bonuses[index]; }  return std::string(); }

    std::string cost_title() const { return this->_costs[IC_TITLE]; }
    std::string gold_cost() const { return this->_costs[IC_GOLD]; }
    std::string food_cost() const { return this->_costs[IC_FOOD]; }
    std::string wood_cost() const { return this->_costs[IC_WOOD]; }
    std::string iron_cost() const { return this->_costs[IC_IRON]; }
    std::string leather_cost() const { return this->_costs[IC_LEATHER]; }

    std::string costs(size_t index) const { if (index < this->_costs.size()) { return this->_costs[index]; } return std::string(); }

    virtual char* to_packet() const;
    virtual void from_packet(char* packet);

  protected:
    std::string get_tag_replacement(size_t tag_id) const;

  private:
    std::vector<std::string> _generals;
    std::vector<std::string> _bonuses;
    std::vector<std::string> _costs;

    size_t parse_object(ItemPart* item_part);
    void get_generals(ItemPart* item_part);
    void get_bonuses(ItemPart* item_part);
    void get_costs(ItemPart* item_part);
};

//-- ItemPartData class end --//

#endif
