.set LOCALID_BIRCH, 1
.set LOCALID_BIRCHBAG, 2
.set LOCALID_POOCHYENA_1, 3
.set LOCALID_POOCHYENA_2, 4
.set LOCALID_POOCHYENA_3, 5
.set LOCALID_RIVAL, 7

Route101_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route101_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route101_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, Route101_OnWarp
	.byte 0

Route101_OnTransition:
	call Route101_EventScript_SetupRivalGfxId
	end

Route101_OnFrame:
	map_script_2 VAR_ROUTE101_STATE, 0, Route101_EventScript_HideMapNamePopup
	map_script_2 VAR_TEMP_2, 1, Route101_EventScript_Birch_AfterPoochyenaBattleLost
	.2byte 0

Route101_OnWarp:
	map_script_2 VAR_TEMP_1, 0, Route101_EventScript_SetUpAfterSaveBirchLoss
	.2byte 0

Route101_EventScript_HideMapNamePopup::
	setflag FLAG_HIDE_MAP_NAME_POPUP
	setvar VAR_ROUTE101_STATE, 1
	hideobjectat LOCALID_RIVAL, MAP_ROUTE101
	end

Route101_EventScript_SetUpAfterSaveBirchLoss:
	setvar VAR_TEMP_1, 1
	goto_if_eq VAR_ROUTE101_STATE, 2, Route101_EventScript_SetUpAfterSaveBirchLoss2
	end

Route101_EventScript_SetUpAfterSaveBirchLoss2:
	setvar VAR_ROUTE101_STATE, 3
	setobjectxy LOCALID_BIRCH, 7, 15
	setvar VAR_TEMP_2, 1
	end

Route101_Trigger_SaveBirchPreventExitLeft::
	lock
	msgbox Route101_Text_PreventExitLeft, MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER, Route101_Movement_StepRight
	waitmovement 0
	release
	end	

Route101_Trigger_SaveBirchPreventExitRight::
	lock
	msgbox Route101_Text_PreventExitRight, MSGBOX_DEFAULT
	applymovement OBJ_EVENT_ID_PLAYER, Route101_Movement_StepLeft
	waitmovement 0
	release
	end

Route101_Text_PreventExitLeft:
	.string "BIRCH: Don't come any closer without\n"
	.string "a POKéMON!$"

Route101_Text_PreventExitRight:
	.string "BIRCH: Wait! Please don't leave!$"

Route101_Movement_StepLeft:
	walk_left
	step_end

Route101_Movement_StepRight:
	walk_right
	step_end

Route101_Trigger_SaveBirchLeft::
	lock
	playbgm MUS_HELP, TRUE
	call Route101_EventScript_Help
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Route101_Movement_SaveBirchLeft
	waitmovement 0
	setvar VAR_ROUTE101_STATE, 2
	call Route101_EventScript_MoveAllPoochyena
	msgbox Route101_Text_Birch_TheBag, MSGBOX_DEFAULT
	release
	end

Route101_Trigger_SaveBirchRight::
	lock
	playbgm MUS_HELP, TRUE
	call Route101_EventScript_Help
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Route101_Movement_SaveBirchRight
	waitmovement 0
	setvar VAR_ROUTE101_STATE, 2
	call Route101_EventScript_MoveAllPoochyena
	msgbox Route101_Text_Birch_TheBag, MSGBOX_DEFAULT
	release
	end

Route101_EventScript_Help:
	msgbox Route101_Text_Help, MSGBOX_DEFAULT
	return

Route101_Text_Help:
	.string "Is someone there?\p"
	.string "Please help!$"

Route101_Movement_SaveBirchLeft:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_left
	step_end

Route101_Movement_SaveBirchRight:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

Route101_Text_Birch_TheBag:
	.string "BIRCH: Please help me!\p"
	.string "The bag there! It has POKéMON\n"
	.string "in it!$"

Route101_EventScript_BirchsBag::
	lock
	faceplayer
	setflag FLAG_SYS_POKEMON_GET
	setflag FLAG_RESCUED_BIRCH
	fadescreen FADE_TO_BLACK
	special ChooseStarter
	waitstate
	call Route101_EventScript_Poochyena_Encounter_1
	call Route101_EventScript_Poochyena_Encounter_2
	call Route101_EventScript_Poochyena_Encounter_3
	goto Route101_EventScript_Birch_AfterPoochyenaBattleWon
	release
	end

Route101_EventScript_MoveAllPoochyena:
	applymovement LOCALID_POOCHYENA_1, Route101_Movement_Poochyena_StepLeft
	waitmovement 0
	applymovement LOCALID_POOCHYENA_3, Route101_Movement_Poochyena_StepLeft
	waitmovement 0
	applymovement LOCALID_POOCHYENA_2, Route101_Movement_Poochyena_StepLeft
	waitmovement 0
	return

Route101_Movement_Poochyena_StepLeft:
	walk_left
	step_end

Route101_EventScript_Poochyena_Encounter_1:
	playse SE_PIN
	applymovement LOCALID_POOCHYENA_1, Common_Movement_ExclamationMark
	waitmovement 0
	setwildbattle SPECIES_POOCHYENA, 2
	waitse
	playmoncry SPECIES_POOCHYENA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	dowildbattle
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_POOCHYENA_1
	fadescreen FADE_FROM_BLACK
	return

Route101_EventScript_Poochyena_Encounter_2:
	playse SE_PIN
	applymovement LOCALID_POOCHYENA_3, Common_Movement_ExclamationMark
	waitmovement 0
	setwildbattle SPECIES_POOCHYENA, 2
	waitse
	playmoncry SPECIES_POOCHYENA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	dowildbattle
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_POOCHYENA_3
	fadescreen FADE_FROM_BLACK
	return

Route101_EventScript_Poochyena_Encounter_3:
	playse SE_PIN
	applymovement LOCALID_POOCHYENA_2, Common_Movement_ExclamationMark
	waitmovement 0
	setwildbattle SPECIES_POOCHYENA, 3
	waitse
	playmoncry SPECIES_POOCHYENA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	dowildbattle
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_POOCHYENA_2
	return

Route101_EventScript_Birch_AfterPoochyenaBattleWon:
	playbgm MUS_ROUTE101, TRUE
	special HealPlayerParty
	removeobject LOCALID_BIRCHBAG
	setobjectxy OBJ_EVENT_ID_PLAYER, 8, 15
	setobjectxy LOCALID_BIRCH, 7, 15
	setflag FLAG_HIDE_ROUTE_101_RIVAL
	setflag FLAG_HIDE_ROUTE_101_BIRCH_POOCHYENA_BATTLE
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_BIRCH
	setflag FLAG_HIDE_ROUTE_101_BIRCH_STARTERS_BAG
	setvar VAR_ROUTE101_STATE, 3
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	setvar VAR_BIRCH_LAB_STATE, 2
	fadescreen FADE_FROM_BLACK
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	call Route101_EventScript_Birch_YouSavedMe
	call Route101_EventScript_Birch_YourePlayer
	warp MAP_LITTLEROOT_TOWN_PROFESSOR_BIRCHS_LAB, 6, 5
	waitstate
	release
	end

Route101_EventScript_Birch_AfterPoochyenaBattleLost:
	setvar VAR_TEMP_2, 2
	setvar VAR_ROUTE101_STATE, 3
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	setvar VAR_BIRCH_LAB_STATE, 2
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	applymovement LOCALID_BIRCH, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	call Route101_EventScript_Rival_ThatWasClose
	call Route101_EventScript_Birch_ThanksRival
	applymovement LOCALID_BIRCH, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	call Route101_EventScript_Birch_ThanksPlayer
	warp MAP_LITTLEROOT_TOWN_PROFESSOR_BIRCHS_LAB, 6, 5
	waitstate
	release
	end

Route101_EventScript_SetupRivalGfxId:
	checkplayergender
	call_if_eq VAR_RESULT, FEMALE, Route101_EventScript_SetupRivalGfxIdMale
	call_if_eq VAR_RESULT, MALE, Route101_EventScript_SetupRivalGfxIdFemale
	return

Route101_EventScript_SetupRivalGfxIdMale:
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_BRENDAN_NORMAL
	return

Route101_EventScript_SetupRivalGfxIdFemale:
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_MAY_NORMAL
	return

Route101_EventScript_Birch_YouSavedMe:
	msgbox Route101_Text_Birch_YouSavedMe, MSGBOX_DEFAULT
	return

Route101_EventScript_Rival_ThatWasClose:
	msgbox Route101_Text_Rival_ThatWasClose, MSGBOX_DEFAULT
	return

Route101_Text_Rival_ThatWasClose:
	.string "{RIVAL}: That was a close one!\n"
	.string "Are you two okay?$"

Route101_EventScript_Birch_ThanksRival:
	msgbox Route101_Text_Birch_ThanksRival, MSGBOX_DEFAULT
	return

Route101_Text_Birch_ThanksRival:
	.string "BIRCH: I think so! Thank you,\n"
	.string "{RIVAL}!$"

Route101_EventScript_Birch_ThanksPlayer:
	msgbox Route101_Text_Birch_ThanksPlayer, MSGBOX_DEFAULT
	return

Route101_Text_Birch_ThanksPlayer:
	.string "And thank you, {PLAYER}.\p"
	.string "If it hadn't been for both your\n"
	.string "efforts, that could have been bad!\p"
	.string "Let's hurry back to the LAB!$"

Route101_Text_Birch_YouSavedMe:
	.string "BIRCH: Phew! You really saved me!\p"
	.string "The POOCHYENA have been a lot\n"
	.string "more territorial recently.\p"
	.string "They totally caught me off guard!$"

Route101_EventScript_Birch_YourePlayer:
	msgbox Route101_Text_Birch_YourePlayer, MSGBOX_DEFAULT
	return

Route101_Text_Birch_YourePlayer:
	.string "Wait... You're {PLAYER}!\p"
	.string "Well, {PLAYER}, it isn't very\n"
	.string "safe talking out here.\p"
	.string "Why don't we head back to my\n"
	.string "LAB?$"

Route101_EventScript_SchoolKid::
	lock
	faceplayer
	msgbox Route101_Text_SchoolKid, MSGBOX_NPC
	release
	end

Route101_Text_SchoolKid:
	.string "My friend brought a POKéMON I'd\n"
	.string "never seen before to school.\p"
	.string "I want to catch a rare POKéMON too.$"

Route101_EventScript_RouteSign::
	msgbox Route101_Text_RouteSign, MSGBOX_SIGN
	end

Route101_Text_RouteSign:
	.string "ROUTE 101\n"
	.string "{UP_ARROW} OLDALE TOWN$"

