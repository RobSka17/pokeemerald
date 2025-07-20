@ NOTE: Route 104's sail to Dewford script references local IDs from Dewford's map.
@  These are labeled in DewfordTown/scripts.inc
.set LOCALID_RIVAL, 34
.set LOCALID_WOODS_GUARD_1, 11
.set LOCALID_WOODS_GUARD_2, 12
.set LOCALID_WOODS_GUARD_3, 13
.set LOCALID_WOODS_GUARD_4, 14

Route104_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route104_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, Route104_OnTransition
	.byte 0

Route104_OnFrame:
	.2byte 0

Route104_OnTransition:
	call_if_gt VAR_ROUTE104_STATE, 0, Route104_EventScript_MoveWoodsGuards
	end

Route104_EventScript_Billy::
	trainerbattle_single TRAINER_BILLY, Route104_Text_BillyIntro, Route104_Text_BillyDefeated
	msgbox Route104_Text_BillyPostBattle, MSGBOX_AUTOCLOSE
	end

Route104_Text_BillyIntro:
	.string "My POKéMON floats in the sea with\n"
	.string "me!$"

Route104_Text_BillyDefeated:
	.string "Awwww...$"

Route104_Text_BillyPostBattle:
	.string "I like to battle but I like\n"
	.string "the sea more.$"

Route104_EventScript_Joan::
	trainerbattle_single TRAINER_JOAN, Route104_Text_JoanIntro, Route104_Text_JoanDefeated
	msgbox Route104_Text_JoanPostBattle, MSGBOX_AUTOCLOSE
	end

Route104_Text_JoanIntro:
	.string "Isn't the seafront such a\n"
	.string "charming place for a battle?$"

Route104_Text_JoanDefeated:
	.string "Simply stunning!$"

Route104_Text_JoanPostBattle:
	.string "I moved here from VERDANTURF.\p"
	.string "I hear some popular kid from\n"
	.string "there used to live here.$"

Route104_EventScript_Kiara::
	trainerbattle_single TRAINER_KIARA, Route104_Text_KiaraIntro, Route104_Text_KiaraDefeated
	msgbox Route104_Text_KiaraPostBattle, MSGBOX_AUTOCLOSE
	end

Route104_Text_KiaraIntro:
	.string "Grrr, those guys won't\n"
	.string "let me into the WOODS.\p"
	.string "What's up with that?$"

Route104_Text_KiaraDefeated:
	.string "Too frustrating!$"

Route104_Text_KiaraPostBattle:
	.string "I gotta keep training!$"

Route104_EventScript_Woman::
	lock
	faceplayer
	msgbox Route104_Text_Woman, MSGBOX_DEFAULT
	release
	end

Route104_Text_Woman:
	.string "My dear BILLY loves the sea.\p"
	.string "But I heard something in the news\n"
	.string "about changing conditions.$"

Route104_EventScript_WoodsGuard::
	lock
	faceplayer
	goto_if_ge VAR_ROUTE104_STATE, 1, Route104_EventScript_WoodsGuard_SkipBadgeCheck
	msgbox Route104_Text_WoodsGuard, MSGBOX_NPC
	closemessage
	delay 80
	goto_if_ge VAR_NUMBER_OF_BADGES_OWNED, 1, Route104_EventScript_WoodsGuard_HasBadge
	msgbox Route104_Text_WoodsGuardDoesNotHaveBadge, MSGBOX_NPC
	release
	end

Route104_EventScript_WoodsGuard_SkipBadgeCheck:
	msgbox Route104_Text_WoodsGuard_SkipBadgeCheck, MSGBOX_NPC
	release
	end

Route104_EventScript_WoodsGuard_HasBadge:
	msgbox Route104_Text_WoodsGuardHasBadge, MSGBOX_NPC
	applymovement OBJ_EVENT_ID_PLAYER, Route104_Movement_PlayerMoveBackFromWoodsGuardSouth
	waitmovement 0
	applymovement LOCALID_WOODS_GUARD_1, Route104_Movement_WoodsGuardRightMoveAwaySouth
	applymovement LOCALID_WOODS_GUARD_2, Route104_Movement_WoodsGuardLeftMoveAwaySouth
	waitmovement 0
	setvar VAR_ROUTE104_STATE, 1
	release
	end

Route104_Text_WoodsGuard:
	.string "Hi there, trainer!\p"
	.string "The new initiative from DEVON CORP.\n"
	.string "includes new safety checks.\p"
	.string "More dangerous BUG POKéMON are making\n"
	.string "PETALBURG WOODS their home recently.\p"
	.string "We're asking trainers to prove they've\n"
	.string "been awarded at least one GYM badge.\p"
	.string "Any badge will do but without it, we\n"
	.string "can't allow entry beyond this point.$"

Route104_Text_WoodsGuard_SkipBadgeCheck:
	.string "Stay safe out there, trainer!$"

Route104_Text_WoodsGuardHasBadge:
	.string "Ah yes, that's an official POKéMON\n"
	.string "LEAGUE badge!\p"
	.string "You may enter but please be on your\n"
	.string "guard.$"

Route104_Text_WoodsGuardDoesNotHaveBadge:
	.string "I'm sorry. Please come back when\n"
	.string "you have at least one badge.$"

Route104_Movement_PlayerMoveBackFromWoodsGuardSouth:
	walk_down
	walk_in_place_faster_up
	step_end

Route104_Movement_WoodsGuardLeftMoveAwaySouth:
	walk_down
	walk_left
	walk_in_place_faster_down
	step_end

Route104_Movement_WoodsGuardRightMoveAwaySouth:
	walk_down
	walk_right
	walk_in_place_faster_down
	step_end

Route104_EventScript_MoveWoodsGuards::
	setobjectxyperm LOCALID_WOODS_GUARD_1, 9, 41
	setobjectxyperm LOCALID_WOODS_GUARD_2, 12, 41
	setobjectxyperm LOCALID_WOODS_GUARD_3, 9, 27
	setobjectxyperm LOCALID_WOODS_GUARD_4, 12, 27
	return

Route104_EventScript_BrineysCottageSign::
	msgbox Route104_Text_MrBrineysCottage, MSGBOX_SIGN
	end

Route104_EventScript_RouteSignPetalburg::
	msgbox Route104_Text_RouteSignPetalburg, MSGBOX_SIGN
	end

Route104_EventScript_RouteSignRustboro::
	msgbox Route104_Text_RouteSignRustboro, MSGBOX_SIGN
	end

Route104_EventScript_FlowerShopSign::
	msgbox Route104_Text_PrettyPetalFlowShop, MSGBOX_SIGN
	end

Route104_EventScript_TrainerTipsDoubleBattles::
	msgbox Route104_Text_TrainerTipsDoubleBattles, MSGBOX_SIGN
	end

Route104_Text_MrBrineysCottage:
	.string "It seems like this used to say\n"
	.string "something.\p"
	.string "But the text has been removed.$"

Route104_Text_RouteSignPetalburg:
	.string "ROUTE 1O4\n"
	.string "{RIGHT_ARROW} PETALBURG CITY$"

Route104_Text_RouteSignRustboro:
	.string "ROUTE 1O4\n"
	.string "{UP_ARROW} RUSTBORO CITY$"

Route104_Text_PrettyPetalFlowShop:
	.string "PRETTY PETAL FLOWER SHOP$"

Route104_Text_TrainerTipsDoubleBattles:
	.string "TRAINER TIPS\p"
	.string "In the HOENN region there are pairs\n"
	.string "of TRAINERS who challenge others\l"
	.string "for 2-on-2 POKéMON battles called\l"
	.string "DOUBLE BATTLES.\p"
	.string "In a DOUBLE BATTLE, the TRAINER must\n"
	.string "send out two POKéMON, the one at the\l"
	.string "left of the list and the top one.\l"
	.string "Watch how POKéMON are lined up.$"

