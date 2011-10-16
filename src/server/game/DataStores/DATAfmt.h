/*
 * Copyright (C) 2008-2011 Trinity <http://www.trinitycore.org/>
 *
 * Copyright (C) 2010-2011 Strawberry-Pr0jcts <http://www.strawberry-pr0jcts.com/>
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

#ifndef STRAWBERRY_DBCSFRM_H
#define STRAWBERRY_DBCSFRM_H

#include "Logging/Log.h"

// NEW DATA FORMAT SYSTEM WILL NOT USE FOR A WHILE..

const char Achievementfmt[] = "niixsxiixixxii";
const char AchievementCriteriafmt[] = "niiiiiiiixsiiiiixxxxxxx";
const char AreaTableEntryfmt[] = "iiinixxxxxisixxxxxxxxxxxxx";
const char AreaGroupEntryfmt[] = "niiiiiii";
const char AreaPOIEntryfmt[] = "niiiiiiiiiiiffixixxixx";
const char AreaTriggerEntryfmt[] = "nifffxxxfffff";
const char ArmorLocationfmt[] = "nfffff";
const char AuctionHouseEntryfmt[] = "niiix";
const char BankBagSlotPricesEntryfmt[] = "ni";
const char BarberShopStyleEntryfmt[] = "nixxxiii";
const char BattlemasterListEntryfmt[] = "niiiiiiiiixsiiiiiiii";
const char CharStartOutfitEntryfmt[] = "diiiiiiiiiiiiiiiiiiiiiiiiixxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
const char CharTitlesEntryfmt[] = "nxsxix";
const char ChatChannelsEntryfmt[] = "nixsx";
const char ChrClassesEntryfmt[] = "nixsxxxixiixxx";
const char ChrRacesEntryfmt[] = "nxixiixixxxxixsxxxxxixxx";
const char CinematicSequencesEntryfmt[] = "nxxxxxxxxx";
const char CreatureDisplayInfofmt[] = "nxxxfxxxxxxxxxxxx";
const char CreatureFamilyfmt[] = "nfifiiiiixsx";
const char CreatureSpellDatafmt[] = "niiiixxxx";
const char CreatureTypefmt[] = "nxx";
const char CurrencyTypesfmt[] = "nxxxxxxiixx";
const char DestructibleModelDatafmt[] = "ixxixxxixxxixxxixxxxxxxx";
const char DungeonEncounterfmt[] = "iiixisxx";
const char DurabilityCostsfmt[] = "niiiiiiiiiiiiiiiiiiiiiiiiiiiii";
const char DurabilityQualityfmt[] = "nf";
const char EmotesEntryfmt[] = "nxxiiixx";
const char EmotesTextEntryfmt[] = "nxixxxxxxxxxxxxxxxx";
const char FactionEntryfmt[] = "niiiiiiiiiiiiiiiiiiffixsxx";
const char FactionTemplateEntryfmt[] = "niiiiiiiiiiiii";
const char GameObjectDisplayInfofmt[] = "nxxxxxxxxxxxffffffxxx";
const char GemPropertiesEntryfmt[] = "nixxix";
const char GlyphPropertiesfmt[] = "niii";
const char GlyphSlotfmt[] = "nii";
const char GtBarberShopCostBasefmt[] = "xf";
const char GtCombatRatingsfmt[] = "xf";
const char GtChanceToMeleeCritBasefmt[] = "xf";
const char GtChanceToMeleeCritfmt[] = "xf";
const char GtChanceToSpellCritBasefmt[] = "xf";
const char GtChanceToSpellCritfmt[] = "xf";
const char GtOCTClassCombatRatingScalarfmt[] = "df";
const char GtOCTHpPerStaminafmt[] = "xf";
const char GtRegenMPPerSptfmt[] = "xf";
const char GtSpellScalingfmt[] = "nf";
const char Holidaysfmt[] = "nxiixxxxxxxxixxxxxxxxxxxxxxxixxxxxxxxxxxiixxxxxxxxxsxix";
const char ItemArmorQualityfmt[] = "nfffffffi";
const char ItemArmorShieldfmt[] = "nifffffff";
const char ItemArmorTotalfmt[] = "niffff";
const char ItemBagFamilyfmt[] = "nx";
const char ItemDamagefmt[] = "nfffffffi";
const char ItemLimitCategoryEntryfmt[] = "nxii";
const char ItemRandomPropertiesfmt[] = "nxiiiiis";
const char ItemRandomSuffixfmt[] = "nsxiiiiiiiiii";
const char ItemSetEntryfmt[] = "dsiiiiiiiiiixxxxxxxiiiiiiiiiiiiiiiiii";
const char ItemReforgefmt[]="nifif";
const char LFGDungeonEntryfmt[] = "nxiiiiiiixixxixixx";
const char LockEntryfmt[] = "niiiiiiiiiiiiiiiiiiiiiiiixxxxxxxx";
const char MailTemplateEntryfmt[] = "nxs";
const char MapEntryfmt[] = "nxixxxsixxixiffxiixx";
const char MapDifficultyEntryfmt[] = "diisiix";
const char MountCapabilityfmt[] = "niixxiii";
const char MountTypefmt[] = "niiiiiiiiiiiiiiiiixxxxxxx";
const char MovieEntryfmt[] = "nxxx";
const char OverrideSpellDatafmt[] = "niiiiiiiiiixx";
const char QuestSortEntryfmt[] = "nx";
const char QuestXPfmt[] = "niiiiiiiiii";
const char QuestFactionRewardfmt[] = "niiiiiiiiii";
const char PvPDifficultyfmt[] = "diiiii";
const char RandomPropertiesPointsfmt[] = "niiiiiiiiiiiiiii";
const char ScalingStatDistributionfmt[] = "niiiiiiiiiiiiiiiiiiiixi";
const char ScalingStatValuesfmt[] = "iniiiiiiiiiiiiiiiiiiiixxxxxxxxxxxxxxxxxxxxxxxxx";
const char SkillLinefmt[] = "nisxixi";
const char SkillLineAbilityfmt[] = "niiiixxiiiiixx";
const char SoundEntriesfmt[] = "nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
const char SpellCastTimefmt[] = "nixx";
const char SpellDifficultyfmt[] = "niiii";
const char SpellDurationfmt[] = "niii";
const char SpellEntryfmt[]      = "niiiiiiiiixxiiiifiiiissxxiixxixiiiiiiixiiiiiiiix";
const char True_SpellEntryfmt[] = "iiiiiiiiiixxiiiifiiiissxxiixxixiiiiiiixiiiiiiiixiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiifffiiiiiiiiifffiiiiiiiiiiiiiiiiiifffiiifffiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiffffffffffiiiiiiiiiii";
const char SpellAuraOptionsEntryfmt[] = "niiii";
const char SpellAuraRestrictionsEntryfmt[] = "niiiiiiii";
const char SpellCastingRequirementsEntryfmt[] = "nixxixi";
const char SpellCategoriesEntryfmt[] = "niiiiii";
const char SpellClassOptionsEntryfmt[] = "nxiiiix";
const char SpellCooldownsEntryfmt[] = "niii";
const char SpellEffectEntryfmt[] = "nifiiiffiiiiiifixfiiiiiiiix";
const char SpellEquippedItemsEntryfmt[] = "niii";
const char SpellInterruptsEntryfmt[] = "nixixi";
const char SpellLevelsEntryfmt[] = "niii";
const char SpellPowerEntryfmt[] = "niiiixx";
const char SpellReagentsEntryfmt[] = "niiiiiiiiiiiiiiii";
const char SpellScalingEntryfmt[] = "niiiiffffffffffi";
const char SpellShapeshiftEntryfmt[] = "nixixx";
const char SpellTargetRestrictionsEntryfmt[] = "dfiiii";
const char SpellTotemsEntryfmt[] = "niiii";
const char SpellFocusObjectfmt[] = "nx";
const char SpellItemEnchantmentfmt[] = "nxiiiiiixxxiiisiiiiiiix";
const char SpellItemEnchantmentConditionfmt[] = "nbbbbbxxxxxbbbbbbbbbbiiiiiXXXXX";
const char SpellRadiusfmt[] = "nfxf";
const char SpellRangefmt[] = "nffffixx";
const char SpellRuneCostfmt[] = "niiii";
const char SpellShapeshiftFormfmt[] = "nxxiixiiixxiiiiiiiixx";
const char SummonPropertiesfmt[] = "niiiii";
const char GuildPerksfmt[] = "nii";
const char TalentEntryfmt[] = "niiiiiiiiixxixxxxxx";
const char TalentTabEntryfmt[] = "nxxiiixxxii";
const char TalentTreePrimarySpellsfmt[] = "niix";
const char TaxiNodesEntryfmt[] = "nifffsiixxx";
const char TaxiPathEntryfmt[] = "niii";
const char TaxiPathNodeEntryfmt[] = "diiifffiiii";
const char TotemCategoryEntryfmt[] = "nxii";
const char VehicleEntryfmt[] = "niffffiiiiiiiifffffffffffffffssssfifiixx";
const char VehicleSeatEntryfmt[] = "niiffffffffffiiiiiifffffffiiifffiiiiiiiffiiiiixxxxxxxxxxxxxxxxxxxx";
const char WMOAreaTableEntryfmt[] = "niiixxxxxiixxxx";
const char WorldMapAreaEntryfmt[] = "xinxffffixxx";
const char WorldMapOverlayEntryfmt[] = "nxiiiixxxxxxxxx";
const char WorldSafeLocsEntryfmt[] = "nifffx";
const char PhaseEntryfmt[] = "nsi";
const char Itemfmt[] = "niiiiiii";
const char ItemCurrencyCostfmt[] = "di";
const char ItemExtendedCostEntryfmt[] = "nxxiiiiiiiiiiiixiiiiiiiiiixxxxx";

/*enum DATAFormats
{
    Achievementfmt,
    AchievementCriteriafmt,
    AreaTableEntryfmt,
    AreaGroupEntryfmt,
    AreaPOIEntryfmt,
    AreaTriggerEntryfmt,
    ArmorLocationfmt,
    AuctionHouseEntryfmt,
    BankBagSlotPricesEntryfmt,
    BarberShopStyleEntryfmt,
    BattlemasterListEntryfmt,
    CharStartOutfitEntryfmt,
    CharTitlesEntryfmt,
    ChatChannelsEntryfmt,
    ChrClassesEntryfmt,
    ChrRacesEntryfmt,
    CinematicSequencesEntryfmt,
    CreatureDisplayInfofmt,
    CreatureFamilyfmt,
    CreatureSpellDatafmt,
    CreatureTypefmt,
    CurrencyTypesfmt,
    DestructibleModelDatafmt,
    DungeonEncounterfmt,
    DurabilityCostsfmt,
    DurabilityQualityfmt,
    EmotesEntryfmt,
    EmotesTextEntryfmt,
    FactionEntryfmt,
    FactionTemplateEntryfmt,
    GameObjectDisplayInfofmt,
    GemPropertiesEntryfmt,
    GlyphPropertiesfmt,
    GlyphSlotfmt,
    GtBarberShopCostBasefmt,
    GtCombatRatingsfmt,
    GtChanceToMeleeCritBasefmt,
    GtChanceToMeleeCritfmt,
    GtChanceToSpellCritBasefmt,
    GtChanceToSpellCritfmt,
    GtOCTClassCombatRatingScalarfmt,
    //GtOCTRegenHPfmt,
    //GtOCTRegenMPfmt,
    //GtRegenHPPerSptfmt,
    GtOCTHpPerStaminafmt,
    GtRegenMPPerSptfmt,
    GtSpellScalingfmt,
    Holidaysfmt,
    ItemArmorQualityfmt,
    ItemArmorShieldfmt,
    ItemArmorTotalfmt,
    ItemBagFamilyfmt,
    //ItemDisplayTemplateEntryfmt,
    //ItemCondExtCostsEntryfmt,
    ItemDamagefmt,
    ItemLimitCategoryEntryfmt,
    ItemRandomPropertiesfmt,
    ItemRandomSuffixfmt,
    ItemSetEntryfmt,
    ItemReforgefmt,
    LFGDungeonEntryfmt,
    LockEntryfmt,
    MailTemplateEntryfmt,
    MapEntryfmt,
    MapDifficultyEntryfmt,
    MountCapabilityfmt,
    MountTypefmt,
    MovieEntryfmt,
    OverrideSpellDatafmt,
    QuestSortEntryfmt,
    QuestXPfmt,
    QuestFactionRewardfmt,
    PvPDifficultyfmt,
    RandomPropertiesPointsfmt,
    ScalingStatDistributionfmt,
    ScalingStatValuesfmt,
    SkillLinefmt,
    SkillLineAbilityfmt,
    SoundEntriesfmt,
    SpellCastTimefmt,
    SpellDifficultyfmt,
    SpellDurationfmt,
    SpellEntryfmt,
    True_SpellEntryfmt,
    SpellAuraOptionsEntryfmt,
    SpellAuraRestrictionsEntryfmt,
    SpellCastingRequirementsEntryfmt,
    SpellCategoriesEntryfmt,
    SpellClassOptionsEntryfmt,
    SpellCooldownsEntryfmt,
    SpellEffectEntryfmt,
    SpellEquippedItemsEntryfmt,
    SpellInterruptsEntryfmt,
    SpellLevelsEntryfmt,
    SpellPowerEntryfmt,
    SpellReagentsEntryfmt,
    SpellScalingEntryfmt,
    SpellShapeshiftEntryfmt,
    SpellTargetRestrictionsEntryfmt,
    SpellTotemsEntryfmt,
    SpellFocusObjectfmt,
    SpellItemEnchantmentfmt,
    SpellItemEnchantmentConditionfmt,
    SpellRadiusfmt,
    SpellRangefmt,
    SpellRuneCostfmt,
    SpellShapeshiftFormfmt,
    SummonPropertiesfmt,
    GuildPerksfmt,
    TalentEntryfmt,
    TalentTabEntryfmt,
    TalentTreePrimarySpellsfmt,
    TaxiNodesEntryfmt,
    TaxiPathEntryfmt,
    TaxiPathNodeEntryfmt,
    TotemCategoryEntryfmt,
    VehicleEntryfmt,
    VehicleSeatEntryfmt,
    WMOAreaTableEntryfmt,
    WorldMapAreaEntryfmt,
    WorldMapOverlayEntryfmt,
    WorldSafeLocsEntryfmt,
    PhaseEntryfmt,
    Itemfmt,
    ItemCurrencyCostfmt,
    ItemExtendedCostEntryfmt,
    LastFormatData
};

extern void LoadDATAStores();

struct FormatHandler
{
    const char* name;
    DATAFormats enumValue;
};

#define MAX_FORMAT_TYPES 500
extern FormatHandler formatTable[MAX_FORMAT_TYPES];
extern char* formatEnumToFormat[LastFormatData];
extern char const* formatEnumToName[LastFormatData];

inline const char* LookupFormatName(DATAFormats enumValue)
{
    if (enumValue >= LastFormatData)
    {
        sLog->outString();
        sLog->outErrorDb("Error: Unknown format name, it's more than max!");
        return NULL;
    }
    return formatEnumToName[enumValue];
}

inline const char* LookupFormat(DATAFormats enumValue)
{
    if (enumValue >= LastFormatData)   // check can be removed for performance
        return "";
    return formatEnumToFormat[enumValue];
}*/

const char* LookupFormat(const char* format)
{
    return format;
}

#endif
