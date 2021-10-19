/*
 * This file is part of the Azerothcore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
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
#include "ScriptPCH.h"
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

#define LOCALE_BES_0 "Blood Elf Racial Trait Swap -"
#define LOCALE_BES_1 "블러드 엘프 인종 특성 스왑 -"
#define LOCALE_BES_2 "Échange de traits raciaux des elfes de sang -"
#define LOCALE_BES_3 "Rassenwechsel der Blutelfen -"
#define LOCALE_BES_4 "血精靈種族特質交換 -"
#define LOCALE_BES_5 "血精靈種族特質交換 -"
#define LOCALE_BES_6 "Intercambio de rasgos raciales de elfos de sangre -"
#define LOCALE_BES_7 "Intercambio de rasgos raciales de elfos de sangre -"
#define LOCALE_BES_8 "Обмен расовой особенностью эльфов крови -"

#define LOCALE_DRS_0 "Draenei Racial Trait Swap  -"
#define LOCALE_DRS_1 "드레나이 인종 특성 스왑 -"
#define LOCALE_DRS_2 "Échange de traits raciaux draeneï -"
#define LOCALE_DRS_3 "Draenei Rasseneigenschaftstausch -"
#define LOCALE_DRS_4 "德萊尼人種特質交換 -"
#define LOCALE_DRS_5 "德萊尼人種特質交換 -"
#define LOCALE_DRS_6 "Cambio de rasgo racial Draenei -"
#define LOCALE_DRS_7 "Cambio de rasgo racial Draenei -"
#define LOCALE_DRS_8 "Обмен расовыми особенностями дренеев -"

#define LOCALE_DWS_0 "Dwarven Racial Trait Swap -"
#define LOCALE_DWS_1 "드워프 종족 특성 전환 -"
#define LOCALE_DWS_2 "Échange de traits raciaux nains -"
#define LOCALE_DWS_3 "Tausch der Rasseneigenschaften der Zwerge -"
#define LOCALE_DWS_4 "矮人種族特質交換 -"
#define LOCALE_DWS_5 "矮人種族特質交換 -"
#define LOCALE_DWS_6 "Intercambio de rasgos raciales enanos -"
#define LOCALE_DWS_7 "Intercambio de rasgos raciales enanos -"
#define LOCALE_DWS_8 "Обмен расовыми особенностями гномов -"

#define LOCALE_GNS_0 "Gnome Racial Trait Swap -"
#define LOCALE_GNS_1 "그놈 인종 특성 스왑 -"
#define LOCALE_GNS_2 "Échange de traits raciaux de gnome -"
#define LOCALE_GNS_3 "Tausch der Rasseneigenschaft Gnom -"
#define LOCALE_GNS_4 "侏儒種族特質交換 -"
#define LOCALE_GNS_5 "侏儒種族特質交換 -"
#define LOCALE_GNS_6 "Cambio de rasgo racial de gnomo -"
#define LOCALE_GNS_7 "Cambio de rasgo racial de gnomo -"
#define LOCALE_GNS_8 "Смена расовой особенности гномов -"

#define LOCALE_HUS_0 "Human Racial Trait Swap -"
#define LOCALE_HUS_1 "인간 인종 특성 교환 -"
#define LOCALE_HUS_2 "Échange de traits raciaux humains -"
#define LOCALE_HUS_3 "Austausch von menschlichen Rassenmerkmalen -"
#define LOCALE_HUS_4 "人類種族特質交換 -"
#define LOCALE_HUS_5 "人類種族特質交換 -"
#define LOCALE_HUS_6 "Intercambio de rasgos raciales humanos -"
#define LOCALE_HUS_7 "Intercambio de rasgos raciales humanos -"
#define LOCALE_HUS_8 "Обмен расовыми особенностями человека -"

#define LOCALE_NES_0 "Night Elf Racial Trait Swap -"
#define LOCALE_NES_1 "나이트 엘프 인종 특성 스왑 -"
#define LOCALE_NES_2 "Échange de traits raciaux des elfes de la nuit -"
#define LOCALE_NES_3 "Tausch der Nachtelfen-Rasseneigenschaft -"
#define LOCALE_NES_4 "暗夜精靈種族特質交換 -"
#define LOCALE_NES_5 "暗夜精靈種族特質交換 -"
#define LOCALE_NES_6 "Cambio de rasgo racial elfo de la noche -"
#define LOCALE_NES_7 "Cambio de rasgo racial elfo de la noche -"
#define LOCALE_NES_8 "Обмен расовыми особенностями ночных эльфов -"

#define LOCALE_ORC_0 "Orc Racial Trait Swap -"
#define LOCALE_ORC_1 "오크 종족 특성 교환 -"
#define LOCALE_ORC_2 "Échange de traits raciaux orques -"
#define LOCALE_ORC_3 "Austausch der Ork-Rassenmerkmale -"
#define LOCALE_ORC_4 "獸人種族特質交換 -"
#define LOCALE_ORC_5 "獸人種族特質交換 -"
#define LOCALE_ORC_6 "Intercambio de rasgos raciales de orcos -"
#define LOCALE_ORC_7 "Intercambio de rasgos raciales de orcos -"
#define LOCALE_ORC_8 "Смена расовой особенности орков -"

#define LOCALE_TUR_0 "Tauren Racial Trait Swap -"
#define LOCALE_TUR_1 "타우렌 인종 특성 교환 -"
#define LOCALE_TUR_2 "Échange de traits raciaux Tauren -"
#define LOCALE_TUR_3 "Tauren Rasseneigenschaftstausch -"
#define LOCALE_TUR_4 "牛頭人種族特質交換 -"
#define LOCALE_TUR_5 "牛頭人種族特質交換 -"
#define LOCALE_TUR_6 "Intercambio de rasgos raciales tauren -"
#define LOCALE_TUR_7 "Intercambio de rasgos raciales tauren -"
#define LOCALE_TUR_8 "Обмен расовыми особенностями тауренов -"

#define LOCALE_TRL_0 "Troll Racial Trait Swap -"
#define LOCALE_TRL_1 "트롤 인종 특성 교환 -"
#define LOCALE_TRL_2 "Échange de traits raciaux de troll -"
#define LOCALE_TRL_3 "Troll-Rasseneigenschaftstausch -"
#define LOCALE_TRL_4 "巨魔種族特質交換 -"
#define LOCALE_TRL_5 "巨魔種族特質交換 -"
#define LOCALE_TRL_6 "Cambio de rasgo racial de trol -"
#define LOCALE_TRL_7 "Cambio de rasgo racial de trol -"
#define LOCALE_TRL_8 "Обмен расовой особенности троллей -"

#define LOCALE_UND_0 "Undead Racial Trait Swap -"
#define LOCALE_UND_1 "언데드 인종 특성 스왑 -"
#define LOCALE_UND_2 "Échange de traits raciaux morts-vivants -"
#define LOCALE_UND_3 "Untoter Rassenmerkmalentausch -"
#define LOCALE_UND_4 "亡靈種族特質交換 -"
#define LOCALE_UND_5 "亡靈種族特質交換 -"
#define LOCALE_UND_6 "Intercambio de rasgos raciales no muertos -"
#define LOCALE_UND_7 "Intercambio de rasgos raciales no muertos -"
#define LOCALE_UND_8 "Смена расовой особенности нежити -"

class Azerothcore_Race_Trait_announce : public PlayerScript
{
public:
    Azerothcore_Race_Trait_announce() : PlayerScript("Azerothcore_Race_Trait_announce") { }

    void OnLogin(Player* Player)
    {
        if (sConfigMgr->GetBoolDefault("Azerothcore.Racial.Trait.Swap.Announce.enable", true))
        {
            ChatHandler(Player->GetSession()).SendSysMessage("This server is running the |cff4CFF00Azerothcore Racial Trait Swap NPC |rmodule.");
        }
    }
};

class npc_race_trait_swap : public CreatureScript
{
public:

    npc_race_trait_swap() : CreatureScript("npc_race_trait_swap") { }

    bool OnGossipHello(Player* player, Creature* creature)
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
        const int32 RTS1 = sConfigMgr->GetIntDefault("Racial.Traits.Swap.Gold", 100);
        char const* localizedExit;
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
        char const* localizedBack;
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
        char const* localizedGold;
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
        char const* localizedBES;
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
        char const* localizedDRS;
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
        char const* localizedDWS;
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
        char const* localizedGNS;
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
        char const* localizedHUS;
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
        char const* localizedNES;
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
        char const* localizedORC;
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
        char const* localizedTUR;
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
        char const* localizedTRL;
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
        char const* localizedUND;
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
            player->learnSpell(28877, false);//Arcane Affinity
            player->learnSpell(822, false);// Magic Resistance
            if (player->getClass() == CLASS_DEATH_KNIGHT)
            {
                player->learnSpell(50613, false);//Arcane Torrent
            }
            if (player->getClass() == CLASS_HUNTER || player->getClass() == CLASS_MAGE || player->getClass() == CLASS_PALADIN || player->getClass() == CLASS_WARLOCK)
            {
                player->learnSpell(28730, false);//Arcane Torrent
            }
            if (player->getClass() == CLASS_ROGUE)
            {
                player->learnSpell(25046, false);//Arcane Torrent
            }
            //Draenei:
            player->removeSpell(28875, SPEC_MASK_ALL, false);// unlearn Gemcutting
            //~DK
            player->removeSpell(59545, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59539, SPEC_MASK_ALL, false);// unlearnShadow Resistance
            //~DK, Hunter, Paladin, Warrior
            player->removeSpell(6562, SPEC_MASK_ALL, false);// unlearn Heroic Presence
            //~Hunter
            player->removeSpell(59543, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59536, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            //~Mage
            player->removeSpell(59548, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59541, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            //~Mage, Priest, Shaman
            player->removeSpell(28878, SPEC_MASK_ALL, false);// unlearn Heroic Presence
            //~Paladin
            player->removeSpell(59542, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59535, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            //~Priest
            player->removeSpell(59544, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59538, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            //~Shaman
            player->removeSpell(59547, SPEC_MASK_ALL, false);// unlearn Gift of the Narru
            player->removeSpell(59540, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            //~Warrior
            player->removeSpell(28880, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59221, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
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
            //~DK, Hunter, Druid, Hunter, Priest, Rogue, Warrior
            player->removeSpell(21009, SPEC_MASK_ALL, false);// unlearn Elusiveness
            //Orc:
            player->removeSpell(20574, SPEC_MASK_ALL, false);// unlearn Axe Specialization
            player->removeSpell(20573, SPEC_MASK_ALL, false);// unlearn Hardiness
            //~DK
            player->removeSpell(54562, SPEC_MASK_ALL, false);// unlearn Command
            //~DK, hunter, rogue, warrior
            player->removeSpell(20572, SPEC_MASK_ALL, false);// unlearn Blood Fury
            //~Druid, mage, paladin, priest, rogue, warrior
            player->removeSpell(21563, SPEC_MASK_ALL, false);// unlearn Command
            //~Hunter
            player->removeSpell(20576, SPEC_MASK_ALL, false);// unlearn Command
            //~Shaman
            player->removeSpell(33697, SPEC_MASK_ALL, false);// unlearn Blood fury
            player->removeSpell(65222, SPEC_MASK_ALL, false);// unlearn Command
            //~Warlock
            player->removeSpell(33702, SPEC_MASK_ALL, false);// unlearn Blood Fury
            player->removeSpell(20575, SPEC_MASK_ALL, false);// unlearn Command
            //Tauren:
            player->removeSpell(20552, SPEC_MASK_ALL, false);// unlearn Cultivation
            player->removeSpell(20550, SPEC_MASK_ALL, false);// unlearn Endurance
            player->removeSpell(20551, SPEC_MASK_ALL, false);// unlearn Nature Resistance
            player->removeSpell(20549, SPEC_MASK_ALL, false);// unlearn Warstomp
            //Troll:
            player->removeSpell(20557, SPEC_MASK_ALL, false);// unlearn Beast Slaying
            player->removeSpell(26297, SPEC_MASK_ALL, false);// unlearn Berserking
            player->removeSpell(26290, SPEC_MASK_ALL, false);// unlearn Bow Specialization
            player->removeSpell(58943, SPEC_MASK_ALL, false);// unlearn Da Voodoo Shuffle
            player->removeSpell(20555, SPEC_MASK_ALL, false);// unlearn Regeneration
            player->removeSpell(20558, SPEC_MASK_ALL, false);// unlearn Throwing Specialization
            //Undead:
            player->removeSpell(20577, SPEC_MASK_ALL, false);// unlearn Cannibalize
            player->removeSpell(20579, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            player->removeSpell(5227, SPEC_MASK_ALL, false);// unlearn Underwater Breating
            player->removeSpell(7744, SPEC_MASK_ALL, false);// unlearn Will of the Forsaken
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
            player->learnSpell(28875, false);// Gem Cutting
            if (player->getClass() == CLASS_DEATH_KNIGHT)
            {
                player->learnSpell(59545, false);//Gift of Naaru
                player->learnSpell(59539, false);//Shadow Resistance
            }
            if (player->getClass() == CLASS_DEATH_KNIGHT || player->getClass() == CLASS_HUNTER || player->getClass() == CLASS_PALADIN || player->getClass() == CLASS_WARRIOR)
            {
                player->learnSpell(6562, false);//Heroic Presence
            }
            if (player->getClass() == CLASS_HUNTER)
            {
                player->learnSpell(59543, false);//Gift of Naaru
                player->learnSpell(59536, false);//Shadow Resistance
            }
            if (player->getClass() == CLASS_MAGE)
            {
                player->learnSpell(59548, false);//Gift of Naaru
                player->learnSpell(59541, false);//Shadow Resistance
            }
            if (player->getClass() == CLASS_MAGE || player->getClass() == CLASS_PRIEST || player->getClass() == CLASS_SHAMAN)
            {
                player->learnSpell(28878, false);//Heroic Presence
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
            if (player->getClass() == CLASS_SHAMAN)
            {
                player->learnSpell(59547, false);//Gift of Naaru
                player->learnSpell(59540, false);//Shadow Resistance
            }
            if (player->getClass() == CLASS_SHAMAN)
            {
                player->learnSpell(28880, false);//Gift of Naaru
                player->learnSpell(59221, false);//Shadow Resistance
            }
            //blood elf:
            player->removeSpell(28877, SPEC_MASK_ALL, false);// unlearn Arcane Affinity
            player->removeSpell(822, SPEC_MASK_ALL, false);// unlearn Magic Resistance
            //~DK
            player->removeSpell(50613, SPEC_MASK_ALL, false);// unlearn Arcane Torrent
            //~Hunter, mage, paladin, priest, warlock
            player->removeSpell(28730, SPEC_MASK_ALL, false);// unlearn Arcane Torrent
            //~Rogue
            player->removeSpell(25046, SPEC_MASK_ALL, false);// unlearn Arcane Torrent
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
            //~DK, Hunter, Druid, Hunter, Priest, Rogue, Warrior
            player->removeSpell(21009, SPEC_MASK_ALL, false);// unlearn Elusiveness
            //Orc:
            player->removeSpell(20574, SPEC_MASK_ALL, false);// unlearn Axe Specialization
            player->removeSpell(20573, SPEC_MASK_ALL, false);// unlearn Hardiness
            //~DK
            player->removeSpell(54562, SPEC_MASK_ALL, false);// unlearn Command
            //~DK, hunter, rogue, warrior
            player->removeSpell(20572, SPEC_MASK_ALL, false);// unlearn Blood Fury
            //~Druid, mage, paladin, priest, rogue, warrior
            player->removeSpell(21563, SPEC_MASK_ALL, false);// unlearn Command
            //~Hunter
            player->removeSpell(20576, SPEC_MASK_ALL, false);// unlearn Command
            //~Shaman
            player->removeSpell(33697, SPEC_MASK_ALL, false);// unlearn Blood fury
            player->removeSpell(65222, SPEC_MASK_ALL, false);// unlearn Command
            //~Warlock
            player->removeSpell(33702, SPEC_MASK_ALL, false);// unlearn Blood Fury
            player->removeSpell(20575, SPEC_MASK_ALL, false);// unlearn Command
            //Tauren:
            player->removeSpell(20552, SPEC_MASK_ALL, false);// unlearn Cultivation
            player->removeSpell(20550, SPEC_MASK_ALL, false);// unlearn Endurance
            player->removeSpell(20551, SPEC_MASK_ALL, false);// unlearn Nature Resistance
            player->removeSpell(20549, SPEC_MASK_ALL, false);// unlearn Warstomp
            //Troll:
            player->removeSpell(20557, SPEC_MASK_ALL, false);// unlearn Beast Slaying
            player->removeSpell(26297, SPEC_MASK_ALL, false);// unlearn Berserking
            player->removeSpell(26290, SPEC_MASK_ALL, false);// unlearn Bow Specialization
            player->removeSpell(58943, SPEC_MASK_ALL, false);// unlearn Da Voodoo Shuffle
            player->removeSpell(20555, SPEC_MASK_ALL, false);// unlearn Regeneration
            player->removeSpell(20558, SPEC_MASK_ALL, false);// unlearn Throwing Specialization
            //Undead:
            player->removeSpell(20577, SPEC_MASK_ALL, false);// unlearn Cannibalize
            player->removeSpell(20579, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            player->removeSpell(5227, SPEC_MASK_ALL, false);// unlearn Underwater Breating
            player->removeSpell(7744, SPEC_MASK_ALL, false);// unlearn Will of the Forsaken
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
            player->learnSpell(2481, false);//Find Treasure
            player->learnSpell(20596, false);//Frost Resistance
            player->learnSpell(20595, false);//Gun Specialization
            player->learnSpell(59224, false);//Mace Specialization
            player->learnSpell(20594, false);//Stoneform
            //blood elf:
            player->removeSpell(28877, SPEC_MASK_ALL, false);// unlearn Arcane Affinity
            player->removeSpell(822, SPEC_MASK_ALL, false);// unlearn Magic Resistance
            //~DK
            player->removeSpell(50613, SPEC_MASK_ALL, false);// unlearn Arcane Torrent
            //~Hunter, mage, paladin, priest, warlock
            player->removeSpell(28730, SPEC_MASK_ALL, false);// unlearn Arcane Torrent
            //~Rogue
            player->removeSpell(25046, SPEC_MASK_ALL, false);// unlearn Arcane Torrent
            //Draenei:
            player->removeSpell(28875, SPEC_MASK_ALL, false);// unlearn Gemcutting
            //~DK
            player->removeSpell(59545, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59539, SPEC_MASK_ALL, false);// unlearnShadow Resistance
            //~DK, Hunter, Paladin, Warrior
            player->removeSpell(6562, SPEC_MASK_ALL, false);// unlearn Heroic Presence
            //~Hunter
            player->removeSpell(59543, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59536, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            //~Mage
            player->removeSpell(59548, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59541, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            //~Mage, Priest, Shaman
            player->removeSpell(28878, SPEC_MASK_ALL, false);// unlearn Heroic Presence
            //~Paladin
            player->removeSpell(59542, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59535, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            //~Priest
            player->removeSpell(59544, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59538, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            //~Shaman
            player->removeSpell(59547, SPEC_MASK_ALL, false);// unlearn Gift of the Narru
            player->removeSpell(59540, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            //~Warrior
            player->removeSpell(28880, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59221, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
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
            //~DK, Hunter, Druid, Hunter, Priest, Rogue, Warrior
            player->removeSpell(21009, SPEC_MASK_ALL, false);// unlearn Elusiveness
            //Orc:
            player->removeSpell(20574, SPEC_MASK_ALL, false);// unlearn Axe Specialization
            player->removeSpell(20573, SPEC_MASK_ALL, false);// unlearn Hardiness
            //~DK
            player->removeSpell(54562, SPEC_MASK_ALL, false);// unlearn Command
            //~DK, hunter, rogue, warrior
            player->removeSpell(20572, SPEC_MASK_ALL, false);// unlearn Blood Fury
            //~Druid, mage, paladin, priest, rogue, warrior
            player->removeSpell(21563, SPEC_MASK_ALL, false);// unlearn Command
            //~Hunter
            player->removeSpell(20576, SPEC_MASK_ALL, false);// unlearn Command
            //~Shaman
            player->removeSpell(33697, SPEC_MASK_ALL, false);// unlearn Blood fury
            player->removeSpell(65222, SPEC_MASK_ALL, false);// unlearn Command
            //~Warlock
            player->removeSpell(33702, SPEC_MASK_ALL, false);// unlearn Blood Fury
            player->removeSpell(20575, SPEC_MASK_ALL, false);// unlearn Command
            //Tauren:
            player->removeSpell(20552, SPEC_MASK_ALL, false);// unlearn Cultivation
            player->removeSpell(20550, SPEC_MASK_ALL, false);// unlearn Endurance
            player->removeSpell(20551, SPEC_MASK_ALL, false);// unlearn Nature Resistance
            player->removeSpell(20549, SPEC_MASK_ALL, false);// unlearn Warstomp
            //Troll:
            player->removeSpell(20557, SPEC_MASK_ALL, false);// unlearn Beast Slaying
            player->removeSpell(26297, SPEC_MASK_ALL, false);// unlearn Berserking
            player->removeSpell(26290, SPEC_MASK_ALL, false);// unlearn Bow Specialization
            player->removeSpell(58943, SPEC_MASK_ALL, false);// unlearn Da Voodoo Shuffle
            player->removeSpell(20555, SPEC_MASK_ALL, false);// unlearn Regeneration
            player->removeSpell(20558, SPEC_MASK_ALL, false);// unlearn Throwing Specialization
            //Undead:
            player->removeSpell(20577, SPEC_MASK_ALL, false);// unlearn Cannibalize
            player->removeSpell(20579, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            player->removeSpell(5227, SPEC_MASK_ALL, false);// unlearn Underwater Breating
            player->removeSpell(7744, SPEC_MASK_ALL, false);// unlearn Will of the Forsaken
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
            player->learnSpell(20592, false);//Arcane Resistance
            player->learnSpell(20593, false);//Engineering Specialization
            player->learnSpell(20589, false);//Escape Artist
            player->learnSpell(20591, false);//Expansive Mind
            //blood elf:
            player->removeSpell(28877, SPEC_MASK_ALL, false);// unlearn Arcane Affinity
            player->removeSpell(822, SPEC_MASK_ALL, false);// unlearn Magic Resistance
            //~DK
            player->removeSpell(50613, SPEC_MASK_ALL, false);// unlearn Arcane Torrent
            //~Hunter, mage, paladin, priest, warlock
            player->removeSpell(28730, SPEC_MASK_ALL, false);// unlearn Arcane Torrent
            //~Rogue
            player->removeSpell(25046, SPEC_MASK_ALL, false);// unlearn Arcane Torrent
            //Draenei:
            player->removeSpell(28875, SPEC_MASK_ALL, false);// unlearn Gemcutting
            //~DK
            player->removeSpell(59545, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59539, SPEC_MASK_ALL, false);// unlearnShadow Resistance
            //~DK, Hunter, Paladin, Warrior
            player->removeSpell(6562, SPEC_MASK_ALL, false);// unlearn Heroic Presence
            //~Hunter
            player->removeSpell(59543, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59536, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            //~Mage
            player->removeSpell(59548, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59541, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            //~Mage, Priest, Shaman
            player->removeSpell(28878, SPEC_MASK_ALL, false);// unlearn Heroic Presence
            //~Paladin
            player->removeSpell(59542, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59535, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            //~Priest
            player->removeSpell(59544, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59538, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            //~Shaman
            player->removeSpell(59547, SPEC_MASK_ALL, false);// unlearn Gift of the Narru
            player->removeSpell(59540, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            //~Warrior
            player->removeSpell(28880, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59221, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            //Dwarven:
            player->removeSpell(2481, SPEC_MASK_ALL, false);// unlearn Find Treasure
            player->removeSpell(20596, SPEC_MASK_ALL, false);// unlearn Frost Resistance
            player->removeSpell(20595, SPEC_MASK_ALL, false);// unlearn Gun Specialization
            player->removeSpell(59224, SPEC_MASK_ALL, false);// unlearn Mace Specialization
            player->removeSpell(20594, SPEC_MASK_ALL, false);// unlearn Stoneform
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
            //~DK, Hunter, Druid, Hunter, Priest, Rogue, Warrior
            player->removeSpell(21009, SPEC_MASK_ALL, false);// unlearn Elusiveness
            //Orc:
            player->removeSpell(20574, SPEC_MASK_ALL, false);// unlearn Axe Specialization
            player->removeSpell(20573, SPEC_MASK_ALL, false);// unlearn Hardiness
            //~DK
            player->removeSpell(54562, SPEC_MASK_ALL, false);// unlearn Command
            //~DK, hunter, rogue, warrior
            player->removeSpell(20572, SPEC_MASK_ALL, false);// unlearn Blood Fury
            //~Druid, mage, paladin, priest, rogue, warrior
            player->removeSpell(21563, SPEC_MASK_ALL, false);// unlearn Command
            //~Hunter
            player->removeSpell(20576, SPEC_MASK_ALL, false);// unlearn Command
            //~Shaman
            player->removeSpell(33697, SPEC_MASK_ALL, false);// unlearn Blood fury
            player->removeSpell(65222, SPEC_MASK_ALL, false);// unlearn Command
            //~Warlock
            player->removeSpell(33702, SPEC_MASK_ALL, false);// unlearn Blood Fury
            player->removeSpell(20575, SPEC_MASK_ALL, false);// unlearn Command
            //Tauren:
            player->removeSpell(20552, SPEC_MASK_ALL, false);// unlearn Cultivation
            player->removeSpell(20550, SPEC_MASK_ALL, false);// unlearn Endurance
            player->removeSpell(20551, SPEC_MASK_ALL, false);// unlearn Nature Resistance
            player->removeSpell(20549, SPEC_MASK_ALL, false);// unlearn Warstomp
            //Troll:
            player->removeSpell(20557, SPEC_MASK_ALL, false);// unlearn Beast Slaying
            player->removeSpell(26297, SPEC_MASK_ALL, false);// unlearn Berserking
            player->removeSpell(26290, SPEC_MASK_ALL, false);// unlearn Bow Specialization
            player->removeSpell(58943, SPEC_MASK_ALL, false);// unlearn Da Voodoo Shuffle
            player->removeSpell(20555, SPEC_MASK_ALL, false);// unlearn Regeneration
            player->removeSpell(20558, SPEC_MASK_ALL, false);// unlearn Throwing Specialization
            //Undead:
            player->removeSpell(20577, SPEC_MASK_ALL, false);// unlearn Cannibalize
            player->removeSpell(20579, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            player->removeSpell(5227, SPEC_MASK_ALL, false);// unlearn Underwater Breating
            player->removeSpell(7744, SPEC_MASK_ALL, false);// unlearn Will of the Forsaken
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
            player->learnSpell(20599, false);//Diplomacy
            player->learnSpell(59752, false);//Every man for himself
            player->learnSpell(20864, false);//Mace Specialization
            player->learnSpell(58985, false);//Perception
            player->learnSpell(20597, false);//Sword Specialization
            player->learnSpell(20598, false);//The Human Spirit
            //blood elf:
            player->removeSpell(28877, SPEC_MASK_ALL, false);// unlearn Arcane Affinity
            player->removeSpell(822, SPEC_MASK_ALL, false);// unlearn Magic Resistance
            //~DK
            player->removeSpell(50613, SPEC_MASK_ALL, false);// unlearn Arcane Torrent
            //~Hunter, mage, paladin, priest, warlock
            player->removeSpell(28730, SPEC_MASK_ALL, false);// unlearn Arcane Torrent
            //~Rogue
            player->removeSpell(25046, SPEC_MASK_ALL, false);// unlearn Arcane Torrent
            //Draenei:
            player->removeSpell(28875, SPEC_MASK_ALL, false);// unlearn Gemcutting
            //~DK
            player->removeSpell(59545, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59539, SPEC_MASK_ALL, false);// unlearnShadow Resistance
            //~DK, Hunter, Paladin, Warrior
            player->removeSpell(6562, SPEC_MASK_ALL, false);// unlearn Heroic Presence
            //~Hunter
            player->removeSpell(59543, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59536, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            //~Mage
            player->removeSpell(59548, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59541, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            //~Mage, Priest, Shaman
            player->removeSpell(28878, SPEC_MASK_ALL, false);// unlearn Heroic Presence
            //~Paladin
            player->removeSpell(59542, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59535, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            //~Priest
            player->removeSpell(59544, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59538, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            //~Shaman
            player->removeSpell(59547, SPEC_MASK_ALL, false);// unlearn Gift of the Narru
            player->removeSpell(59540, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            //~Warrior
            player->removeSpell(28880, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59221, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
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
            //Night Elf:
            player->removeSpell(20583, SPEC_MASK_ALL, false);// unlearn Nature Resistance
            player->removeSpell(20582, SPEC_MASK_ALL, false);// unlearn Quickness
            player->removeSpell(58984, SPEC_MASK_ALL, false);// unlearn Shadowmeld
            player->removeSpell(20585, SPEC_MASK_ALL, false);// unlearn Wisp Spirit
            //~DK, Hunter, Druid, Hunter, Priest, Rogue, Warrior
            player->removeSpell(21009, SPEC_MASK_ALL, false);// unlearn Elusiveness
            //Orc:
            player->removeSpell(20574, SPEC_MASK_ALL, false);// unlearn Axe Specialization
            player->removeSpell(20573, SPEC_MASK_ALL, false);// unlearn Hardiness
            //~DK
            player->removeSpell(54562, SPEC_MASK_ALL, false);// unlearn Command
            //~DK, hunter, rogue, warrior
            player->removeSpell(20572, SPEC_MASK_ALL, false);// unlearn Blood Fury
            //~Druid, mage, paladin, priest, rogue, warrior
            player->removeSpell(21563, SPEC_MASK_ALL, false);// unlearn Command
            //~Hunter
            player->removeSpell(20576, SPEC_MASK_ALL, false);// unlearn Command
            //~Shaman
            player->removeSpell(33697, SPEC_MASK_ALL, false);// unlearn Blood fury
            player->removeSpell(65222, SPEC_MASK_ALL, false);// unlearn Command
            //~Warlock
            player->removeSpell(33702, SPEC_MASK_ALL, false);// unlearn Blood Fury
            player->removeSpell(20575, SPEC_MASK_ALL, false);// unlearn Command
            //Tauren:
            player->removeSpell(20552, SPEC_MASK_ALL, false);// unlearn Cultivation
            player->removeSpell(20550, SPEC_MASK_ALL, false);// unlearn Endurance
            player->removeSpell(20551, SPEC_MASK_ALL, false);// unlearn Nature Resistance
            player->removeSpell(20549, SPEC_MASK_ALL, false);// unlearn Warstomp
            //Troll:
            player->removeSpell(20557, SPEC_MASK_ALL, false);// unlearn Beast Slaying
            player->removeSpell(26297, SPEC_MASK_ALL, false);// unlearn Berserking
            player->removeSpell(26290, SPEC_MASK_ALL, false);// unlearn Bow Specialization
            player->removeSpell(58943, SPEC_MASK_ALL, false);// unlearn Da Voodoo Shuffle
            player->removeSpell(20555, SPEC_MASK_ALL, false);// unlearn Regeneration
            player->removeSpell(20558, SPEC_MASK_ALL, false);// unlearn Throwing Specialization
            //Undead:
            player->removeSpell(20577, SPEC_MASK_ALL, false);// unlearn Cannibalize
            player->removeSpell(20579, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            player->removeSpell(5227, SPEC_MASK_ALL, false);// unlearn Underwater Breating
            player->removeSpell(7744, SPEC_MASK_ALL, false);// unlearn Will of the Forsaken
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
            player->learnSpell(20583, false);//Nature Resistance
            player->learnSpell(20582, false);//Quickness
            player->learnSpell(58984, false);//Shadowmeld
            player->learnSpell(20585, false);//Wisp Spirit
            if (player->getClass() == CLASS_DEATH_KNIGHT || player->getClass() == CLASS_DRUID || player->getClass() == CLASS_HUNTER || player->getClass() == CLASS_PRIEST || player->getClass() == CLASS_ROGUE || player->getClass() == CLASS_WARRIOR)
            {
                player->learnSpell(21009, false);//Elusiveness
            }
            //blood elf:
            player->removeSpell(28877, SPEC_MASK_ALL, false);// unlearn Arcane Affinity
            player->removeSpell(822, SPEC_MASK_ALL, false);// unlearn Magic Resistance
            //~DK
            player->removeSpell(50613, SPEC_MASK_ALL, false);// unlearn Arcane Torrent
            //~Hunter, mage, paladin, priest, warlock
            player->removeSpell(28730, SPEC_MASK_ALL, false);// unlearn Arcane Torrent
            //~Rogue
            player->removeSpell(25046, SPEC_MASK_ALL, false);// unlearn Arcane Torrent
            //Draenei:
            player->removeSpell(28875, SPEC_MASK_ALL, false);// unlearn Gemcutting
            //~DK
            player->removeSpell(59545, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59539, SPEC_MASK_ALL, false);// unlearnShadow Resistance
            //~DK, Hunter, Paladin, Warrior
            player->removeSpell(6562, SPEC_MASK_ALL, false);// unlearn Heroic Presence
            //~Hunter
            player->removeSpell(59543, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59536, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            //~Mage
            player->removeSpell(59548, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59541, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            //~Mage, Priest, Shaman
            player->removeSpell(28878, SPEC_MASK_ALL, false);// unlearn Heroic Presence
            //~Paladin
            player->removeSpell(59542, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59535, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            //~Priest
            player->removeSpell(59544, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59538, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            //~Shaman
            player->removeSpell(59547, SPEC_MASK_ALL, false);// unlearn Gift of the Narru
            player->removeSpell(59540, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            //~Warrior
            player->removeSpell(28880, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59221, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
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
            //Orc:
            player->removeSpell(20574, SPEC_MASK_ALL, false);// unlearn Axe Specialization
            player->removeSpell(20573, SPEC_MASK_ALL, false);// unlearn Hardiness
            //~DK
            player->removeSpell(54562, SPEC_MASK_ALL, false);// unlearn Command
            //~DK, hunter, rogue, warrior
            player->removeSpell(20572, SPEC_MASK_ALL, false);// unlearn Blood Fury
            //~Druid, mage, paladin, priest, rogue, warrior
            player->removeSpell(21563, SPEC_MASK_ALL, false);// unlearn Command
            //~Hunter
            player->removeSpell(20576, SPEC_MASK_ALL, false);// unlearn Command
            //~Shaman
            player->removeSpell(33697, SPEC_MASK_ALL, false);// unlearn Blood fury
            player->removeSpell(65222, SPEC_MASK_ALL, false);// unlearn Command
            //~Warlock
            player->removeSpell(33702, SPEC_MASK_ALL, false);// unlearn Blood Fury
            player->removeSpell(20575, SPEC_MASK_ALL, false);// unlearn Command
            //Tauren:
            player->removeSpell(20552, SPEC_MASK_ALL, false);// unlearn Cultivation
            player->removeSpell(20550, SPEC_MASK_ALL, false);// unlearn Endurance
            player->removeSpell(20551, SPEC_MASK_ALL, false);// unlearn Nature Resistance
            player->removeSpell(20549, SPEC_MASK_ALL, false);// unlearn Warstomp
            //Troll:
            player->removeSpell(20557, SPEC_MASK_ALL, false);// unlearn Beast Slaying
            player->removeSpell(26297, SPEC_MASK_ALL, false);// unlearn Berserking
            player->removeSpell(26290, SPEC_MASK_ALL, false);// unlearn Bow Specialization
            player->removeSpell(58943, SPEC_MASK_ALL, false);// unlearn Da Voodoo Shuffle
            player->removeSpell(20555, SPEC_MASK_ALL, false);// unlearn Regeneration
            player->removeSpell(20558, SPEC_MASK_ALL, false);// unlearn Throwing Specialization
            //Undead:
            player->removeSpell(20577, SPEC_MASK_ALL, false);// unlearn Cannibalize
            player->removeSpell(20579, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            player->removeSpell(5227, SPEC_MASK_ALL, false);// unlearn Underwater Breating
            player->removeSpell(7744, SPEC_MASK_ALL, false);// unlearn Will of the Forsaken
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
            player->learnSpell(20574, false);//Axe Specialization
            player->learnSpell(20573, false);//Hardiness
            if (player->getClass() == CLASS_DEATH_KNIGHT)
            {
                player->learnSpell(54562, false);//Command
            }
            if (player->getClass() == CLASS_DEATH_KNIGHT || player->getClass() == CLASS_HUNTER || player->getClass() == CLASS_ROGUE || player->getClass() == CLASS_WARRIOR)
            {
                player->learnSpell(20572, false);//Blood Fury
            }
            if (player->getClass() == CLASS_DRUID || player->getClass() == CLASS_PALADIN || player->getClass() == CLASS_PRIEST || player->getClass() == CLASS_ROGUE || player->getClass() == CLASS_WARRIOR)
            {
                player->learnSpell(21563, false);//Command
            }
            if (player->getClass() == CLASS_HUNTER)
            {
                player->learnSpell(20576, false);//Command
            }
            if (player->getClass() == CLASS_SHAMAN)
            {
                player->learnSpell(33697, false);//Blood Fury
                player->learnSpell(65222, false);//Command
            }
            if (player->getClass() == CLASS_WARLOCK)
            {
                player->learnSpell(33702, false);//Blood Fury
                player->learnSpell(20575, false);//Command
            }
            //blood elf:
            player->removeSpell(28877, SPEC_MASK_ALL, false);// unlearn Arcane Affinity
            player->removeSpell(822, SPEC_MASK_ALL, false);// unlearn Magic Resistance
            //~DK
            player->removeSpell(50613, SPEC_MASK_ALL, false);// unlearn Arcane Torrent
            //~Hunter, mage, paladin, priest, warlock
            player->removeSpell(28730, SPEC_MASK_ALL, false);// unlearn Arcane Torrent
            //~Rogue
            player->removeSpell(25046, SPEC_MASK_ALL, false);// unlearn Arcane Torrent
            //Draenei:
            player->removeSpell(28875, SPEC_MASK_ALL, false);// unlearn Gemcutting
            //~DK
            player->removeSpell(59545, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59539, SPEC_MASK_ALL, false);// unlearnShadow Resistance
            //~DK, Hunter, Paladin, Warrior
            player->removeSpell(6562, SPEC_MASK_ALL, false);// unlearn Heroic Presence
            //~Hunter
            player->removeSpell(59543, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59536, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            //~Mage
            player->removeSpell(59548, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59541, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            //~Mage, Priest, Shaman
            player->removeSpell(28878, SPEC_MASK_ALL, false);// unlearn Heroic Presence
            //~Paladin
            player->removeSpell(59542, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59535, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            //~Priest
            player->removeSpell(59544, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59538, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            //~Shaman
            player->removeSpell(59547, SPEC_MASK_ALL, false);// unlearn Gift of the Narru
            player->removeSpell(59540, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            //~Warrior
            player->removeSpell(28880, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59221, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
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
            //~DK, Hunter, Druid, Hunter, Priest, Rogue, Warrior
            player->removeSpell(21009, SPEC_MASK_ALL, false);// unlearn Elusiveness
            //Tauren:
            player->removeSpell(20552, SPEC_MASK_ALL, false);// unlearn Cultivation
            player->removeSpell(20550, SPEC_MASK_ALL, false);// unlearn Endurance
            player->removeSpell(20551, SPEC_MASK_ALL, false);// unlearn Nature Resistance
            player->removeSpell(20549, SPEC_MASK_ALL, false);// unlearn Warstomp
            //Troll:
            player->removeSpell(20557, SPEC_MASK_ALL, false);// unlearn Beast Slaying
            player->removeSpell(26297, SPEC_MASK_ALL, false);// unlearn Berserking
            player->removeSpell(26290, SPEC_MASK_ALL, false);// unlearn Bow Specialization
            player->removeSpell(58943, SPEC_MASK_ALL, false);// unlearn Da Voodoo Shuffle
            player->removeSpell(20555, SPEC_MASK_ALL, false);// unlearn Regeneration
            player->removeSpell(20558, SPEC_MASK_ALL, false);// unlearn Throwing Specialization
            //Undead:
            player->removeSpell(20577, SPEC_MASK_ALL, false);// unlearn Cannibalize
            player->removeSpell(20579, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            player->removeSpell(5227, SPEC_MASK_ALL, false);// unlearn Underwater Breating
            player->removeSpell(7744, SPEC_MASK_ALL, false);// unlearn Will of the Forsaken
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
            player->learnSpell(20552, false);//Cultivation
            player->learnSpell(20550, false);//Endurance
            player->learnSpell(20551, false);//Nature Resistance
            player->learnSpell(20549, false);//Warstomp
            //blood elf:
            player->removeSpell(28877, SPEC_MASK_ALL, false);// unlearn Arcane Affinity
            player->removeSpell(822, SPEC_MASK_ALL, false);// unlearn Magic Resistance
            //~DK
            player->removeSpell(50613, SPEC_MASK_ALL, false);// unlearn Arcane Torrent
            //~Hunter, mage, paladin, priest, warlock
            player->removeSpell(28730, SPEC_MASK_ALL, false);// unlearn Arcane Torrent
            //~Rogue
            player->removeSpell(25046, SPEC_MASK_ALL, false);// unlearn Arcane Torrent
            //Draenei:
            player->removeSpell(28875, SPEC_MASK_ALL, false);// unlearn Gemcutting
            //~DK
            player->removeSpell(59545, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59539, SPEC_MASK_ALL, false);// unlearnShadow Resistance
            //~DK, Hunter, Paladin, Warrior
            player->removeSpell(6562, SPEC_MASK_ALL, false);// unlearn Heroic Presence
            //~Hunter
            player->removeSpell(59543, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59536, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            //~Mage
            player->removeSpell(59548, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59541, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            //~Mage, Priest, Shaman
            player->removeSpell(28878, SPEC_MASK_ALL, false);// unlearn Heroic Presence
            //~Paladin
            player->removeSpell(59542, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59535, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            //~Priest
            player->removeSpell(59544, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59538, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            //~Shaman
            player->removeSpell(59547, SPEC_MASK_ALL, false);// unlearn Gift of the Narru
            player->removeSpell(59540, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            //~Warrior
            player->removeSpell(28880, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59221, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
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
            //~DK, Hunter, Druid, Hunter, Priest, Rogue, Warrior
            player->removeSpell(21009, SPEC_MASK_ALL, false);// unlearn Elusiveness
            //Orc:
            player->removeSpell(20574, SPEC_MASK_ALL, false);// unlearn Axe Specialization
            player->removeSpell(20573, SPEC_MASK_ALL, false);// unlearn Hardiness
            //~DK
            player->removeSpell(54562, SPEC_MASK_ALL, false);// unlearn Command
            //~DK, hunter, rogue, warrior
            player->removeSpell(20572, SPEC_MASK_ALL, false);// unlearn Blood Fury
            //~Druid, mage, paladin, priest, rogue, warrior
            player->removeSpell(21563, SPEC_MASK_ALL, false);// unlearn Command
            //~Hunter
            player->removeSpell(20576, SPEC_MASK_ALL, false);// unlearn Command
            //~Shaman
            player->removeSpell(33697, SPEC_MASK_ALL, false);// unlearn Blood fury
            player->removeSpell(65222, SPEC_MASK_ALL, false);// unlearn Command
            //~Warlock
            player->removeSpell(33702, SPEC_MASK_ALL, false);// unlearn Blood Fury
            player->removeSpell(20575, SPEC_MASK_ALL, false);// unlearn Command
            //Troll:
            player->removeSpell(20557, SPEC_MASK_ALL, false);// unlearn Beast Slaying
            player->removeSpell(26297, SPEC_MASK_ALL, false);// unlearn Berserking
            player->removeSpell(26290, SPEC_MASK_ALL, false);// unlearn Bow Specialization
            player->removeSpell(58943, SPEC_MASK_ALL, false);// unlearn Da Voodoo Shuffle
            player->removeSpell(20555, SPEC_MASK_ALL, false);// unlearn Regeneration
            player->removeSpell(20558, SPEC_MASK_ALL, false);// unlearn Throwing Specialization
            //Undead:
            player->removeSpell(20577, SPEC_MASK_ALL, false);// unlearn Cannibalize
            player->removeSpell(20579, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            player->removeSpell(5227, SPEC_MASK_ALL, false);// unlearn Underwater Breating
            player->removeSpell(7744, SPEC_MASK_ALL, false);// unlearn Will of the Forsaken
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
            player->learnSpell(20557, false);//Beast Slaying
            player->learnSpell(26297, false);//Berserking
            player->learnSpell(26290, false);//Bow Specialization
            player->learnSpell(58943, false);//Da Voodoo Shuffle
            player->learnSpell(20555, false);//Regeneration
            player->learnSpell(20558, false);//Throwing Specialization
            //blood elf:
            player->removeSpell(28877, SPEC_MASK_ALL, false);// unlearn Arcane Affinity
            player->removeSpell(822, SPEC_MASK_ALL, false);// unlearn Magic Resistance
            //~DK
            player->removeSpell(50613, SPEC_MASK_ALL, false);// unlearn Arcane Torrent
            //~Hunter, mage, paladin, priest, warlock
            player->removeSpell(28730, SPEC_MASK_ALL, false);// unlearn Arcane Torrent
            //~Rogue
            player->removeSpell(25046, SPEC_MASK_ALL, false);// unlearn Arcane Torrent
            //Draenei:
            player->removeSpell(28875, SPEC_MASK_ALL, false);// unlearn Gemcutting
            //~DK
            player->removeSpell(59545, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59539, SPEC_MASK_ALL, false);// unlearnShadow Resistance
            //~DK, Hunter, Paladin, Warrior
            player->removeSpell(6562, SPEC_MASK_ALL, false);// unlearn Heroic Presence
            //~Hunter
            player->removeSpell(59543, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59536, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            //~Mage
            player->removeSpell(59548, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59541, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            //~Mage, Priest, Shaman
            player->removeSpell(28878, SPEC_MASK_ALL, false);// unlearn Heroic Presence
            //~Paladin
            player->removeSpell(59542, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59535, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            //~Priest
            player->removeSpell(59544, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59538, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            //~Shaman
            player->removeSpell(59547, SPEC_MASK_ALL, false);// unlearn Gift of the Narru
            player->removeSpell(59540, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            //~Warrior
            player->removeSpell(28880, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59221, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
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
            //~DK, Hunter, Druid, Hunter, Priest, Rogue, Warrior
            player->removeSpell(21009, SPEC_MASK_ALL, false);// unlearn Elusiveness
            //Orc:
            player->removeSpell(20574, SPEC_MASK_ALL, false);// unlearn Axe Specialization
            player->removeSpell(20573, SPEC_MASK_ALL, false);// unlearn Hardiness
            //~DK
            player->removeSpell(54562, SPEC_MASK_ALL, false);// unlearn Command
            //~DK, hunter, rogue, warrior
            player->removeSpell(20572, SPEC_MASK_ALL, false);// unlearn Blood Fury
            //~Druid, mage, paladin, priest, rogue, warrior
            player->removeSpell(21563, SPEC_MASK_ALL, false);// unlearn Command
            //~Hunter
            player->removeSpell(20576, SPEC_MASK_ALL, false);// unlearn Command
            //~Shaman
            player->removeSpell(33697, SPEC_MASK_ALL, false);// unlearn Blood fury
            player->removeSpell(65222, SPEC_MASK_ALL, false);// unlearn Command
            //~Warlock
            player->removeSpell(33702, SPEC_MASK_ALL, false);// unlearn Blood Fury
            player->removeSpell(20575, SPEC_MASK_ALL, false);// unlearn Command
            //Tauren:
            player->removeSpell(20552, SPEC_MASK_ALL, false);// unlearn Cultivation
            player->removeSpell(20550, SPEC_MASK_ALL, false);// unlearn Endurance
            player->removeSpell(20551, SPEC_MASK_ALL, false);// unlearn Nature Resistance
            player->removeSpell(20549, SPEC_MASK_ALL, false);// unlearn Warstomp
            //Undead:
            player->removeSpell(20577, SPEC_MASK_ALL, false);// unlearn Cannibalize
            player->removeSpell(20579, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            player->removeSpell(5227, SPEC_MASK_ALL, false);// unlearn Underwater Breating
            player->removeSpell(7744, SPEC_MASK_ALL, false);// unlearn Will of the Forsaken
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
            player->learnSpell(20577, false);//Cannibalize
            player->learnSpell(20579, false);//Shadow Resistance
            player->learnSpell(5227, false);//Underwater Breating
            player->learnSpell(7744, false);//Will of the Forsaken
            //blood elf:
            player->removeSpell(28877, SPEC_MASK_ALL, false);// unlearn Arcane Affinity
            player->removeSpell(822, SPEC_MASK_ALL, false);// unlearn Magic Resistance
            //~DK
            player->removeSpell(50613, SPEC_MASK_ALL, false);// unlearn Arcane Torrent
            //~Hunter, mage, paladin, priest, warlock
            player->removeSpell(28730, SPEC_MASK_ALL, false);// unlearn Arcane Torrent
            //~Rogue
            player->removeSpell(25046, SPEC_MASK_ALL, false);// unlearn Arcane Torrent
            //Draenei:
            player->removeSpell(28875, SPEC_MASK_ALL, false);// unlearn Gemcutting
            //~DK
            player->removeSpell(59545, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59539, SPEC_MASK_ALL, false);// unlearnShadow Resistance
            //~DK, Hunter, Paladin, Warrior
            player->removeSpell(6562, SPEC_MASK_ALL, false);// unlearn Heroic Presence
            //~Hunter
            player->removeSpell(59543, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59536, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            //~Mage
            player->removeSpell(59548, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59541, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            //~Mage, Priest, Shaman
            player->removeSpell(28878, SPEC_MASK_ALL, false);// unlearn Heroic Presence
            //~Paladin
            player->removeSpell(59542, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59535, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            //~Priest
            player->removeSpell(59544, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59538, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            //~Shaman
            player->removeSpell(59547, SPEC_MASK_ALL, false);// unlearn Gift of the Narru
            player->removeSpell(59540, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
            //~Warrior
            player->removeSpell(28880, SPEC_MASK_ALL, false);// unlearn Gift of Naaru
            player->removeSpell(59221, SPEC_MASK_ALL, false);// unlearn Shadow Resistance
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
            //~DK, Hunter, Druid, Hunter, Priest, Rogue, Warrior
            player->removeSpell(21009, SPEC_MASK_ALL, false);// unlearn Elusiveness
            //Orc:
            player->removeSpell(20574, SPEC_MASK_ALL, false);// unlearn Axe Specialization
            player->removeSpell(20573, SPEC_MASK_ALL, false);// unlearn Hardiness
            //~DK
            player->removeSpell(54562, SPEC_MASK_ALL, false);// unlearn Command
            //~DK, hunter, rogue, warrior
            player->removeSpell(20572, SPEC_MASK_ALL, false);// unlearn Blood Fury
            //~Druid, mage, paladin, priest, rogue, warrior
            player->removeSpell(21563, SPEC_MASK_ALL, false);// unlearn Command
            //~Hunter
            player->removeSpell(20576, SPEC_MASK_ALL, false);// unlearn Command
            //~Shaman
            player->removeSpell(33697, SPEC_MASK_ALL, false);// unlearn Blood fury
            player->removeSpell(65222, SPEC_MASK_ALL, false);// unlearn Command
            //~Warlock
            player->removeSpell(33702, SPEC_MASK_ALL, false);// unlearn Blood Fury
            player->removeSpell(20575, SPEC_MASK_ALL, false);// unlearn Command
            //Tauren:
            player->removeSpell(20552, SPEC_MASK_ALL, false);// unlearn Cultivation
            player->removeSpell(20550, SPEC_MASK_ALL, false);// unlearn Endurance
            player->removeSpell(20551, SPEC_MASK_ALL, false);// unlearn Nature Resistance
            player->removeSpell(20549, SPEC_MASK_ALL, false);// unlearn Warstomp
            //Troll:
            player->removeSpell(20557, SPEC_MASK_ALL, false);// unlearn Beast Slaying
            player->removeSpell(26297, SPEC_MASK_ALL, false);// unlearn Berserking
            player->removeSpell(26290, SPEC_MASK_ALL, false);// unlearn Bow Specialization
            player->removeSpell(58943, SPEC_MASK_ALL, false);// unlearn Da Voodoo Shuffle
            player->removeSpell(20555, SPEC_MASK_ALL, false);// unlearn Regeneration
            player->removeSpell(20558, SPEC_MASK_ALL, false);// unlearn Throwing Specialization
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
