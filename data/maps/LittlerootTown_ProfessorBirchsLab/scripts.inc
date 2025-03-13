.set LOCALID_AIDE, 1
.set LOCALID_BIRCH, 2
.set LOCALID_AIDE3, 3
.set LOCALID_BOY, 4
.set LOCALID_GIRL, 5
.set LOCALID_AIDE2, 6

LittlerootTown_ProfessorBirchsLab_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LittlerootTown_ProfessorBirchsLab_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, LittlerootTown_ProfessorBirchsLab_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LittlerootTown_ProfessorBirchsLab_OnFrame
	.byte 0

	@ State descriptions for VAR_DEX_UPGRADE_JOHTO_STARTER_STATE
	@ 1: Beat Elite Four, Dex upgrade ready
	@ 2: Received National Dex
	@ 3: Left lab after receiving National Dex
	@ 4: Entered lab after catching all Hoenn mons
	@ 5: Birch told player to choose Johto starter
	@ 6: Chose Johto starter

	@ State descriptions for VAR_BIRCH_LAB_STATE
	@ 1: Never occurs
	@ 2: Chose starter
	@ 3: Received starter in lab
	@ 4: Defeated rival on Route 103
	@ 5: Received pokedex

LittlerootTown_ProfessorBirchsLab_OnTransition:
	end

LittlerootTown_ProfessorBirchsLab_OnWarp:
	map_script_2 VAR_BIRCH_LAB_STATE, 2, LittlerootTown_ProfessorBirchsLab_EventScript_SetPlayerPosForReceiveStarter
	.2byte 0

LittlerootTown_ProfessorBirchsLab_EventScript_SetPlayerPosForReceiveStarter::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

LittlerootTown_ProfessorBirchsLab_OnFrame:
	map_script_2 VAR_BIRCH_LAB_STATE, 2, LittlerootTown_ProfessorBirchsLab_EventScript_GiveStarterEvent
	.2byte 0

@ The starter is technically given prior to this on Route 101 by special ChooseStarter
@ This is just where the game tells you its yours and lets you nickname it
LittlerootTown_ProfessorBirchsLab_EventScript_GiveStarterEvent::
	lockall
	msgbox LittlerootTown_ProfessorBirchsLab_Text_HoennChanging, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BIRCH, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	delay 40
	applymovement LOCALID_BIRCH, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 40
	applymovement LOCALID_BIRCH, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	bufferleadmonspeciesname STR_VAR_1
	message LittlerootTown_ProfessorBirchsLab_Text_KeepThatPokemon
	waitmessage
	playfanfare MUS_OBTAIN_ITEM
	waitfanfare
	msgbox LittlerootTown_ProfessorBirchsLab_Text_WantGiveNickname, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, LittlerootTown_ProfessorBirchsLab_EventScript_NicknameStarter
	goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_GiveTask
	end

LittlerootTown_ProfessorBirchsLab_Text_HoennChanging:
	.string "BIRCH: Well, {PLAYER}! That isn't quite\n"
	.string "how I'd envisioned our meeting!\p"
	.string "But now you've experienced\n"
	.string "how the HOENN region is changing.\p"
	.string "That POKéMON you encountered earlier,\n"
	.string "it's called POOCHYENA.\p"
	.string "They can certainly be aggressive but\n"
	.string "they usually turn tail at a challenge.\p"
	.string "As I mentioned earlier, however, they're\n"
	.string "becoming increasingly territorial.\p"
	.string "You see, a lot of POKéMON not typically\n"
	.string "seen have started appearing in HOENN.\p"
	.string "We believe this change has lead to\n"
	.string "this behaviour.$"

LittlerootTown_ProfessorBirchsLab_Text_KeepThatPokemon:
	.string "{PLAYER}, I had something\n"
	.string "in mind for you to do...\p"
	.string "But I've had a thought.\p"
	.string "I'd like you to keep that {STR_VAR_1}.\p"
	.string "{PLAYER} received the {STR_VAR_1}!$"

LittlerootTown_ProfessorBirchsLab_EventScript_GiveTask:
	setvar VAR_BIRCH_LAB_STATE, 3
	setvar VAR_LITTLEROOT_TOWN_STATE, 2
	msgbox LittlerootTown_ProfessorBirchsLab_Text_GiveTask, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message LittlerootTown_ProfessorBirchsLab_Text_GotNationalDex
	waitmessage
	waitfanfare
	setflag FLAG_SYS_POKEDEX_GET
	special SetUnlockedPokedexFlags
	setflag FLAG_RECEIVED_POKEDEX_FROM_BIRCH
	setvar VAR_CABLE_CLUB_TUTORIAL_STATE, 1
	setflag FLAG_SYS_NATIONAL_DEX
	special EnableNationalPokedex
	release
	end

LittlerootTown_ProfessorBirchsLab_Text_GiveTask:
	.string "I received an email from a man called\n"
	.string "STEVEN STONE earlier.\p"
	.string "He took over as the head of DEVON\n"
	.string "CORP. when his father retired.\p"
	.string "They're a company based in RUSTBURO,\n"
	.string "a city on the eastern coast.\p"
	.string "We've been working with them to\n"
	.string "respond to the changes in HOENN.\p"
	.string "He asked if I could visit him at\n"
	.string "the DEVON HQ.\p"
	.string "But the truth is I've really got\n"
	.string "my hands full here.\p"
	.string "I'd like you to go and meet him.\p"
	.string "You can get to RUSTBURO via\n"
	.string "PETALBURG or MAUVILLE.\p"
	.string "I'd like you to take this too.$"

LittlerootTown_ProfessorBirchsLab_Text_GotNationalDex:
	.string "{PLAYER} received the NATIONAL POKéDEX\n"
	.string "from BIRCH!$"

LittlerootTown_ProfessorBirchsLab_EventScript_NicknameStarter::
	setvar VAR_0x8004, 0
	call Common_EventScript_NameReceivedPartyMon
	goto LittlerootTown_ProfessorBirchsLab_EventScript_GiveTask
	end

LittlerootTown_ProfessorBirchsLab_EventScript_Aide2::
	lock
	faceplayer
	goto_if_eq VAR_BIRCH_LAB_STATE, 1, LittlerootTown_ProfessorBirchLab_EventScript_Aide2BirchNotHere
	goto_if_eq VAR_BIRCH_LAB_STATE, 3, LittlerootTown_ProfessorBirchLab_EventScript_Aide2ThanksForHelping
	msgbox LittlerootTown_ProfessorBirchLabText_Aide2Default, MSGBOX_DEFAULT
	release
	end

LittlerootTown_ProfessorBirchLab_EventScript_Aide2ThanksForHelping:
	msgbox LittlerootTown_ProfessorBirchLabText_Aide2ThanksForHelping, MSGBOX_DEFAULT
	release
	end

LittlerootTown_ProfessorBirchLabText_Aide2ThanksForHelping:
	.string "Thanks for helping the PROFESSOR!\p"
	.string "It really is getting more dangerous\n"
	.string "to go into wild POKéMON habitats.$"

LittlerootTown_ProfessorBirchLab_EventScript_Aide2BirchNotHere:
	msgbox LittlerootTown_ProfessorBirchLabText_Aide2BirchNotHere, MSGBOX_DEFAULT
	release
	end

LittlerootTown_ProfessorBirchLabText_Aide2BirchNotHere:
	.string "The PROFESSOR? I'm afraid he isn't here.\p"
	.string "Come to think of it, I thought he'd be\n"
	.string "back by now.$"

LittlerootTown_ProfessorBirchLabText_Aide2Default:
	.string "More and more young people are getting\n"
	.string "involved in BIRCH's youth scheme.\p"
	.string "It's important the changing world\n"
	.string "doesn't put off new young trainers.$"

LittlerootTown_ProfessorBirchLab_EventScript_Aide3::
	lock
	goto_if_eq VAR_BIRCH_LAB_STATE, 1, LittlerootTown_ProfessorBirchLab_EventScript_Aide3AsYouCanSee
	goto_if_eq VAR_BIRCH_LAB_STATE, 3, LittlerootTown_ProfessorBirchLab_EventScript_Aide3YouReallyHelped
	faceplayer
	msgbox LittlerootTown_ProfessorBirchLabText_Aide3Default, MSGBOX_DEFAULT
	applymovement LOCALID_AIDE3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end


LittlerootTown_ProfessorBirchLab_EventScript_Aide3AsYouCanSee:
	msgbox LittlerootTown_ProfessorBirchLabText_Aide3AsYouCanSee, MSGBOX_DEFAULT
	faceplayer
	msgbox LittlerootTown_ProfessorBirchLabText_Aide3HmmProfBirch, MSGBOX_DEFAULT
	applymovement LOCALID_AIDE3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LittlerootTown_ProfessorBirchLabText_Aide3AsYouCanSee:
	.string "So, as you can see, some POKéMON have\n"
	.string "two types. That means that...$"

LittlerootTown_ProfessorBirchLabText_Aide3HmmProfBirch:
	.string "Hmm? PROFESSOR BIRCH?\p"
	.string "I haven't seen him in a while.$"

LittlerootTown_ProfessorBirchLab_EventScript_Aide3YouReallyHelped:
	faceplayer
	msgbox LittlerootTown_ProfessorBirchLabText_Aide3YouReallyHelped, MSGBOX_DEFAULT
	applymovement LOCALID_AIDE3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LittlerootTown_ProfessorBirchLabText_Aide3YouReallyHelped:
	.string "You really helped the PROFESSOR!$"

LittlerootTown_ProfessorBirchLabText_Aide3Default:
	.string "The PROFESSOR is leading HOENN's\n"
	.string "efforts to educate children.$"

LittlerootTown_ProfessorBirchsLab_EventScript_Aide::
	lock
	faceplayer
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_Girl::
	lock
	faceplayer
	msgbox LittlerootTown_ProfessorBirchsLabText_Girl, MSGBOX_DEFAULT
	applymovement LOCALID_GIRL, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LittlerootTown_ProfessorBirchsLabText_Girl:
	.string "POKéMON are so interesting!\p"
	.string "I can't wait to go on my own journey\n"
	.string "with them!$"

LittlerootTown_ProfessorBirchsLab_EventScript_Boy::
	lock
	faceplayer
	msgbox LittlerootTown_ProfessorBirchsLabText_Boy, MSGBOX_DEFAULT
	applymovement LOCALID_BOY, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LittlerootTown_ProfessorBirchsLabText_Boy:
	.string "I want to become a POKéMON\n"
	.string "trainer one day.\p"
	.string "But there sure is a lot to study!$"

LittlerootTown_ProfessorBirchsLab_EventScript_Birch::
	lock
	faceplayer
	goto_if_eq VAR_BIRCH_LAB_STATE, 3, LittlerootTown_ProfessorBirchsLab_EventScript_BirchRustburo
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_BirchRustburo:
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BirchRustburo, MSGBOX_DEFAULT
	release
	end

LittlerootTown_ProfessorBirchsLab_Text_BirchRustburo:
	.string "BIRCH: STEVEN is at the DEVON CORP.\n"
	.string "in RUSTBURO.\p"
	.string "You can get there via PETALBURG\n"
	.string "or MAUVILLE.$"

LittlerootTown_ProfessorBirchsLab_EventScript_Machine::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_SeriousLookingMachine, MSGBOX_SIGN
	end

LittlerootTown_ProfessorBirchsLab_EventScript_PC::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_PCUsedForResearch, MSGBOX_SIGN
	end

LittlerootTown_ProfessorBirchsLab_EventScript_Bookshelf::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_CrammedWithBooksOnPokemon, MSGBOX_SIGN
	end

LittlerootTown_ProfessorBirchsLab_EventScript_Book::
	msgbox LittlerootTown_ProfessorBirchsLab_Text_Book, MSGBOX_SIGN
	end

LittlerootTown_ProfessorBirchsLab_Text_WantGiveNickname:
	.string "You can give that {STR_VAR_1}\n"
	.string "a nickname if you'd like.$"

LittlerootTown_ProfessorBirchsLab_Text_SeriousLookingMachine:
	.string "It's a serious-looking machine.\n"
	.string "The PROF must use this for research.$"

LittlerootTown_ProfessorBirchsLab_Text_PCUsedForResearch:
	.string "It's a PC used for research.\n"
	.string "Better not mess around with it.$"

LittlerootTown_ProfessorBirchsLab_Text_CrammedWithBooksOnPokemon:
	.string "It's crammed with books on POKéMON.$"

LittlerootTown_ProfessorBirchsLab_Text_Book:
	.string "It's a book on POKéMON. It's full of\n"
	.string "dense language.$"
