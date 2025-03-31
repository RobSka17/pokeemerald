CelestialCavern_DeoxysRoom_MapScripts::
	.byte 0


CelestialCavern_DeoxysRoom_EventScript_DeoxysTriangle::
	lock
	msgbox CelestialCavern_DeoxysRoom_Text_DeoxysTriangle, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, CelestialCavern_DeoxysRoom_EventScript_DeoxysTriangle_Touch
	release
	end

CelestialCavern_DeoxysRoom_EventScript_DeoxysTriangle_Touch:
	playse SE_THUNDER
	special DoSealedChamberShakingEffect_Long
	waitstate
	delay 40
	playse SE_THUNDER
	special DoSealedChamberShakingEffect_Long
	waitstate
	delay 40
	setweather WEATHER_DROUGHT
	doweather
	delay 240
	setweather WEATHER_SHADE
	doweather
	delay 80
	playmoncry SPECIES_DEOXYS, CRY_MODE_ENCOUNTER
	waitmoncry
	setwildbattle SPECIES_DEOXYS, 80
	special BattleSetup_StartLegendaryBattle
	release
	end

CelestialCavern_DeoxysRoom_Text_DeoxysTriangle:
	.string "A mysterious artefact.\n"
	.string "It exudes an ominous energy.\p"
	.string "Touch it?$"

