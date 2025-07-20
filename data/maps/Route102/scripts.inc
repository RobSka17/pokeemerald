Route102_MapScripts::
	.byte 0

Route102_EventScript_LittleBoy::
	msgbox Route102_Text_ImNotVeryTall, MSGBOX_NPC
	end

Route102_EventScript_RouteSignOldale::
	msgbox Route102_Text_RouteSignOldale, MSGBOX_SIGN
	end

Route102_EventScript_RouteSignPetalburg::
	msgbox Route102_Text_RouteSignPetalburg, MSGBOX_SIGN
	end

Route102_EventScript_Jimmy::
	trainerbattle_single TRAINER_JIMMY, Route102_Text_JimmyIntro, Route102_Text_JimmyDefeated
	msgbox Route102_Text_JimmyPostBattle, MSGBOX_AUTOCLOSE
	end

Route102_Text_JimmyIntro:
	.string "I caught this POKéMON myself with\n"
	.string "the POKé BALLS my dad bought!$"

Route102_Text_JimmyDefeated:
	.string "Nooo, my POKéMON!$"

Route102_Text_JimmyPostBattle:
	.string "Now I'm gonna have to go home...$"

Route102_EventScript_Liz::
	trainerbattle_single TRAINER_LIZ, Route102_Text_LizIntro, Route102_Text_LizDefeated
	msgbox Route102_Text_LizPostBattle, MSGBOX_AUTOCLOSE
	end

Route102_Text_LizIntro:
	.string "I love to be outdoors with my\n"
	.string "dear POKéMON.\p"
	.string "Don't you love the sweet aromas\n"
	.string "of nature?$"

Route102_Text_LizDefeated:
	.string "Oh my...$"

Route102_Text_LizPostBattle:
	.string "Nature is always so soothing.$"

Route102_EventScript_Ralph::
	trainerbattle_single TRAINER_RALPH, Route102_Text_RalphIntro, Route102_Text_RalphDefeated
	msgbox Route102_Text_RalphPostBattle, MSGBOX_AUTOCLOSE
	end

Route102_Text_RalphIntro:
	.string "My friends dared me to\n"
	.string "challenge the GYM.\p"
	.string "I didn't stand a chance.$"

Route102_Text_RalphDefeated:
	.string "My poor BUGS! Forgive me!$"

Route102_Text_RalphPostBattle:
	.string "My BUGS will be always be\n"
	.string "cool, even if they lose!$"

Route102_EventScript_Gregory::
	trainerbattle_single TRAINER_GREGORY, Route102_Text_GregoryIntro, Route102_Text_GregoryDefeated
	msgbox Route102_Text_GregoryPostBattle, MSGBOX_AUTOCLOSE
	end

Route102_Text_GregoryIntro:
	.string "Dang, I was fast asleep\n"
	.string "there!$"

Route102_Text_GregoryDefeated:
	.string "Seems my battle skills\n"
	.string "were asleep too.$"

Route102_Text_GregoryPostBattle:
	.string "Nothing beats a good nap!$"

Route102_EventScript_Antidote::
	finditem ITEM_ANTIDOTE
	end

Route102_EventScript_Rick::
	trainerbattle_single TRAINER_RICK, Route102_Text_RickIntro, Route102_Text_RickDefeated
	msgbox Route102_Text_RickPostBattle, MSGBOX_AUTOCLOSE
	end

Route102_EventScript_Tiana::
	trainerbattle_single TRAINER_TIANA, Route102_Text_TianaIntro, Route102_Text_TianaDefeated
	msgbox Route102_Text_TianaPostBattle, MSGBOX_AUTOCLOSE
	end

Route102_EventScript_Allen::
	trainerbattle_single TRAINER_ALLEN, Route102_Text_AllenIntro, Route102_Text_AllenDefeated
	msgbox Route102_Text_AllenPostBattle, MSGBOX_AUTOCLOSE
	end

Route102_Text_WatchMeCatchPokemon:
	.string "WALLY: {PLAYER}…\n"
	.string "POKéMON hide in tall grass like this,\l"
	.string "don't they?\p"
	.string "Please watch me and see if I can\n"
	.string "catch one properly.\p"
	.string "…Whoa!$"

Route102_Text_WallyIDidIt:
	.string "WALLY: I did it… It's my…\n"
	.string "My POKéMON!$"

Route102_Text_LetsGoBack:
	.string "{PLAYER}, thank you!\n"
	.string "Let's go back to the GYM!$"

Route102_Text_ImNotVeryTall:
	.string "I'm…not very tall, so I sink right\n"
	.string "into tall grass.\p"
	.string "The grass goes up my nose and…\n"
	.string "Fwafwafwafwafwa…\p"
	.string "Fwatchoo!$"

Route102_Text_RouteSignOldale:
	.string "ROUTE 102\n"
	.string "{RIGHT_ARROW} OLDALE TOWN$"

Route102_Text_RouteSignPetalburg:
	.string "ROUTE 102\n"
	.string "{LEFT_ARROW} PETALBURG CITY$"
