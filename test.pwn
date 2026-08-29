#include <a_samp>
#include <Pawn.CMD>

#define FDIALOG_TEXT_EMPTY "{FFFFFF}Empty..."
#define FDIALOG_TEXT_SELECT "O"
#define FDIALOG_TEXT_CLOSE "X"
#define FDIALOG_TEXT_NUMERATION "[%i]"
#define FDIALOG_MESSAGE_TEXT_NEXT "››"
#define FDIALOG_MESSAGE_TEXT_BACK "‹‹"
#define FDIALOG_LIST_TEXT_NEXT "{A0A0A0}>>>"
#define FDIALOG_LIST_TEXT_BACK "{A0A0A0}<<<"

#include <flip-dialog>

new nicknames[][MAX_PLAYER_NAME + 1] = 
	{
		"Foxze", "Ziggi", "Nexius", "Neuty", "Kalcor",
		"Kocmoc", "DELIVER", "Roberto_Coluccio", "Artem_Gorden",
		"Danil_Marciface", "VanilaSW", "Dima_Rendi", "Fix_Unvardo", "Itsuki_Yorimoto",
		"Flatt_Delx", "Fredorico_Viton", "Demetrio_Santini", "Maks_Anurov",
		"Vladislav_Barsov", "Doni_Visage", "Richi_Klay", "Sebastian_Undeground"
	};

/*
	Basic usage
*/

CMD:fdtest1(playerid)
{
	for (new i; i < sizeof(nicknames); i++) {
		DialogPagin_AddLine(playerid, 0xFF6347FF, // 0x00000000 - removes numbering
			"{FFFFFF}Nickname - %s",
			nicknames[i]);
	}

	DialogPagin_Open(playerid, Dialog:TestDialog1, DIALOG_STYLE_LIST, 10,
		"{FF6347}Basic usage");

	return 1;
}

DialogResponse:TestDialog1(playerid, response, listitem, inputtext[])
{
	if (!response) {
		return 1;	
	}
	return 1;
}

/*
	Basic usage | Message
*/

CMD:fdtest2(playerid)
{
	for (new i; i < sizeof(nicknames); i++) {
		DialogPagin_AddLine(playerid, 0x00000000,
			"{FFFFFF}%s",
			nicknames[i]);
	}

	DialogPagin_Open(playerid, Dialog:TestDialog2, DIALOG_STYLE_MSGBOX, 5,
		"{FF6347}Basic usage | Message");

	return 1;
}

DialogResponse:TestDialog2(playerid, response, listitem, inputtext[])
{
	if (!response) {
		return 1;	
	}
	return 1;
}

/*
	Static lines
*/

CMD:fdtest3(playerid)
{
	DialogPagin_AddStaticLine(playerid, 0xFFAC55FF,
		"{FFFFFF}Tab 1");

	DialogPagin_AddStaticLine(playerid, 0xFFAC55FF,
		"{FFFFFF}Tab 2");

	DialogPagin_AddStaticLine(playerid, 0xFFAC55FF,
		"{FFFFFF}Tab 3");

	for (new i; i < sizeof(nicknames); i++) {
		DialogPagin_AddLine(playerid, 0xFF6347FF,
			"{FFFFFF}%s", nicknames[i]);
	}

	DialogPagin_Open(playerid, Dialog:TestDialog3, DIALOG_STYLE_LIST, 6,
		"{FF6347}Static lines");

	return 1;
}

DialogResponse:TestDialog3(playerid, response, listitem, inputtext[])
{
	if (!response) {
		return 1;	
	}

	if (DialogPagin_IsFirstPage(playerid)) {
		switch (listitem) {
			case 0: {
				SendClientMessage(playerid, -1, "Tab 1");
				return 1;
			}
			case 1: {
				SendClientMessage(playerid, -1, "Tab 2");
				return 1;
			}
			case 2: {
				SendClientMessage(playerid, -1, "Tab 3");
				return 1;
			}
		}
	}
	return 1;
}

/*
	Data storage for lines
*/

CMD:fdtest4(playerid)
{
	for (new i; i < sizeof(nicknames); i++) {
		DialogPagin_AddLine(playerid, 0xFF6347FF,
			"{FFFFFF}Name - %s", nicknames[i]);

		DialogPagin_SetLineName(playerid,
			nicknames[i]);
	}

	DialogPagin_Open(playerid, Dialog:TestDialog4, DIALOG_STYLE_LIST, 10,
		"{FF6347}Data storage for lines");

	return 1;
}

DialogResponse:TestDialog4(playerid, response, listitem, inputtext[])
{
	if (!response) {
		return 1;	
	}

	new
		string[64],
		playerName[MAX_PLAYER_NAME + 1];

	DialogPagin_GetSelectLineName(playerid, playerName);

	format(string, sizeof(string), "Select %s", playerName);
	SendClientMessage(playerid, 0xFFFFFFFF, string);
	return 1;
}

/*
	Manual mode
*/

new
	test_offset[MAX_PLAYERS];

CMD:fdtest5(playerid)
{
	DialogPagin_SetMode(playerid, FDIALOG_MODE_MANUAL);

	DialogPagin_Open(playerid, Dialog:TestDialog5, DIALOG_STYLE_LIST, 6,
		"{FF6347}Manual mode");

	return 1;
}

DialogResponse:TestDialog5(playerid, response, listitem, inputtext[])
{
	new
		start_offset,
		next_offset,
		max_lines_on_page = DialogPagin_GetMaxLinesOnPage(playerid);

	switch (response) {
		case FDIALOG_RESPONSE_CLOSE: {
			return 1;
		}
		case FDIALOG_RESPONSE_SELECT: {
			return 1;
		}
		case FDIALOG_RESPONSE_INIT: {
			start_offset = 0;
			next_offset = max_lines_on_page;

			test_offset[playerid] = start_offset;
		}
		case FDIALOG_RESPONSE_NEXT_PAGE: {
			start_offset = test_offset[playerid] + max_lines_on_page;
			next_offset = start_offset + max_lines_on_page;

			test_offset[playerid] = start_offset;
		}
		case FDIALOG_RESPONSE_BACK_PAGE: {
			start_offset = test_offset[playerid] - max_lines_on_page;

			if (start_offset < 0) {
				start_offset = 0;
			}

			next_offset = start_offset + max_lines_on_page;
			test_offset[playerid] = start_offset;
		}
	}

	new
		total_lines = sizeof(nicknames);

	for (new i = start_offset; i < next_offset && i < total_lines; i++) {
		DialogPagin_AddLine(playerid, 0xFF6347FF,
			"{FFFFFF}%s",
			nicknames[i]);
	}

	DialogPagin_ProcessManual(playerid, total_lines);
	return 1;
}

/*
	Monster
*/

new
	test_offset2[MAX_PLAYERS];

CMD:fdtest6(playerid)
{
	DialogPagin_SetMode(playerid, FDIALOG_MODE_MANUAL);

	DialogPagin_AddStaticLine(playerid, 0xFFAC55FF,
		"{FFFFFF}Tab 1");

	DialogPagin_AddStaticLine(playerid, 0xFFAC55FF,
		"{FFFFFF}Tab 2");

	DialogPagin_AddStaticLine(playerid, 0xFFAC55FF,
		"{FFFFFF}Tab 3");

	DialogPagin_SetTablist(playerid, "{FF6347}Name\t{FF6347}Date");

	DialogPagin_Open(playerid, Dialog:TestDialog6, DIALOG_STYLE_TABLIST_HEADERS, 6,
		"{FF6347}Monster");

	return 1;
}

DialogResponse:TestDialog6(playerid, response, listitem, inputtext[])
{
	new
		start_offset,
		next_offset,
		max_lines_on_page = DialogPagin_GetMaxLinesOnPage(playerid);

	switch (response) {
		case FDIALOG_RESPONSE_CLOSE: {
			return 1;
		}
		case FDIALOG_RESPONSE_SELECT: {
			if (DialogPagin_IsFirstPage(playerid)) {
				switch (listitem) {
					case 0: {
						SendClientMessage(playerid, -1, "Tab 1");
						return 1;
					}
					case 1: {
						SendClientMessage(playerid, -1, "Tab 2");
						return 1;
					}
					case 2: {
						SendClientMessage(playerid, -1, "Tab 3");
						return 1;
					}
				}
			}

			new
				string[64],
				playerName[MAX_PLAYER_NAME + 1];

			DialogPagin_GetSelectLineName(playerid, playerName);

			format(string, sizeof(string), "Select %s", playerName);
			SendClientMessage(playerid, 0xFFFFFFFF, string);
			return 1;
		}
		case FDIALOG_RESPONSE_INIT: {
			start_offset = 0;
			next_offset = max_lines_on_page;

			test_offset2[playerid] = start_offset;
		}
		case FDIALOG_RESPONSE_NEXT_PAGE: {
			start_offset = test_offset2[playerid] + max_lines_on_page;
			next_offset = start_offset + max_lines_on_page;

			test_offset2[playerid] = start_offset;
		}
		case FDIALOG_RESPONSE_BACK_PAGE: {
			start_offset = test_offset2[playerid] - max_lines_on_page;

			if (start_offset < 0) {
				start_offset = 0;
			}

			next_offset = start_offset + max_lines_on_page;
			test_offset2[playerid] = start_offset;
		}
	}

	new
		total_lines = sizeof(nicknames);

	for (new i = start_offset; i < next_offset && i < total_lines; i++) {
		DialogPagin_AddLine(playerid, 0xFF6347FF,
			"{FFFFFF}%s\t[2001-01-01 01:01:01]",
			nicknames[i]);

		DialogPagin_SetLineName(playerid,
			nicknames[i]);
	}

	DialogPagin_ProcessManual(playerid, total_lines);
	return 1;
}

/*
	ReOpen
*/

CMD:fdtest7(playerid)
{
	DialogPagin_ReOpen(playerid);
	return 1;
}
