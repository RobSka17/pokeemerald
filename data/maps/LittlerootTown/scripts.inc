.set LOCALID_TWIN, 1
.set LOCALID_MOM, 4
.set LOCALID_RIVAL, 7
.set LOCALID_BIRCH, 8
.set LOCALID_BOY, 3
.set LOCALID_ZIGZAGOON, 9
.set LOCALID_WOMAN, 10
.set LOCALID_KIRLIA, 11
.set LOCALID_RIVAL2, 12

LittlerootTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LittlerootTown_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LittlerootTown_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, LittlerootTown_OnWarp
	.byte 0

	@ State descriptions for VAR_LITTLEROOT_TOWN_STATE
	@ 1: Met Rival
	@ 2: Saving Birch
	@ 3: Received Pokedex
	@ 4: Received Running Shoes

	@ State descriptions for VAR_LITTLEROOT_INTRO_STATE
	@ 1: In truck male
	@ 2: In truck female
	@ 3: Entered house
	@ 4: Told to go set clock
	@ 5: Entered 2F to set clock
	@ 6: Set clock
	@ 7: Told to go meet rival

	@ State descriptions for VAR_LITTLEROOT_HOUSES_STATE_MAY
	@                    and VAR_LITTLEROOT_HOUSES_STATE_BRENDAN
	@ 1: On Truck (and is corresponding gender)
	@ 2: Met Rival's Mom (and is corresponding gender)
	@ 3: Entered Hall of Fame
	@ 4: Completed Lati TV / SS Ticket event
	@ 5: Exited house after above event

	@ State descriptions for VAR_LITTLEROOT_RIVAL_STATE
	@ 1: Never occurs
	@ 2: Entered Rival's bedroom
	@ 3: Met Rival
	@ 4: Received Pokedex


LittlerootTown_OnTransition:
	setflag FLAG_VISITED_LITTLEROOT_TOWN
	call LittlerootTown_EventScript_SetupRivalGfxId
	call_if_eq VAR_LITTLEROOT_INTRO_STATE, 2, LittlerootTown_EventScript_MoveMomToMaysDoor
	end

LittlerootTown_OnWarp:
	.2byte 0

LittlerootTown_EventScript_SetupRivalGfxId::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_SetupRivalGfxIdFemale
	goto_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_SetupRivalGfxIdMale
	end

LittlerootTown_EventScript_SetupRivalGfxIdFemale::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_RIVAL_MAY_NORMAL
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_RIVAL_MAY_NORMAL
	return

LittlerootTown_EventScript_SetupRivalGfxIdMale::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_RIVAL_BRENDAN_NORMAL
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_RIVAL_BRENDAN_NORMAL
	return

LittlerootTown_EventScript_MoveMomToMaysDoor::
	setobjectxyperm LOCALID_MOM, 14, 8
	return

LittlerootTown_EventScript_SetMomInFrontOfDoorMale::
	setobjectxyperm LOCALID_MOM, 5, 9
	return

LittlerootTown_EventScript_SetMomInFrontOfDoorFemale::
	setobjectxyperm LOCALID_MOM, 14, 9
	return

LittlerootTown_OnFrame:
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 1, LittlerootTown_EventScript_StepOffTruckMale
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 2, LittlerootTown_EventScript_StepOffTruckFemale
	map_script_2 VAR_LITTLEROOT_TOWN_STATE, 4, LittlerootTown_EventScript_SetUpAfterRivalFirstBattleLost
	.2byte 0

LittlerootTown_EventScript_StepOffTruckMale::
	lockall
	setvar VAR_0x8004, 5
	setvar VAR_0x8005, 8
	call LittlerootTown_EventScript_GoInsideWithMom
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_TRUCK
	warpsilent MAP_LITTLEROOT_TOWN_BRENDANS_HOUSE_1F, 8, 8
	waitstate
	releaseall
	end

LittlerootTown_EventScript_StepOffTruckFemale::
	lockall
	setvar VAR_0x8004, 14
	setvar VAR_0x8005, 8
	call LittlerootTown_EventScript_GoInsideWithMom
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_TRUCK
	warpsilent MAP_LITTLEROOT_TOWN_MAYS_HOUSE_1F, 2, 8
	waitstate
	releaseall
	end

LittlerootTown_EventScript_GoInsideWithMom::
	delay 15
	playse SE_LEDGE
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_Movement_PlayerStepOffTruck
	waitmovement 0
	opendoor VAR_0x8004, VAR_0x8005
	waitdooranim
	addobject LOCALID_MOM
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomExitHouse
	waitmovement 0
	closedoor VAR_0x8004, VAR_0x8005
	waitdooranim
	delay 10
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomApproachPlayerAtTruck
	waitmovement 0
	msgbox LittlerootTown_Text_WereHere, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomApproachDoor
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_Movement_PlayerApproachDoor
	waitmovement 0
	opendoor VAR_0x8004, VAR_0x8005
	waitdooranim
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomEnterHouse
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_Movement_PlayerEnterHouse
	waitmovement 0
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MOM_OUTSIDE
	setvar VAR_LITTLEROOT_INTRO_STATE, 3
	hideobjectat OBJ_EVENT_ID_PLAYER, 0
	closedoor VAR_0x8004, VAR_0x8005
	waitdooranim
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_FAT_MAN
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	return

LittlerootTown_Movement_MomExitHouse:
	walk_down
	step_end

LittlerootTown_Movement_MomApproachPlayerAtTruck:
	walk_down
	walk_in_place_faster_left
	step_end

LittlerootTown_Movement_MomApproachDoor:
	delay_16
	delay_8
	walk_up
	step_end

LittlerootTown_Movement_MomEnterHouse:
	walk_up
	set_invisible
	step_end

LittlerootTown_Movement_PlayerApproachDoor:
	delay_16
	delay_8
	walk_right
	walk_in_place_faster_up
	step_end

LittlerootTown_Movement_PlayerEnterHouse:
	walk_up
	walk_up
	step_end

LittlerootTown_Movement_PlayerStepOffTruck:
	jump_right
	delay_16
	delay_16
	delay_16
	step_end

LittlerootTown_EventScript_FatMan::
	msgbox LittlerootTown_Text_FatMan, MSGBOX_NPC
	end

LittlerootTown_EventScript_Boy::
	lock
	faceplayer
	msgbox LittlerootTown_Text_KirliaIsPopular, MSGBOX_NPC
	applymovement LOCALID_BOY, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LittlerootTown_Text_KirliaIsPopular:
	.string "KIRLIA is really popular with the\n"
	.string "kids in the PROFESSOR's programme.\p"
	.string "It's very sensitive to human\n"
	.string "emotions.$"

LittlerootTown_EventScript_Woman::
	lock
	faceplayer
	msgbox LittlerootTown_Text_IntroduceToPokemon, MSGBOX_NPC
	applymovement LOCALID_WOMAN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LittlerootTown_Text_IntroduceToPokemon:
	.string "We're helping introduce children\n"
	.string "to POKéMON at a young age.\p"
	.string "It's part of the PROFESSOR's\n"
	.string "programme!$"

LittlerootTown_EventScript_Zigzagoon::
	lock
	faceplayer
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox LittlerootTown_Text_Zigzagoon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

LittlerootTown_Text_Zigzagoon:
	.string "ZIGZAGOON: GAGOOON!$"

LittlerootTown_EventScript_Kirlia::
	lock
	faceplayer
	playmoncry SPECIES_KIRLIA, CRY_MODE_NORMAL
	msgbox LittlerootTown_Text_Kirlia, MSGBOX_DEFAULT
	waitmoncry
	release
	end

LittlerootTown_Text_Kirlia:
	.string "KIRLIA: KIII!$"

LittlerootTown_EventScript_Twin::
	lock
	faceplayer
	msgbox LittlerootTown_Text_ZigzagoonIsSoft, MSGBOX_NPC
	applymovement LOCALID_TWIN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LittlerootTown_Text_ZigzagoonIsSoft:
	.string "ZIGZAGOON's fur is so soft!\p"
	.string "I love hugging him!$"

LittlerootTown_EventScript_TownSign::
	msgbox LittlerootTown_Text_TownSign, MSGBOX_SIGN
	end

LittlerootTown_EventScript_BirchsLabSign::
	msgbox LittlerootTown_Text_ProfBirchsLab, MSGBOX_SIGN
	end

LittlerootTown_EventScript_BrendansHouseSign::
	lockall
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_PlayersHouseSignMale
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_BirchsHouseSignFemale
	releaseall
	end

LittlerootTown_EventScript_PlayersHouseSignMale::
	msgbox LittlerootTown_Text_PlayersHouse, MSGBOX_DEFAULT
	return

LittlerootTown_EventScript_BirchsHouseSignFemale::
	msgbox LittlerootTown_Text_ProfBirchsHouse, MSGBOX_DEFAULT
	return

LittlerootTown_EventScript_MaysHouseSign::
	lockall
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_BirchsHouseSignMale
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_PlayersHouseSignFemale
	releaseall
	end

LittlerootTown_EventScript_BirchsHouseSignMale::
	msgbox LittlerootTown_Text_ProfBirchsHouse, MSGBOX_DEFAULT
	return

LittlerootTown_EventScript_PlayersHouseSignFemale::
	msgbox LittlerootTown_Text_PlayersHouse, MSGBOX_DEFAULT
	return

LittlerootTown_EventScript_WarningSign::
	msgbox LittlerootTown_Text_WarningSign, MSGBOX_SIGN
	end

LittlerootTown_EventScript_SetHomeDoorCoordsMale::
	setvar VAR_0x8009, 5
	setvar VAR_0x800A, 8
	return

LittlerootTown_EventScript_SetHomeDoorCoordsFemale::
	setvar VAR_0x8009, 14
	setvar VAR_0x800A, 8
	return

LittlerootTown_Movement_MomExitThroughDoor:
	walk_up
	step_end

LittlerootTown_Text_WereHere:
	.string "MUM: Well, {PLAYER}, we're here!\p"
	.string "This is LITTLEROOT, our new home!\p"
	.string "I know you'll be missing JOHTO\n"
	.string "but we need to support dad.\p"
	.string "He's been busy getting set up in\n"
	.string "his new job at the GYM.\p"
	.string "It's not every day a GYM in another\n"
	.string "region asks you to take over!\p"
	.string "...\p"
	.string "What's that? You got a call from\n"
	.string "PROFESSOR BIRCH on the way here?\p"
	.string "Why don't you just check out the\n"
	.string "house quickly then meet him?\p"
	.string "He should be either next door\n"
	.string "or in his LAB."
	.string "$"

LittlerootTown_Text_FatMan:
	.string "The HOENN region is changing but\n"
	.string "BIRCH is helping a lot.\p"
	.string "He set up a whole new scheme.\p"
	.string "It's dedicated to preparing the next\n"
	.string "generation of trainers.$"

LittlerootTown_Text_GoodLuckCatchingPokemon:
	.string "Are you going to catch POKéMON?\n"
	.string "Good luck!$"

LittlerootTown_Text_TownSign:
	.string "LITTLEROOT TOWN\n"
	.string "“A town that can't be shaded any hue.”$"

LittlerootTown_Text_ProfBirchsLab:
	.string "PROF. BIRCH'S POKéMON LAB$"

LittlerootTown_Text_PlayersHouse:
	.string "{PLAYER}'s HOUSE$"

LittlerootTown_Text_WarningSign:
	.string "WARNING! INCREASE IN AGGRESSIVE\n"
	.string "WILD POKéMON IN THE AREA.$"

LittlerootTown_Text_ProfBirchsHouse:
	.string "PROF. BIRCH'S HOUSE$"

LittlerootTown_Text_BirchSomethingToShowYouAtLab:
	.string "PROF. BIRCH: Well, well, {PLAYER}{KUN}!\n"
	.string "That was good work out there!\p"
	.string "I knew there was something special\n"
	.string "about you when I first saw you,\l"
	.string "but I never expected this.\p"
	.string "Oh, yes. Do you still have the POKéDEX\n"
	.string "I gave you?\p"
	.string "I have something to show you.\n"
	.string "Let's go to my LAB.$"

LittlerootTown_EventScript_TriggerRivalFirstBattleLeft::
	lock
	setflag FLAG_HIDE_LITTLEROOT_TOWN_RIVAL
	msgbox LittlerootTown_Text_RivalStopPlayerFirstBattle, MSGBOX_DEFAULT
	closemessage
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_PlayMayTheme
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_PlayBrendanTheme
	addobject LOCALID_RIVAL
	applymovement LOCALID_RIVAL, LittlerootTown_Movement_RivalFirstBattleLeftMove
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox LittlerootTown_Text_RivalFirstBattle, MSGBOX_DEFAULT
	goto_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_RivalFirstBattleMay
	goto_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_RivalFirstBattleBrendan
	release
	end

LittlerootTown_PlayMayTheme:
	playbgm MUS_ENCOUNTER_MAY, TRUE
	return

LittlerootTown_PlayBrendanTheme:
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
	return

LittlerootTown_Movement_RivalFirstBattleLeftMove:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_up
	step_end

LittlerootTown_EventScript_TriggerRivalFirstBattleRight::
	lock
	setflag FLAG_HIDE_LITTLEROOT_TOWN_RIVAL
	msgbox LittlerootTown_Text_RivalStopPlayerFirstBattle, MSGBOX_DEFAULT
	closemessage
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_PlayMayTheme
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_PlayBrendanTheme
	addobject LOCALID_RIVAL
	applymovement LOCALID_RIVAL, LittlerootTown_Movement_RivalFirstBattleRightMove
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox LittlerootTown_Text_RivalFirstBattle, MSGBOX_DEFAULT
	goto_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_RivalFirstBattleMay
	goto_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_RivalFirstBattleBrendan
	release
	end

LittlerootTown_Movement_RivalFirstBattleRightMove:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_EventScript_RivalFirstBattleMay:
	switch VAR_STARTER_MON
	case 0, LittlerootTown_EventScript_RivalFirstBattleMayBulbasaur
	case 1, LittlerootTown_EventScript_RivalFirstBattleMayCyndaquil
	case 2, LittlerootTown_EventScript_RivalFirstBattleMayMudkip
	end

LittlerootTown_EventScript_RivalFirstBattleMayBulbasaur:
	trainerbattle_no_intro TRAINER_MAY_LITTLEROOT_BULBASAUR, LittlerootTown_Text_RivalFirstBattleDefeated
	goto LittlerootTown_EventScript_RivalAfterFirstBattle
	end

LittlerootTown_EventScript_RivalFirstBattleMayCyndaquil:
	trainerbattle_no_intro TRAINER_MAY_LITTLEROOT_CYNDAQUIL, LittlerootTown_Text_RivalFirstBattleDefeated
	goto LittlerootTown_EventScript_RivalAfterFirstBattle
	end

LittlerootTown_EventScript_RivalFirstBattleMayMudkip:
	trainerbattle_no_intro TRAINER_MAY_LITTLEROOT_MUDKIP, LittlerootTown_Text_RivalFirstBattleDefeated
	goto LittlerootTown_EventScript_RivalAfterFirstBattle
	end

LittlerootTown_EventScript_RivalFirstBattleBrendan:
	switch VAR_STARTER_MON
	case 0, LittlerootTown_EventScript_RivalFirstBattleBrendanBulbasaur
	case 1, LittlerootTown_EventScript_RivalFirstBattleBrendanCyndaquil
	case 2, LittlerootTown_EventScript_RivalFirstBattleBrendanMudkip
	end

LittlerootTown_EventScript_RivalFirstBattleBrendanBulbasaur:
	trainerbattle_no_intro TRAINER_BRENDAN_LITTLEROOT_BULBASAUR, LittlerootTown_Text_RivalFirstBattleDefeated
	goto LittlerootTown_EventScript_RivalAfterFirstBattle
	end

LittlerootTown_EventScript_RivalFirstBattleBrendanCyndaquil:
	trainerbattle_no_intro TRAINER_BRENDAN_LITTLEROOT_CYNDAQUIL, LittlerootTown_Text_RivalFirstBattleDefeated
	goto LittlerootTown_EventScript_RivalAfterFirstBattle
	end

LittlerootTown_EventScript_RivalFirstBattleBrendanMudkip:
	trainerbattle_no_intro TRAINER_BRENDAN_LITTLEROOT_MUDKIP, LittlerootTown_Text_RivalFirstBattleDefeated
	goto LittlerootTown_EventScript_RivalAfterFirstBattle
	end

LittlerootTown_Text_RivalStopPlayerFirstBattle:
	.string "Wait a minute, {PLAYER}!$"

LittlerootTown_Text_RivalFirstBattle:
	.string "{RIVAL}: I heard my dad was having\n"
	.string "you go to meet STEVEN in RUSTBURO.\p"
	.string "Truth is, I want to make sure you're\n"
	.string "prepared for that.\p"
	.string "You just got your first POKéMON,\n"
	.string "right?\p"
	.string "Let's see what you're capable of!$"

LittlerootTown_Text_RivalFirstBattleDefeated:
	.string "I guess you know something about\n"
	.string "battling...$"

LittlerootTown_EventScript_RivalAfterFirstBattle:
	specialvar VAR_RESULT, GetBattleOutcome
	call_if_eq VAR_RESULT, B_OUTCOME_WON, LittlerootTown_EventScript_RivalAfterFirstBattleWon
	goto LittlerootTown_EventScript_GivePlayerItems
	end

LittlerootTown_EventScript_GivePlayerItems:
	giveitem ITEM_POKE_BALL 10
	msgbox LittlerootTown_Text_RivalGivePotion, MSGBOX_DEFAULT
	giveitem ITEM_POTION
	msgbox LittlerootTown_Text_RivalFirstBattleLeave, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_RIVAL2, LittlerootTown_Movement_RivalFirstBattleLeave
	waitmovement 0
	removeobject LOCALID_RIVAL2
	playbgm MUS_LITTLEROOT, TRUE
	release
	end

LittlerootTown_EventScript_SetUpAfterRivalFirstBattleLost:
	setvar VAR_LITTLEROOT_TOWN_STATE, 5
	setobjectxy LOCALID_RIVAL, 10, 2
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_PlayMayTheme
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_PlayBrendanTheme
	call LittlerootTown_EventScript_RivalAfterFirstBattleLost
	goto LittlerootTown_EventScript_GivePlayerItems
	end

LittlerootTown_EventScript_RivalAfterFirstBattleWon:
	setvar VAR_LITTLEROOT_TOWN_STATE, 5
	msgbox LittlerootTown_Text_RivalAfterFirstBattleWon, MSGBOX_DEFAULT
	return

LittlerootTown_EventScript_RivalAfterFirstBattleLost:
	msgbox LittlerootTown_Text_RivalAfterFirstBattleLost, MSGBOX_DEFAULT
	return

LittlerootTown_Text_RivalAfterFirstBattleWon:
	.string "{RIVAL}: Hmm, well I suppose I\n"
	.string "have to admit you're not useless.\p"
	.string "But don't go thinking for a\n"
	.string "minute I was serious!\p"
	.string "Next time we battle it'll be a\n"
	.string "different story.\p"
	.string "I'm going to travel HOENN and\n"
	.string "put together a new team.\p"
	.string "It's part of the work I'm doing\n"
	.string "for my dad.\p"
	.string "You should catch some more\n"
	.string "POKéMON too. Take these.$"

LittlerootTown_Text_RivalAfterFirstBattleLost:
	.string "{RIVAL}: Sigh... Well, I can't\n"
	.string "stop you doing what my dad asked.\p"
	.string "But you'd better toughen up if\n"
	.string "you want to survive out there.\p"
	.string "I've healed your POKéMON.\p"
	.string "I'm going to catch a bunch of\n"
	.string "POKéMON from all over HOENN.\p"
	.string "You'd better go out and catch\n"
	.string "some more too. Take these.$"

LittlerootTown_Text_RivalGivePotion:
	.string "I'm not going to be around to\n"
	.string "heal you all the time.\p"
	.string "Take this too.$"

LittlerootTown_Text_RivalFirstBattleLeave:
	.string "Okay. I'm going back home to\n"
	.string "finish preparing.\p"
	.string "Try not to get too beaten up\n"
	.string "out there.\p"
	.string "Oh, and make sure you visit\n"
	.string "Some GYMs on your way.\p"
	.string "I'm sure I'll see you around,\n"
	.string "{PLAYER}!$"

LittlerootTown_Movement_RivalFirstBattleLeave:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

