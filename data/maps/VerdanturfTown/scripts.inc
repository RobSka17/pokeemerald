.set LOCALID_TUNNEL_GUARD, 1

VerdanturfTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VerdanturfTown_OnTransition
	.byte 0

VerdanturfTown_OnTransition:
	setflag FLAG_VISITED_VERDANTURF_TOWN
	setvar VAR_CONTEST_HALL_STATE, 0
	call_if_gt VAR_VERDANTURF_TOWN_STATE, 0, VerdanturfTown_EventScript_MoveTunnelGuard
	end

VerdanturfTown_EventScript_MoveTunnelGuard::
	setobjectxyperm LOCALID_TUNNEL_GUARD, 7, 2
	applymovement LOCALID_TUNNEL_GUARD, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

VerdanturfTown_EventScript_TunnelGuard::
	lock
	faceplayer
	goto_if_ge VAR_VERDANTURF_TOWN_STATE, 1, VerdanturfTown_EventScript_TunnelGuard_SkipBadgeCheck
	msgbox VerdanturfTown_Text_TunnelGuard, MSGBOX_NPC
	closemessage
	delay 80
	goto_if_ge VAR_NUMBER_OF_BADGES_OWNED, 1, VerdanturfTown_Text_TunnelGuardHasBadge
	msgbox VerdanturfTown_Text_TunnelGuardDoesNotHaveBadge, MSGBOX_NPC
	release
	end

VerdanturfTown_EventScript_TunnelGuard_SkipBadgeCheck:
	msgbox Route104_Text_WoodsGuard_SkipBadgeCheck, MSGBOX_NPC
	release
	end

VerdanturfTown_EventScript_TunnelGuard_HasBadge:
	msgbox Route104_Text_WoodsGuardHasBadge, MSGBOX_NPC
	applymovement LOCALID_TUNNEL_GUARD, VerdanturfTown_Movement_TunnelGuardMove
	waitmovement 0
	setvar VAR_VERDANTURF_TOWN_STATE, 1
	release
	end

VerdanturfTown_Text_TunnelGuard:
	.string "Hi there, trainer!\p"
	.string "The new initiative from DEVON CORP.\n"
	.string "includes new safety checks.\p"
	.string "RUSTURF TUNNEL has become home to\n"
	.string "more potentially dangerous POKéMON.\p"
	.string "We're asking trainers to prove they've\n"
	.string "been awarded at least one GYM badge.\p"
	.string "Any badge will do but without it, we\n"
	.string "can't allow entry beyond this point.$"

VerdanturfTown_Text_TunnelGuard_SkipBadgeCheck:
	.string "Stay safe out there, trainer!$"

VerdanturfTown_Text_TunnelGuardHasBadge:
	.string "Ah yes, that's an official POKéMON\n"
	.string "LEAGUE badge!\p"
	.string "You may enter but please be on your\n"
	.string "guard.$"

VerdanturfTown_Text_TunnelGuardDoesNotHaveBadge:
	.string "I'm sorry. Please come back when\n"
	.string "you have at least one badge.$"

VerdanturfTown_Movement_TunnelGuardMove:
	walk_left
	walk_in_place_faster_right
	step_end

VerdanturfTown_EventScript_TownSign::
	msgbox VerdanturfTown_Text_TownSign, MSGBOX_SIGN
	end

VerdanturfTown_EventScript_WandasHouseSign::
	msgbox VerdanturfTown_Text_WandasHouse, MSGBOX_SIGN
	end

VerdanturfTown_EventScript_BattleTentSign::
	msgbox VerdanturfTown_Text_BattleTentSign, MSGBOX_SIGN
	end

VerdanturfTown_EventScript_RusturfTunnelSign::
	msgbox VerdanturfTown_Text_RusturfTunnelSign, MSGBOX_SIGN
	end

VerdanturfTown_Text_TownSign:
	.string "VERDANTURF TOWN\p"
	.string "“The windswept highlands with the\n"
	.string "sweet fragrance of grass.”$"

VerdanturfTown_Text_WandasHouse:
	.string "WANDA'S HOUSE$"

VerdanturfTown_Text_BattleTentSign:
	.string "BATTLE TENT VERDANTURF SITE\n"
	.string "“Feast Your Eyes on Battles!”$"

VerdanturfTown_Text_RusturfTunnelSign:
	.string "RUSTURF TUNNEL\p"
	.string "“Permitted access only.”$"

