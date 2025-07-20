OldaleTown_House1_MapScripts::
	.byte 0

OldaleTown_House1_EventScript_Woman::
	lock
	faceplayer
	msgbox OldaleTown_House1_Text_Woman, MSGBOX_NPC
	release
	end

OldaleTown_House1_Text_Woman:
	.string "Isn't my AZUMARILL absolutely\n"
	.string "precious?$"

OldaleTown_House1_EventScript_Azumarill::
	lock
	faceplayer
	playmoncry SPECIES_AZUMARILL, CRY_MODE_NORMAL
	waitmoncry
	msgbox OldaleTown_House1_Text_Azumarill, MSGBOX_DEFAULT
	release
	end

OldaleTown_House1_Text_Azumarill:
	.string "AZUUU!$"

