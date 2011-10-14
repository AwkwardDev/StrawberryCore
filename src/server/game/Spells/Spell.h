/*
 * Copyright (C) 2008-2011 Trinity <http://www.trinitycore.org/>
 *
 * Copyright (C) 2010-2011 Strawberry Project <http://www.strawberry-pr0jcts.com/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef __SPELL_H
#define __SPELL_H

#include "GridDefines.h"
#include "SharedDefines.h"
#include "ObjectMgr.h"

class Unit;
class Player;
class GameObject;
class DynamicObject;
class WorldObject;
class Aura;
class SpellScript;
class ByteBuffer;

struct SpellEntry;

#define SPELL_CHANNEL_UPDATE_INTERVAL (1 * IN_MILLISECONDS)

enum SpellCastTargetFlags
{
    TARGET_FLAG_SELF            = 0x00000000,
    TARGET_FLAG_UNUSED_1        = 0x00000001,               // not used
    TARGET_FLAG_UNIT            = 0x00000002,               // pguid
    TARGET_FLAG_UNIT_RAID       = 0x00000004,               // not sent, used to validate target (if raid member)
    TARGET_FLAG_UNIT_PARTY      = 0x00000008,               // not sent, used to validate target (if party member)
    TARGET_FLAG_ITEM            = 0x00000010,               // pguid
    TARGET_FLAG_SOURCE_LOCATION = 0x00000020,               // pguid, 3 float
    TARGET_FLAG_DEST_LOCATION   = 0x00000040,               // pguid, 3 float
    TARGET_FLAG_UNIT_ENEMY      = 0x00000080,               // not sent, used to validate target (if enemy) - used in 7 spells only
    TARGET_FLAG_UNIT_ALLY       = 0x00000100,               // not sent, used to validate target (if ally)
    TARGET_FLAG_CORPSE_ENEMY    = 0x00000200,               // pguid
    TARGET_FLAG_UNIT_DEAD       = 0x00000400,               // not sent, used to validate target (if dead creature)
    TARGET_FLAG_GAMEOBJECT      = 0x00000800,               // pguid, used with TARGET_GAMEOBJECT
    TARGET_FLAG_TRADE_ITEM      = 0x00001000,               // pguid
    TARGET_FLAG_STRING          = 0x00002000,               // string
    TARGET_FLAG_GAMEOBJECT_ITEM = 0x00004000,               // not sent, used with TARGET_GAMEOBJECT_ITEM
    TARGET_FLAG_CORPSE_ALLY     = 0x00008000,               // pguid
    TARGET_FLAG_UNIT_MINIPET    = 0x00010000,               // pguid, used to validate target (if non combat pet)
    TARGET_FLAG_GLYPH_SLOT      = 0x00020000,               // used in glyph spells
    TARGET_FLAG_DEST_TARGET     = 0x00040000,               // sometimes appears with DEST_TARGET spells (may appear or not for a given spell)
    TARGET_FLAG_UNUSED20        = 0x00080000,               // uint32 counter, loop { vec3 - screen position (?), guid }, not used so far
    TARGET_FLAG_UNIT_PASSENGER  = 0x00100000,               // guessed, used to validate target (if vehicle passenger)

    TARGET_FLAG_UNIT_MASK = TARGET_FLAG_UNIT | TARGET_FLAG_UNIT_RAID | TARGET_FLAG_UNIT_PARTY 
        | TARGET_FLAG_UNIT_ENEMY | TARGET_FLAG_UNIT_ALLY | TARGET_FLAG_UNIT_DEAD | TARGET_FLAG_UNIT_MINIPET | TARGET_FLAG_UNIT_PASSENGER,
    TARGET_FLAG_GAMEOBJECT_MASK = TARGET_FLAG_GAMEOBJECT | TARGET_FLAG_GAMEOBJECT_ITEM,
    TARGET_FLAG_CORPSE_MASK = TARGET_FLAG_CORPSE_ALLY | TARGET_FLAG_CORPSE_ENEMY,
};
#define MAX_TARGET_FLAGS 21

enum SpellsModType // These are only for "spell_stats".
{
    SPELL_MOD_MANA                            = 0,
    SPELL_MOD_HEALTH                          = 1,
    SPELL_MOD_AGILITY                         = 3,
    SPELL_MOD_STRENGTH                        = 4,
    SPELL_MOD_INTELLECT                       = 5,
    SPELL_MOD_SPIRIT                          = 6,
    SPELL_MOD_STAMINA                         = 7,
    SPELL_MOD_DEFENSE_SKILL_RATING            = 12,
    SPELL_MOD_DODGE_RATING                    = 13,
    SPELL_MOD_PARRY_RATING                    = 14,
    SPELL_MOD_BLOCK_RATING                    = 15,
    SPELL_MOD_HIT_MELEE_RATING                = 16,
    SPELL_MOD_HIT_RANGED_RATING               = 17,
    SPELL_MOD_HIT_SPELL_RATING                = 18,
    SPELL_MOD_CRIT_MELEE_RATING               = 19,
    SPELL_MOD_CRIT_RANGED_RATING              = 20,
    SPELL_MOD_CRIT_SPELL_RATING               = 21,
    SPELL_MOD_HIT_TAKEN_MELEE_RATING          = 22,
    SPELL_MOD_HIT_TAKEN_RANGED_RATING         = 23,
    SPELL_MOD_HIT_TAKEN_SPELL_RATING          = 24,
    SPELL_MOD_CRIT_TAKEN_MELEE_RATING         = 25,
    SPELL_MOD_CRIT_TAKEN_RANGED_RATING        = 26,
    SPELL_MOD_CRIT_TAKEN_SPELL_RATING         = 27,
    SPELL_MOD_HASTE_MELEE_RATING              = 28,
    SPELL_MOD_HASTE_RANGED_RATING             = 29,
    SPELL_MOD_HASTE_SPELL_RATING              = 30,
    SPELL_MOD_HIT_RATING                      = 31,
    SPELL_MOD_CRIT_RATING                     = 32,
    SPELL_MOD_HIT_TAKEN_RATING                = 33,
    SPELL_MOD_CRIT_TAKEN_RATING               = 34,
    SPELL_MOD_RESILIENCE_RATING               = 35,
    SPELL_MOD_HASTE_RATING                    = 36,
    SPELL_MOD_EXPERTISE_RATING                = 37,
    SPELL_MOD_ATTACK_POWER                    = 38,
    SPELL_MOD_RANGED_ATTACK_POWER             = 39,
    //SPELL_MOD_FERAL_ATTACK_POWER              = 40, not in 3.3
    SPELL_MOD_SPELL_HEALING_DONE              = 41,                 // deprecated
    SPELL_MOD_SPELL_DAMAGE_DONE               = 42,                 // deprecated
    SPELL_MOD_MANA_REGENERATION               = 43,
    SPELL_MOD_ARMOR_PENETRATION_RATING        = 44,
    SPELL_MOD_SPELL_POWER                     = 45,
    SPELL_MOD_HEALTH_REGEN                    = 46,
    SPELL_MOD_SPELL_PENETRATION               = 47,
    SPELL_MOD_BLOCK_VALUE                     = 48,
    SPELL_MOD_MASTERY_RATING                  = 49,
    SPELL_MOD_EXTRA_ARMOR                     = 50,
    SPELL_MOD_FIRE_RESISTANCE                 = 51,
    SPELL_MOD_FROST_RESISTANCE                = 52,
    SPELL_MOD_HOLY_RESISTANCE                 = 53,
    SPELL_MOD_SHADOW_RESISTANCE               = 54,
    SPELL_MOD_NATURE_RESISTANCE               = 55,
    SPELL_MOD_ARCANE_RESISTANCE               = 56,
    SPELL_MOD_ATTACK_POWER_POS_AND_NEG        = 57,                 // independent
    SPELL_MOD_ATTACK_POWER_RANGED_POS_AND_NEG = 58,                 // independent
};
#define MAX_SPELL_MOD 58

enum SpellCastFlags
{
    CAST_FLAG_NONE               = 0x00000000,
    CAST_FLAG_PENDING            = 0x00000001,              // aoe combat log?
    CAST_FLAG_UNKNOWN_2          = 0x00000002,
    CAST_FLAG_UNKNOWN_3          = 0x00000004,
    CAST_FLAG_UNKNOWN_4          = 0x00000008,              // ignore AOE visual
    CAST_FLAG_UNKNOWN_5          = 0x00000010,
    CAST_FLAG_AMMO               = 0x00000020,              // Projectiles visual
    CAST_FLAG_UNKNOWN_7          = 0x00000040,
    CAST_FLAG_UNKNOWN_8          = 0x00000080,
    CAST_FLAG_UNKNOWN_9          = 0x00000100,
    CAST_FLAG_UNKNOWN_10         = 0x00000200,
    CAST_FLAG_UNKNOWN_11         = 0x00000400,
    CAST_FLAG_POWER_LEFT_SELF    = 0x00000800,
    CAST_FLAG_UNKNOWN_13         = 0x00001000,
    CAST_FLAG_UNKNOWN_14         = 0x00002000,
    CAST_FLAG_UNKNOWN_15         = 0x00004000,
    CAST_FLAG_UNKNOWN_16         = 0x00008000,
    CAST_FLAG_UNKNOWN_17         = 0x00010000,
    CAST_FLAG_UNKNOWN_18         = 0x00020000,
    CAST_FLAG_ADJUST_MISSILE     = 0x00040000,
    CAST_FLAG_VISUAL_CHAIN       = 0x00080000,
    CAST_FLAG_UNKNOWN_21         = 0x00100000,
    CAST_FLAG_RUNE_LIST          = 0x00200000,
    CAST_FLAG_IMMUNITY           = 0x00400000,
    CAST_FLAG_UNKNOWN_24         = 0x00800000,
    CAST_FLAG_UNKNOWN_25         = 0x01000000,
    CAST_FLAG_UNKNOWN_26         = 0x02000000,
    CAST_FLAG_UNKNOWN_27         = 0x04000000,
    CAST_FLAG_UNKNOWN_28         = 0x08000000,
    CAST_FLAG_UNKNOWN_29         = 0x10000000,
    CAST_FLAG_UNKNOWN_30         = 0x20000000,
    CAST_FLAG_UNKNOWN_31         = 0x40000000,
    CAST_FLAG_UNKNOWN_32         = 0x80000000,
};

enum SpellRangeFlag
{
    SPELL_RANGE_DEFAULT             = 0,
    SPELL_RANGE_MELEE               = 1,     //melee
    SPELL_RANGE_RANGED              = 2,     //hunter range and ranged weapon
};

enum SpellNotifyPushType
{
    PUSH_NONE           = 0,
    PUSH_IN_FRONT,
    PUSH_IN_BACK,
    PUSH_IN_LINE,
    PUSH_IN_THIN_LINE,
    PUSH_SRC_CENTER,
    PUSH_DST_CENTER,
    PUSH_CASTER_CENTER, //this is never used in grid search
    PUSH_CHAIN,
};

enum SpellLogType
{
    SPELL_LOG_NON_MELEE_DAMAGE          = 29868,
    SPELL_LOG_EXECUTE                   = 46824,
    SPELL_LOG_ENERGIZE                  = 61676,
    SPELL_LOG_HEAL                      = 28292,
    SPELL_LOG_MISS                      = 48548,
    SPELL_LOG_PERIODIC_AURA             = 13192,
    SPELL_LOG_REMOVE_1                  = 0xED7E,       // currently unused (not updated even)
    SPELL_LOG_REMOVE_2                  = 0x9F74,       // currently unused (n/u)
    SPELL_LOG_REMOVE_3                  = 0xD557,       // currently unused (n/u)
};
bool IsQuestTameSpell(uint32 spellId);

namespace Trinity
{
    struct SpellNotifierCreatureAndPlayer;
}

typedef std::list<Unit*> UnitList;

class SpellCastTargets
{
    public:
        SpellCastTargets();
        ~SpellCastTargets();

        SpellCastTargets& operator=(const SpellCastTargets &target);

        void Read (ByteBuffer& data, Unit* caster);
        void Write (ByteBuffer& data);

        uint32 GetTargetMask() const { return m_targetMask; }
        void SetTargetMask(uint32 newMask) { m_targetMask = newMask; }

        uint64 GetUnitTargetGUID() const { return m_unitTargetGUID; }
        Unit* GetUnitTarget() const { return m_unitTarget; }
        void SetUnitTarget(Unit* target);

        Position const* GetSrc() const;
        void SetSrc(float x, float y, float z);
        void SetSrc(Position const& pos);
        void SetSrc(WorldObject const& wObj);
        void ModSrc(Position const& pos);

        WorldLocation const* GetDst() const;
        void SetDst(float x, float y, float z, float orientation, uint32 mapId = MAPID_INVALID);
        void SetDst(Position const& pos);
        void SetDst(WorldObject const& wObj);
        void SetDst(SpellCastTargets const& spellTargets);
        void ModDst(Position const& pos);

        uint64 GetGOTargetGUID() const { return m_GOTargetGUID; }
        GameObject* GetGOTarget() const { return m_GOTarget; }
        void SetGOTarget(GameObject* target);

        uint64 GetCorpseTargetGUID() const { return m_CorpseTargetGUID; }
        void SetCorpseTarget(Corpse* corpse);

        uint64 GetItemTargetGUID() const { return m_itemTargetGUID; }
        Item* GetItemTarget() const { return m_itemTarget; }
        uint32 GetItemTargetEntry() const { return m_itemTargetEntry; }
        void SetItemTarget(Item* item);
        void SetTradeItemTarget(Player* caster);
        void UpdateTradeSlotItem();

        bool IsEmpty() const { return m_GOTargetGUID == 0 && m_unitTargetGUID == 0 && m_itemTarget == 0 && m_CorpseTargetGUID == 0; }
        bool HasSrc() const { return GetTargetMask() & TARGET_FLAG_SOURCE_LOCATION; }
        bool HasDst() const { return GetTargetMask() & TARGET_FLAG_DEST_LOCATION; }
        bool HasTraj() const { return m_speed != 0; }

        float GetElevation() const { return m_elevation; }
        void SetElevation(float elevation) { m_elevation = elevation; }
        float GetSpeed() const { return m_speed; }
        void SetSpeed(float speed) { m_speed = speed; }

        float GetDist2d() const { return m_srcPos.GetExactDist2d(&m_dstPos); }
        float GetSpeedXY() const { return m_speed * cos(m_elevation); }
        float GetSpeedZ() const { return m_speed * sin(m_elevation); }

        void Update(Unit* caster);
        void OutDebug() const;

    private:
        uint32 m_targetMask;
        // objects (can be used at spell creating and after Update at casting
        Unit* m_unitTarget;
        GameObject* m_GOTarget;
        Item* m_itemTarget;

        // object GUID/etc, can be used always
        uint64 m_unitTargetGUID;
        uint64 m_GOTargetGUID;
        uint64 m_CorpseTargetGUID;
        uint64 m_itemTargetGUID;
        uint32 m_itemTargetEntry;

        uint64 m_srcTransGUID;
        Position m_srcTransOffset;
        Position m_srcPos;

        uint64 m_dstTransGUID;
        Position m_dstTransOffset;
        WorldLocation m_dstPos;

        float m_elevation, m_speed;
        std::string m_strTarget;
};

struct SpellValue
{
    explicit SpellValue(SpellEntry const* proto)
    {
        for (uint32 i = 0; i < MAX_SPELL_EFFECTS; ++i)
            EffectBasePoints[i] = proto->GetSpellEffectBasePoints(i);
        MaxAffectedTargets = proto->GetMaxAffectedTargets();
        RadiusMod = 1.0f;
        AuraStackAmount = 1;
    }
    int32     EffectBasePoints[MAX_SPELL_EFFECTS];
    uint32    MaxAffectedTargets;
    float     RadiusMod;
    uint8     AuraStackAmount;
};

enum SpellState
{
    SPELL_STATE_NULL      = 0,
    SPELL_STATE_PREPARING = 1,
    SPELL_STATE_CASTING   = 2,
    SPELL_STATE_FINISHED  = 3,
    SPELL_STATE_IDLE      = 4,
    SPELL_STATE_DELAYED   = 5
};

enum ReplenishType
{
    REPLENISH_UNDEFINED = 0,
    REPLENISH_HEALTH    = 20,
    REPLENISH_MANA      = 21,
    REPLENISH_RAGE      = 22
};

enum SpellTargets
{
    SPELL_TARGETS_NONE      = 0,
    SPELL_TARGETS_ALLY,
    SPELL_TARGETS_ENEMY,
    SPELL_TARGETS_ENTRY,
    SPELL_TARGETS_CHAINHEAL,
    SPELL_TARGETS_ANY,
    SPELL_TARGETS_GO
};

namespace Voragine
{
    struct SpellNotifierCreatureAndPlayer;
}

class Spell
{
    friend struct Voragine::SpellNotifierCreatureAndPlayer;
    friend void Unit::SetCurrentCastedSpell(Spell * pSpell);
    friend class SpellScript;
    public:

        void EffectNULL(SpellEffectEntry const* effect);
        void EffectUnused(SpellEffectEntry const* effect);
        void EffectDistract(SpellEffectEntry const* effect);
        void EffectPull(SpellEffectEntry const* effect);
        void EffectSchoolDMG(SpellEffectEntry const* effect);
        void EffectEnvirinmentalDMG(SpellEffectEntry const* effect);
        void EffectInstaKill(SpellEffectEntry const* effect);
        void EffectDummy(SpellEffectEntry const* effect);
        void EffectTeleportUnits(SpellEffectEntry const* effect);
        void EffectApplyAura(SpellEffectEntry const* effect);
        void EffectSendEvent(SpellEffectEntry const* effect);
        void EffectPowerBurn(SpellEffectEntry const* effect);
        void EffectPowerDrain(SpellEffectEntry const* effect);
        void EffectHeal(SpellEffectEntry const* effect);
        void EffectBind(SpellEffectEntry const* effect);
        void EffectHealthLeech(SpellEffectEntry const* effect);
        void EffectQuestComplete(SpellEffectEntry const* effect);
        void EffectCreateItem(SpellEffectEntry const* effect);
        void EffectCreateItem2(SpellEffectEntry const* effect);
        void EffectCreateRandomItem(SpellEffectEntry const* effect);
        void EffectPersistentAA(SpellEffectEntry const* effect);
        void EffectEnergize(SpellEffectEntry const* effect);
        void EffectOpenLock(SpellEffectEntry const* effect);
        void EffectSummonChangeItem(SpellEffectEntry const* effect);
        void EffectProficiency(SpellEffectEntry const* effect);
        void EffectApplyAreaAura(SpellEffectEntry const* effect);
        void EffectSummonType(SpellEffectEntry const* effect);
        void EffectLearnSpell(SpellEffectEntry const* effect);
        void EffectDispel(SpellEffectEntry const* effect);
        void EffectDualWield(SpellEffectEntry const* effect);
        void EffectPickPocket(SpellEffectEntry const* effect);
        void EffectAddFarsight(SpellEffectEntry const* effect);
        void EffectUntrainTalents(SpellEffectEntry const* effect);
        void EffectHealMechanical(SpellEffectEntry const* effect);
        void EffectJump(SpellEffectEntry const* effect);
        void EffectJumpDest(SpellEffectEntry const* effect);
        void EffectLeapBack(SpellEffectEntry const* effect);
        void EffectQuestClear(SpellEffectEntry const* effect);
        void EffectTeleUnitsFaceCaster(SpellEffectEntry const* effect);
        void EffectLearnSkill(SpellEffectEntry const* effect);
        void EffectAddHonor(SpellEffectEntry const* effect);
        void EffectTradeSkill(SpellEffectEntry const* effect);
        void EffectEnchantItemPerm(SpellEffectEntry const* effect);
        void EffectEnchantItemTmp(SpellEffectEntry const* effect);
        void EffectTameCreature(SpellEffectEntry const* effect);
        void EffectSummonPet(SpellEffectEntry const* effect);
        void EffectLearnPetSpell(SpellEffectEntry const* effect);
        void EffectWeaponDmg(SpellEffectEntry const* effect);
        void EffectForceCast(SpellEffectEntry const* effect);
        void EffectForceCastWithValue(SpellEffectEntry const* effect);
        void EffectTriggerSpell(SpellEffectEntry const* effect);
        void EffectTriggerMissileSpell(SpellEffectEntry const* effect);
        void EffectThreat(SpellEffectEntry const* effect);
        void EffectHealMaxHealth(SpellEffectEntry const* effect);
        void EffectInterruptCast(SpellEffectEntry const* effect);
        void EffectSummonObjectWild(SpellEffectEntry const* effect);
        void EffectScriptEffect(SpellEffectEntry const* effect);
        void EffectSanctuary(SpellEffectEntry const* effect);
        void EffectAddComboPoints(SpellEffectEntry const* effect);
        void EffectDuel(SpellEffectEntry const* effect);
        void EffectStuck(SpellEffectEntry const* effect);
        void EffectSummonPlayer(SpellEffectEntry const* effect);
        void EffectActivateObject(SpellEffectEntry const* effect);
        void EffectApplyGlyph(SpellEffectEntry const* effect);
        void EffectEnchantHeldItem(SpellEffectEntry const* effect);
        void EffectSummonObject(SpellEffectEntry const* effect);
        void EffectResurrect(SpellEffectEntry const* effect);
        void EffectParry(SpellEffectEntry const* effect);
        void EffectBlock(SpellEffectEntry const* effect);
        void EffectLeap(SpellEffectEntry const* effect);
        void EffectTransmitted(SpellEffectEntry const* effect);
        void EffectDisEnchant(SpellEffectEntry const* effect);
        void EffectInebriate(SpellEffectEntry const* effect);
        void EffectFeedPet(SpellEffectEntry const* effect);
        void EffectDismissPet(SpellEffectEntry const* effect);
        void EffectReputation(SpellEffectEntry const* effect);
        void EffectForceDeselect(SpellEffectEntry const* effect);
        void EffectSelfResurrect(SpellEffectEntry const* effect);
        void EffectSkinning(SpellEffectEntry const* effect);
        void EffectCharge(SpellEffectEntry const* effect);
        void EffectChargeDest(SpellEffectEntry const* effect);
        void EffectProspecting(SpellEffectEntry const* effect);
        void EffectMilling(SpellEffectEntry const* effect);
        void EffectRenamePet(SpellEffectEntry const* effect);
        void EffectSendTaxi(SpellEffectEntry const* effect);
        void EffectSummonCritter(SpellEffectEntry const* effect);
        void EffectKnockBack(SpellEffectEntry const* effect);
        void EffectPullTowards(SpellEffectEntry const* effect);
        void EffectDispelMechanic(SpellEffectEntry const* effect);
        void EffectSummonDeadPet(SpellEffectEntry const* effect);
        void EffectDestroyAllTotems(SpellEffectEntry const* effect);
        void EffectDurabilityDamage(SpellEffectEntry const* effect);
        void EffectSkill(SpellEffectEntry const* effect);
        void EffectTaunt(SpellEffectEntry const* effect);
        void EffectDurabilityDamagePCT(SpellEffectEntry const* effect);
        void EffectModifyThreatPercent(SpellEffectEntry const* effect);
        void EffectResurrectNew(SpellEffectEntry const* effect);
        void EffectAddExtraAttacks(SpellEffectEntry const* effect);
        void EffectSpiritHeal(SpellEffectEntry const* effect);
        void EffectSkinPlayerCorpse(SpellEffectEntry const* effect);
        void EffectStealBeneficialBuff(SpellEffectEntry const* effect);
        void EffectUnlearnSpecialization(SpellEffectEntry const* effect);
        void EffectHealPct(SpellEffectEntry const* effect);
        void EffectEnergizePct(SpellEffectEntry const* effect);
        void EffectTriggerSpellWithValue(SpellEffectEntry const* effect);
        void EffectTriggerRitualOfSummoning(SpellEffectEntry const* effect);
        void EffectKillCreditPersonal(SpellEffectEntry const* effect);
        void EffectKillCredit(SpellEffectEntry const* effect);
        void EffectQuestFail(SpellEffectEntry const* effect);
        void EffectQuestStart(SpellEffectEntry const* effect);
        void EffectRedirectThreat(SpellEffectEntry const* effect);
        void EffectGameObjectDamage(SpellEffectEntry const* effect);
        void EffectGameObjectRepair(SpellEffectEntry const* effect);
        void EffectGameObjectSetDestructionState(SpellEffectEntry const* effect);
        void EffectActivateRune(SpellEffectEntry const* effect);
        void EffectCreateTamedPet(SpellEffectEntry const* effect);
        void EffectDiscoverTaxi(SpellEffectEntry const* effect);
        void EffectTitanGrip(SpellEffectEntry const* effect);
        void EffectEnchantItemPrismatic(SpellEffectEntry const* effect);
        void EffectPlayMusic(SpellEffectEntry const* effect);
        void EffectSpecCount(SpellEffectEntry const* effect);
        void EffectActivateSpec(SpellEffectEntry const* effect);
        void EffectPlayerNotification(SpellEffectEntry const* effect);
        void EffectRemoveAura(SpellEffectEntry const* effect);
        void EffectCastButtons(SpellEffectEntry const* effect);
        void EffectRechargeManaGem(SpellEffectEntry const* effect);

        typedef std::set<Aura*> UsedSpellMods;

        Spell(Unit* caster, SpellEntry const *info, TriggerCastFlags triggerFlags, uint64 originalCasterGUID = 0, bool skipCheck = false);
        ~Spell();

        void prepare(SpellCastTargets const* targets, AuraEffect const* triggeredByAura = NULL);
        void cancel();
        void update(uint32 difftime);
        void cast(bool skipCheck = false);
        void finish(bool ok = true);
        void TakePower();
        void TakeAmmo();

        void TakeRunePower(bool didHit);
        void TakeReagents();
        void TakeCastItem();

        SpellCastResult CheckCast(bool strict);
        SpellCastResult CheckPetCast(Unit* target);

        // handlers
        void handle_immediate();
        uint64 handle_delayed(uint64 t_offset);
        // handler helpers
        void _handle_immediate_phase();
        void _handle_finish_phase();

        SpellCastResult CheckItems();
        SpellCastResult CheckRange(bool strict);
        SpellCastResult CheckPower();
        SpellCastResult CheckRuneCost(uint32 runeCostID);
        SpellCastResult CheckCasterAuras() const;

        int32 CalculateDamage(uint8 i, Unit* target) { return m_caster->CalculateSpellDamage(target, m_spellInfo, i, &m_spellValue->EffectBasePoints[i]); }

        bool HaveTargetsForEffect(uint8 effect) const;
        void Delayed();
        void DelayedChannel();
        uint32 getState() const { return m_spellState; }
        void setState(uint32 state) { m_spellState = state; }

        void DoCreateItem(uint32 i, uint32 itemtype);
        void WriteSpellGoTargets(WorldPacket * data);
        void WriteAmmoToPacket(WorldPacket * data);

        void SelectSpellTargets();
        void SelectEffectTargets(uint32 i, uint32 cur);
        void SelectTrajTargets();

        template<typename T> WorldObject* FindCorpseUsing();

        bool CheckTarget(Unit* target, uint32 eff);
        bool CanAutoCast(Unit* target);
        void CheckSrc() { if (!m_targets.HasSrc()) m_targets.SetSrc(*m_caster); }
        void CheckDst() { if (!m_targets.HasDst()) m_targets.SetDst(*m_caster); }

        static void SendCastResult(Player* caster, SpellEntry const* spellInfo, uint8 cast_count, SpellCastResult result, SpellCustomErrors customError = SPELL_CUSTOM_ERROR_NONE);
        void SendCastResult(SpellCastResult result);
        void SendSpellStart();
        void SendSpellGo();
        void SendSpellCooldown();
        void SendLogExecute();
        void ExecuteLogEffectTakeTargetPower(uint8 effIndex, Unit* target, uint32 powerType, uint32 powerTaken, float gainMultiplier);
        void ExecuteLogEffectExtraAttacks(uint8 effIndex, Unit* victim, uint32 attCount);
        void ExecuteLogEffectInterruptCast(uint8 effIndex, Unit* victim, uint32 spellId);
        void ExecuteLogEffectDurabilityDamage(uint8 effIndex, Unit* victim, uint32 itemslot, uint32 damage);
        void ExecuteLogEffectOpenLock(uint8 effIndex, Object * obj);
        void ExecuteLogEffectCreateItem(uint8 effIndex, uint32 entry);
        void ExecuteLogEffectDestroyItem(uint8 effIndex, uint32 entry);
        void ExecuteLogEffectSummonObject(uint8 effIndex, WorldObject * obj);
        void ExecuteLogEffectUnsummonObject(uint8 effIndex, WorldObject * obj);
        void ExecuteLogEffectResurrect(uint8 effIndex, Unit* target);
        void SendInterrupted(uint8 result);
        void SendChannelUpdate(uint32 time);
        void SendChannelStart(uint32 duration);
        void SendResurrectRequest(Player* target);
        void SendPlaySpellVisual(uint32 SpellID);

        void HandleEffects(Unit *pUnitTarget, Item *pItemTarget, GameObject *pGOTarget, uint32 i);
        void HandleThreatSpells(uint32 spellId);

        const SpellEntry * const m_spellInfo;
        SpellInterruptsEntry const* m_spellInterrupts;
        Item* m_CastItem;
        uint64 m_castItemGUID;
        uint8 m_cast_count;
        uint32 m_glyphIndex;
        uint32 m_preCastSpell;
        SpellCastTargets m_targets;
        int8 m_comboPointGain;
        SpellCustomErrors m_customError;

        UsedSpellMods m_appliedMods;

        int32 GetCastTime() const { return m_casttime; }
        bool IsAutoRepeat() const { return m_autoRepeat; }
        void SetAutoRepeat(bool rep) { m_autoRepeat = rep; }
        void ReSetTimer() { m_timer = m_casttime > 0 ? m_casttime : 0; }
        bool IsNextMeleeSwingSpell() const
        {
            return m_spellInfo->Attributes & SPELL_ATTR0_ON_NEXT_SWING;
        }
        bool IsTriggered() const {return _triggeredCastFlags & TRIGGERED_FULL_MASK;};
        bool IsChannelActive() const { return m_caster->GetUInt32Value(UNIT_CHANNEL_SPELL) != 0; }
        bool IsAutoActionResetSpell() const { return !IsTriggered() && (m_spellInfo->GetInterruptFlags() & SPELL_INTERRUPT_FLAG_AUTOATTACK);  }

        bool IsDeletable() const { return !m_referencedFromCurrentSpell && !m_executedCurrently; }
        void SetReferencedFromCurrent(bool yes) { m_referencedFromCurrentSpell = yes; }
        bool IsInterruptable() const { return !m_executedCurrently; }
        void SetExecutedCurrently(bool yes) {m_executedCurrently = yes;}
        uint64 GetDelayStart() const { return m_delayStart; }
        void SetDelayStart(uint64 m_time) { m_delayStart = m_time; }
        uint64 GetDelayMoment() const { return m_delayMoment; }

        bool IsNeedSendToClient() const;

        CurrentSpellTypes GetCurrentContainer();

        Unit* GetCaster() const { return m_caster; }
        Unit* GetOriginalCaster() const { return m_originalCaster; }
        SpellEntry const* GetSpellInfo() const { return m_spellInfo; }
        int32 GetPowerCost() const { return m_powerCost; }

        void UpdatePointers();                              // must be used at call Spell code after time delay (non triggered spell cast/update spell call/etc)

        bool CheckTargetCreatureType(Unit* target) const;

        void CleanupTargetList();

        void SetSpellValue(SpellValueMod mod, int32 value);

        void SetMagnetingAura(Aura* aura) { m_magnetingAura = aura; }
    protected:
        bool HasGlobalCooldown();
        void TriggerGlobalCooldown();
        void CancelGlobalCooldown();

        void SendLoot(uint64 guid, LootType loottype);

        Unit* const m_caster;

        SpellValue * const m_spellValue;

        uint64 m_originalCasterGUID;                        // real source of cast (aura caster/etc), used for spell targets selection
                                                            // e.g. damage around area spell trigered by victim aura and damage enemies of aura caster
        Unit* m_originalCaster;                             // cached pointer for m_originalCaster, updated at Spell::UpdatePointers()

        Spell** m_selfContainer;                            // pointer to our spell container (if applicable)

        //Spell data
        SpellSchoolMask m_spellSchoolMask;                  // Spell school (can be overwrite for some spells (wand shoot for example)
        WeaponAttackType m_attackType;                      // For weapon based attack
        int32 m_powerCost;                                  // Calculated spell cost initialized only in Spell::prepare
        int32 m_casttime;                                   // Calculated spell cast time initialized only in Spell::prepare
        bool m_canReflect;                                  // can reflect this spell?
        bool m_autoRepeat;
        uint8 m_runesState;

        uint8 m_delayAtDamageCount;
        bool isDelayableNoMore()
        {
            if (m_delayAtDamageCount >= 2)
                return true;

            m_delayAtDamageCount++;
            return false;
        }

        // Delayed spells system
        uint64 m_delayStart;                                // time of spell delay start, filled by event handler, zero = just started
        uint64 m_delayMoment;                               // moment of next delay call, used internally
        bool m_immediateHandled;                            // were immediate actions handled? (used by delayed spells only)

        // These vars are used in both delayed spell system and modified immediate spell system
        bool m_referencedFromCurrentSpell;                  // mark as references to prevent deleted and access by dead pointers
        bool m_executedCurrently;                           // mark as executed to prevent deleted and access by dead pointers
        bool m_needComboPoints;
        uint8 m_applyMultiplierMask;
        float m_damageMultipliers[3];

        // Current targets, to be used in SpellEffects (MUST BE USED ONLY IN SPELL EFFECTS)
        Unit* unitTarget;
        Item* itemTarget;
        GameObject* gameObjTarget;
        int32 damage;
        // used in effects handlers
        Aura * m_spellAura;
        // pointer to magneting aura if spell is redirected
        Aura* m_magnetingAura;

        // this is set in Spell Hit, but used in Apply Aura handler
        DiminishingLevels m_diminishLevel;
        DiminishingGroup m_diminishGroup;

        // -------------------------------------------
        GameObject* focusObject;

        // Damage and healing in effects need just calculate
        int32 m_damage;           // Damge   in effects count here
        int32 m_healing;          // Healing in effects count here
        int32 m_final_damage;     // Final damage in effects count here

        // ******************************************
        // Spell trigger system
        // ******************************************
        uint32 m_procAttacker;                // Attacker trigger flags
        uint32 m_procVictim;                  // Victim   trigger flags
        uint32 m_procEx;
        void   prepareDataForTriggerSystem(AuraEffect const* triggeredByAura);

        // *****************************************
        // Spell target subsystem
        // *****************************************
        // Targets store structures and data
        struct TargetInfo
        {
            uint64 targetGUID;
            uint64 timeDelay;
            SpellMissInfo missCondition:8;
            SpellMissInfo reflectResult:8;
            uint8  effectMask:8;
            bool   processed:1;
            bool   alive:1;
            bool   crit:1;
            bool   scaleAura:1;
            int32  damage;
        };
        std::list<TargetInfo> m_UniqueTargetInfo;
        uint8 m_channelTargetEffectMask;                        // Mask req. alive targets

        struct GOTargetInfo
        {
            uint64 targetGUID;
            uint64 timeDelay;
            uint8  effectMask:8;
            bool   processed:1;
        };
        std::list<GOTargetInfo> m_UniqueGOTargetInfo;

        struct ItemTargetInfo
        {
            Item  *item;
            uint8 effectMask;
        };
        std::list<ItemTargetInfo> m_UniqueItemInfo;

        void AddUnitTarget(Unit* target, uint32 effIndex);
        void AddUnitTarget(uint64 unitGUID, uint32 effIndex);
        void AddGOTarget(GameObject* target, uint32 effIndex);
        void AddGOTarget(uint64 goGUID, uint32 effIndex);
        void AddItemTarget(Item* target, uint32 effIndex);
        void DoAllEffectOnTarget(TargetInfo *target);
        SpellMissInfo DoSpellHitOnUnit(Unit *unit, uint32 effectMask, bool scaleAura);
        void DoTriggersOnSpellHit(Unit *unit, uint8 effMask);
        void DoAllEffectOnTarget(GOTargetInfo *target);
        void DoAllEffectOnTarget(ItemTargetInfo *target);
        bool UpdateChanneledTargetList();
        void SearchAreaTarget(std::list<Unit*> &unitList, float radius, SpellNotifyPushType type, SpellTargets TargetType, uint32 entry = 0);
        void SearchGOAreaTarget(std::list<GameObject*> &gobjectList, float radius, SpellNotifyPushType type, SpellTargets TargetType, uint32 entry = 0);
        void SearchChainTarget(std::list<Unit*> &unitList, float radius, uint32 unMaxTargets, SpellTargets TargetType);
        WorldObject* SearchNearbyTarget(float range, SpellTargets TargetType, SpellEffectEntry const* effect);
        bool IsValidSingleTargetEffect(Unit const* target, Targets type) const;
        bool IsValidSingleTargetSpell(Unit const* target) const;
        bool IsValidDeadOrAliveTarget(Unit const* target) const;
        void CalculateDamageDoneForAllTargets();
        int32 CalculateDamageDone(Unit *unit, const uint32 effectMask, float *multiplier);
        void SpellDamageSchoolDmg(SpellEffectEntry const* effect);
        void SpellDamageWeaponDmg(SpellEffectEntry const* effect);
        void SpellDamageHeal(SpellEffectEntry const* effect);

        void PrepareTargetProcessing();
        void FinishTargetProcessing();

        // spell execution log
        void InitEffectExecuteData(uint8 effIndex);
        void CleanupEffectExecuteData();
        void CheckEffectExecuteData();

        // Scripting system
        void LoadScripts();
        SpellCastResult CallScriptCheckCastHandlers();
        void PrepareScriptHitHandlers();
        bool CallScriptEffectHandlers(SpellEffIndex effIndex);
        void CallScriptBeforeHitHandlers();
        void CallScriptOnHitHandlers();
        void CallScriptAfterHitHandlers();
        void CallScriptAfterUnitTargetSelectHandlers(std::list<Unit*>& unitTargets, SpellEffectEntry const* effect);
        std::list<SpellScript *> m_loadedScripts;

        bool CanExecuteTriggersOnHit(uint8 effMask) const;
        void PrepareTriggersExecutedOnHit();
        typedef std::list< std::pair<SpellEntry const*, int32> > HitTriggerSpells;
        HitTriggerSpells m_hitTriggerSpells;

        // effect helpers
        void GetSummonPosition(uint32 i, Position &pos, float radius = 0.0f, uint32 count = 0);
        void SummonGuardian(uint32 i, uint32 entry, SummonPropertiesEntry const *properties);
        void CalculateJumpSpeeds(uint8 i, float dist, float & speedxy, float & speedz);

        SpellCastResult CanOpenLock(uint32 effIndex, uint32 lockid, SkillType& skillid, int32& reqSkillValue, int32& skillValue);
        // -------------------------------------------

        //List For Triggered Spells
        typedef std::vector< std::pair<SpellEntry const*, int32> > ChanceTriggerSpells;
        ChanceTriggerSpells m_ChanceTriggerSpells;

        uint32 m_spellState;
        uint32 m_timer;

        TriggerCastFlags _triggeredCastFlags;

        // if need this can be replaced by Aura copy
        // we can't store original aura link to prevent access to deleted auras
        // and in same time need aura data and after aura deleting.
        SpellEntry const* m_triggeredByAuraSpell;

        uint32 m_customAttr;
        bool m_skipCheck;
        uint32 m_effectMask;
        uint8 m_auraScaleMask;

        ByteBuffer * m_effectExecuteData[MAX_SPELL_EFFECTS];

#ifdef MAP_BASED_RAND_GEN
        int32 irand(int32 min, int32 max)       { return int32 (m_caster->GetMap()->mtRand.randInt(max - min)) + min; }
        uint32 urand(uint32 min, uint32 max)    { return m_caster->GetMap()->mtRand.randInt(max - min) + min; }
        int32 rand32()                          { return m_caster->GetMap()->mtRand.randInt(); }
        double rand_norm()                      { return m_caster->GetMap()->mtRand.randExc(); }
        double rand_chance()                    { return m_caster->GetMap()->mtRand.randExc(100.0); }
#endif
};

namespace Voragine
{
    struct SpellNotifierCreatureAndPlayer
    {
        std::list<Unit*> *i_data;
        SpellNotifyPushType i_push_type;
        float i_radius;
        SpellTargets i_TargetType;
        const Unit* const i_source;
        uint32 i_entry;
        const Position * const i_pos;
        bool i_requireDeadTarget;
        SpellEntry const* i_spellProto;

        SpellNotifierCreatureAndPlayer(Unit *source, std::list<Unit*> &data, float radius, SpellNotifyPushType type,
            SpellTargets TargetType = SPELL_TARGETS_ENEMY, const Position *pos = NULL, uint32 entry = 0, SpellEntry const* spellProto = NULL)
            : i_data(&data), i_push_type(type), i_radius(radius), i_TargetType(TargetType),
            i_source(source), i_entry(entry), i_pos(pos), i_spellProto(spellProto)
        {
            ASSERT(i_source);
        }

        template<class T> inline void Visit(GridRefManager<T>& m)
        {
            i_requireDeadTarget = i_spellProto ? bool(i_spellProto->AttributesEx3 & SPELL_ATTR3_REQUIRE_DEAD_TARGET) : false;

            for (typename GridRefManager<T>::iterator itr = m.begin(); itr != m.end(); ++itr)
            {
                Unit* target = (Unit*)itr->getSource();

                if (!i_source->canSeeOrDetect(target, true))
                    continue;

                switch (i_TargetType)
                {
                    case SPELL_TARGETS_ENEMY:
                        if (target->isTotem())
                            continue;
                        if (!target->isAttackableByAOE(i_spellProto))
                            continue;
                        if (i_source->IsControlledByPlayer())
                        {
                            if (i_source->IsFriendlyTo(target))
                                continue;
                        }
                        else
                        {
                            if (!i_source->IsHostileTo(target))
                                continue;
                        }
                        break;
                    case SPELL_TARGETS_ALLY:
                        if (target->isTotem())
                            continue;
                        if (!i_source->IsFriendlyTo(target))
                            continue;
                        if (target->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE))
                            continue;
                        if (target->GetTypeId() == TYPEID_PLAYER && target->ToPlayer()->isGameMaster())
                            continue;
                        if (target->isAlive() == i_requireDeadTarget)
                            continue;
                        break;
                    case SPELL_TARGETS_ENTRY:
                        if (target->GetEntry()!= i_entry)
                            continue;
                        break;
                    case SPELL_TARGETS_ANY:
                    default:
                        break;
                }

                switch(i_push_type)
                {
                    case PUSH_SRC_CENTER:
                    case PUSH_DST_CENTER:
                    case PUSH_CHAIN:
                    default:
                        if (target->IsWithinDist3d(i_pos, i_radius))
                            i_data->push_back(target);
                        break;
                    case PUSH_IN_FRONT:
                        if (i_source->isInFront(target, i_radius, static_cast<float>(M_PI/2)))
                            i_data->push_back(target);
                        break;
                    case PUSH_IN_BACK:
                        if (i_source->isInBack(target, i_radius, static_cast<float>(M_PI/2)))
                            i_data->push_back(target);
                        break;
                    case PUSH_IN_LINE:
                        if (i_source->HasInLine(target, i_radius, i_source->GetObjectSize()))
                            i_data->push_back(target);
                        break;
                    case PUSH_IN_THIN_LINE: // only traj
                        if (i_pos->HasInLine(target, i_radius, 0))
                            i_data->push_back(target);
                        break;
                }
            }
        }

        #ifdef _WIN32
        template<> inline void Visit(CorpseMapType &) {}
        template<> inline void Visit(GameObjectMapType &) {}
        template<> inline void Visit(DynamicObjectMapType &) {}
        #endif
    };

    #ifndef _WIN32
    template<> inline void SpellNotifierCreatureAndPlayer::Visit(CorpseMapType&) {}
    template<> inline void SpellNotifierCreatureAndPlayer::Visit(GameObjectMapType&) {}
    template<> inline void SpellNotifierCreatureAndPlayer::Visit(DynamicObjectMapType&) {}
    #endif
}

typedef void(Spell::*pEffect)(SpellEffectEntry const* spellEffect);

class SpellEvent : public BasicEvent
{
    public:
        SpellEvent(Spell* spell);
        virtual ~SpellEvent();

        virtual bool Execute(uint64 e_time, uint32 p_time);
        virtual void Abort(uint64 e_time);
        virtual bool IsDeletable() const;
    protected:
        Spell* m_Spell;
};
#endif
