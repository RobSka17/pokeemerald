.set LOCALID_NORMAN, 1
.set LOCALID_NORMAN_2, 10

PetalburgCity_Gym_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, PetalburgCity_Gym_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, PetalburgCity_Gym_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, PetalburgCity_Gym_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PetalburgCity_Gym_OnFrame
	.byte 0

PetalburgCity_Gym_OnLoad:
	call_if_eq VAR_PETALBURG_GYM_STATE, 0, PetalburgCity_Gym_Test
	goto_if_eq VAR_PETALBURG_GYM_STATE, 0, PetalburgCity_Gym_EventScript_OpenEntranceDoorsOnEntry
	goto_if_eq VAR_PETALBURG_GYM_STATE, 1, PetalburgCity_Gym_EventScript_OpenUnlockedDoors
	call_if_ge VAR_PETALBURG_GYM_STATE, 2, PetalburgCity_Gym_EventScript_UnlockAllDoors
	end

PetalburgCity_Gym_Test:
	clearflag FLAG_HIDE_PETALBURG_GYM_NORMAN_2
	givemon SPECIES_IVYSAUR, 28
	givemon SPECIES_POOCHYENA, 28
	givemon SPECIES_KADABRA, 28
	givemon SPECIES_MACHOKE, 28
	setvar VAR_NUMBER_OF_BADGES_OWNED, 2
	return

PetalburgCity_Gym_EventScript_OpenEntranceDoorsOnEntry:
	setvar VAR_0x8005, 1
	call PetalburgCity_Gym_EventScript_OpenGymEntranceDoors
	end

@ NOTE: Strength and OHKO rooms are misleading. Both are more accurately Critical-Hit
PetalburgCity_Gym_EventScript_OpenUnlockedDoors::
	setvar VAR_0x8005, 1
	call PetalburgCity_Gym_EventScript_OpenGymEntranceDoors
	call_if_defeated TRAINER_RANDALL, PetalburgCity_Gym_EventScript_OpenSpeedRoomDoors
	call_if_defeated TRAINER_RANDALL, PetalburgCity_Gym_EventScript_OpenAccuracyRoomDoors
	call_if_defeated TRAINER_MARY, PetalburgCity_Gym_EventScript_OpenAccuracyRoomDoors
	call_if_defeated TRAINER_MARY, PetalburgCity_Gym_EventScript_OpenSpeedRoomDoors
	call_if_defeated TRAINER_PARKER, PetalburgCity_Gym_EventScript_OpenConfusionRoomDoors
	call_if_defeated TRAINER_PARKER, PetalburgCity_Gym_EventScript_OpenDefenseRoomDoors
	call_if_defeated TRAINER_PARKER, PetalburgCity_Gym_EventScript_OpenRecoveryRoomDoors
	call_if_defeated TRAINER_ALEXIA, PetalburgCity_Gym_EventScript_OpenDefenseRoomDoors
	call_if_defeated TRAINER_ALEXIA, PetalburgCity_Gym_EventScript_OpenConfusionRoomDoors
	call_if_defeated TRAINER_ALEXIA, PetalburgCity_Gym_EventScript_OpenRecoveryRoomDoors
	call_if_defeated TRAINER_GEORGE, PetalburgCity_Gym_EventScript_OpenRecoveryRoomDoors
	call_if_defeated TRAINER_GEORGE, PetalburgCity_Gym_EventScript_OpenDefenseRoomDoors
	call_if_defeated TRAINER_GEORGE, PetalburgCity_Gym_EventScript_OpenConfusionRoomDoors
	call_if_defeated TRAINER_JODY, PetalburgCity_Gym_EventScript_OpenStrengthRoomDoors
	call_if_defeated TRAINER_JODY, PetalburgCity_Gym_EventScript_OpenOHKORoomDoors
	call_if_defeated TRAINER_BERKE, PetalburgCity_Gym_EventScript_OpenOHKORoomDoors
	call_if_defeated TRAINER_BERKE, PetalburgCity_Gym_EventScript_OpenStrengthRoomDoors
	end

PetalburgCity_Gym_EventScript_UnlockAllDoors::
	setvar VAR_0x8005, 1
	call PetalburgCity_Gym_EventScript_OpenGymEntranceDoors
	call PetalburgCity_Gym_EventScript_OpenSpeedRoomDoors
	call PetalburgCity_Gym_EventScript_OpenAccuracyRoomDoors
	call PetalburgCity_Gym_EventScript_OpenConfusionRoomDoors
	call PetalburgCity_Gym_EventScript_OpenDefenseRoomDoors
	call PetalburgCity_Gym_EventScript_OpenRecoveryRoomDoors
	call PetalburgCity_Gym_EventScript_OpenStrengthRoomDoors
	call PetalburgCity_Gym_EventScript_OpenOHKORoomDoors
	return

PetalburgCity_Gym_OnTransition:
	call_if_set FLAG_SYS_GAME_CLEAR, PetalburgCity_Gym_EventScript_CheckNormanForRematch
	end

PetalburgCity_Gym_EventScript_MoveNormanToEntrance::
	setobjectxyperm LOCALID_NORMAN, 4, 107
	return

PetalburgCity_Gym_EventScript_CheckNormanForRematch::
	setorcopyvar VAR_TRAINER_BATTLE_OPPONENT_A, TRAINER_NORMAN_1
	specialvar VAR_RESULT, IsTrainerReadyForRematch
	goto_if_eq VAR_RESULT, TRUE, PetalburgCity_Gym_EventScript_DontMoveNormanToFront
	goto_if_eq VAR_PETALBURG_GYM_STATE, 8, PetalburgCity_Gym_EventScript_DontMoveNormanToFront
	setobjectxyperm LOCALID_NORMAN, 4, 107
	return

PetalburgCity_Gym_EventScript_DontMoveNormanToFront::
	setvar VAR_PETALBURG_GYM_STATE, 8
	end

PetalburgCity_Gym_OnWarp:
	map_script_2 VAR_PETALBURG_GYM_STATE, 1, PetalburgCity_Gym_EventScript_TurnPlayerNorth
	.2byte 0

PetalburgCity_Gym_OnFrame:
	map_script_2 VAR_PETALBURG_GYM_STATE, 0, PetalburgCity_Gym_EventScript_NormanWelcome
	.2byte 0

PetalburgCity_Gym_EventScript_TurnPlayerNorth::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

PetalburgCity_Gym_EventScript_Norman::
	lock
	faceplayer
	goto_if_unset FLAG_DEFEATED_PETALBURG_GYM, PetalburgCity_Gym_EventScript_NormanBattle
	msgbox PetalburgCity_Gym_Text_NormanPostBadge, MSGBOX_DEFAULT
	release
	end

PetalburgCity_Gym_Text_NormanPostBadge:
	.string "DAD: Here's some advice, {PLAYER}.\p"
	.string "Life is a lot like the journey of\n"
	.string "a trainer.\p"
	.string "New experiences help us understand\n"
	.string "things in new ways.\p"
	.string "Overcoming challenges makes us\n"
	.string "stronger.\p"
	.string "But it's also important to take\n"
	.string "time to recover.\p"
	.string "And however strong we may become,\n"
	.string "there's always room to grow.$"

PetalburgCity_Gym_EventScript_NormanWelcome:
	lock
	setvar VAR_PETALBURG_GYM_STATE, 1
	applymovement LOCALID_NORMAN_2, Common_Movement_ExclamationMark
	playse SE_PIN
	waitse
	applymovement OBJ_EVENT_ID_PLAYER, PetalburgCity_Gym_Movement_PlayerWalkToNorman
	waitmovement 0
	msgbox PetalburgCity_Gym_Text_NormanWelcome, MSGBOX_DEFAULT
	closemessage
	delay 40
	call_if_eq VAR_NUMBER_OF_BADGES_OWNED, 0, PetalburgCity_Gym_EventScript_Norman0Badges
	call_if_eq VAR_NUMBER_OF_BADGES_OWNED, 1, PetalburgCity_Gym_EventScript_Norman1Badge
	call_if_ge VAR_NUMBER_OF_BADGES_OWNED, 2, PetalburgCity_Gym_EventScript_NormanMultipleBadges
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_NORMAN_2
	playse SE_EXIT
	waitse
	fadescreen FADE_FROM_BLACK
	release
	return

PetalburgCity_Gym_Movement_PlayerWalkToNorman:
	walk_up
	walk_up
	step_end

PetalburgCity_Gym_Text_NormanWelcome:
	.string "DAD: Well, if it isn't {PLAYER}!\p"
	.string "I see you and your mother arrived\n"
	.string "just fine in HOENN!\p"
	.string "I know I dragged you over here when\n"
	.string "I took over at this GYM.\p"
	.string "Seems like you're making a fine\n"
	.string "start already, though.\p"
	.string "...\p"
	.string "Hmm, I see. So you're collecting\n"
	.string "GYM badges.\p"
	.string "It's true. I have one of the badges\n"
	.string "you want.\p"
	.string "Let's see how many you have so far.$"

PetalburgCity_Gym_EventScript_Norman0Badges::
	msgbox PetalburgCity_Gym_Text_Norman0Badges, MSGBOX_DEFAULT
	closemessage
	return

PetalburgCity_Gym_Text_Norman0Badges:
	.string "Well... I'll be honest.\p"
	.string "I see you don't have any badges\n"
	.string "just yet.\p"
	.string "As your father, I'd really like\n"
	.string "to hold off our battle.\p"
	.string "There are other GYMS you can\n"
	.string "challenge and other badges.\p"
	.string "I'd love to see you again when\n"
	.string "you're a little stronger.\p"
	.string "That said, as the GYM LEADER,\n"
	.string "I will accept your choice.\p"
	.string "In case you don't know already,\n"
	.string "I'll explain a little.\p"
	.string "GYM LEADERS are prepared for any\n"
	.string "level of challenger.\p"
	.string "We look at how many badges the\n"
	.string "challenger has received.\p"
	.string "We then adjust the challenge\n"
	.string "accordingly.\p"
	.string "I'll accept your challenge if\n"
	.string "you want to battle now.\p"
	.string "Or you can come back later.\p"
	.string "You can battle the trainers in\n"
	.string "the GYM whenever you like.$"

PetalburgCity_Gym_EventScript_Norman1Badge::
	msgbox PetalburgCity_Gym_Text_Norman1Badge, MSGBOX_DEFAULT
	closemessage
	return

PetalburgCity_Gym_Text_Norman1Badge:
	.string "Ah, I see you've received a\n"
	.string "badge already!\p"
	.string "Since you have one, I'll be\n"
	.string "using a slightly stronger team.\p"
	.string "Perhaps you know this already\n"
	.string "but that's how GYMS work.\p"
	.string "I'll be awaiting your\n"
	.string "challenge, {PLAYER}!$"

PetalburgCity_Gym_EventScript_NormanMultipleBadges::
	msgbox PetalburgCity_Gym_Text_NormanMultipleBadges, MSGBOX_DEFAULT
	closemessage
	return

PetalburgCity_Gym_Text_NormanMultipleBadges:
	.string "Very impressive, {PLAYER}!\p"
	.string "I see you've already been\n"
	.string "awarded multiple badges!\p"
	.string "As a parent, it makes me so\n"
	.string "happy.\p"
	.string "I'll be eagerly waiting to\n"
	.string "see how you battle!$"

PetalburgCity_Gym_Text_NormanBattleIntro:
	.string "DAD: Well, {PLAYER}...\p"
	.string "I hope you understand this is\n"
	.string "an official GYM battle.\p"
	.string "I won't hold back.\p"
	.string "NORMAL types might not seem\n"
	.string "as exciting as others.\p"
	.string "But they can be highly versatile\n"
	.string "and have limited weaknesses.\p"
	.string "{PLAYER}, as the PETALBURG GYM\n"
	.string "LEADER, I accept your challenge!$"

PetalburgCity_Gym_EventScript_NormanRematch::
	trainerbattle_rematch_double TRAINER_NORMAN_1, PetalburgCity_Gym_Text_NormanPreRematch, PetalburgCity_Gym_Text_NormanRematchDefeat, PetalburgCity_Gym_Text_NormanRematchNeedTwoMons
	msgbox PetalburgCity_Gym_Text_NormanPostRematch, MSGBOX_AUTOCLOSE
	end

PetalburgCity_Gym_EventScript_NormanBattle::
	msgbox PetalburgCity_Gym_Text_NormanBattleIntro, MSGBOX_DEFAULT
	switch VAR_NUMBER_OF_BADGES_OWNED
	case 0, PetalburgCity_Gym_EventScript_SetUpNormanBattle0Badges
	case 1, PetalburgCity_Gym_EventScript_SetUpNormanBattle1Badge
	case 2, PetalburgCity_Gym_EventScript_SetUpNormanBattle2Badges
	case 3, PetalburgCity_Gym_EventScript_SetUpNormanBattle3Badges
	end

PetalburgCity_Gym_EventScript_SetUpNormanBattle0Badges:
	trainerbattle_no_intro TRAINER_NORMAN_1, PetalburgCity_Gym_Text_NormanDefeat
	goto PetalburgCity_Gym_EventScript_NormanBattleEnded
	end

PetalburgCity_Gym_EventScript_SetUpNormanBattle1Badge:
	trainerbattle_no_intro TRAINER_NORMAN_2, PetalburgCity_Gym_Text_NormanDefeat
	goto PetalburgCity_Gym_EventScript_NormanBattleEnded
	end

PetalburgCity_Gym_EventScript_SetUpNormanBattle2Badges:
	trainerbattle_no_intro TRAINER_NORMAN_3, PetalburgCity_Gym_Text_NormanDefeat
	goto PetalburgCity_Gym_EventScript_NormanBattleEnded
	end

PetalburgCity_Gym_EventScript_SetUpNormanBattle3Badges:
	trainerbattle_no_intro TRAINER_NORMAN_4, PetalburgCity_Gym_Text_NormanDefeat
	goto PetalburgCity_Gym_EventScript_NormanBattleEnded
	end

PetalburgCity_Gym_EventScript_NormanBattleEnded:
	msgbox PetalburgCity_Gym_Text_NormanBattleEnded, MSGBOX_DEFAULT
	message PetalburgCity_Gym_Text_ReceivedBalanceBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox PetalburgCity_Gym_Text_ExplainBalanceBadge, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_PETALBURG_GYM
	setvar VAR_PETALBURG_GYM_STATE, 2
	setflag FLAG_BADGE05_GET
	special ResetHealLocationFromDewford
	call EventScript_HideMrBriney
	setflag FLAG_HIDE_MAUVILLE_GYM_WATTSON
	clearflag FLAG_HIDE_MAUVILLE_CITY_WATTSON
	setvar VAR_0x8008, 5
	call Common_EventScript_SetGymTrainers
	clearflag FLAG_HIDE_DEWFORD_HALL_SLUDGE_BOMB_MAN
	call PetalburgCity_Gym_EventScript_UnlockAllDoors
	special DrawWholeMapView
	switch VAR_NUMBER_OF_BADGES_OWNED
	case 0, PetalburgCity_Gym_EventScript_ReceiveFirstBadge
	case 1, PetalburgCity_Gym_EventScript_ReceiveSecondBadge
	case 2, PetalburgCity_Gym_EventScript_ReceiveThirdBadge
	end

PetalburgCity_Gym_Text_NormanBattleEnded:
	.string "I can't believe it...\p"
	.string "As a trainer, as a GYM LEADER,\n"
	.string "a loss always stings.\p"
	.string "But as your father...\p"
	.string "{PLAYER}...\p"
	.string "Nothing makes me happier than\n"
	.string "seeing you succeed.\p"
	.string "I'm proud to present you with\n"
	.string "this.$"

PetalburgCity_Gym_EventScript_GiveFacade::
	giveitem ITEM_TM_FACADE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	setflag FLAG_RECEIVED_TM_FACADE
	msgbox PetalburgCity_Gym_Text_ExplainFacade, MSGBOX_DEFAULT
	return

PetalburgCity_Gym_EventScript_NoAmountOfTrainingIsEnough::
	msgbox PetalburgCity_Gym_Text_DadNoAmountOfTrainingIsEnough, MSGBOX_DEFAULT
	release
	end

PetalburgCity_Gym_EventScript_SpeedRoomDoor::
	lockall
	setvar VAR_0x8008, 7
	setvar VAR_0x8009, 85
	msgbox PetalburgCity_Gym_Text_EnterSpeedRoom, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PetalburgCity_Gym_EventScript_EnterRoom
	goto_if_eq VAR_RESULT, NO, PetalburgCity_Gym_EventScript_DontEnterRoom
	end

PetalburgCity_Gym_EventScript_EnterRoom::
	closemessage
	delay 30
	warpdoor MAP_PETALBURG_CITY_GYM, VAR_0x8008, VAR_0x8009
	waitstate
	releaseall
	end

PetalburgCity_Gym_EventScript_DontEnterRoom::
	releaseall
	end

PetalburgCity_Gym_EventScript_DoorLocked::
	msgbox PetalburgCity_Gym_Text_DoorAppearsLocked, MSGBOX_DEFAULT
	releaseall
	end

@ VAR_0x8008 and VAR_0x8009 below are the x and y coordinates of the warp
PetalburgCity_Gym_EventScript_AccuracyRoomDoor::
	lockall
	setvar VAR_0x8008, 1
	setvar VAR_0x8009, 98
	msgbox PetalburgCity_Gym_Text_EnterAccuracyRoom, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PetalburgCity_Gym_EventScript_EnterRoom
	goto_if_eq VAR_RESULT, NO, PetalburgCity_Gym_EventScript_DontEnterRoom
	end

PetalburgCity_Gym_EventScript_ConfusionRoomDoor::
	lockall
	goto_if_defeated TRAINER_RANDALL, PetalburgCity_Gym_EventScript_ConfusionRoomDoorConfirmEnter
	goto_if_defeated TRAINER_MARY, PetalburgCity_Gym_EventScript_ConfusionRoomDoorConfirmEnter
	goto PetalburgCity_Gym_EventScript_DoorLocked
	end

PetalburgCity_Gym_EventScript_ConfusionRoomDoorConfirmEnter:
	setvar VAR_0x8008, 7
	setvar VAR_0x8009, 46
	msgbox PetalburgCity_Gym_Text_EnterConfusionRoom, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PetalburgCity_Gym_EventScript_EnterRoom
	goto_if_eq VAR_RESULT, NO, PetalburgCity_Gym_EventScript_DontEnterRoom
	end

PetalburgCity_Gym_EventScript_LeftDefenseRoomDoor::
	lockall
	goto_if_defeated TRAINER_RANDALL, PetalburgCity_Gym_EventScript_LeftDefenseRoomDoorConfirmEnter
	goto_if_defeated TRAINER_MARY, PetalburgCity_Gym_EventScript_LeftDefenseRoomDoorConfirmEnter
	goto PetalburgCity_Gym_EventScript_DoorLocked
	end

PetalburgCity_Gym_EventScript_LeftDefenseRoomDoorConfirmEnter:
	setvar VAR_0x8008, 1
	setvar VAR_0x8009, 59
	msgbox PetalburgCity_Gym_Text_EnterDefenseRoom, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PetalburgCity_Gym_EventScript_EnterRoom
	goto_if_eq VAR_RESULT, NO, PetalburgCity_Gym_EventScript_DontEnterRoom
	end

PetalburgCity_Gym_EventScript_RightDefenseRoomDoor::
	lockall
	goto_if_defeated TRAINER_RANDALL, PetalburgCity_Gym_EventScript_RightDefenseRoomDoorConfirmEnter
	goto_if_defeated TRAINER_MARY, PetalburgCity_Gym_EventScript_RightDefenseRoomDoorConfirmEnter
	goto PetalburgCity_Gym_EventScript_DoorLocked
	end

PetalburgCity_Gym_EventScript_RightDefenseRoomDoorConfirmEnter:
	setvar VAR_0x8008, 7
	setvar VAR_0x8009, 59
	msgbox PetalburgCity_Gym_Text_EnterDefenseRoom, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PetalburgCity_Gym_EventScript_EnterRoom
	goto_if_eq VAR_RESULT, NO, PetalburgCity_Gym_EventScript_DontEnterRoom
	end

PetalburgCity_Gym_EventScript_RecoveryRoomDoor::
	lockall
	goto_if_defeated TRAINER_RANDALL, PetalburgCity_Gym_EventScript_RecoveryRoomDoorConfirmEnter
	goto_if_defeated TRAINER_MARY, PetalburgCity_Gym_EventScript_RecoveryRoomDoorConfirmEnter
	goto PetalburgCity_Gym_EventScript_DoorLocked
	end

PetalburgCity_Gym_EventScript_RecoveryRoomDoorConfirmEnter:
	setvar VAR_0x8008, 1
	setvar VAR_0x8009, 72
	msgbox PetalburgCity_Gym_Text_EnterRecoveryRoom, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PetalburgCity_Gym_EventScript_EnterRoom
	goto_if_eq VAR_RESULT, NO, PetalburgCity_Gym_EventScript_DontEnterRoom
	end

PetalburgCity_Gym_EventScript_LeftStrengthRoomDoor::
	lockall
	goto_if_defeated TRAINER_PARKER, PetalburgCity_Gym_EventScript_LeftStrengthRoomDoorConfirmEnter
	goto_if_defeated TRAINER_GEORGE, PetalburgCity_Gym_EventScript_LeftStrengthRoomDoorConfirmEnter
	goto_if_defeated TRAINER_ALEXIA, PetalburgCity_Gym_EventScript_LeftStrengthRoomDoorConfirmEnter
	goto PetalburgCity_Gym_EventScript_DoorLocked
	end

PetalburgCity_Gym_EventScript_LeftStrengthRoomDoorConfirmEnter:
	setvar VAR_0x8008, 1
	setvar VAR_0x8009, 20
	msgbox PetalburgCity_Gym_Text_EnterStrengthRoom, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PetalburgCity_Gym_EventScript_EnterRoom
	goto_if_eq VAR_RESULT, NO, PetalburgCity_Gym_EventScript_DontEnterRoom
	end

PetalburgCity_Gym_EventScript_RightStrengthRoomDoor::
	lockall
	goto_if_defeated TRAINER_PARKER, PetalburgCity_Gym_EventScript_RightStrengthRoomDoorConfirmEnter
	goto_if_defeated TRAINER_GEORGE, PetalburgCity_Gym_EventScript_RightStrengthRoomDoorConfirmEnter
	goto_if_defeated TRAINER_ALEXIA, PetalburgCity_Gym_EventScript_RightStrengthRoomDoorConfirmEnter
	goto PetalburgCity_Gym_EventScript_DoorLocked
	end

PetalburgCity_Gym_EventScript_RightStrengthRoomDoorConfirmEnter:
	setvar VAR_0x8008, 7
	setvar VAR_0x8009, 20
	msgbox PetalburgCity_Gym_Text_EnterStrengthRoom, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PetalburgCity_Gym_EventScript_EnterRoom
	goto_if_eq VAR_RESULT, NO, PetalburgCity_Gym_EventScript_DontEnterRoom
	end

PetalburgCity_Gym_EventScript_LeftOHKORoomDoor::
	lockall
	goto_if_defeated TRAINER_PARKER, PetalburgCity_Gym_EventScript_LeftOHKORoomDoorConfirmEnter
	goto_if_defeated TRAINER_GEORGE, PetalburgCity_Gym_EventScript_LeftOHKORoomDoorConfirmEnter
	goto_if_defeated TRAINER_ALEXIA, PetalburgCity_Gym_EventScript_LeftOHKORoomDoorConfirmEnter
	goto PetalburgCity_Gym_EventScript_DoorLocked
	end

PetalburgCity_Gym_EventScript_LeftOHKORoomDoorConfirmEnter:
	setvar VAR_0x8008, 1
	setvar VAR_0x8009, 33
	msgbox PetalburgCity_Gym_Text_EnterOHKORoom, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PetalburgCity_Gym_EventScript_EnterRoom
	goto_if_eq VAR_RESULT, NO, PetalburgCity_Gym_EventScript_DontEnterRoom
	end

PetalburgCity_Gym_EventScript_RightOHKORoomDoor::
	lockall
	goto_if_defeated TRAINER_PARKER, PetalburgCity_Gym_EventScript_RightOHKORoomDoorConfirmEnter
	goto_if_defeated TRAINER_GEORGE, PetalburgCity_Gym_EventScript_RightOHKORoomDoorConfirmEnter
	goto_if_defeated TRAINER_ALEXIA, PetalburgCity_Gym_EventScript_RightOHKORoomDoorConfirmEnter
	goto PetalburgCity_Gym_EventScript_DoorLocked
	end

PetalburgCity_Gym_EventScript_RightOHKORoomDoorConfirmEnter:
	setvar VAR_0x8008, 7
	setvar VAR_0x8009, 33
	msgbox PetalburgCity_Gym_Text_EnterOHKORoom, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PetalburgCity_Gym_EventScript_EnterRoom
	goto_if_eq VAR_RESULT, NO, PetalburgCity_Gym_EventScript_DontEnterRoom
	end

PetalburgCity_Gym_EventScript_LeftGymLeadersRoomDoor::
	lockall
	goto_if_defeated TRAINER_JODY, PetalburgCity_Gym_EventScript_LeftGymLeadersRoomDoorConfirmEnter
	goto_if_defeated TRAINER_BERKE, PetalburgCity_Gym_EventScript_LeftGymLeadersRoomDoorConfirmEnter
	goto PetalburgCity_Gym_EventScript_DoorLocked
	end

PetalburgCity_Gym_EventScript_LeftGymLeadersRoomDoorConfirmEnter:
	setvar VAR_0x8008, 1
	setvar VAR_0x8009, 7
	msgbox PetalburgCity_Gym_Text_EnterGymLeadersRoom, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PetalburgCity_Gym_EventScript_EnterRoom
	goto_if_eq VAR_RESULT, NO, PetalburgCity_Gym_EventScript_DontEnterRoom
	end

PetalburgCity_Gym_EventScript_RightGymLeadersRoomDoor::
	lockall
	goto_if_defeated TRAINER_JODY, PetalburgCity_Gym_EventScript_RightGymLeadersRoomDoorConfirmEnter
	goto_if_defeated TRAINER_BERKE, PetalburgCity_Gym_EventScript_RightGymLeadersRoomDoorConfirmEnter
	goto PetalburgCity_Gym_EventScript_DoorLocked
	end

PetalburgCity_Gym_EventScript_RightGymLeadersRoomDoorConfirmEnter:
	setvar VAR_0x8008, 7
	setvar VAR_0x8009, 7
	msgbox PetalburgCity_Gym_Text_EnterGymLeadersRoom, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PetalburgCity_Gym_EventScript_EnterRoom
	goto_if_eq VAR_RESULT, NO, PetalburgCity_Gym_EventScript_DontEnterRoom
	end

PetalburgCity_Gym_EventScript_Randall::
	goto_if_defeated TRAINER_RANDALL PetalburgCity_Gym_EventScript_RandallPostBattle
	goto_if_defeated TRAINER_MARY PetalburgCity_Gym_EventScript_RandallPostBattle
	trainerbattle_single TRAINER_RANDALL, PetalburgCity_Gym_Text_RandallIntro, PetalburgCity_Gym_Text_RandallDefeat, PetalburgCity_Gym_EventScript_SlideOpenSpeedRoomDoors
	goto_if_set FLAG_DEFEATED_PETALBURG_GYM, PetalburgCity_Gym_EventScript_RandallPostBadge
	goto PetalburgCity_Gym_EventScript_RandallPostBattle
	end

PetalburgCity_Gym_Text_RandallIntro:
	.string "SPEED can be huge in battle.\p"
	.string "Landing an attack first can be the\n"
	.string "thing that secures a win.\p"
	.string "Can you keep up with my POKéMON?$"

PetalburgCity_Gym_Text_RandallDefeat:
	.string "Turns out I couldn't keep up with you.$"

PetalburgCity_Gym_EventScript_RandallPostBattle:
	msgbox PetalburgCity_Gym_Text_RandallPostBattle, MSGBOX_AUTOCLOSE
	end

PetalburgCity_Gym_Text_RandallPostBattle:
	.string "I reckon you've got the potential\n"
	.string "to keep speeding ahead.$"

PetalburgCity_Gym_EventScript_RandallPostBadge::
	msgbox PetalburgCity_Gym_Text_RandallPostBadge, MSGBOX_NPC
	end

PetalburgCity_Gym_Text_RandallPostBadge:
	.string "Keep racing for new victories.\p"
	.string "I'm sure NORMAN will be watching\n"
	.string "where your strength takes you.$"

PetalburgCity_Gym_EventScript_SlideOpenSpeedRoomDoors::
	setvar VAR_0x8005, 0
	call PetalburgCity_Gym_EventScript_OpenSpeedRoomDoors
	special DrawWholeMapView
	release
	end

PetalburgCity_Gym_EventScript_Parker::
	goto_if_defeated TRAINER_PARKER, PetalburgCity_Gym_EventScript_ParkerPostBattle
	goto_if_defeated TRAINER_GEORGE, PetalburgCity_Gym_EventScript_ParkerPostBattle
	goto_if_defeated TRAINER_ALEXIA, PetalburgCity_Gym_EventScript_ParkerPostBattle
	trainerbattle_single TRAINER_PARKER, PetalburgCity_Gym_Text_ParkerIntro, PetalburgCity_Gym_Text_ParkerDefeat, PetalburgCity_Gym_EventScript_SlideOpenConfusionRoomDoors
	goto_if_set FLAG_DEFEATED_PETALBURG_GYM, PetalburgCity_Gym_EventScript_ParkerPostBadge
	msgbox PetalburgCity_Gym_Text_ParkerPostBattle, MSGBOX_AUTOCLOSE
	end

PetalburgCity_Gym_EventScript_SlideOpenConfusionRoomDoors::
	setvar VAR_0x8005, 0
	call PetalburgCity_Gym_EventScript_OpenConfusionRoomDoors
	special DrawWholeMapView
	release
	end

PetalburgCity_Gym_EventScript_ParkerPostBattle:
	msgbox PetalburgCity_Gym_Text_ParkerPostBattle, MSGBOX_NPC
	end

PetalburgCity_Gym_EventScript_ParkerPostBadge::
	msgbox PetalburgCity_Gym_Text_ParkerPostBadge, MSGBOX_NPC
	end

PetalburgCity_Gym_Text_ParkerIntro:
	.string "Confusion is infuriating\p"
	.string "Seeing your POKéMON unable to\n"
	.string "follow your instructions...\p"
	.string "Can you handle it?$"

PetalburgCity_Gym_Text_ParkerDefeat:
	.string "Well, you certainly did handle it.$"

PetalburgCity_Gym_Text_ParkerPostBattle:
	.string "If you can keep your cool like\n"
	.string "that, maybe you can beat NORMAN.$"

PetalburgCity_Gym_Text_ParkerPostBadge:
	.string "Keep that level head and you'll\n"
	.string "go far.$"

PetalburgCity_Gym_EventScript_George::
	goto_if_defeated TRAINER_PARKER, PetalburgCity_Gym_EventScript_GeorgePostBattle
	goto_if_defeated TRAINER_GEORGE, PetalburgCity_Gym_EventScript_GeorgePostBattle
	goto_if_defeated TRAINER_ALEXIA, PetalburgCity_Gym_EventScript_GeorgePostBattle
	trainerbattle_single TRAINER_GEORGE, PetalburgCity_Gym_Text_GeorgeIntro, PetalburgCity_Gym_Text_GeorgeDefeat, PetalburgCity_Gym_EventScript_SlideOpenRecoveryRoomDoors
	goto_if_set FLAG_DEFEATED_PETALBURG_GYM, PetalburgCity_Gym_EventScript_GeorgePostBadge
	msgbox PetalburgCity_Gym_Text_GeorgePostBattle, MSGBOX_AUTOCLOSE
	end

PetalburgCity_Gym_EventScript_SlideOpenRecoveryRoomDoors::
	setvar VAR_0x8005, 0
	call PetalburgCity_Gym_EventScript_OpenRecoveryRoomDoors
	special DrawWholeMapView
	release
	end

PetalburgCity_Gym_EventScript_GeorgePostBattle:
	msgbox PetalburgCity_Gym_Text_GeorgePostBattle, MSGBOX_NPC
	end

PetalburgCity_Gym_EventScript_GeorgePostBadge::
	msgbox PetalburgCity_Gym_Text_GeorgePostBadge, MSGBOX_NPC
	end

PetalburgCity_Gym_EventScript_Berke::
	goto_if_defeated TRAINER_BERKE, PetalburgCity_Gym_EventScript_BerkePostBattle
	goto_if_defeated TRAINER_JODY, PetalburgCity_Gym_EventScript_BerkePostBattle
	trainerbattle_single TRAINER_BERKE, PetalburgCity_Gym_Text_BerkeIntro, PetalburgCity_Gym_Text_BerkeDefeat, PetalburgCity_Gym_EventScript_SlideOpenOHKORoomDoors
	goto_if_set FLAG_DEFEATED_PETALBURG_GYM, PetalburgCity_Gym_EventScript_BerkePostBadge
	msgbox PetalburgCity_Gym_Text_BerkePostBattle, MSGBOX_AUTOCLOSE
	end

PetalburgCity_Gym_Text_GeorgeIntro:
	.string "Seeing your opponent heal in\n"
	.string "battle...\p"
	.string "It's like watching victory\n"
	.string "slip further away.$"

PetalburgCity_Gym_Text_GeorgeDefeat:
	.string "I couldn't keep victory from you.$"

PetalburgCity_Gym_Text_GeorgePostBattle:
	.string "NORMAN's the real deal.\p"
	.string "It'll be much harder to claim\n"
	.string "victory against him.$"

PetalburgCity_Gym_Text_GeorgePostBadge:
	.string "Even NORMAN couldn't keep\n"
	.string "you from claiming victory.$"

PetalburgCity_Gym_EventScript_SlideOpenOHKORoomDoors::
	setvar VAR_0x8005, 0
	call PetalburgCity_Gym_EventScript_OpenOHKORoomDoors
	special DrawWholeMapView
	release
	end

PetalburgCity_Gym_EventScript_BerkePostBattle:
	msgbox PetalburgCity_Gym_Text_BerkePostBattle, MSGBOX_NPC
	end

PetalburgCity_Gym_EventScript_BerkePostBadge::
	msgbox PetalburgCity_Gym_Text_BerkePostBadge, MSGBOX_NPC
	end

PetalburgCity_Gym_Text_BerkeIntro:
	.string "STATUS conditions can be a\n"
	.string "real nightmare.\p"
	.string "Allow me to demonstrate by\n"
	.string "inflicting them on your POKéMON!$"

PetalburgCity_Gym_Text_BerkeDefeat:
	.string "The real nightmare was facing\n"
	.string "a team like yours.$"

PetalburgCity_Gym_Text_BerkePostBattle:
	.string "NORMAN is in the room ahead.\p"
	.string "Prepare yourself for the ultimate\n"
	.string "challenge our GYM has to offer.$"

PetalburgCity_Gym_Text_BerkePostBadge:
	.string "Not even our greatest challenge\n"
	.string "could stand in your way.$"

PetalburgCity_Gym_EventScript_Mary::
	goto_if_defeated TRAINER_RANDALL PetalburgCity_Gym_EventScript_MaryPostBattle
	goto_if_defeated TRAINER_MARY PetalburgCity_Gym_EventScript_MaryPostBattle
	trainerbattle_single TRAINER_MARY, PetalburgCity_Gym_Text_MaryIntro, PetalburgCity_Gym_Text_MaryDefeat, PetalburgCity_Gym_EventScript_SlideOpenAccuracyRoomDoors
	goto_if_set FLAG_DEFEATED_PETALBURG_GYM, PetalburgCity_Gym_EventScript_MaryPostBadge
	goto PetalburgCity_Gym_EventScript_MaryPostBattle
	end

PetalburgCity_Gym_EventScript_MaryPostBattle:
	msgbox PetalburgCity_Gym_Text_MaryPostBattle, MSGBOX_AUTOCLOSE
	end

PetalburgCity_Gym_EventScript_SlideOpenAccuracyRoomDoors::
	setvar VAR_0x8005, 0
	call PetalburgCity_Gym_EventScript_OpenAccuracyRoomDoors
	special DrawWholeMapView
	release
	end

PetalburgCity_Gym_EventScript_MaryPostBadge::
	msgbox PetalburgCity_Gym_Text_MaryPostBadge, MSGBOX_NPC
	end

PetalburgCity_Gym_Text_MaryIntro:
	.string "Hehe\n"
	.string "Feeling confident?\p"
	.string "Let's see how you feel when you\n"
	.string "can't land a hit on my POKéMON.$"

PetalburgCity_Gym_Text_MaryDefeat:
	.string "Your strength was right on the mark...$"

PetalburgCity_Gym_Text_MaryPostBattle:
	.string "Your skills are real. Just\n"
	.string "keep your eyes on the target.$"

PetalburgCity_Gym_Text_MaryPostBadge:
	.string "I think you've got what it takes\n"
	.string "to hit everything you aim for.$"

PetalburgCity_Gym_EventScript_Alexia::
	goto_if_defeated TRAINER_PARKER, PetalburgCity_Gym_EventScript_AlexiaPostBattle
	goto_if_defeated TRAINER_GEORGE, PetalburgCity_Gym_EventScript_AlexiaPostBattle
	goto_if_defeated TRAINER_ALEXIA, PetalburgCity_Gym_EventScript_AlexiaPostBattle
	trainerbattle_single TRAINER_ALEXIA, PetalburgCity_Gym_Text_AlexiaIntro, PetalburgCity_Gym_Text_AlexiaDefeat, PetalburgCity_Gym_EventScript_SlideOpenDefenseRoomDoors
	goto_if_set FLAG_DEFEATED_PETALBURG_GYM, PetalburgCity_Gym_EventScript_AlexiaPostBadge
	msgbox PetalburgCity_Gym_Text_AlexiaPostBattle, MSGBOX_AUTOCLOSE
	end

PetalburgCity_Gym_EventScript_SlideOpenDefenseRoomDoors::
	setvar VAR_0x8005, 0
	call PetalburgCity_Gym_EventScript_OpenDefenseRoomDoors
	special DrawWholeMapView
	release
	end

PetalburgCity_Gym_EventScript_AlexiaPostBattle:
	msgbox PetalburgCity_Gym_Text_AlexiaPostBattle, MSGBOX_NPC
	end

PetalburgCity_Gym_EventScript_AlexiaPostBadge::
	msgbox PetalburgCity_Gym_Text_AlexiaPostBadge, MSGBOX_NPC
	end

PetalburgCity_Gym_Text_AlexiaIntro:
	.string "My POKéMON's DEFENSE is strong,\n"
	.string "just like our bond.$"

PetalburgCity_Gym_Text_AlexiaDefeat:
	.string "Your bonds overwhelmed our defenses.$"

PetalburgCity_Gym_Text_AlexiaPostBattle:
	.string "ATTACK and DEFENSE....\p"
	.string "Find the balance between these\n"
	.string "two and you can win.$"

PetalburgCity_Gym_Text_AlexiaPostBadge:
	.string "Looks like your bonds will take\n$"
	.string "you far.$"

PetalburgCity_Gym_EventScript_Jody::
	goto_if_defeated TRAINER_JODY, PetalburgCity_Gym_EventScript_JodyPostBattle
	goto_if_defeated TRAINER_BERKE, PetalburgCity_Gym_EventScript_JodyPostBattle
	trainerbattle_single TRAINER_JODY, PetalburgCity_Gym_Text_JodyIntro, PetalburgCity_Gym_Text_JodyDefeat, PetalburgCity_Gym_EventScript_SlideOpenStrengthRoomDoors
	goto_if_set FLAG_DEFEATED_PETALBURG_GYM, PetalburgCity_Gym_EventScript_JodyPostBadge
	msgbox PetalburgCity_Gym_Text_JodyPostBattle, MSGBOX_AUTOCLOSE
	end

PetalburgCity_Gym_EventScript_SlideOpenStrengthRoomDoors::
	setvar VAR_0x8005, 0
	call PetalburgCity_Gym_EventScript_OpenStrengthRoomDoors
	special DrawWholeMapView
	release
	end

PetalburgCity_Gym_EventScript_JodyPostBattle:
	msgbox PetalburgCity_Gym_Text_JodyPostBattle, MSGBOX_NPC
	end

PetalburgCity_Gym_EventScript_JodyPostBadge::
	msgbox PetalburgCity_Gym_Text_JodyPostBadge, MSGBOX_NPC
	end

PetalburgCity_Gym_Text_JodyIntro:
	.string "Overwhelming ATTACK power is\n"
	.string "truly terrifying.\p"
	.string "Ever seen a POKéMON's strength\n"
	.string "sweep your team?$"

PetalburgCity_Gym_Text_JodyDefeat:
	.string "Your power was greater than mine.$"

PetalburgCity_Gym_Text_JodyPostBattle:
	.string "The LEADER is up ahead.\p"
	.string "He'll show you the meaning of\n"
	.string "true power!$"

PetalburgCity_Gym_Text_JodyPostBadge:
	.string "I think you'll keep going from\n"
	.string "strength to strength!$"

@ VAR_0x8004 below is the room number
@ VAR_0x8005 below is 0 when the door should be slid open and 1 when it should be unlocked immediately
PetalburgCity_Gym_EventScript_OpenGymEntranceDoors::
	setvar VAR_0x8004, 1
	call_if_eq VAR_0x8005, 0, PetalburgCity_Gym_EventScript_SlideOpenRoomDoors
	call_if_eq VAR_0x8005, 1, PetalburgCity_Gym_EventScript_UnlockRoomDoors
	call PetalburgCity_Gym_EventScript_SetEntranceRoomDoorMetatiles
	return

PetalburgCity_Gym_EventScript_OpenSpeedRoomDoors::
	setvar VAR_0x8004, 2
	call_if_eq VAR_0x8005, 0, PetalburgCity_Gym_EventScript_SlideOpenRoomDoors
	call_if_eq VAR_0x8005, 1, PetalburgCity_Gym_EventScript_UnlockRoomDoors
	call PetalburgCity_Gym_EventScript_SetSpeedRoomDoorMetatiles
	return

PetalburgCity_Gym_EventScript_OpenAccuracyRoomDoors::
	setvar VAR_0x8004, 3
	call_if_eq VAR_0x8005, 0, PetalburgCity_Gym_EventScript_SlideOpenRoomDoors
	call_if_eq VAR_0x8005, 1, PetalburgCity_Gym_EventScript_UnlockRoomDoors
	call PetalburgCity_Gym_EventScript_SetAccuracyRoomDoorMetatiles
	return

PetalburgCity_Gym_EventScript_OpenConfusionRoomDoors::
	setvar VAR_0x8004, 4
	call_if_eq VAR_0x8005, 0, PetalburgCity_Gym_EventScript_SlideOpenRoomDoors
	call_if_eq VAR_0x8005, 1, PetalburgCity_Gym_EventScript_UnlockRoomDoors
	call PetalburgCity_Gym_EventScript_SetConfusionRoomDoorMetatiles
	return

PetalburgCity_Gym_EventScript_OpenDefenseRoomDoors::
	setvar VAR_0x8004, 5
	call_if_eq VAR_0x8005, 0, PetalburgCity_Gym_EventScript_SlideOpenRoomDoors
	call_if_eq VAR_0x8005, 1, PetalburgCity_Gym_EventScript_UnlockRoomDoors
	call PetalburgCity_Gym_EventScript_SetDefenseRoomDoorMetatiles
	return

PetalburgCity_Gym_EventScript_OpenRecoveryRoomDoors::
	setvar VAR_0x8004, 6
	call_if_eq VAR_0x8005, 0, PetalburgCity_Gym_EventScript_SlideOpenRoomDoors
	call_if_eq VAR_0x8005, 1, PetalburgCity_Gym_EventScript_UnlockRoomDoors
	call PetalburgCity_Gym_EventScript_SetRecoveryRoomDoorMetatiles
	return

PetalburgCity_Gym_EventScript_OpenStrengthRoomDoors::
	setvar VAR_0x8004, 7
	call_if_eq VAR_0x8005, 0, PetalburgCity_Gym_EventScript_SlideOpenRoomDoors
	call_if_eq VAR_0x8005, 1, PetalburgCity_Gym_EventScript_UnlockRoomDoors
	call PetalburgCity_Gym_EventScript_SetStrengthRoomDoorMetatiles
	return

PetalburgCity_Gym_EventScript_OpenOHKORoomDoors::
	setvar VAR_0x8004, 8
	call_if_eq VAR_0x8005, 0, PetalburgCity_Gym_EventScript_SlideOpenRoomDoors
	call_if_eq VAR_0x8005, 1, PetalburgCity_Gym_EventScript_UnlockRoomDoors
	call PetalburgCity_Gym_EventScript_SetOHKORoomDoorMetatiles
	return

PetalburgCity_Gym_EventScript_SetEntranceRoomDoorMetatiles::
	setmetatile 6, 85, METATILE_PetalburgGym_RoomEntrance_Left, FALSE
	setmetatile 7, 85, METATILE_PetalburgGym_RoomEntrance_Right, FALSE
	setmetatile 1, 98, METATILE_PetalburgGym_RoomEntrance_Left, FALSE
	setmetatile 2, 98, METATILE_PetalburgGym_RoomEntrance_Right, FALSE
	return

PetalburgCity_Gym_EventScript_SetSpeedRoomDoorMetatiles::
	setmetatile 6, 46, METATILE_PetalburgGym_RoomEntrance_Left, FALSE
	setmetatile 7, 46, METATILE_PetalburgGym_RoomEntrance_Right, FALSE
	setmetatile 1, 59, METATILE_PetalburgGym_RoomEntrance_Left, FALSE
	setmetatile 2, 59, METATILE_PetalburgGym_RoomEntrance_Right, FALSE
	return

PetalburgCity_Gym_EventScript_SetAccuracyRoomDoorMetatiles::
	setmetatile 6, 59, METATILE_PetalburgGym_RoomEntrance_Left, FALSE
	setmetatile 7, 59, METATILE_PetalburgGym_RoomEntrance_Right, FALSE
	setmetatile 1, 72, METATILE_PetalburgGym_RoomEntrance_Left, FALSE
	setmetatile 2, 72, METATILE_PetalburgGym_RoomEntrance_Right, FALSE
	return

PetalburgCity_Gym_EventScript_SetConfusionRoomDoorMetatiles::
	setmetatile 1, 20, METATILE_PetalburgGym_RoomEntrance_Left, FALSE
	setmetatile 2, 20, METATILE_PetalburgGym_RoomEntrance_Right, FALSE
	return

PetalburgCity_Gym_EventScript_SetDefenseRoomDoorMetatiles::
	setmetatile 6, 20, METATILE_PetalburgGym_RoomEntrance_Left, FALSE
	setmetatile 7, 20, METATILE_PetalburgGym_RoomEntrance_Right, FALSE
	setmetatile 1, 33, METATILE_PetalburgGym_RoomEntrance_Left, FALSE
	setmetatile 2, 33, METATILE_PetalburgGym_RoomEntrance_Right, FALSE
	return

PetalburgCity_Gym_EventScript_SetRecoveryRoomDoorMetatiles::
	setmetatile 6, 33, METATILE_PetalburgGym_RoomEntrance_Left, FALSE
	setmetatile 7, 33, METATILE_PetalburgGym_RoomEntrance_Right, FALSE
	return

PetalburgCity_Gym_EventScript_SetStrengthRoomDoorMetatiles::
	setmetatile 1, 7, METATILE_PetalburgGym_RoomEntrance_Left, FALSE
	setmetatile 2, 7, METATILE_PetalburgGym_RoomEntrance_Right, FALSE
	return

PetalburgCity_Gym_EventScript_SetOHKORoomDoorMetatiles::
	setmetatile 6, 7, METATILE_PetalburgGym_RoomEntrance_Left, FALSE
	setmetatile 7, 7, METATILE_PetalburgGym_RoomEntrance_Right, FALSE
	return

PetalburgCity_Gym_EventScript_SlideOpenRoomDoors::
	special PetalburgGymSlideOpenRoomDoors
	waitstate
	return

PetalburgCity_Gym_EventScript_UnlockRoomDoors::
	special PetalburgGymUnlockRoomDoors
	return

PetalburgCity_Gym_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_PETALBURG_GYM, PetalburgCity_Gym_EventScript_GymGuidePostVictory
	msgbox PetalburgCity_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

PetalburgCity_Gym_EventScript_GymGuidePostVictory::
	msgbox PetalburgCity_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

PetalburgCity_Gym_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE05_GET, PetalburgCity_Gym_EventScript_GymStatueCertified
	goto PetalburgCity_Gym_EventScript_GymStatue
	end

PetalburgCity_Gym_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE05_GET, PetalburgCity_Gym_EventScript_GymStatueCertified
	goto PetalburgCity_Gym_EventScript_GymStatue
	end

PetalburgCity_Gym_EventScript_GymStatueCertified::
	msgbox PetalburgCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

PetalburgCity_Gym_EventScript_GymStatue::
	msgbox PetalburgCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

PetalburgCity_Gym_Text_NormanDefeat:
	.string "...\p"
	.string "......\p"
	.string "{PLAYER}...\p"
	.string "I'm so proud of you.$"

PetalburgCity_Gym_Text_ReceivedBalanceBadge:
	.string "{PLAYER} received the BALANCE BADGE\n"
	.string "from DAD!$"

PetalburgCity_Gym_Text_ExplainBalanceBadge:
	.string "DAD: With that BADGE, the DEFENSE\n"
	.string "of all your POKéMON will increase.$"

PetalburgCity_Gym_EventScript_TakeThisToo:
	.string "Please take this too!$"

PetalburgCity_Gym_EventScript_ReceiveFirstBadge:
	setvar VAR_NUMBER_OF_BADGES_OWNED, 1
	msgbox PetalburgCity_Gym_Text_ReceiveFirstBadge, MSGBOX_DEFAULT
	msgbox PetalburgCity_Gym_EventScript_TakeThisToo, MSGBOX_DEFAULT
	giveitem ITEM_HM_CUT
	msgbox PetalburgCity_Gym_Text_NormanBattleEndedConclusion, MSGBOX_DEFAULT
	end

PetalburgCity_Gym_Text_ReceiveFirstBadge:
	.string "That's your first badge,\n"
	.string "{PLAYER}!$"

PetalburgCity_Gym_EventScript_ReceiveSecondBadge:
	setvar VAR_NUMBER_OF_BADGES_OWNED, 2
	msgbox PetalburgCity_Gym_Text_ReceiveSecondBadge, MSGBOX_DEFAULT
	msgbox PetalburgCity_Gym_EventScript_TakeThisToo, MSGBOX_DEFAULT
	giveitem ITEM_HM_FLASH
	msgbox PetalburgCity_Gym_Text_NormanBattleEndedConclusion, MSGBOX_DEFAULT
	end

PetalburgCity_Gym_Text_ReceiveSecondBadge:
	.string "That makes two badges,\n"
	.string "{PLAYER}!$"

PetalburgCity_Gym_EventScript_ReceiveThirdBadge:
	setvar VAR_NUMBER_OF_BADGES_OWNED, 3
	msgbox PetalburgCity_Gym_Text_ReceiveThirdBadge, MSGBOX_DEFAULT
	msgbox PetalburgCity_Gym_EventScript_TakeThisToo, MSGBOX_DEFAULT
	giveitem ITEM_HM_ROCK_SMASH
	msgbox PetalburgCity_Gym_Text_NormanBattleEndedConclusion, MSGBOX_DEFAULT
	end

PetalburgCity_Gym_Text_ReceiveThirdBadge:
	.string "Three badges, {PLAYER}!\p"
	.string "You're really making progress\n"
	.string "collecting them!$"

PetalburgCity_Gym_Text_NormanBattleEndedConclusion:
	.string "{PLAYER}, I can't wait to see\n"
	.string "how far your strength takes you!$"

PetalburgCity_Gym_Text_GymGuideAdvice:
	.string "Hey there, trainer! Allow me to\n"
	.string "explain this GYM to you!\p"
	.string "PETALBURG GYM specialises in\n"
	.string "NORMAL type POKéMON.\p"
	.string "To get to NORMAN, you'll have to\n"
	.string "go through the doors ahead.\p"
	.string "Choose a door and defeat the trainer\n"
	.string "to unlock the next stage.\p"
	.string "You'll only have to defeat one\n"
	.string "trainer per stage.\p"
	.string "Each trainer focuses on a component\n"
	.string "of battle.\p"
	.string "Try and pick the one you think you\n"
	.string "will handle best!\p"
	.string "Good luck!$"

PetalburgCity_Gym_Text_GymGuidePostVictory:
	.string "{PLAYER}! Whoa! You've overcome even\n"
	.string "your own father!\p"
	.string "Like, whoa!\n"
	.string "What a stunning turn of events!$"

PetalburgCity_Gym_Text_DoorAppearsLocked:
	.string "This door appears to be locked\n"
	.string "right now…$"

PetalburgCity_Gym_Text_EnterSpeedRoom:
	.string "“SPEED ROOM,” the sign says.\p"
	.string "Do you want to go through?$"

PetalburgCity_Gym_Text_EnterAccuracyRoom:
	.string "“ACCURACY ROOM,” the sign says.\p"
	.string "Do you want to go through?$"

PetalburgCity_Gym_Text_EnterConfusionRoom:
	.string "“CONFUSION ROOM,” the sign says.\p"
	.string "Do you want to go through?$"

PetalburgCity_Gym_Text_EnterDefenseRoom:
	.string "“DEFENSE ROOM,” the sign says.\p"
	.string "Do you want to go through?$"

PetalburgCity_Gym_Text_EnterRecoveryRoom:
	.string "“RECOVERY ROOM,” the sign says.\p"
	.string "Do you want to go through?$"

PetalburgCity_Gym_Text_EnterStrengthRoom:
	.string "“STRENGTH ROOM,” the sign says.\p"
	.string "Do you want to go through?$"

PetalburgCity_Gym_Text_EnterOHKORoom:
	.string "“STATUS ROOM,” the sign says.\p"
	.string "Do you want to go through?$"

PetalburgCity_Gym_Text_EnterGymLeadersRoom:
	.string "“GYM LEADER'S ROOM\p"
	.string "“See for yourself what POKéMON await\n"
	.string "you!” the sign says.\p"
	.string "Do you want to go through?$"

PetalburgCity_Gym_Text_GymStatue:
	.string "PETALBURG CITY POKéMON GYM$"

PetalburgCity_Gym_Text_GymStatueCertified:
	.string "PETALBURG CITY POKéMON GYM\p"
	.string "NORMAN'S CERTIFIED TRAINERS:\n"
	.string "{PLAYER}$"

PetalburgCity_Gym_Text_NormanPreRematch:
	.string "DAD: {PLAYER}…\n"
	.string "I had a feeling that you would come.\p"
	.string "I would never refuse to accept\n"
	.string "a challenge from you.\p"
	.string "You do understand, don't you?\p"
	.string "Inside a GYM, it doesn't matter that\n"
	.string "we are a parent and child.\p"
	.string "…No, because we are parent and child,\n"
	.string "we owe it to each other to do the best\l"
	.string "we can. Isn't that right, {PLAYER}?$"

PetalburgCity_Gym_Text_NormanRematchDefeat:
	.string "Uh… Haha…\n"
	.string "Maybe that was going too hard…$"

PetalburgCity_Gym_Text_NormanPostRematch:
	.string "DAD: {PLAYER}…\n"
	.string "What is your dream?\p"
	.string "My dream…\n"
	.string "Hahaha…\l"
	.string "It has already come true, actually.$"

PetalburgCity_Gym_Text_NormanRematchNeedTwoMons:
	.string "DAD: {PLAYER}…\n"
	.string "I had a feeling that you would come.\p"
	.string "I would never refuse to accept\n"
	.string "a challenge from you.\p"
	.string "You do understand, don't you?\p"
	.string "Inside a GYM, it doesn't matter that\n"
	.string "we are a parent and child.\p"
	.string "Hm? Wait a second, {PLAYER}.\p"
	.string "Do you only have one POKéMON that is\n"
	.string "capable of battle?\p"
	.string "Sorry, but you'll have to come back\n"
	.string "with at least two POKéMON.$"

