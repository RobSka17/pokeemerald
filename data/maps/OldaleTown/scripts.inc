OldaleTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, OldaleTown_OnTransition
	.byte 0

OldaleTown_OnTransition:
	setflag FLAG_VISITED_OLDALE_TOWN
	end

OldaleTown_EventScript_TownSign::
	msgbox OldaleTown_Text_TownSign, MSGBOX_SIGN
	end

OldaleTown_Text_TownSign:
	.string "OLDALE TOWN\n"
	.string "“Where things start off scarce.”$"

OldaleTown_EventScript_Sailor::
	lock
	faceplayer
	msgbox OldaleTown_Text_Sailor, MSGBOX_DEFAULT
	release
	end

OldaleTown_Text_Sailor:
	.string "I'm on break from my job at the\n"
	.string "RIVER CROSSING north of here.\p"
	.string "You can get a ferry to SLATEPORT\n"
	.string "instead of going the long way.\p"
	.string "I hear the market there is great\n"
	.string "for POKéMON TRAINERS.$"

OldaleTown_EventScript_Youngster::
	lock
	faceplayer
	msgbox OldaleTown_Text_Youngster, MSGBOX_DEFAULT
	release
	end

OldaleTown_Text_Youngster:
	.string "Sigh... I told my friends I was\n"
	.string "starting a journey as a trainer.\p"
	.string "But the truth is... It turns out\n"
	.string "I'm not good at battling.\p"
	.string "It'd be embarassing to go back\n"
	.string "home. I don't know what to do.$"

OldaleTown_EventScript_MartEmployee::
	lock
	faceplayer
	msgbox OldaleTown_Text_MartEmployee, MSGBOX_DEFAULT
	release
	end

OldaleTown_Text_MartEmployee:
	.string "Where do all great trainers\n"
	.string "start?\p"
	.string "Head on down to POKé MART!\p"
	.string "...\p"
	.string "I'm really not paid enough\n"
	.string "for this...$"
