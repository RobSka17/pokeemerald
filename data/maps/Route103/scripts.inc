.set LOCALID_RIVAL, 2

Route103_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route103_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, Route103_OnLoad
	.byte 0

Route103_OnTransition:
	end

Route103_OnLoad:
	call_if_set FLAG_SYS_GAME_CLEAR, Route103_EventScript_OpenAlteringCave
	end

Route103_EventScript_OpenAlteringCave::
	setmetatile 45, 5, METATILE_General_CaveEntrance_Top, TRUE
	setmetatile 45, 6, METATILE_General_CaveEntrance_Bottom, FALSE
	return

Route103_EventScript_HarbourSign::
	msgbox Route103_Text_HarbourSign, MSGBOX_SIGN
	end

Route103_Text_HarbourSign:
	.string "OLDALE RIVER CROSSING\n"
	.string "{RIGHT_ARROW} MAUVILLE/SLATEPORT$"

Route103_EventScript_HarbourSign2::
	msgbox Route103_Text_HarbourSign2, MSGBOX_SIGN
	end

Route103_Text_HarbourSign2:
	.string "OLDALE RIVER CROSSING\n"
	.string "{LEFT_ARROW} OLDALE$"

Route103_EventScript_RouteSign::
	msgbox Route103_Text_RouteSign, MSGBOX_SIGN
	end

Route103_Text_RouteSign:
	.string "ROUTE 103\n"
	.string "{DOWN_ARROW} OLDALE TOWN$"

