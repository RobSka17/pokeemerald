Route112_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route112_OnTransition
	.byte 0

Route112_OnTransition:
	clearflag FLAG_FORCE_MIRAGE_TOWER_VISIBLE
	setvar VAR_JAGGED_PASS_ASH_WEATHER, 0
	end

Route112_EventScript_MtChimneyCableCarSign::
	msgbox Route112_Text_MtChimneyCableCarSign, MSGBOX_SIGN
	end

Route112_EventScript_MtChimneySign::
	msgbox Route112_Text_MtChimneySign, MSGBOX_SIGN
	end

Route112_EventScript_RouteSignLavaridge::
	msgbox Route112_Text_RouteSignLavaridge, MSGBOX_SIGN
	end

Route112_Text_MtChimneyCableCarSign:
	.string "MT. CHIMNEY CABLE CAR\n"
	.string "“A short walk {UP_ARROW} way!”$"

Route112_Text_MtChimneySign:
	.string "MT. CHIMNEY\p"
	.string "“For LAVARIDGE TOWN or the summit,\n"
	.string "please take the CABLE CAR.”$"

Route112_Text_RouteSignLavaridge:
	.string "ROUTE 112\n"
	.string "{LEFT_ARROW} LAVARIDGE TOWN$"

Route112_EventScript_WooperLady::
	lock
	faceplayer
	msgbox Route112_Text_WooperLady, MSGBOX_DEFAULT
	release
	end

Route112_Text_WooperLady:
	.string "MT. CHIMNEY has been more active\n"
	.string "recently.\p"
	.string "It's impacting air humidity\n"
	.string "and launching ash into the air.\p"
	.string "The flora is sensitive to\n"
	.string "these kinds of changes.\p"
	.string "That's why WOOPER and I are out\n"
	.string "here watering.\p"
	.string "It's a real challenge, though.\p"
	.string "I don't know how much more of\n"
	.string "this the environment can take.$"

Route112_EventScript_Wooper::
	lock
	faceplayer
	msgbox Route112_Text_Wooper, MSGBOX_DEFAULT
	release
	end

Route112_Text_Wooper:
	.string "Paaaa!$"

