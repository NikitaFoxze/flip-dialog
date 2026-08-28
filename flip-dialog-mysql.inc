/*

	About: module flip-dialog for mysql
	Version: 1.0.0
	Author: Foxze

*/

#if defined _flip_dialog_mysql_included
	#endinput
#endif

#define _flip_dialog_mysql_included

/*
	flip-dialog
*/

#tryinclude "flip-dialog"
#tryinclude <flip-dialog>

#if !defined DialogPagin_Open
	#error flip-dialog library not found for flip-dialog-mysql
#endif

/*
	MySQL
*/

#tryinclude "a_mysql"
#tryinclude <a_mysql>

#if !defined mysql_format
	#error a_mysql library not found for flip-dialog-mysql
#endif

/*
	Defines
*/

#if !defined FDIALOG_MAX_MYSQL_SIZE
	#define FDIALOG_MAX_MYSQL_SIZE MAX_LENGTH_FORMAT
#endif

/*
	Vars
*/

static
	gDialogFunction[MAX_PLAYERS][MAX_FUNCTION_NAME + 1],
	gPaginQuery[MAX_PLAYERS][FDIALOG_MAX_MYSQL_SIZE + 1],
	gPaginOffset[MAX_PLAYERS],
	MySQL:gPaginHandle[MAX_PLAYERS];

/*
	Functions
*/

stock DPMySQL_Open(playerid, const function[], DIALOG_STYLE:style, max_lines_on_page, MySQL:handle, const query[], const caption[], dialog_pagin_args<>)
{
	if (handle == MYSQL_INVALID_HANDLE) {
		printf("flip-dialog-mysql [%s]: incorrect handle %i", function, _:handle);
		return 0;
	}

	if (isnull(query)) {
		printf("flip-dialog-mysql [%s]: incorrect query", function);
		return 0;
	}

	DialogPagin_SetMode(playerid, FDIALOG_MODE_MANUAL);

	gPaginOffset[playerid] = 0;
	gPaginHandle[playerid] = handle;

	gDialogFunction[playerid] = "dre_";
	strcat(gDialogFunction[playerid], function);

	gPaginQuery[playerid][0] = '\0';
	strcat(gPaginQuery[playerid], query);

	static
		string_caption[FDIALOG_MAX_FORMAT_STRING + 1];

#if defined MDIALOG_ZLANG_MODE
	Lang_GetPlayerText(playerid, caption, string_caption);
#else
	_MPagin_strcpy(string_caption, caption);
#endif

	if (numargs() > 7) {
		DialogPagin_format(string_caption, sizeof(string_caption), string_caption, dialog_pagin_start<7>);
	}

	return DialogPagin_Open(playerid, Dialog:DialogPaginMySQL, style, max_lines_on_page, string_caption);
}

DialogResponse:DialogPaginMySQL(playerid, response, listitem, inputtext[])
{
	switch (response) {
		case FDIALOG_RESPONSE_INIT: {
			gPaginOffset[playerid] = 0;
			_FDialog_SendQuery(playerid, 0);
			return 1;
		}
		case FDIALOG_RESPONSE_NEXT_PAGE: {
			gPaginOffset[playerid] += DialogPagin_GetMaxLinesOnPage(playerid);
			_FDialog_SendQuery(playerid, gPaginOffset[playerid]);
			return 1;
		}
		case FDIALOG_RESPONSE_BACK_PAGE: {
			gPaginOffset[playerid] -= DialogPagin_GetMaxLinesOnPage(playerid);

			if (gPaginOffset[playerid] < 0) {
				gPaginOffset[playerid] = 0;
			}

			_FDialog_SendQuery(playerid, gPaginOffset[playerid]);
			return 1;
		}
	}
	return CallLocalFunction(gDialogFunction[playerid], "ddds", playerid, response, listitem, "\0");
}

static stock _FDialog_SendQuery(playerid, offset)
{
	static
		query[FDIALOG_MAX_MYSQL_SIZE + 1],
		MySQL:handle;

	handle = gPaginHandle[playerid];

	mysql_format(handle, query, sizeof(query),
		"%s LIMIT %i, %i",
		gPaginQuery[playerid], offset, DialogPagin_GetMaxLinesOnPage(playerid) + 1);

	mysql_tquery(handle, query, gDialogFunction[playerid], "ddds", playerid, FDIALOG_RESPONSE_LOAD_DATA, 0, "\0");
}