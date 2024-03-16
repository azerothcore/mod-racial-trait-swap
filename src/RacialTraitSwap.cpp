/*
 *MIT License
 *
 *Copyright (c) 2023 Azerothcore
 *
 *Permission is hereby granted, free of charge, to any person obtaining a copy
 *of this software and associated documentation files (the "Software"), to deal
 *in the Software without restriction, including without limitation the rights
 *to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *copies of the Software, and to permit persons to whom the Software is
 *furnished to do so, subject to the following conditions:
 *
 *The above copyright notice and this permission notice shall be included in all
 *copies or substantial portions of the Software.
 *
 *THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *SOFTWARE.
 *
 * Racial Traits Swap NPC For Azerothcore Custom Changes Branch
 * Written by SPP DEV MDIC
 * SQL Assistance by Nemesis Dev Jinnai
 * Modified for Azerothcore
*/

#include "Chat.h"
#include "Config.h"
#include "Creature.h"
#include "GameEventMgr.h"
#include "Item.h"
#include "ItemEnchantmentMgr.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "WorldSession.h"

#define LOCALE_RACESWAP_0 "Racial Trait Swap"
#define LOCALE_RACESWAP_1 "인종 특성 교환"
#define LOCALE_RACESWAP_2 "Échange de traits raciaux"
#define LOCALE_RACESWAP_3 "Rassenmerkmalswechsel"
#define LOCALE_RACESWAP_4 "種族特質交換"
#define LOCALE_RACESWAP_5 "種族特質交換"
#define LOCALE_RACESWAP_6 "Intercambio de rasgos raciales"
#define LOCALE_RACESWAP_7 "Intercambio de rasgos raciales"
#define LOCALE_RACESWAP_8 "Обмен расовыми особенностями"

#define LOCALE_EXIT_0 "[EXIT]"
#define LOCALE_EXIT_1 "[출구]"
#define LOCALE_EXIT_2 "[SORTIR]"
#define LOCALE_EXIT_3 "[AUSFAHRT]"
#define LOCALE_EXIT_4 "[出口]"
#define LOCALE_EXIT_5 "[出口]"
#define LOCALE_EXIT_6 "[SALIDA]"
#define LOCALE_EXIT_7 "[SALIDA]"
#define LOCALE_EXIT_8 "[ВЫХОД]"

#define LOCALE_BACK_0 "[BACK]"
#define LOCALE_BACK_1 "[출구]"
#define LOCALE_BACK_2 "[RETOUR]"
#define LOCALE_BACK_3 "[ZURÜCK]"
#define LOCALE_BACK_4 "[背部]"
#define LOCALE_BACK_5 "[背部]"
#define LOCALE_BACK_6 "[ESPALDA]"
#define LOCALE_BACK_7 "[ESPALDA]"
#define LOCALE_BACK_8 "[НАЗАД]"

#define LOCALE_GOLD_0 " Gold."
#define LOCALE_GOLD_1 " 골드."
#define LOCALE_GOLD_2 " L' or."
#define LOCALE_GOLD_3 " Gold."
#define LOCALE_GOLD_4 " 金."
#define LOCALE_GOLD_5 " 金."
#define LOCALE_GOLD_6 " Oro."
#define LOCALE_GOLD_7 " Oro."
#define LOCALE_GOLD_8 " Золото."

// female icons
#define LOCALE_BES_0 "|TInterface\\icons\\Achievement_Character_Bloodelf_Female:25|tBlood Elf Racial Trait Swap -"
#define LOCALE_BES_1 "|TInterface\\icons\\Achievement_Character_Bloodelf_Female:25|t블러드 엘프 인종 특성 스왑 -"
#define LOCALE_BES_2 "|TInterface\\icons\\Achievement_Character_Bloodelf_Female:25|tÉchange de traits raciaux des elfes de sang -"
#define LOCALE_BES_3 "|TInterface\\icons\\Achievement_Character_Bloodelf_Female:25|tRassenwechsel der Blutelfen -"
#define LOCALE_BES_4 "|TInterface\\icons\\Achievement_Character_Bloodelf_Female:25|t血精靈種族特質交換 -"
#define LOCALE_BES_5 "|TInterface\\icons\\Achievement_Character_Bloodelf_Female:25|t血精靈種族特質交換 -"
#define LOCALE_BES_6 "|TInterface\\icons\\Achievement_Character_Bloodelf_Female:25|tIntercambio de rasgos raciales de elfos de sangre -"
#define LOCALE_BES_7 "|TInterface\\icons\\Achievement_Character_Bloodelf_Female:25|tIntercambio de rasgos raciales de elfos de sangre -"
#define LOCALE_BES_8 "|TInterface\\icons\\Achievement_Character_Bloodelf_Female:25|tОбмен расовой особенностью эльфов крови -"

// male icons
#define LOCALE_BES_9  "|TInterface\\icons\\Achievement_Character_Bloodelf_Male:25|tBlood Elf Racial Trait Swap -"
#define LOCALE_BES_10 "|TInterface\\icons\\Achievement_Character_Bloodelf_Male:25|t블러드 엘프 인종 특성 스왑 -"
#define LOCALE_BES_11 "|TInterface\\icons\\Achievement_Character_Bloodelf_Male:25|tÉchange de traits raciaux des elfes de sang -"
#define LOCALE_BES_12 "|TInterface\\icons\\Achievement_Character_Bloodelf_Male:25|tRassenwechsel der Blutelfen -"
#define LOCALE_BES_13 "|TInterface\\icons\\Achievement_Character_Bloodelf_Male:25|t血精靈種族特質交換 -"
#define LOCALE_BES_14 "|TInterface\\icons\\Achievement_Character_Bloodelf_Male:25|t血精靈種族特質交換 -"
#define LOCALE_BES_15 "|TInterface\\icons\\Achievement_Character_Bloodelf_Male:25|tIntercambio de rasgos raciales de elfos de sangre -"
#define LOCALE_BES_16 "|TInterface\\icons\\Achievement_Character_Bloodelf_Male:25|tIntercambio de rasgos raciales de elfos de sangre -"
#define LOCALE_BES_17 "|TInterface\\icons\\Achievement_Character_Bloodelf_Male:25|tОбмен расовой особенностью эльфов крови -"

// female icons
#define LOCALE_DRS_0 "|TInterface\\icons\\Achievement_Character_Draenei_Female:25|tDraenei Racial Trait Swap  -"
#define LOCALE_DRS_1 "|TInterface\\icons\\Achievement_Character_Draenei_Female:25|t드레나이 인종 특성 스왑 -"
#define LOCALE_DRS_2 "|TInterface\\icons\\Achievement_Character_Draenei_Female:25|tÉchange de traits raciaux draeneï -"
#define LOCALE_DRS_3 "|TInterface\\icons\\Achievement_Character_Draenei_Female:25|tDraenei Rasseneigenschaftstausch -"
#define LOCALE_DRS_4 "|TInterface\\icons\\Achievement_Character_Draenei_Female:25|t德萊尼人種特質交換 -"
#define LOCALE_DRS_5 "|TInterface\\icons\\Achievement_Character_Draenei_Female:25|t德萊尼人種特質交換 -"
#define LOCALE_DRS_6 "|TInterface\\icons\\Achievement_Character_Draenei_Female:25|tCambio de rasgo racial Draenei -"
#define LOCALE_DRS_7 "|TInterface\\icons\\Achievement_Character_Draenei_Female:25|tCambio de rasgo racial Draenei -"
#define LOCALE_DRS_8 "|TInterface\\icons\\Achievement_Character_Draenei_Female:25|tОбмен расовыми особенностями дренеев -"

//male icons
#define LOCALE_DRS_9 "|TInterface\\icons\\Achievement_Character_Draenei_Male:25|tDraenei Racial Trait Swap  -"
#define LOCALE_DRS_10 "|TInterface\\icons\\Achievement_Character_Draenei_Male:25|t드레나이 인종 특성 스왑 -"
#define LOCALE_DRS_11 "|TInterface\\icons\\Achievement_Character_Draenei_Male:25|tÉchange de traits raciaux draeneï -"
#define LOCALE_DRS_12 "|TInterface\\icons\\Achievement_Character_Draenei_Male:25|tDraenei Rasseneigenschaftstausch -"
#define LOCALE_DRS_13 "|TInterface\\icons\\Achievement_Character_Draenei_Male:25|t德萊尼人種特質交換 -"
#define LOCALE_DRS_14 "|TInterface\\icons\\Achievement_Character_Draenei_Male:25|t德萊尼人種特質交換 -"
#define LOCALE_DRS_15 "|TInterface\\icons\\Achievement_Character_Draenei_Male:25|tCambio de rasgo racial Draenei -"
#define LOCALE_DRS_16 "|TInterface\\icons\\Achievement_Character_Draenei_Male:25|tCambio de rasgo racial Draenei -"
#define LOCALE_DRS_17 "|TInterface\\icons\\Achievement_Character_Draenei_Male:25|tОбмен расовыми особенностями дренеев -"

//female icons
#define LOCALE_DWS_0 "|TInterface\\icons\\Achievement_Character_Dwarf_Female:25|tDwarven Racial Trait Swap -"
#define LOCALE_DWS_1 "|TInterface\\icons\\Achievement_Character_Dwarf_Female:25|t드워프 종족 특성 전환 -"
#define LOCALE_DWS_2 "|TInterface\\icons\\Achievement_Character_Dwarf_Female:25|tÉchange de traits raciaux nains -"
#define LOCALE_DWS_3 "|TInterface\\icons\\Achievement_Character_Dwarf_Female:25|tTausch der Rasseneigenschaften der Zwerge -"
#define LOCALE_DWS_4 "|TInterface\\icons\\Achievement_Character_Dwarf_Female:25|t矮人種族特質交換 -"
#define LOCALE_DWS_5 "|TInterface\\icons\\Achievement_Character_Dwarf_Female:25|t矮人種族特質交換 -"
#define LOCALE_DWS_6 "|TInterface\\icons\\Achievement_Character_Dwarf_Female:25|tIntercambio de rasgos raciales enanos -"
#define LOCALE_DWS_7 "|TInterface\\icons\\Achievement_Character_Dwarf_Female:25|tIntercambio de rasgos raciales enanos -"
#define LOCALE_DWS_8 "|TInterface\\icons\\Achievement_Character_Dwarf_Female:25|tОбмен расовыми особенностями гномов -"

//male icons
#define LOCALE_DWS_9 "|TInterface\\icons\\Achievement_Character_Dwarf_Male:25|tDwarven Racial Trait Swap -"
#define LOCALE_DWS_10 "|TInterface\\icons\\Achievement_Character_Dwarf_Male:25|t드워프 종족 특성 전환 -"
#define LOCALE_DWS_11 "|TInterface\\icons\\Achievement_Character_Dwarf_Male:25|tÉchange de traits raciaux nains -"
#define LOCALE_DWS_12 "|TInterface\\icons\\Achievement_Character_Dwarf_Male:25|tTausch der Rasseneigenschaften der Zwerge -"
#define LOCALE_DWS_13 "|TInterface\\icons\\Achievement_Character_Dwarf_Male:25|t矮人種族特質交換 -"
#define LOCALE_DWS_14 "|TInterface\\icons\\Achievement_Character_Dwarf_Male:25|t矮人種族特質交換 -"
#define LOCALE_DWS_15 "|TInterface\\icons\\Achievement_Character_Dwarf_Male:25|tIntercambio de rasgos raciales enanos -"
#define LOCALE_DWS_16 "|TInterface\\icons\\Achievement_Character_Dwarf_Male:25|tIntercambio de rasgos raciales enanos -"
#define LOCALE_DWS_17 "|TInterface\\icons\\Achievement_Character_Dwarf_Male:25|tОбмен расовыми особенностями гномов -"

//female icons
#define LOCALE_GNS_0 "|TInterface\\icons\\Achievement_Character_Gnome_Female:25|tGnome Racial Trait Swap -"
#define LOCALE_GNS_1 "|TInterface\\icons\\Achievement_Character_Gnome_Female:25|t그놈 인종 특성 스왑 -"
#define LOCALE_GNS_2 "|TInterface\\icons\\Achievement_Character_Gnome_Female:25|tÉchange de traits raciaux de gnome -"
#define LOCALE_GNS_3 "|TInterface\\icons\\Achievement_Character_Gnome_Female:25|tTausch der Rasseneigenschaft Gnom -"
#define LOCALE_GNS_4 "|TInterface\\icons\\Achievement_Character_Gnome_Female:25|t侏儒種族特質交換 -"
#define LOCALE_GNS_5 "|TInterface\\icons\\Achievement_Character_Gnome_Female:25|t侏儒種族特質交換 -"
#define LOCALE_GNS_6 "|TInterface\\icons\\Achievement_Character_Gnome_Female:25|tCambio de rasgo racial de gnomo -"
#define LOCALE_GNS_7 "|TInterface\\icons\\Achievement_Character_Gnome_Female:25|tCambio de rasgo racial de gnomo -"
#define LOCALE_GNS_8 "|TInterface\\icons\\Achievement_Character_Gnome_Female:25|tСмена расовой особенности гномов -"

//male icons
#define LOCALE_GNS_9 "|TInterface\\icons\\Achievement_Character_Gnome_Male:25|tGnome Racial Trait Swap -"
#define LOCALE_GNS_10 "|TInterface\\icons\\Achievement_Character_Gnome_Male:25|t그놈 인종 특성 스왑 -"
#define LOCALE_GNS_11 "|TInterface\\icons\\Achievement_Character_Gnome_Male:25|tÉchange de traits raciaux de gnome -"
#define LOCALE_GNS_12 "|TInterface\\icons\\Achievement_Character_Gnome_Male:25|tTausch der Rasseneigenschaft Gnom -"
#define LOCALE_GNS_13 "|TInterface\\icons\\Achievement_Character_Gnome_Male:25|t侏儒種族特質交換 -"
#define LOCALE_GNS_14 "|TInterface\\icons\\Achievement_Character_Gnome_Male:25|t侏儒種族特質交換 -"
#define LOCALE_GNS_15 "|TInterface\\icons\\Achievement_Character_Gnome_Male:25|tCambio de rasgo racial de gnomo -"
#define LOCALE_GNS_16 "|TInterface\\icons\\Achievement_Character_Gnome_Male:25|tCambio de rasgo racial de gnomo -"
#define LOCALE_GNS_17 "|TInterface\\icons\\Achievement_Character_Gnome_Male:25|tСмена расовой особенности гномов -"

//female icons
#define LOCALE_HUS_0 "|TInterface\\icons\\Achievement_Character_Human_Female:25|tHuman Racial Trait Swap -"
#define LOCALE_HUS_1 "|TInterface\\icons\\Achievement_Character_Human_Female:25|t인간 인종 특성 교환 -"
#define LOCALE_HUS_2 "|TInterface\\icons\\Achievement_Character_Human_Female:25|tÉchange de traits raciaux humains -"
#define LOCALE_HUS_3 "|TInterface\\icons\\Achievement_Character_Human_Female:25|tAustausch von menschlichen Rassenmerkmalen -"
#define LOCALE_HUS_4 "|TInterface\\icons\\Achievement_Character_Human_Female:25|t人類種族特質交換 -"
#define LOCALE_HUS_5 "|TInterface\\icons\\Achievement_Character_Human_Female:25|t人類種族特質交換 -"
#define LOCALE_HUS_6 "|TInterface\\icons\\Achievement_Character_Human_Female:25|tIntercambio de rasgos raciales humanos -"
#define LOCALE_HUS_7 "|TInterface\\icons\\Achievement_Character_Human_Female:25|tIntercambio de rasgos raciales humanos -"
#define LOCALE_HUS_8 "|TInterface\\icons\\Achievement_Character_Human_Female:25|tОбмен расовыми особенностями человека -"

//male icons
#define LOCALE_HUS_9 "|TInterface\\icons\\Achievement_Character_Human_Male:25|tHuman Racial Trait Swap -"
#define LOCALE_HUS_10 "|TInterface\\icons\\Achievement_Character_Human_Male:25|t인간 인종 특성 교환 -"
#define LOCALE_HUS_11 "|TInterface\\icons\\Achievement_Character_Human_Male:25|tÉchange de traits raciaux humains -"
#define LOCALE_HUS_12 "|TInterface\\icons\\Achievement_Character_Human_Male:25|tAustausch von menschlichen Rassenmerkmalen -"
#define LOCALE_HUS_13 "|TInterface\\icons\\Achievement_Character_Human_Male:25|t人類種族特質交換 -"
#define LOCALE_HUS_14 "|TInterface\\icons\\Achievement_Character_Human_Male:25|t人類種族特質交換 -"
#define LOCALE_HUS_15 "|TInterface\\icons\\Achievement_Character_Human_Male:25|tIntercambio de rasgos raciales humanos -"
#define LOCALE_HUS_16 "|TInterface\\icons\\Achievement_Character_Human_Male:25|tIntercambio de rasgos raciales humanos -"
#define LOCALE_HUS_17 "|TInterface\\icons\\Achievement_Character_Human_Male:25|tОбмен расовыми особенностями человека -"

//female icons
#define LOCALE_NES_0 "|TInterface\\icons\\Achievement_Character_Nightelf_Female:25|tNight Elf Racial Trait Swap -"
#define LOCALE_NES_1 "|TInterface\\icons\\Achievement_Character_Nightelf_Female:25|t나이트 엘프 인종 특성 스왑 -"
#define LOCALE_NES_2 "|TInterface\\icons\\Achievement_Character_Nightelf_Female:25|tÉchange de traits raciaux des elfes de la nuit -"
#define LOCALE_NES_3 "|TInterface\\icons\\Achievement_Character_Nightelf_Female:25|tTausch der Nachtelfen-Rasseneigenschaft -"
#define LOCALE_NES_4 "|TInterface\\icons\\Achievement_Character_Nightelf_Female:25|t暗夜精靈種族特質交換 -"
#define LOCALE_NES_5 "|TInterface\\icons\\Achievement_Character_Nightelf_Female:25|t暗夜精靈種族特質交換 -"
#define LOCALE_NES_6 "|TInterface\\icons\\Achievement_Character_Nightelf_Female:25|tCambio de rasgo racial elfo de la noche -"
#define LOCALE_NES_7 "|TInterface\\icons\\Achievement_Character_Nightelf_Female:25|tCambio de rasgo racial elfo de la noche -"
#define LOCALE_NES_8 "|TInterface\\icons\\Achievement_Character_Nightelf_Female:25|tОбмен расовыми особенностями ночных эльфов -"

//male icons
#define LOCALE_NES_9 "|TInterface\\icons\\Achievement_Character_Nightelf_Male:25|tNight Elf Racial Trait Swap -"
#define LOCALE_NES_10 "|TInterface\\icons\\Achievement_Character_Nightelf_Male:25|t나이트 엘프 인종 특성 스왑 -"
#define LOCALE_NES_11 "|TInterface\\icons\\Achievement_Character_Nightelf_Male:25|tÉchange de traits raciaux des elfes de la nuit -"
#define LOCALE_NES_12 "|TInterface\\icons\\Achievement_Character_Nightelf_Male:25|tTausch der Nachtelfen-Rasseneigenschaft -"
#define LOCALE_NES_13 "|TInterface\\icons\\Achievement_Character_Nightelf_Male:25|t暗夜精靈種族特質交換 -"
#define LOCALE_NES_14 "|TInterface\\icons\\Achievement_Character_Nightelf_Male:25|t暗夜精靈種族特質交換 -"
#define LOCALE_NES_15 "|TInterface\\icons\\Achievement_Character_Nightelf_Male:25|tCambio de rasgo racial elfo de la noche -"
#define LOCALE_NES_16 "|TInterface\\icons\\Achievement_Character_Nightelf_Male:25|tCambio de rasgo racial elfo de la noche -"
#define LOCALE_NES_17 "|TInterface\\icons\\Achievement_Character_Nightelf_Male:25|tОбмен расовыми особенностями ночных эльфов -"

//female icons
#define LOCALE_ORC_0 "|TInterface\\icons\\Achievement_Character_Orc_Female:25|tOrc Racial Trait Swap -"
#define LOCALE_ORC_1 "|TInterface\\icons\\Achievement_Character_Orc_Female:25|t오크 종족 특성 교환 -"
#define LOCALE_ORC_2 "|TInterface\\icons\\Achievement_Character_Orc_Female:25|tÉchange de traits raciaux orques -"
#define LOCALE_ORC_3 "|TInterface\\icons\\Achievement_Character_Orc_Female:25|tAustausch der Ork-Rassenmerkmale -"
#define LOCALE_ORC_4 "|TInterface\\icons\\Achievement_Character_Orc_Female:25|t獸人種族特質交換 -"
#define LOCALE_ORC_5 "|TInterface\\icons\\Achievement_Character_Orc_Female:25|t獸人種族特質交換 -"
#define LOCALE_ORC_6 "|TInterface\\icons\\Achievement_Character_Orc_Female:25|tIntercambio de rasgos raciales de orcos -"
#define LOCALE_ORC_7 "|TInterface\\icons\\Achievement_Character_Orc_Female:25|tIntercambio de rasgos raciales de orcos -"
#define LOCALE_ORC_8 "|TInterface\\icons\\Achievement_Character_Orc_Female:25|tСмена расовой особенности орков -"

//male icons
#define LOCALE_ORC_9 "|TInterface\\icons\\Achievement_Character_Orc_Male:25|tOrc Racial Trait Swap -"
#define LOCALE_ORC_10 "|TInterface\\icons\\Achievement_Character_Orc_Male:25|t오크 종족 특성 교환 -"
#define LOCALE_ORC_11 "|TInterface\\icons\\Achievement_Character_Orc_Male:25|tÉchange de traits raciaux orques -"
#define LOCALE_ORC_12 "|TInterface\\icons\\Achievement_Character_Orc_Male:25|tAustausch der Ork-Rassenmerkmale -"
#define LOCALE_ORC_13 "|TInterface\\icons\\Achievement_Character_Orc_Male:25|t獸人種族特質交換 -"
#define LOCALE_ORC_14 "|TInterface\\icons\\Achievement_Character_Orc_Male:25|t獸人種族特質交換 -"
#define LOCALE_ORC_15 "|TInterface\\icons\\Achievement_Character_Orc_Male:25|tIntercambio de rasgos raciales de orcos -"
#define LOCALE_ORC_16 "|TInterface\\icons\\Achievement_Character_Orc_Male:25|tIntercambio de rasgos raciales de orcos -"
#define LOCALE_ORC_17 "|TInterface\\icons\\Achievement_Character_Orc_Male:25|tСмена расовой особенности орков -"

//female icons
#define LOCALE_TUR_0 "|TInterface\\icons\\Achievement_Character_Tauren_Female:25|tTauren Racial Trait Swap -"
#define LOCALE_TUR_1 "|TInterface\\icons\\Achievement_Character_Tauren_Female:25|t타우렌 인종 특성 교환 -"
#define LOCALE_TUR_2 "|TInterface\\icons\\Achievement_Character_Tauren_Female:25|tÉchange de traits raciaux Tauren -"
#define LOCALE_TUR_3 "|TInterface\\icons\\Achievement_Character_Tauren_Female:25|tTauren Rasseneigenschaftstausch -"
#define LOCALE_TUR_4 "|TInterface\\icons\\Achievement_Character_Tauren_Female:25|t牛頭人種族特質交換 -"
#define LOCALE_TUR_5 "|TInterface\\icons\\Achievement_Character_Tauren_Female:25|t牛頭人種族特質交換 -"
#define LOCALE_TUR_6 "|TInterface\\icons\\Achievement_Character_Tauren_Female:25|tIntercambio de rasgos raciales tauren -"
#define LOCALE_TUR_7 "|TInterface\\icons\\Achievement_Character_Tauren_Female:25|tIntercambio de rasgos raciales tauren -"
#define LOCALE_TUR_8 "|TInterface\\icons\\Achievement_Character_Tauren_Female:25|tОбмен расовыми особенностями тауренов -"

//male icons
#define LOCALE_TUR_9 "|TInterface\\icons\\Achievement_Character_Tauren_Male:25|tTauren Racial Trait Swap -"
#define LOCALE_TUR_10 "|TInterface\\icons\\Achievement_Character_Tauren_Male:25|t타우렌 인종 특성 교환 -"
#define LOCALE_TUR_11 "|TInterface\\icons\\Achievement_Character_Tauren_Male:25|tÉchange de traits raciaux Tauren -"
#define LOCALE_TUR_12 "|TInterface\\icons\\Achievement_Character_Tauren_Male:25|tTauren Rasseneigenschaftstausch -"
#define LOCALE_TUR_13 "|TInterface\\icons\\Achievement_Character_Tauren_Male:25|t牛頭人種族特質交換 -"
#define LOCALE_TUR_14 "|TInterface\\icons\\Achievement_Character_Tauren_Male:25|t牛頭人種族特質交換 -"
#define LOCALE_TUR_15 "|TInterface\\icons\\Achievement_Character_Tauren_Male:25|tIntercambio de rasgos raciales tauren -"
#define LOCALE_TUR_16 "|TInterface\\icons\\Achievement_Character_Tauren_Male:25|tIntercambio de rasgos raciales tauren -"
#define LOCALE_TUR_17 "|TInterface\\icons\\Achievement_Character_Tauren_Male:25|tОбмен расовыми особенностями тауренов -"

//female icons
#define LOCALE_TRL_0 "|TInterface\\icons\\Achievement_Character_Troll_Female:25|tTroll Racial Trait Swap -"
#define LOCALE_TRL_1 "|TInterface\\icons\\Achievement_Character_Troll_Female:25|t트롤 인종 특성 교환 -"
#define LOCALE_TRL_2 "|TInterface\\icons\\Achievement_Character_Troll_Female:25|tÉchange de traits raciaux de troll -"
#define LOCALE_TRL_3 "|TInterface\\icons\\Achievement_Character_Troll_Female:25|tTroll-Rasseneigenschaftstausch -"
#define LOCALE_TRL_4 "|TInterface\\icons\\Achievement_Character_Troll_Female:25|t巨魔種族特質交換 -"
#define LOCALE_TRL_5 "|TInterface\\icons\\Achievement_Character_Troll_Female:25|t巨魔種族特質交換 -"
#define LOCALE_TRL_6 "|TInterface\\icons\\Achievement_Character_Troll_Female:25|tCambio de rasgo racial de trol -"
#define LOCALE_TRL_7 "|TInterface\\icons\\Achievement_Character_Troll_Female:25|tCambio de rasgo racial de trol -"
#define LOCALE_TRL_8 "|TInterface\\icons\\Achievement_Character_Troll_Female:25|tОбмен расовой особенности троллей -"

//male icons
#define LOCALE_TRL_9 "|TInterface\\icons\\Achievement_Character_Troll_Male:25|tTroll Racial Trait Swap -"
#define LOCALE_TRL_10 "|TInterface\\icons\\Achievement_Character_Troll_Male:25|t트롤 인종 특성 교환 -"
#define LOCALE_TRL_11 "|TInterface\\icons\\Achievement_Character_Troll_Male:25|tÉchange de traits raciaux de troll -"
#define LOCALE_TRL_12 "|TInterface\\icons\\Achievement_Character_Troll_Male:25|tTroll-Rasseneigenschaftstausch -"
#define LOCALE_TRL_13 "|TInterface\\icons\\Achievement_Character_Troll_Male:25|t巨魔種族特質交換 -"
#define LOCALE_TRL_14 "|TInterface\\icons\\Achievement_Character_Troll_Male:25|t巨魔種族特質交換 -"
#define LOCALE_TRL_15 "|TInterface\\icons\\Achievement_Character_Troll_Male:25|tCambio de rasgo racial de trol -"
#define LOCALE_TRL_16 "|TInterface\\icons\\Achievement_Character_Troll_Male:25|tCambio de rasgo racial de trol -"
#define LOCALE_TRL_17 "|TInterface\\icons\\Achievement_Character_Troll_Male:25|tОбмен расовой особенности троллей -"

//female icons
#define LOCALE_UND_0 "|TInterface\\icons\\Achievement_Character_Undead_Female:25|tUndead Racial Trait Swap -"
#define LOCALE_UND_1 "|TInterface\\icons\\Achievement_Character_Undead_Female:25|t언데드 인종 특성 스왑 -"
#define LOCALE_UND_2 "|TInterface\\icons\\Achievement_Character_Undead_Female:25|tÉchange de traits raciaux morts-vivants -"
#define LOCALE_UND_3 "|TInterface\\icons\\Achievement_Character_Undead_Female:25|tUntoter Rassenmerkmalentausch -"
#define LOCALE_UND_4 "|TInterface\\icons\\Achievement_Character_Undead_Female:25|t亡靈種族特質交換 -"
#define LOCALE_UND_5 "|TInterface\\icons\\Achievement_Character_Undead_Female:25|t亡靈種族特質交換 -"
#define LOCALE_UND_6 "|TInterface\\icons\\Achievement_Character_Undead_Female:25|tIntercambio de rasgos raciales no muertos -"
#define LOCALE_UND_7 "|TInterface\\icons\\Achievement_Character_Undead_Female:25|tIntercambio de rasgos raciales no muertos -"
#define LOCALE_UND_8 "|TInterface\\icons\\Achievement_Character_Undead_Female:25|tСмена расовой особенности нежити -"

//male icons
#define LOCALE_UND_9 "|TInterface\\icons\\Achievement_Character_Undead_Male:25|tUndead Racial Trait Swap -"
#define LOCALE_UND_10 "|TInterface\\icons\\Achievement_Character_Undead_Male:25|t언데드 인종 특성 스왑 -"
#define LOCALE_UND_11 "|TInterface\\icons\\Achievement_Character_Undead_Male:25|tÉchange de traits raciaux morts-vivants -"
#define LOCALE_UND_12 "|TInterface\\icons\\Achievement_Character_Undead_Male:25|tUntoter Rassenmerkmalentausch -"
#define LOCALE_UND_13 "|TInterface\\icons\\Achievement_Character_Undead_Male:25|t亡靈種族特質交換 -"
#define LOCALE_UND_14 "|TInterface\\icons\\Achievement_Character_Undead_Male:25|t亡靈種族特質交換 -"
#define LOCALE_UND_15 "|TInterface\\icons\\Achievement_Character_Undead_Male:25|tIntercambio de rasgos raciales no muertos -"
#define LOCALE_UND_16 "|TInterface\\icons\\Achievement_Character_Undead_Male:25|tIntercambio de rasgos raciales no muertos -"
#define LOCALE_UND_17 "|TInterface\\icons\\Achievement_Character_Undead_Male:25|tСмена расовой особенности нежити -"

// New Function - remove all existing racials
void RemoveAllRacials(Player* player) {
    //Dranei:
    player->removeSpell(28875, SPEC_MASK_ALL, false);// unlearn Gemcutting
    player->removeSpell(6562, SPEC_MASK_ALL, false);// unlearn Heroic Presence (Warrior, Paladin, Hunter, DK)
    player->removeSpell(28878, SPEC_MASK_ALL, false);// unlearn Heroic Presence (Priest, Shaman)
    player->removeSpell(28880, SPEC_MASK_ALL, false);// unlearn Gift of Naaru (Warrior, increased by AP)
    player->removeSpell(59542, SPEC_MASK_ALL, false);// unlearn Gift of Naaru (Paladin, increase by AP or SP, whichever is higher)
    player->removeSpell(59543, SPEC_MASK_ALL, false);// unlearn Gift of Naaru (Hunter, increase by AP)
    player->removeSpell(59544, SPEC_MASK_ALL, false);// unlearn Gift of Naaru (Priest, increase by SP)
    player->removeSpell(59545, SPEC_MASK_ALL, false);// unlearn Gift of Naaru (DK, increased by AP)
    player->removeSpell(59547, SPEC_MASK_ALL, false);// unlearn Gift of Narru (Shaman, increase by AP or SP, whichever is higher)
    player->removeSpell(59548, SPEC_MASK_ALL, false);// unlearn Gift of Naaru (Mage, increase by SP)
    player->removeSpell(59221, SPEC_MASK_ALL, false);// unlearn Shadow Resistance (Warrior)
    player->removeSpell(59535, SPEC_MASK_ALL, false);// unlearn Shadow Resistance (Paladin)
    player->removeSpell(59536, SPEC_MASK_ALL, false);// unlearn Shadow Resistance (Hunter)
    player->removeSpell(59538, SPEC_MASK_ALL, false);// unlearn Shadow Resistance (Priest)    
    player->removeSpell(59539, SPEC_MASK_ALL, false);// unlearn Shadow Resistance (DK)
    player->removeSpell(59540, SPEC_MASK_ALL, false);// unlearn Shadow Resistance (Shaman)
    player->removeSpell(59541, SPEC_MASK_ALL, false);// unlearn Shadow Resistance (Mage)
    
    //Dwarven:
    player->removeSpell(2481, SPEC_MASK_ALL, false);// unlearn Find Treasure
    player->removeSpell(20596, SPEC_MASK_ALL, false);// unlearn Frost Resistance
    player->removeSpell(20595, SPEC_MASK_ALL, false);// unlearn Gun Specialization
    player->removeSpell(59224, SPEC_MASK_ALL, false);// unlearn Mace Specialization
    player->removeSpell(20594, SPEC_MASK_ALL, false);// unlearn Stoneform

    //Gnome:
    player->removeSpell(20592, SPEC_MASK_ALL, false);// unlearn Arcane Resistance
    player->removeSpell(20593, SPEC_MASK_ALL, false);// unlearn Engineering Specialization
    player->removeSpell(20589, SPEC_MASK_ALL, false);// unlearn Escape Artist
    player->removeSpell(20591, SPEC_MASK_ALL, false);// unlearn Expansive Mind

    //Human:
    player->removeSpell(20599, SPEC_MASK_ALL, false);// unlearn Diplomacy
    player->removeSpell(59752, SPEC_MASK_ALL, false);// unlearn Every man for himself
    player->removeSpell(20864, SPEC_MASK_ALL, false);// unlearn Mace Specialization
    player->removeSpell(58985, SPEC_MASK_ALL, false);// unlearn Perception
    player->removeSpell(20597, SPEC_MASK_ALL, false);// unlearn Sword Specialization
    player->removeSpell(20598, SPEC_MASK_ALL, false);// unlearn The Human Spirit

    //Night Elf:
    player->removeSpell(20583, SPEC_MASK_ALL, false);// unlearn Nature Resistance
    player->removeSpell(20582, SPEC_MASK_ALL, false);// unlearn Quickness
    player->removeSpell(58984, SPEC_MASK_ALL, false);// unlearn Shadowmeld
    player->removeSpell(20585, SPEC_MASK_ALL, false);// unlearn Wisp Spirit
    player->removeSpell(21009, SPEC_MASK_ALL, false);// unlearn Elusiveness

    //Orc:
    player->removeSpell(20574, SPEC_MASK_ALL, false);// unlearn Axe Specialization
    player->removeSpell(20573, SPEC_MASK_ALL, false);// unlearn Hardiness
    player->removeSpell(54562, SPEC_MASK_ALL, false);// unlearn Command (DK)
    player->removeSpell(20576, SPEC_MASK_ALL, false);// unlearn Command (Hunter)
    player->removeSpell(65222, SPEC_MASK_ALL, false);// unlearn Command (Shaman)
    player->removeSpell(20575, SPEC_MASK_ALL, false);// unlearn Command (Warlock)
    player->removeSpell(21563, SPEC_MASK_ALL, false);// unlearn Command (non-pet class)
    player->removeSpell(20572, SPEC_MASK_ALL, false);// unlearn Blood Fury (AP only)
    player->removeSpell(33697, SPEC_MASK_ALL, false);// unlearn Blood fury (AP + SP)
    player->removeSpell(33702, SPEC_MASK_ALL, false);// unlearn Blood Fury (SP only)
    
    //Tauren:
    player->removeSpell(20552, SPEC_MASK_ALL, false);// unlearn Cultivation
    player->removeSpell(20550, SPEC_MASK_ALL, false);// unlearn Endurance
    player->removeSpell(20551, SPEC_MASK_ALL, false);// unlearn Nature Resistance
    player->removeSpell(20549, SPEC_MASK_ALL, false);// unlearn Warstomp
    
    //Troll:
    player->removeSpell(20557, SPEC_MASK_ALL, false);// unlearn Beast Slaying
    player->removeSpell(26297, SPEC_MASK_ALL, false);// unlearn Berserking
    player->removeSpell(26290, SPEC_MASK_ALL, false);// unlearn Bow Specialization
    player->removeSpell(20558, SPEC_MASK_ALL, false);// unlearn Throwing Specialization
    player->removeSpell(58943, SPEC_MASK_ALL, false);// unlearn Da Voodoo Shuffle
    player->removeSpell(20555, SPEC_MASK_ALL, false);// unlearn Regeneration
    
    //Undead:
    player->removeSpell(20577, SPEC_MASK_ALL, false);// unlearn Cannibalize
    player->removeSpell(20579, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
    player->removeSpell(5227, SPEC_MASK_ALL, false);// unlearn Underwater Breating
    player->removeSpell(7744, SPEC_MASK_ALL, false);// unlearn Will of the Forsaken

    //Blood Elf:
    player->removeSpell(28877, SPEC_MASK_ALL, false);// unlearn Arcane Affinity
    player->removeSpell(28730, SPEC_MASK_ALL, false);// unlearn Arcane Torrent (mana)
    player->removeSpell(25046, SPEC_MASK_ALL, false);// unlearn Arcane Torrent (energy)
    player->removeSpell(50613, SPEC_MASK_ALL, false);// unlearn Arcane Torrent (runic power)
    player->removeSpell(822, SPEC_MASK_ALL, false);// unlearn Magic Resistance
}


class Azerothcore_Race_Trait_announce : public PlayerScript
{
public:
    Azerothcore_Race_Trait_announce() : PlayerScript("Azerothcore_Race_Trait_announce") { }

    void OnLogin(Player* Player)
    {
        if (sConfigMgr->GetOption<bool>("Azerothcore.Racial.Trait.Swap.Announce.enable", true))
        {
            ChatHandler(Player->GetSession()).SendSysMessage("This server is running the |cff4CFF00Azerothcore Racial Trait Swap NPC |rmodule.");
        }
    }
};

class npc_race_trait_swap : public CreatureScript
{
public:

    npc_race_trait_swap() : CreatureScript("npc_race_trait_swap") { }

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        char const* localizedEntry;
        switch (player->GetSession()->GetSessionDbcLocale())
        {
            case LOCALE_koKR: localizedEntry = LOCALE_RACESWAP_1; break;
            case LOCALE_frFR: localizedEntry = LOCALE_RACESWAP_2; break;
            case LOCALE_deDE: localizedEntry = LOCALE_RACESWAP_3; break;
            case LOCALE_zhCN: localizedEntry = LOCALE_RACESWAP_4; break;
            case LOCALE_zhTW: localizedEntry = LOCALE_RACESWAP_5; break;
            case LOCALE_esES: localizedEntry = LOCALE_RACESWAP_6; break;
            case LOCALE_esMX: localizedEntry = LOCALE_RACESWAP_7; break;
            case LOCALE_ruRU: localizedEntry = LOCALE_RACESWAP_8; break;
            case LOCALE_enUS: default: localizedEntry = LOCALE_RACESWAP_0;
        }
        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, localizedEntry, GOSSIP_SENDER_MAIN, 11);
        SendGossipMenuFor(player, 98888, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*menuId*/, uint32 gossipListId) override
    {
        const int32 RTS1 = sConfigMgr->GetOption<uint32>("Racial.Traits.Swap.Gold", 100);

        char const* localizedExit = {};
        char const* localizedBack = {};
        char const* localizedGold = {};
        char const* localizedBES = {};
        char const* localizedDRS = {};
        char const* localizedDWS = {};
        char const* localizedGNS = {};
        char const* localizedHUS = {};
        char const* localizedNES = {};
        char const* localizedORC = {};
        char const* localizedTUR = {};
        char const* localizedTRL = {};
        char const* localizedUND = {};

        switch (player->GetSession()->GetSessionDbcLocale())
        {
            case LOCALE_koKR: localizedExit = LOCALE_EXIT_1; break;
            case LOCALE_frFR: localizedExit = LOCALE_EXIT_2; break;
            case LOCALE_deDE: localizedExit = LOCALE_EXIT_3; break;
            case LOCALE_zhCN: localizedExit = LOCALE_EXIT_4; break;
            case LOCALE_zhTW: localizedExit = LOCALE_EXIT_5; break;
            case LOCALE_esES: localizedExit = LOCALE_EXIT_6; break;
            case LOCALE_esMX: localizedExit = LOCALE_EXIT_7; break;
            case LOCALE_ruRU: localizedExit = LOCALE_EXIT_8; break;
            case LOCALE_enUS: default: localizedExit = LOCALE_EXIT_0;
        }

        switch (player->GetSession()->GetSessionDbcLocale())
        {
            case LOCALE_koKR: localizedBack = LOCALE_BACK_1; break;
            case LOCALE_frFR: localizedBack = LOCALE_BACK_2; break;
            case LOCALE_deDE: localizedBack = LOCALE_BACK_3; break;
            case LOCALE_zhCN: localizedBack = LOCALE_BACK_4; break;
            case LOCALE_zhTW: localizedBack = LOCALE_BACK_5; break;
            case LOCALE_esES: localizedBack = LOCALE_BACK_6; break;
            case LOCALE_esMX: localizedBack = LOCALE_BACK_7; break;
            case LOCALE_ruRU: localizedBack = LOCALE_BACK_8; break;
            case LOCALE_enUS: default: localizedBack = LOCALE_BACK_0;
        }

        switch (player->GetSession()->GetSessionDbcLocale())
        {
            case LOCALE_koKR: localizedGold = LOCALE_GOLD_1; break;
            case LOCALE_frFR: localizedGold = LOCALE_GOLD_2; break;
            case LOCALE_deDE: localizedGold = LOCALE_GOLD_3; break;
            case LOCALE_zhCN: localizedGold = LOCALE_GOLD_4; break;
            case LOCALE_zhTW: localizedGold = LOCALE_GOLD_5; break;
            case LOCALE_esES: localizedGold = LOCALE_GOLD_6; break;
            case LOCALE_esMX: localizedGold = LOCALE_GOLD_7; break;
            case LOCALE_ruRU: localizedGold = LOCALE_GOLD_8; break;
            case LOCALE_enUS: default: localizedGold = LOCALE_GOLD_0;
        }

        if (player->getGender() == GENDER_FEMALE)
        {
            switch (player->GetSession()->GetSessionDbcLocale())
            {
                case LOCALE_koKR: localizedBES = LOCALE_BES_1; break;
                case LOCALE_frFR: localizedBES = LOCALE_BES_2; break;
                case LOCALE_deDE: localizedBES = LOCALE_BES_3; break;
                case LOCALE_zhCN: localizedBES = LOCALE_BES_4; break;
                case LOCALE_zhTW: localizedBES = LOCALE_BES_5; break;
                case LOCALE_esES: localizedBES = LOCALE_BES_6; break;
                case LOCALE_esMX: localizedBES = LOCALE_BES_7; break;
                case LOCALE_ruRU: localizedBES = LOCALE_BES_8; break;
                case LOCALE_enUS: default: localizedBES = LOCALE_BES_0;
            }
            switch (player->GetSession()->GetSessionDbcLocale())
            {
                case LOCALE_koKR: localizedDRS = LOCALE_DRS_1; break;
                case LOCALE_frFR: localizedDRS = LOCALE_DRS_2; break;
                case LOCALE_deDE: localizedDRS = LOCALE_DRS_3; break;
                case LOCALE_zhCN: localizedDRS = LOCALE_DRS_4; break;
                case LOCALE_zhTW: localizedDRS = LOCALE_DRS_5; break;
                case LOCALE_esES: localizedDRS = LOCALE_DRS_6; break;
                case LOCALE_esMX: localizedDRS = LOCALE_DRS_7; break;
                case LOCALE_ruRU: localizedDRS = LOCALE_DRS_8; break;
                case LOCALE_enUS: default: localizedDRS = LOCALE_DRS_0;
            }

            switch (player->GetSession()->GetSessionDbcLocale())
            {
                case LOCALE_koKR: localizedDWS = LOCALE_DWS_1; break;
                case LOCALE_frFR: localizedDWS = LOCALE_DWS_2; break;
                case LOCALE_deDE: localizedDWS = LOCALE_DWS_3; break;
                case LOCALE_zhCN: localizedDWS = LOCALE_DWS_4; break;
                case LOCALE_zhTW: localizedDWS = LOCALE_DWS_5; break;
                case LOCALE_esES: localizedDWS = LOCALE_DWS_6; break;
                case LOCALE_esMX: localizedDWS = LOCALE_DWS_7; break;
                case LOCALE_ruRU: localizedDWS = LOCALE_DWS_8; break;
                case LOCALE_enUS: default: localizedDWS = LOCALE_DWS_0;
            }
            switch (player->GetSession()->GetSessionDbcLocale())
            {
                 case LOCALE_koKR: localizedGNS = LOCALE_GNS_1; break;
                 case LOCALE_frFR: localizedGNS = LOCALE_GNS_2; break;
                 case LOCALE_deDE: localizedGNS = LOCALE_GNS_3; break;
                 case LOCALE_zhCN: localizedGNS = LOCALE_GNS_4; break;
                 case LOCALE_zhTW: localizedGNS = LOCALE_GNS_5; break;
                 case LOCALE_esES: localizedGNS = LOCALE_GNS_6; break;
                 case LOCALE_esMX: localizedGNS = LOCALE_GNS_7; break;
                 case LOCALE_ruRU: localizedGNS = LOCALE_GNS_8; break;
                 case LOCALE_enUS: default: localizedGNS = LOCALE_GNS_0;
            }
            switch (player->GetSession()->GetSessionDbcLocale())
            {
                case LOCALE_koKR: localizedHUS = LOCALE_HUS_1; break;
                case LOCALE_frFR: localizedHUS = LOCALE_HUS_2; break;
                case LOCALE_deDE: localizedHUS = LOCALE_HUS_3; break;
                case LOCALE_zhCN: localizedHUS = LOCALE_HUS_4; break;
                case LOCALE_zhTW: localizedHUS = LOCALE_HUS_5; break;
                case LOCALE_esES: localizedHUS = LOCALE_HUS_6; break;
                case LOCALE_esMX: localizedHUS = LOCALE_HUS_7; break;
                case LOCALE_ruRU: localizedHUS = LOCALE_HUS_8; break;
                case LOCALE_enUS: default: localizedHUS = LOCALE_HUS_0;
            }
            switch (player->GetSession()->GetSessionDbcLocale())
            {
                case LOCALE_koKR: localizedNES = LOCALE_NES_1; break;
                case LOCALE_frFR: localizedNES = LOCALE_NES_2; break;
                case LOCALE_deDE: localizedNES = LOCALE_NES_3; break;
                case LOCALE_zhCN: localizedNES = LOCALE_NES_4; break;
                case LOCALE_zhTW: localizedNES = LOCALE_NES_5; break;
                case LOCALE_esES: localizedNES = LOCALE_NES_6; break;
                case LOCALE_esMX: localizedNES = LOCALE_NES_7; break;
                case LOCALE_ruRU: localizedNES = LOCALE_NES_8; break;
                case LOCALE_enUS: default: localizedNES = LOCALE_NES_0;
            }
            switch (player->GetSession()->GetSessionDbcLocale())
            {
                case LOCALE_koKR: localizedORC = LOCALE_ORC_1; break;
                case LOCALE_frFR: localizedORC = LOCALE_ORC_2; break;
                case LOCALE_deDE: localizedORC = LOCALE_ORC_3; break;
                case LOCALE_zhCN: localizedORC = LOCALE_ORC_4; break;
                case LOCALE_zhTW: localizedORC = LOCALE_ORC_5; break;
                case LOCALE_esES: localizedORC = LOCALE_ORC_6; break;
                case LOCALE_esMX: localizedORC = LOCALE_ORC_7; break;
                case LOCALE_ruRU: localizedORC = LOCALE_ORC_8; break;
                case LOCALE_enUS: default: localizedORC = LOCALE_ORC_0;
            }
            switch (player->GetSession()->GetSessionDbcLocale())
            {
                case LOCALE_koKR: localizedTUR = LOCALE_TUR_1; break;
                case LOCALE_frFR: localizedTUR = LOCALE_TUR_2; break;
                case LOCALE_deDE: localizedTUR = LOCALE_TUR_3; break;
                case LOCALE_zhCN: localizedTUR = LOCALE_TUR_4; break;
                case LOCALE_zhTW: localizedTUR = LOCALE_TUR_5; break;
                case LOCALE_esES: localizedTUR = LOCALE_TUR_6; break;
                case LOCALE_esMX: localizedTUR = LOCALE_TUR_7; break;
                case LOCALE_ruRU: localizedTUR = LOCALE_TUR_8; break;
                case LOCALE_enUS: default: localizedTUR = LOCALE_TUR_0;
            }
            switch (player->GetSession()->GetSessionDbcLocale())
            {
                case LOCALE_koKR: localizedTRL = LOCALE_TRL_1; break;
                case LOCALE_frFR: localizedTRL = LOCALE_TRL_2; break;
                case LOCALE_deDE: localizedTRL = LOCALE_TRL_3; break;
                case LOCALE_zhCN: localizedTRL = LOCALE_TRL_4; break;
                case LOCALE_zhTW: localizedTRL = LOCALE_TRL_5; break;
                case LOCALE_esES: localizedTRL = LOCALE_TRL_6; break;
                case LOCALE_esMX: localizedTRL = LOCALE_TRL_7; break;
                case LOCALE_ruRU: localizedTRL = LOCALE_TRL_8; break;
                case LOCALE_enUS: default: localizedTRL = LOCALE_TRL_0;
            }
            switch (player->GetSession()->GetSessionDbcLocale())
            {
                case LOCALE_koKR: localizedUND = LOCALE_UND_1; break;
                case LOCALE_frFR: localizedUND = LOCALE_UND_2; break;
                case LOCALE_deDE: localizedUND = LOCALE_UND_3; break;
                case LOCALE_zhCN: localizedUND = LOCALE_UND_4; break;
                case LOCALE_zhTW: localizedUND = LOCALE_UND_5; break;
                case LOCALE_esES: localizedUND = LOCALE_UND_6; break;
                case LOCALE_esMX: localizedUND = LOCALE_UND_7; break;
                case LOCALE_ruRU: localizedUND = LOCALE_UND_8; break;
                case LOCALE_enUS: default: localizedUND = LOCALE_UND_0;
            }
        }
        if (player->getGender() == GENDER_MALE)
        {
            switch (player->GetSession()->GetSessionDbcLocale())
            {
                case LOCALE_koKR: localizedBES = LOCALE_BES_10; break;
                case LOCALE_frFR: localizedBES = LOCALE_BES_11; break;
                case LOCALE_deDE: localizedBES = LOCALE_BES_12; break;
                case LOCALE_zhCN: localizedBES = LOCALE_BES_13; break;
                case LOCALE_zhTW: localizedBES = LOCALE_BES_14; break;
                case LOCALE_esES: localizedBES = LOCALE_BES_15; break;
                case LOCALE_esMX: localizedBES = LOCALE_BES_16; break;
                case LOCALE_ruRU: localizedBES = LOCALE_BES_17; break;
                case LOCALE_enUS: default: localizedBES = LOCALE_BES_9;
            }
            switch (player->GetSession()->GetSessionDbcLocale())
            {
                case LOCALE_koKR: localizedDRS = LOCALE_DRS_10; break;
                case LOCALE_frFR: localizedDRS = LOCALE_DRS_11; break;
                case LOCALE_deDE: localizedDRS = LOCALE_DRS_12; break;
                case LOCALE_zhCN: localizedDRS = LOCALE_DRS_13; break;
                case LOCALE_zhTW: localizedDRS = LOCALE_DRS_14; break;
                case LOCALE_esES: localizedDRS = LOCALE_DRS_15; break;
                case LOCALE_esMX: localizedDRS = LOCALE_DRS_16; break;
                case LOCALE_ruRU: localizedDRS = LOCALE_DRS_17; break;
                case LOCALE_enUS: default: localizedDRS = LOCALE_DRS_9;
            }
            switch (player->GetSession()->GetSessionDbcLocale())
            {
                case LOCALE_koKR: localizedDWS = LOCALE_DWS_10; break;
                case LOCALE_frFR: localizedDWS = LOCALE_DWS_11; break;
                case LOCALE_deDE: localizedDWS = LOCALE_DWS_12; break;
                case LOCALE_zhCN: localizedDWS = LOCALE_DWS_13; break;
                case LOCALE_zhTW: localizedDWS = LOCALE_DWS_14; break;
                case LOCALE_esES: localizedDWS = LOCALE_DWS_15; break;
                case LOCALE_esMX: localizedDWS = LOCALE_DWS_16; break;
                case LOCALE_ruRU: localizedDWS = LOCALE_DWS_17; break;
                case LOCALE_enUS: default: localizedDWS = LOCALE_DWS_9;
            }
            switch (player->GetSession()->GetSessionDbcLocale())
            {
                case LOCALE_koKR: localizedGNS = LOCALE_GNS_10; break;
                case LOCALE_frFR: localizedGNS = LOCALE_GNS_11; break;
                case LOCALE_deDE: localizedGNS = LOCALE_GNS_12; break;
                case LOCALE_zhCN: localizedGNS = LOCALE_GNS_13; break;
                case LOCALE_zhTW: localizedGNS = LOCALE_GNS_14; break;
                case LOCALE_esES: localizedGNS = LOCALE_GNS_15; break;
                case LOCALE_esMX: localizedGNS = LOCALE_GNS_16; break;
                case LOCALE_ruRU: localizedGNS = LOCALE_GNS_17; break;
                case LOCALE_enUS: default: localizedGNS = LOCALE_GNS_9;
            }
            switch (player->GetSession()->GetSessionDbcLocale())
            {
                case LOCALE_koKR: localizedHUS = LOCALE_HUS_10; break;
                case LOCALE_frFR: localizedHUS = LOCALE_HUS_11; break;
                case LOCALE_deDE: localizedHUS = LOCALE_HUS_12; break;
                case LOCALE_zhCN: localizedHUS = LOCALE_HUS_13; break;
                case LOCALE_zhTW: localizedHUS = LOCALE_HUS_14; break;
                case LOCALE_esES: localizedHUS = LOCALE_HUS_15; break;
                case LOCALE_esMX: localizedHUS = LOCALE_HUS_16; break;
                case LOCALE_ruRU: localizedHUS = LOCALE_HUS_17; break;
                case LOCALE_enUS: default: localizedHUS = LOCALE_HUS_9;
            }
            switch (player->GetSession()->GetSessionDbcLocale())
            {
                case LOCALE_koKR: localizedNES = LOCALE_NES_10; break;
                case LOCALE_frFR: localizedNES = LOCALE_NES_11; break;
                case LOCALE_deDE: localizedNES = LOCALE_NES_12; break;
                case LOCALE_zhCN: localizedNES = LOCALE_NES_13; break;
                case LOCALE_zhTW: localizedNES = LOCALE_NES_14; break;
                case LOCALE_esES: localizedNES = LOCALE_NES_15; break;
                case LOCALE_esMX: localizedNES = LOCALE_NES_16; break;
                case LOCALE_ruRU: localizedNES = LOCALE_NES_17; break;
                case LOCALE_enUS: default: localizedNES = LOCALE_NES_9;
            }
            switch (player->GetSession()->GetSessionDbcLocale())
            {
                case LOCALE_koKR: localizedORC = LOCALE_ORC_10; break;
                case LOCALE_frFR: localizedORC = LOCALE_ORC_11; break;
                case LOCALE_deDE: localizedORC = LOCALE_ORC_12; break;
                case LOCALE_zhCN: localizedORC = LOCALE_ORC_13; break;
                case LOCALE_zhTW: localizedORC = LOCALE_ORC_14; break;
                case LOCALE_esES: localizedORC = LOCALE_ORC_15; break;
                case LOCALE_esMX: localizedORC = LOCALE_ORC_16; break;
                case LOCALE_ruRU: localizedORC = LOCALE_ORC_17; break;
                case LOCALE_enUS: default: localizedORC = LOCALE_ORC_9;
            }
            switch (player->GetSession()->GetSessionDbcLocale())
            {
                case LOCALE_koKR: localizedTUR = LOCALE_TUR_10; break;
                case LOCALE_frFR: localizedTUR = LOCALE_TUR_11; break;
                case LOCALE_deDE: localizedTUR = LOCALE_TUR_12; break;
                case LOCALE_zhCN: localizedTUR = LOCALE_TUR_13; break;
                case LOCALE_zhTW: localizedTUR = LOCALE_TUR_14; break;
                case LOCALE_esES: localizedTUR = LOCALE_TUR_15; break;
                case LOCALE_esMX: localizedTUR = LOCALE_TUR_16; break;
                case LOCALE_ruRU: localizedTUR = LOCALE_TUR_17; break;
                case LOCALE_enUS: default: localizedTUR = LOCALE_TUR_9;
            }
            switch (player->GetSession()->GetSessionDbcLocale())
            {
                case LOCALE_koKR: localizedTRL = LOCALE_TRL_10; break;
                case LOCALE_frFR: localizedTRL = LOCALE_TRL_11; break;
                case LOCALE_deDE: localizedTRL = LOCALE_TRL_12; break;
                case LOCALE_zhCN: localizedTRL = LOCALE_TRL_13; break;
                case LOCALE_zhTW: localizedTRL = LOCALE_TRL_14; break;
                case LOCALE_esES: localizedTRL = LOCALE_TRL_15; break;
                case LOCALE_esMX: localizedTRL = LOCALE_TRL_16; break;
                case LOCALE_ruRU: localizedTRL = LOCALE_TRL_17; break;
                case LOCALE_enUS: default: localizedTRL = LOCALE_TRL_9;
            }
            switch (player->GetSession()->GetSessionDbcLocale())
            {
                case LOCALE_koKR: localizedUND = LOCALE_UND_10; break;
                case LOCALE_frFR: localizedUND = LOCALE_UND_11; break;
                case LOCALE_deDE: localizedUND = LOCALE_UND_12; break;
                case LOCALE_zhCN: localizedUND = LOCALE_UND_13; break;
                case LOCALE_zhTW: localizedUND = LOCALE_UND_14; break;
                case LOCALE_esES: localizedUND = LOCALE_UND_15; break;
                case LOCALE_esMX: localizedUND = LOCALE_UND_16; break;
                case LOCALE_ruRU: localizedUND = LOCALE_UND_17; break;
                case LOCALE_enUS: default: localizedUND = LOCALE_UND_9;
            }
        }

        std::ostringstream messageBE;
        messageBE << localizedBES << RTS1 << localizedGold;
        std::ostringstream messageDR;
        messageDR << localizedDRS << RTS1 << localizedGold;
        std::ostringstream messageDW;
        messageDW << localizedDWS << RTS1 << localizedGold;
        std::ostringstream messageGN;
        messageGN << localizedGNS << RTS1 << localizedGold;
        std::ostringstream messageHU;
        messageHU << localizedHUS << RTS1 << localizedGold;
        std::ostringstream messageNE;
        messageNE << localizedNES << RTS1 << localizedGold;
        std::ostringstream messageOR;
        messageOR << localizedORC << RTS1 << localizedGold;
        std::ostringstream messageTA;
        messageTA << localizedTUR << RTS1 << localizedGold;
        std::ostringstream messageTR;
        messageTR << localizedTRL << RTS1 << localizedGold;
        std::ostringstream messageUN;
        messageUN << localizedUND << RTS1 << localizedGold;

        ClearGossipMenuFor(player);

        switch (gossipListId)
        {

        case 11:

            if (player)
            {
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, messageBE.str(), GOSSIP_SENDER_MAIN, 1);//Blood Elf Selection
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, messageDR.str(), GOSSIP_SENDER_MAIN, 2);//Draenei Selection
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, messageDW.str(), GOSSIP_SENDER_MAIN, 3);//Dwarves Selection
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, messageGN.str(), GOSSIP_SENDER_MAIN, 4);//Gnome Selection
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, messageHU.str(), GOSSIP_SENDER_MAIN, 5);//Human Selection
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, messageNE.str(), GOSSIP_SENDER_MAIN, 6);//Night Elf Selection
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, messageOR.str(), GOSSIP_SENDER_MAIN, 7);//Orc Selection
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, messageTA.str(), GOSSIP_SENDER_MAIN, 8);//Tauren Selection
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, messageTR.str(), GOSSIP_SENDER_MAIN, 9);//Troll Selection
                AddGossipItemFor(player, GOSSIP_ICON_MONEY_BAG, messageUN.str(), GOSSIP_SENDER_MAIN, 10);//Undead
                AddGossipItemFor(player, GOSSIP_ICON_TALK, localizedExit, GOSSIP_SENDER_MAIN, 1111);
                SendGossipMenuFor(player, 98888, creature->GetGUID());
            }
            break;

        case 1111://close
            CloseGossipMenuFor(player);
            break;

        case 1://Blood Elf Selection
            AddGossipItemFor(player, GOSSIP_ICON_INTERACT_1, "Commit to the Pride of the Blood Elves", GOSSIP_SENDER_MAIN, 112);
            AddGossipItemFor(player, GOSSIP_ICON_TALK, localizedBack, GOSSIP_SENDER_MAIN, 11);
            AddGossipItemFor(player, GOSSIP_ICON_TALK, localizedExit, GOSSIP_SENDER_MAIN, 1111);
            SendGossipMenuFor(player, 988881, creature->GetGUID());
            break;

        case 112://Blood Elf
            CloseGossipMenuFor(player);
            if (!player->HasEnoughMoney(int32(RTS1 * GOLD)))//gold check
                return true;
            player->ModifyMoney(int32(-RTS1 * GOLD));//Deducting the money if check passes
            player->CastSpell(player, 47292);//Level up visual effect to let you know the transaction did occure and money is deducted
            RemoveAllRacials(player); //Remove all racials
            player->learnSpell(28877, false);//Arcane Affinity
            player->learnSpell(822, false);//Magic Resistance
            if (player->getClass() == CLASS_DEATH_KNIGHT || player->getClass() == CLASS_WARRIOR) // Need custom Arcane Torrent to regen rage, thus in meantime giving Warrior runic power version for a silence
            {
                player->learnSpell(50613, false);//Arcane Torrent
            }
            if (player->getClass() == CLASS_HUNTER || player->getClass() == CLASS_MAGE || player->getClass() == CLASS_PALADIN || player->getClass() == CLASS_WARLOCK || player->getClass() == CLASS_PRIEST || player->getClass() == CLASS_SHAMAN || player->getClass() == CLASS_DRUID)
            {
                player->learnSpell(28730, false);//Arcane Torrent
            }
            if (player->getClass() == CLASS_ROGUE || player->getClass() == CLASS_DRUID)
            {
                player->learnSpell(25046, false);//Arcane Torrent
            }
            // NOTE: Druid will get 2 versions of Arcane Torrent since they can use both Energy and Mana. If the custom version of Arcane Torrent is added, the druid will also need to pick that up.
            break;

        case 2://Draenei Selection
            AddGossipItemFor(player, GOSSIP_ICON_INTERACT_1, "Commit to the Light of the Draenei", GOSSIP_SENDER_MAIN, 212);
            AddGossipItemFor(player, GOSSIP_ICON_TALK, localizedBack, GOSSIP_SENDER_MAIN, 11);
            AddGossipItemFor(player, GOSSIP_ICON_TALK, localizedExit, GOSSIP_SENDER_MAIN, 1111);
            SendGossipMenuFor(player, 988882, creature->GetGUID());
            break;

        case 212://Draenei
            CloseGossipMenuFor(player);
            if (!player->HasEnoughMoney(int32(RTS1 * GOLD)))//gold check
                return true;
            player->ModifyMoney(int32(-RTS1 * GOLD));//Deducting the money if check passes
            player->CastSpell(player, 47292);//Level up visual effect to let you know the transaction did occure and money is deducted
            RemoveAllRacials(player); //Remove all racials
            player->learnSpell(28875, false);// Gem Cutting

            // HEROIC PRESENCE VARIANTS
            if (player->getClass() == CLASS_DEATH_KNIGHT || player->getClass() == CLASS_HUNTER || player->getClass() == CLASS_PALADIN || player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_ROGUE)
            {
                player->learnSpell(6562, false);//Heroic Presence
            }
            if (player->getClass() == CLASS_MAGE || player->getClass() == CLASS_PRIEST || player->getClass() == CLASS_SHAMAN || player->getClass() == CLASS_WARLOCK || player->getClass() == CLASS_DRUID)
            {
                player->learnSpell(28878, false);//Heroic Presence
            }

            // Gift of Naaru + Shadow Resistance VARIANTS
            if (player->getClass() == CLASS_DEATH_KNIGHT)
            {
                player->learnSpell(59545, false);//Gift of Naaru
                player->learnSpell(59539, false);//Shadow Resistance
            }
            if (player->getClass() == CLASS_HUNTER)
            {
                player->learnSpell(59543, false);//Gift of Naaru
                player->learnSpell(59536, false);//Shadow Resistance
            }
            if (player->getClass() == CLASS_MAGE || player->getClass() == CLASS_WARLOCK)
            {
                player->learnSpell(59548, false);//Gift of Naaru
                player->learnSpell(59541, false);//Shadow Resistance
            }
            if (player->getClass() == CLASS_PALADIN)
            {
                player->learnSpell(59542, false);//Gift of Naaru
                player->learnSpell(59535, false);//Shadow Resistance
            }
            if (player->getClass() == CLASS_PRIEST)
            {
                player->learnSpell(59544, false);//Gift of Naaru
                player->learnSpell(59538, false);//Shadow Resistance
            }
            if (player->getClass() == CLASS_SHAMAN || player->getClass() == CLASS_DRUID)
            {
                player->learnSpell(59547, false);//Gift of Naaru
                player->learnSpell(59540, false);//Shadow Resistance
            }
            if (player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_ROGUE)
            {
                player->learnSpell(28880, false);//Gift of Naaru
                player->learnSpell(59221, false);//Shadow Resistance
            }
            break;

        case 3://Dwarves Selection
            AddGossipItemFor(player, GOSSIP_ICON_INTERACT_1, "Commit to the Iron Will of the Dwarves", GOSSIP_SENDER_MAIN, 31);
            AddGossipItemFor(player, GOSSIP_ICON_TALK, localizedBack, GOSSIP_SENDER_MAIN, 11);
            AddGossipItemFor(player, GOSSIP_ICON_TALK, localizedExit, GOSSIP_SENDER_MAIN, 1111);
            SendGossipMenuFor(player, 988883, creature->GetGUID());
            break;

        case 31://Dwarves
            CloseGossipMenuFor(player);
            if (!player->HasEnoughMoney(int32(RTS1 * GOLD)))//gold check
                return true;
            player->ModifyMoney(int32(-RTS1 * GOLD));//Deducting the money if check passes
            player->CastSpell(player, 47292);//Level up visual effect to let you know the transaction did occure and money is deducted
            RemoveAllRacials(player); //Remove all racials
            player->learnSpell(2481, false);//Find Treasure
            player->learnSpell(20596, false);//Frost Resistance
            player->learnSpell(20595, false);//Gun Specialization
            player->learnSpell(59224, false);//Mace Specialization
            player->learnSpell(20594, false);//Stoneform
            break;

        case 4://Gnome Selection
            AddGossipItemFor(player, GOSSIP_ICON_INTERACT_1, "Commit to the Technological Might of the Gnomes", GOSSIP_SENDER_MAIN, 41);
            AddGossipItemFor(player, GOSSIP_ICON_TALK, localizedBack, GOSSIP_SENDER_MAIN, 11);
            AddGossipItemFor(player, GOSSIP_ICON_TALK, localizedExit, GOSSIP_SENDER_MAIN, 1111);
            SendGossipMenuFor(player, 988884, creature->GetGUID());
            break;

        case 41://Gnome
            CloseGossipMenuFor(player);
            if (!player->HasEnoughMoney(int32(RTS1 * GOLD)))//gold check
                return true;
            player->ModifyMoney(int32(-RTS1 * GOLD));//Deducting the money if check passes
            player->CastSpell(player, 47292);//Level up visual effect to let you know the transaction did occur and money is deducted
            RemoveAllRacials(player); //Remove all racials
            player->learnSpell(20592, false);//Arcane Resistance
            player->learnSpell(20593, false);//Engineering Specialization
            player->learnSpell(20589, false);//Escape Artist
            player->learnSpell(20591, false);//Expansive Mind
            break;

        case 5://Human Selection
            AddGossipItemFor(player, GOSSIP_ICON_INTERACT_1, "Commit to the Human Spirit", GOSSIP_SENDER_MAIN, 51);
            AddGossipItemFor(player, GOSSIP_ICON_TALK, localizedBack, GOSSIP_SENDER_MAIN, 11);
            AddGossipItemFor(player, GOSSIP_ICON_TALK, localizedExit, GOSSIP_SENDER_MAIN, 1111);
            SendGossipMenuFor(player, 988885, creature->GetGUID());
            break;

        case 51://Human
            CloseGossipMenuFor(player);
            if (!player->HasEnoughMoney(int32(RTS1 * GOLD)))//gold check
                return true;
            player->ModifyMoney(int32(-RTS1 * GOLD));//Deducting the money if check passes
            player->CastSpell(player, 47292);//Level up visual effect to let you know the transaction did occure and money is deducted
            RemoveAllRacials(player); //Remove all racials
            player->learnSpell(20599, false);//Diplomacy
            player->learnSpell(59752, false);//Every man for himself
            player->learnSpell(20864, false);//Mace Specialization
            player->learnSpell(58985, false);//Perception
            player->learnSpell(20597, false);//Sword Specialization
            player->learnSpell(20598, false);//The Human Spirit
            break;

        case 6://Night Elf Selection
            AddGossipItemFor(player, GOSSIP_ICON_INTERACT_1, "Commit to the Ancient Night Elves", GOSSIP_SENDER_MAIN, 61);
            AddGossipItemFor(player, GOSSIP_ICON_TALK, localizedBack, GOSSIP_SENDER_MAIN, 11);
            AddGossipItemFor(player, GOSSIP_ICON_TALK, localizedExit, GOSSIP_SENDER_MAIN, 1111);
            SendGossipMenuFor(player, 988886, creature->GetGUID());
            break;

        case 61://Night Elf
            CloseGossipMenuFor(player);
            if (!player->HasEnoughMoney(int32(RTS1 * GOLD)))//gold check
                return true;
            player->ModifyMoney(int32(-RTS1 * GOLD));//Deducting the money if check passes
            player->CastSpell(player, 47292);//Level up visual effect to let you know the transaction did occure and money is deducted
            RemoveAllRacials(player); //Remove all racials
            player->learnSpell(20583, false);//Nature Resistance
            player->learnSpell(20582, false);//Quickness
            player->learnSpell(58984, false);//Shadowmeld
            player->learnSpell(20585, false);//Wisp Spirit
            player->learnSpell(21009, false);//Elusiveness
            break;

        case 7://Orc Selection
            AddGossipItemFor(player, GOSSIP_ICON_INTERACT_1, "Commit to the Strength of the Orc", GOSSIP_SENDER_MAIN, 71);
            AddGossipItemFor(player, GOSSIP_ICON_TALK, localizedBack, GOSSIP_SENDER_MAIN, 11);
            AddGossipItemFor(player, GOSSIP_ICON_TALK, localizedExit, GOSSIP_SENDER_MAIN, 1111);
            SendGossipMenuFor(player, 988887, creature->GetGUID());
            break;

        case 71://Orc
            CloseGossipMenuFor(player);
            if (!player->HasEnoughMoney(int32(RTS1 * GOLD)))//gold check
                return true;
            player->ModifyMoney(int32(-RTS1 * GOLD));//Deducting the money if check passes
            player->CastSpell(player, 47292);//Level up visual effect to let you know the transaction did occure and money is deducted
            RemoveAllRacials(player); //Remove all racials
            player->learnSpell(20574, false);//Axe Specialization
            player->learnSpell(20573, false);//Hardiness

            // COMMAND VARIANTS
            if (player->getClass() == CLASS_DEATH_KNIGHT)
            {
                player->learnSpell(54562, false);//Command (DK)
            }
            if (player->getClass() == CLASS_HUNTER)
            {
                player->learnSpell(20576, false);//Command (Hunter)
            }
            if (player->getClass() == CLASS_SHAMAN)
            {
                player->learnSpell(65222, false);//Command (Shaman)
            }
            if (player->getClass() == CLASS_WARLOCK)
            {
                player->learnSpell(20575, false);//Command (Warlock)
            }
            if (player->getClass() == CLASS_ROGUE || player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_DRUID || player->getClass() == CLASS_PALADIN || player->getClass() == CLASS_PRIEST)
            {
                player->learnSpell(21563, false);//Command (Non Pet Users)
            }

            // BLOOD FURY VARIANTS
            if (player->getClass() == CLASS_ROGUE || player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_HUNTER || player->getClass() == CLASS_DEATH_KNIGHT)
            {
                player->learnSpell(20572, false);//Blood Fury (AP only)
            }
            if (player->getClass() == CLASS_SHAMAN || player->getClass() == CLASS_DRUID || player->getClass() == CLASS_PALADIN)
            {
                player->learnSpell(33697, false);//Blood Fury (SP + AP)
            }
            if (player->getClass() == CLASS_MAGE || player->getClass() == CLASS_WARLOCK || player->getClass() == CLASS_PRIEST)
            {
                player->learnSpell(33702, false);//Blood Fury (SP only)
            }
            break;

        case 8://Tauren Selection
            AddGossipItemFor(player, GOSSIP_ICON_INTERACT_1, "Commit to the Endurance of the Taurens", GOSSIP_SENDER_MAIN, 81);
            AddGossipItemFor(player, GOSSIP_ICON_TALK, localizedBack, GOSSIP_SENDER_MAIN, 11);
            AddGossipItemFor(player, GOSSIP_ICON_TALK, localizedExit, GOSSIP_SENDER_MAIN, 1111);
            SendGossipMenuFor(player, 988888, creature->GetGUID());
            break;

        case 81://Tauren
            CloseGossipMenuFor(player);
            if (!player->HasEnoughMoney(int32(RTS1 * GOLD)))//gold check
                return true;
            player->ModifyMoney(int32(-RTS1 * GOLD));//Deducting the money if check passes
            player->CastSpell(player, 47292);//Level up visual effect to let you know the transaction did occure and money is deducted
            RemoveAllRacials(player); //Remove all racials
            player->learnSpell(20552, false);//Cultivation
            player->learnSpell(20550, false);//Endurance
            player->learnSpell(20551, false);//Nature Resistance
            player->learnSpell(20549, false);//Warstomp
            break;

        case 9://Troll Selection
            AddGossipItemFor(player, GOSSIP_ICON_INTERACT_1, "Commit to the Vodoo of the Trolls", GOSSIP_SENDER_MAIN, 91);
            AddGossipItemFor(player, GOSSIP_ICON_TALK, localizedBack, GOSSIP_SENDER_MAIN, 11);
            AddGossipItemFor(player, GOSSIP_ICON_TALK, localizedExit, GOSSIP_SENDER_MAIN, 1111);
            SendGossipMenuFor(player, 988889, creature->GetGUID());
            break;

        case 91://Troll
            CloseGossipMenuFor(player);
            if (!player->HasEnoughMoney(int32(RTS1 * GOLD)))//gold check
                return true;
            player->ModifyMoney(int32(-RTS1 * GOLD));//Deducting the money if check passes
            player->CastSpell(player, 47292);//Level up visual effect to let you know the transaction did occure and money is deducted
            RemoveAllRacials(player); //Remove all racials
            player->learnSpell(20557, false);//Beast Slaying
            player->learnSpell(26297, false);//Berserking
            player->learnSpell(26290, false);//Bow Specialization
            player->learnSpell(58943, false);//Da Voodoo Shuffle
            player->learnSpell(20555, false);//Regeneration
            player->learnSpell(20558, false);//Throwing Specialization
            break;

        case 10://Undead Selection
            AddGossipItemFor(player, GOSSIP_ICON_INTERACT_1, "Commit to the Will of the Forsaken", GOSSIP_SENDER_MAIN, 101);
            AddGossipItemFor(player, GOSSIP_ICON_TALK, localizedBack, GOSSIP_SENDER_MAIN, 11);
            AddGossipItemFor(player, GOSSIP_ICON_TALK, localizedExit, GOSSIP_SENDER_MAIN, 1111);
            SendGossipMenuFor(player, 988880, creature->GetGUID());
            break;

        case 101://Undead
            CloseGossipMenuFor(player);
            if (!player->HasEnoughMoney(int32(RTS1 * GOLD)))//gold check
                return true;
            player->ModifyMoney(int32(-RTS1 * GOLD));//Deducting the money if check passes
            player->CastSpell(player, 47292);//Level up visual effect to let you know the transaction did occure and money is deducted
            RemoveAllRacials(player); //Remove all racials
            player->learnSpell(20577, false);//Cannibalize
            player->learnSpell(20579, false);//Shadow Resistance
            player->learnSpell(5227, false);//Underwater Breating
            player->learnSpell(7744, false);//Will of the Forsaken
            break;

        default:

            break;
        }
        return true;
    }
};

void AddSC_racial_traits_npc()
{
    new Azerothcore_Race_Trait_announce();
    new npc_race_trait_swap();
}
