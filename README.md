# ![logo](https://raw.githubusercontent.com/azerothcore/azerothcore.github.io/master/images/logo-github.png) AzerothCore

## mod-racial-trait-swap

## Description

- Racial Trait NPC, that allows you, for a ingame cost of gold (configurable), to trade out your racial traits for another.

## How to use ingame

1. Enable in conf
2. Go into conf and set any features you want to enable or modify
3. Spawn NPC ID 98888 anywhere and talk to him.

## Notice:

Due to the uniquiness of the module you will get this message on the worldconsole, but nothing is broken.
It is due to the npc not exactly having a gossip menu in the database, the script handles the gossip menu because of the additional locales.
![image](https://user-images.githubusercontent.com/16887899/152653351-7f49e93c-efa9-4396-aa2e-6bad159920ef.png)

Please add the adjustment to the conf to have that error message not show up:
```
#    Creatures.CustomIDs
#        Description: The list of custom creatures with gossip dialogues hardcoded in core,
#                     divided by "," without spaces.
#                     It is implied that you do not use for these NPC dialogs data from "gossip_menu" table.
#                     Server will skip these IDs during the definitions validation process.
#        Example:     Creatures.CustomIDs = "190010,55005,999991,25462,98888" - Npcs for Transmog, Guild-zone, 1v1-arena modules
#                                                                               Skip Dk Module, Racial Trait Swap Modules
#        Default:     ""

Creatures.CustomIDs = "190010,55005,999991,25462,98888"
```

## Requirements

- Latest AzerothCore Wotlk commit [de13bf4](https://github.com/azerothcore/azerothcore-wotlk/commit/de13bf426e162ee10cbd5470cec74122d1d4afa0) or newer

## Installation

1. Simply place the module under the `modules` directory of your AzerothCore source. 
1. Re-run CMake and rebuild the AzerothCore source.

## Edit module configuration (optional)

If you need to change the module configuration, go to your server configuration folder (where your worldserver or worldserver.exe is), copy RacialTraitSwap.conf.dist to RacialTraitSwap.conf and edit that new file.

### Credits ###
------------------------------------------------------------------------------------------------------------------
- [acidmanifesto (MDic)](https://github.com/acidmanifesto/TC-Custom-Scripts/tree/main/335%20TC/Official%20Trinitycore%20Custom%20Scripts/Official%20Merged/Racial%20Swap%20Skills%20Abilities%20NPC)
- [Jinnaix](https://github.com/Jinnaix) For Translations
- [bench](https://github.com/benjymansy123) For Compile Fixes on Core Revisions

- AzerothCore: [repository](https://github.com/azerothcore) - [website](http://azerothcore.org/) - [discord chat community](https://discord.gg/PaqQRkd)
