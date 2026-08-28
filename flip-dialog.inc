/*

	About: pagination system for dialog
	Version: 1.0.0
	Author: Foxze

*/

#if defined _flip_dialog_included
	#endinput
#endif

#define _flip_dialog_included

/*
	mdialog
*/

#tryinclude "mdialog"
#tryinclude <mdialog>

/*
	Defines
*/

#if !defined MAX_FUNCTION_NAME
	#define MAX_FUNCTION_NAME 32
#endif

#if !defined MAX_LENGTH_FORMAT
	#define MAX_LENGTH_FORMAT 4096
#endif

#if !defined FDIALOG_DIALOG_ID
	#define FDIALOG_DIALOG_ID 32700
#endif

#if !defined FDIALOG_MAX_STATIC_LINES
	#define FDIALOG_MAX_STATIC_LINES 10
#endif

#if !defined FDIALOG_MAX_LINES
	#define FDIALOG_MAX_LINES 500
#endif

#if !defined FDIALOG_COLOR_NONE
	#define FDIALOG_COLOR_NONE 0x00000000
#endif

#if !defined FDIALOG_MAX_FORMAT_STRING
	#define FDIALOG_MAX_FORMAT_STRING 144
#endif

#if !defined FDIALOG_MAX_LINE_SIZE
	#define FDIALOG_MAX_LINE_SIZE 288
#endif

#if !defined FDIALOG_MAX_INFO_SIZE
	#define FDIALOG_MAX_INFO_SIZE MAX_LENGTH_FORMAT
#endif

#if !defined FDIALOG_MAX_COLOR_SIZE
	#define FDIALOG_MAX_COLOR_SIZE 8
#endif

#if !defined FDIALOG_INVALID_LINE_ID
	#define FDIALOG_INVALID_LINE_ID (-1)
#endif

#if !defined FDIALOG_MAX_LINE_NAME
	#define FDIALOG_MAX_LINE_NAME 144
#endif

#if !defined FDIALOG_STYLE_MESSAGE
	#define FDIALOG_STYLE_MESSAGE \
		DIALOG_STYLE_MSGBOX
#endif

#if !defined FDIALOG_STYLE_LIST
	#define FDIALOG_STYLE_LIST \
		DIALOG_STYLE_LIST, \
		DIALOG_STYLE_TABLIST, \
		DIALOG_STYLE_TABLIST_HEADERS
#endif

// pagination texts
#if !defined FDIALOG_TEXT_EMPTY
	#define FDIALOG_TEXT_EMPTY "{FFFFFF}Empty..."
#endif

#if !defined FDIALOG_TEXT_SELECT
	#define FDIALOG_TEXT_SELECT "O"
#endif

#if !defined FDIALOG_TEXT_CLOSE
	#define FDIALOG_TEXT_CLOSE "X"
#endif

#if !defined FDIALOG_TEXT_NUMERATION
	#define FDIALOG_TEXT_NUMERATION "[%i]"
#endif

#if !defined FDIALOG_MESSAGE_TEXT_NEXT
	#define FDIALOG_MESSAGE_TEXT_NEXT "››"
#endif

#if !defined FDIALOG_MESSAGE_TEXT_BACK
	#define FDIALOG_MESSAGE_TEXT_BACK "‹‹"
#endif

#if !defined FDIALOG_LIST_TEXT_NEXT
	#define FDIALOG_LIST_TEXT_NEXT "{A0A0A0}>>>"
#endif

#if !defined FDIALOG_LIST_TEXT_BACK
	#define FDIALOG_LIST_TEXT_BACK "{A0A0A0}<<<"
#endif

#if defined MDIALOG_ZLANG_MODE
	#if FDIALOG_MAX_FORMAT_STRING > MAX_LANG_FORMAT_STRING
		#undef FDIALOG_MAX_FORMAT_STRING
		#define FDIALOG_MAX_FORMAT_STRING MAX_LANG_FORMAT_STRING
	#endif

	#if FDIALOG_MAX_INFO_SIZE > MAX_LANG_MVALUE_STRING
		#undef FDIALOG_MAX_INFO_SIZE
		#define FDIALOG_MAX_INFO_SIZE MAX_LANG_MVALUE_STRING
	#endif
#endif

#if !defined isnull
	#define isnull(%1) \
		((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif

#if !defined DialogResponse
	#define DialogResponse:%0(%1) \
		forward dre_%0(%1); \
		public dre_%0(%1)
#endif

#if !defined Dialog
	#define Dialog: #
#endif

#if !defined _INC_open_mp
	#if !defined DIALOG_STYLE
		#define DIALOG_STYLE: _:
	#endif
#endif

#define dialog_pagin_args<%0> {Float, _}:...
#define dialog_pagin_start<%0> (dialog_pagin_:(%0))

/*
	Enums
*/

enum E_FDIALOG_PAGINATION_DATA {
	e_fpMode,
	e_fpPreviousMode,
	e_fpRowCount,
	e_fpPreviousRowCount,
	e_fpListOffset,
	e_fpTotalLines,
	e_fpLinesOnPage,
	e_fpTotalStaticLines,
	e_fpStaticLinesOnPage,
	e_fpMaxLinesOnPage,
	bool:e_fpIsInitLines,
	bool:e_fpPreviousIsInitLines,
	bool:e_fpIsInitStaticLines,
	bool:e_fpPreviousIsInitStaticLines,
	bool:e_fpIsButtonNext,
	bool:e_fpIsButtonBack,
	bool:e_fpIsProcessResponse
};

enum {
	FDIALOG_MODE_AUTO = 0,
	FDIALOG_MODE_MANUAL
};

enum {
	FDIALOG_RESPONSE_CLOSE = 0,
	FDIALOG_RESPONSE_SELECT,
	FDIALOG_RESPONSE_INIT,
	FDIALOG_RESPONSE_NEXT_PAGE,
	FDIALOG_RESPONSE_BACK_PAGE,
	// For async data and others...
	FDIALOG_RESPONSE_LOAD_DATA
};

enum {
	FDIALOG_PAGE_OPEN = 0,
	FDIALOG_PAGE_NEXT,
	FDIALOG_PAGE_BACK,
	FDIALOG_PAGE_CURRENT
};

enum {
	FDIALOG_BUTTON_1 = 0,
	FDIALOG_BUTTON_2
};

/*
	Vars
*/

static
	gPaginData[MAX_PLAYERS][E_FDIALOG_PAGINATION_DATA];

static
	gIsDialogOpen[MAX_PLAYERS char],
	gDialogFunction[MAX_PLAYERS][MAX_FUNCTION_NAME + 1],
	gDialogPreviousFunction[MAX_PLAYERS][MAX_FUNCTION_NAME + 1],
	DIALOG_STYLE:gDialogStyle[MAX_PLAYERS],
	gDialogCaption[MAX_PLAYERS][FDIALOG_MAX_FORMAT_STRING + 1],
	gDialogButton1[MAX_PLAYERS][FDIALOG_MAX_FORMAT_STRING + 1],
	gDialogButton2[MAX_PLAYERS][FDIALOG_MAX_FORMAT_STRING + 1];

static
	bool:gIsInitLinesID[MAX_PLAYERS char],
	bool:gIsPreviousInitLinesID[MAX_PLAYERS char],
	gTotalLinesID[MAX_PLAYERS],
	gListLineID[MAX_PLAYERS][FDIALOG_MAX_LINES],
	gSelectLineID[MAX_PLAYERS];

static
	bool:gIsInitLinesName[MAX_PLAYERS char],
	bool:gIsPreviousInitLinesName[MAX_PLAYERS char],
	gTotalLinesName[MAX_PLAYERS],
	gListLineName[MAX_PLAYERS][FDIALOG_MAX_LINES][FDIALOG_MAX_LINE_NAME + 1],
	gSelectLineName[MAX_PLAYERS][FDIALOG_MAX_LINE_NAME + 1];

static
	gTablistBuffer[MAX_PLAYERS][FDIALOG_MAX_LINE_SIZE + 1],
	gLineBuffer[MAX_PLAYERS][FDIALOG_MAX_LINES][FDIALOG_MAX_LINE_SIZE + 1],
	gStaticLineBuffer[MAX_PLAYERS][FDIALOG_MAX_STATIC_LINES][FDIALOG_MAX_LINE_SIZE + 1],
	gDialogBuffer[MAX_PLAYERS][FDIALOG_MAX_INFO_SIZE + 1];

/*
	OnGameModeInit
*/

public OnGameModeInit()
{
	for (new i = 0; i < MAX_PLAYERS; i++) {
		_FDialog_ClearData(i);
	}

	#if defined FDialog_OnGameModeInit
		return FDialog_OnGameModeInit();
	#else
		return 1;
	#endif
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit FDialog_OnGameModeInit
#if defined FDialog_OnGameModeInit
	forward FDialog_OnGameModeInit();
#endif

/*
	OnPlayerConnect
*/

public OnPlayerConnect(playerid)
{
	DialogPagin_ResetData(playerid);

	#if defined FDialog_OnPlayerConnect
		return FDialog_OnPlayerConnect(playerid);
	#else
		return 1;
	#endif
}

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect FDialog_OnPlayerConnect
#if defined FDialog_OnPlayerConnect
	forward FDialog_OnPlayerConnect(playerid);
#endif

#if defined _mdialog_included

/*
	DialogPagin
*/

DialogResponse:DialogPagin(playerid, response, listitem, inputtext[])
{
	if(!_FDialog_ProcessResponse(playerid, response, listitem)) {
		return 0;
	}

	static
		temp[128];

	_FDialog_strcpy(temp, inputtext);
	return CallLocalFunction(gDialogPreviousFunction[playerid], "ddds", playerid, response, listitem, temp);
}

/*
	Dialog_Show
*/

stock DialogPagin_Show(playerid, const function[])
{
	if (gPaginData[playerid][e_fpIsProcessResponse]) {
		DialogPagin_ResetData(playerid);
	}

    return Dialog_Show(playerid, function);
}

#if defined _ALS_Dialog_Show
    #undef Dialog_Show
#else
    #define _ALS_Dialog_Show
#endif
#define Dialog_Show DialogPagin_Show

#else

/*
	OnDialogResponse
*/

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	static temp[128];
	_FDialog_strcpy(temp, inputtext);

	if (dialogid == FDIALOG_DIALOG_ID) {
		if (DialogPagin_IsOpen(playerid)) {
			if(!_FDialog_ProcessResponse(playerid, response, listitem)) {
				return 0;
			}
			return CallLocalFunction(gDialogPreviousFunction[playerid], "ddds", playerid, response, listitem, "\1");
		}
		return 0;
	}

	#if defined FDialog_OnDialogResponse
		return FDialog_OnDialogResponse(playerid, dialogid, response, listitem, temp);
	#else
		return 0;
	#endif
}

#if defined _ALS_OnDialogResponse
	#undef OnDialogResponse
#else
	#define _ALS_OnDialogResponse
#endif
#define OnDialogResponse FDialog_OnDialogResponse
#if defined FDialog_OnDialogResponse
	forward FDialog_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif

/*
	FDialogFix_ShowPlayerDialog
*/

#if !defined FIX_const
	#define FIX_const 0
	#define MDIALOG_FIX_CLEAR
#endif

native FDialogFix_ShowPlayerDialog(playerid, dialogid, style, const caption[], const info[], const button1[], const button2[]) = ShowPlayerDialog;

#if !FIX_const
	#if defined _ALS_ShowPlayerDialog
		#undef ShowPlayerDialog
	#else
		#define _ALS_ShowPlayerDialog
	#endif

	#define ShowPlayerDialog FDialogFix_ShowPlayerDialog

	#if defined MDIALOG_FIX_CLEAR
		#undef MDIALOG_FIX_CLEAR
		#undef FIX_const
	#endif
#endif

#endif

/*
	ShowPlayerDialog
*/

stock FDialog_ShowPlayerDialog(playerid, dialogid, style, const caption[], const info[], const button1[], const button2[])
{
	if (gPaginData[playerid][e_fpIsProcessResponse]) {
		DialogPagin_ResetData(playerid);
	}

	return ShowPlayerDialog(playerid, dialogid, style, caption, info, button1, button2);
}

#if defined _ALS_ShowPlayerDialog
	#undef ShowPlayerDialog
#else
	#define _ALS_ShowPlayerDialog
#endif
#define ShowPlayerDialog FDialog_ShowPlayerDialog

/*
	Functions
*/

stock DialogPagin_Open(playerid, const function[], DIALOG_STYLE:style, max_lines_on_page, const caption[], dialog_pagin_args<>)
{
	if (isnull(function)) {
		return 0;
	}

	if (!_FDialog_IsValidStyle(style)) {
		return 0;
	}

	gDialogStyle[playerid] = style;

	gDialogFunction[playerid] = "dre_";
	gDialogPreviousFunction[playerid] = "dre_";

	strcat(gDialogFunction[playerid], function);
	strcat(gDialogPreviousFunction[playerid], function);

	gPaginData[playerid][e_fpMaxLinesOnPage] = max_lines_on_page;
	gPaginData[playerid][e_fpPreviousIsInitStaticLines] = gPaginData[playerid][e_fpIsInitStaticLines];

	static
		string_caption[FDIALOG_MAX_FORMAT_STRING + 1];

#if defined MDIALOG_ZLANG_MODE
	Lang_GetPlayerText(playerid, caption, string_caption);
#else
	_FDialog_strcpy(string_caption, caption);
#endif

	if (numargs() > 5) {
		DialogPagin_format(string_caption, sizeof(string_caption), string_caption, dialog_pagin_start<5>);
	}

	_FDialog_strcpy(gDialogCaption[playerid], string_caption, sizeof(gDialogCaption[]));

	if (gPaginData[playerid][e_fpMode] == FDIALOG_MODE_AUTO) {
		return _FDialog_ProcessPagination(playerid, FDIALOG_PAGE_OPEN);
	}
	else {
		return CallLocalFunction(gDialogFunction[playerid], "ddds", playerid, FDIALOG_RESPONSE_INIT, 0, "\1");
	}
}

stock DialogPagin_AddLine(playerid, color, const text[], dialog_pagin_args<>)
{
	if (!gPaginData[playerid][e_fpIsInitLines]) {
		gPaginData[playerid][e_fpIsInitLines] = true;
		gPaginData[playerid][e_fpTotalLines] = 0;
	}

	if (gPaginData[playerid][e_fpTotalLines] >= FDIALOG_MAX_LINES) {
		return 0;
	}

	if (gPaginData[playerid][e_fpIsProcessResponse]) {
		gPaginData[playerid][e_fpIsProcessResponse] = false;
		gPaginData[playerid][e_fpRowCount] = gPaginData[playerid][e_fpPreviousRowCount];
	}

	static
		temp[FDIALOG_MAX_LINE_SIZE + 1];

#if defined MDIALOG_ZLANG_MODE
	Lang_GetPlayerText(playerid, text, temp);
#else
	_FDialog_strcpy(temp, text);
#endif

	if (numargs() > 3) {
		DialogPagin_format(temp, sizeof(temp), temp, dialog_pagin_start<3>);
	}

	if (color != FDIALOG_COLOR_NONE) {
		static
			number,
			previous_color,
			string_nums[FDIALOG_MAX_COLOR_SIZE + 11],
			string_color[FDIALOG_MAX_COLOR_SIZE + 1];

		number = gPaginData[playerid][e_fpRowCount] + 1;

		// Optimization
		if (previous_color != color) {
			previous_color = color;
			_FDialog_IntToHex(string_color, color);
		}

		format(string_nums, sizeof(string_nums),
			"%s"FDIALOG_TEXT_NUMERATION" ",
			string_color,
			number);

		strins(temp, string_nums, 0);
	}

	strcat(temp, "\n");
	_FDialog_strcpy(gLineBuffer[playerid][gPaginData[playerid][e_fpTotalLines]], temp);

	gPaginData[playerid][e_fpTotalLines]++;
	gPaginData[playerid][e_fpRowCount]++;
	return 1;
}

stock DialogPagin_AddStaticLine(playerid, color, const text[], dialog_pagin_args<>)
{
	if (!gPaginData[playerid][e_fpIsInitStaticLines]) {
		gPaginData[playerid][e_fpIsInitStaticLines] = true;
		gPaginData[playerid][e_fpTotalStaticLines] = 0;
	}

	if (gPaginData[playerid][e_fpTotalStaticLines] >= FDIALOG_MAX_STATIC_LINES) {
		return 0;
	}

	static
		temp[FDIALOG_MAX_LINE_SIZE + 1];

#if defined MDIALOG_ZLANG_MODE
	Lang_GetPlayerText(playerid, text, temp);
#else
	_FDialog_strcpy(temp, text);
#endif

	if (numargs() > 3) {
		DialogPagin_format(temp, sizeof(temp), temp, dialog_pagin_start<3>);
	}

	if (color != FDIALOG_COLOR_NONE) {
		static
			previous_color,
			string_nums[FDIALOG_MAX_COLOR_SIZE + 11],
			string_color[FDIALOG_MAX_COLOR_SIZE + 1];

		// Optimization
		if (previous_color != color) {
			previous_color = color;
			_FDialog_IntToHex(string_color, color);
		}

		format(string_nums, sizeof(string_nums),
			"%s"FDIALOG_TEXT_NUMERATION" ",
			string_color,
			gPaginData[playerid][e_fpTotalStaticLines] + 1);

		strins(temp, string_nums, 0);
	}

	strcat(temp, "\n");

	_FDialog_strcpy(gStaticLineBuffer[playerid][gPaginData[playerid][e_fpTotalStaticLines]], temp);
	gPaginData[playerid][e_fpTotalStaticLines]++;
	return 1;
}

stock DialogPagin_SetTablist(playerid, const text[], dialog_pagin_args<>)
{
	static
		temp[FDIALOG_MAX_FORMAT_STRING + 1];

#if defined MDIALOG_ZLANG_MODE
	Lang_GetPlayerText(playerid, text, temp);
#else
	_FDialog_strcpy(temp, text);
#endif

	if (numargs() > 2) {
		DialogPagin_format(temp, sizeof(temp), temp, dialog_pagin_start<2>);
	}

	strcat(temp, "\n");
	_FDialog_strcpy(gTablistBuffer[playerid], temp);
}

stock DialogPagin_SetLineID(playerid, abstractid)
{
	if (!gIsInitLinesID{playerid}) {
		gIsInitLinesID{playerid} = true;
		gTotalLinesID[playerid] = 0;
	}

	if (gTotalLinesID[playerid] >= FDIALOG_MAX_LINES) {
		return 0;
	}

	gListLineID[playerid][gTotalLinesID[playerid]] = abstractid;
	gTotalLinesID[playerid]++;
	return 1;
}

stock DialogPagin_GetSelectLineID(playerid)
{
	return gSelectLineID[playerid];
}

stock DialogPagin_SetLineName(playerid, const abstract_name[])
{
	if (!gIsInitLinesName{playerid}) {
		gIsInitLinesName{playerid} = true;
		gTotalLinesName[playerid] = 0;
	}

	if (gTotalLinesName[playerid] >= FDIALOG_MAX_LINES) {
		return 0;
	}

	_FDialog_strcpy(gListLineName[playerid][gTotalLinesName[playerid]], abstract_name);
	gTotalLinesName[playerid]++;
	return 1;
}

stock DialogPagin_GetSelectLineName(playerid, output[], const size = sizeof(output))
{
	_FDialog_strcpy(output, gSelectLineName[playerid], size);
}

stock DialogPagin_ChangeCaption(playerid, const text[], dialog_pagin_args<>)
{
	static
		temp[FDIALOG_MAX_FORMAT_STRING + 1];

#if defined MDIALOG_ZLANG_MODE
	Lang_GetPlayerText(playerid, text, temp);
#else
	_FDialog_strcpy(temp, text);
#endif

	if (numargs() > 2) {
		DialogPagin_format(temp, sizeof(temp), temp, dialog_pagin_start<2>);
	}

	strcat(temp, "\n");
	_FDialog_strcpy(gDialogCaption[playerid], temp);
}

stock DialogPagin_IsOpen(playerid, const function[] = "")
{
	if (isnull(function)) {
		return _:gIsDialogOpen{playerid};
	}

	if (!isnull(gDialogFunction[playerid]) && gIsDialogOpen{playerid} && strcmp(gDialogFunction[playerid][4], function) == 0) {
		return 1;
	}

	return 0;
}

stock DialogPagin_GetTotalLines(playerid)
{
	return gPaginData[playerid][e_fpTotalLines];
}

stock DialogPagin_GetMaxLinesOnPage(playerid)
{
	return gPaginData[playerid][e_fpMaxLinesOnPage];
}

stock DialogPagin_IsFirstPage(playerid)
{
	return (gPaginData[playerid][e_fpIsButtonBack] == false);
}

stock DialogPagin_IsLastPage(playerid)
{
	return (gPaginData[playerid][e_fpIsButtonNext] == false);
}

stock DialogPagin_ReOpen(playerid)
{
	gPaginData[playerid][e_fpIsProcessResponse] = false;

	_FDialog_RecoveryData(playerid);
	return _FDialog_ProcessPagination(playerid, FDIALOG_PAGE_CURRENT);
}

stock DialogPagin_SetMode(playerid, modeid)
{
	gPaginData[playerid][e_fpMode] = modeid;
	gPaginData[playerid][e_fpPreviousMode] = modeid;
}

stock DialogPagin_ProcessManual(playerid, total_lines = 0)
{
	gPaginData[playerid][e_fpIsProcessResponse] = false;

	static
		bool:is_next_page,
		bool:is_back_page;

	// Remove unnecessary lines from the counter, if available
	if (gPaginData[playerid][e_fpRowCount] > 0) {
		if (gPaginData[playerid][e_fpTotalLines] > gPaginData[playerid][e_fpMaxLinesOnPage]) {
			gPaginData[playerid][e_fpRowCount] -= gPaginData[playerid][e_fpTotalLines] - gPaginData[playerid][e_fpMaxLinesOnPage];
		}
	}

	// The first method is to find out if there is a next page.
	// It is recognized through one "extra" added line, which will no longer be used in the future.
	if (total_lines <= 0) {
		total_lines = gPaginData[playerid][e_fpMaxLinesOnPage] + 1;

		if (gPaginData[playerid][e_fpTotalLines] >= total_lines) {
			is_next_page = true;
		}
		else {
			is_next_page = false;
		}
	}
	// The second method is simply found out through the already known number of all lines.
	else {
		if (gPaginData[playerid][e_fpRowCount] < total_lines) {
			is_next_page = true;
		}
		else {
			is_next_page = false;
		}
	}

	is_back_page = (gPaginData[playerid][e_fpRowCount] > gPaginData[playerid][e_fpMaxLinesOnPage]);

	// Button - next
	if (is_next_page) {
		gPaginData[playerid][e_fpIsButtonNext] = true;
	}
	else {
		gPaginData[playerid][e_fpIsButtonNext] = false;
	}

	// Button - back
	if (is_back_page) {
		gPaginData[playerid][e_fpIsButtonBack] = true;
	}
	else {
		gPaginData[playerid][e_fpIsButtonBack] = false;
	}

	_FDialog_strcpy(gDialogFunction[playerid], gDialogPreviousFunction[playerid]);

	gPaginData[playerid][e_fpMode] = FDIALOG_MODE_MANUAL;
	gPaginData[playerid][e_fpIsInitStaticLines] = gPaginData[playerid][e_fpPreviousIsInitStaticLines];
	return _FDialog_ProcessPagination(playerid, FDIALOG_PAGE_OPEN);
}

stock DialogPagin_ResetData(playerid)
{
	gPaginData[playerid][e_fpIsProcessResponse] = false;
	_FDialog_ResetData(playerid);
}

static stock _FDialog_OpenDialog(playerid)
{
	gIsDialogOpen{playerid} = true;

#if defined _mdialog_included
	return Dialog_Open(playerid, Dialog:DialogPagin,
		gDialogStyle[playerid],
		gDialogCaption[playerid],
		gDialogBuffer[playerid],
		gDialogButton1[playerid],
		gDialogButton2[playerid]);
#else
#if defined MDIALOG_ZLANG_MODE
	static
		Lang:lang,
		temp_button1[FDIALOG_MAX_FORMAT_STRING + 1],
		temp_button2[FDIALOG_MAX_FORMAT_STRING + 1],
		temp_info[FDIALOG_MAX_INFO_SIZE + 1];

	lang = Lang_GetPlayerLang(playerid);

	Lang_GetText(lang, gDialogBuffer[playerid], temp_info);
	Lang_GetText(lang, gDialogButton1[playerid], temp_button1);

	if (!isnull(gDialogButton2[playerid])) {
		Lang_GetText(lang, gDialogButton2[playerid], temp_button2);
	} else {
		temp_button2[0] = '\0';
	}

	return ShowPlayerDialog(playerid, FDIALOG_DIALOG_ID,
		gDialogStyle[playerid],
		gDialogCaption[playerid],
		temp_info,
		temp_button1,
		temp_button2);
#else
	return ShowPlayerDialog(playerid, FDIALOG_DIALOG_ID,
		gDialogStyle[playerid],
		gDialogCaption[playerid],
		gDialogBuffer[playerid],
		gDialogButton1[playerid],
		gDialogButton2[playerid]);
#endif
#endif
}

static stock _FDialog_ResetData(playerid)
{
	gIsDialogOpen{playerid} = false;
	gDialogFunction[playerid][0] = '\0';

	gPaginData[playerid][e_fpMode] = FDIALOG_MODE_AUTO;
	gPaginData[playerid][e_fpRowCount] = 0;

	gPaginData[playerid][e_fpIsInitLines] =
	gPaginData[playerid][e_fpIsInitStaticLines] = false;

	gIsInitLinesID{playerid} =
	gIsInitLinesName{playerid} = false;
}

static stock _FDialog_CopyData(playerid)
{
	gPaginData[playerid][e_fpPreviousMode] = gPaginData[playerid][e_fpMode];
	gPaginData[playerid][e_fpPreviousRowCount] = gPaginData[playerid][e_fpRowCount];

	gPaginData[playerid][e_fpPreviousIsInitLines] = gPaginData[playerid][e_fpIsInitLines];
	gPaginData[playerid][e_fpPreviousIsInitStaticLines] = gPaginData[playerid][e_fpIsInitStaticLines];

	gIsPreviousInitLinesID{playerid} = gIsInitLinesID{playerid};
	gIsPreviousInitLinesName{playerid} = gIsInitLinesName{playerid};
}

static stock _FDialog_RecoveryData(playerid)
{
	_FDialog_strcpy(gDialogFunction[playerid], gDialogPreviousFunction[playerid]);

	gPaginData[playerid][e_fpMode] = gPaginData[playerid][e_fpPreviousMode];
	gPaginData[playerid][e_fpRowCount] = gPaginData[playerid][e_fpPreviousRowCount];

	gPaginData[playerid][e_fpIsInitLines] = gPaginData[playerid][e_fpPreviousIsInitLines];
	gPaginData[playerid][e_fpIsInitStaticLines] = gPaginData[playerid][e_fpPreviousIsInitStaticLines];

	gIsInitLinesID{playerid} = gIsPreviousInitLinesID{playerid};
	gIsInitLinesName{playerid} = gIsPreviousInitLinesName{playerid};
}

static stock _FDialog_ClearData(playerid)
{
	gIsDialogOpen{playerid} = false;
	gDialogFunction[playerid][0] =
	gDialogPreviousFunction[playerid][0] =
	gDialogCaption[playerid][0] =
	gDialogButton1[playerid][0] =
	gDialogButton2[playerid][0] = '\0';
	gDialogStyle[playerid] = DIALOG_STYLE:-1;

	gPaginData[playerid][e_fpMode] =
	gPaginData[playerid][e_fpPreviousMode] = FDIALOG_MODE_AUTO;
	gPaginData[playerid][e_fpRowCount] =
	gPaginData[playerid][e_fpPreviousRowCount] =
	gPaginData[playerid][e_fpListOffset] =
	gPaginData[playerid][e_fpTotalLines] =
	gPaginData[playerid][e_fpLinesOnPage] =
	gPaginData[playerid][e_fpTotalStaticLines] =
	gPaginData[playerid][e_fpStaticLinesOnPage] =
	gPaginData[playerid][e_fpMaxLinesOnPage] = 0;
	gPaginData[playerid][e_fpIsInitLines] =
	gPaginData[playerid][e_fpPreviousIsInitLines] =
	gPaginData[playerid][e_fpIsInitStaticLines] =
	gPaginData[playerid][e_fpPreviousIsInitStaticLines] =
	gPaginData[playerid][e_fpIsButtonNext] =
	gPaginData[playerid][e_fpIsButtonBack] = false;

	gIsInitLinesID{playerid} =
	gIsPreviousInitLinesID{playerid} =
	gIsInitLinesName{playerid} =
	gIsPreviousInitLinesName{playerid} = false;
	gTotalLinesID[playerid] =
	gTotalLinesName[playerid] = 0;
	gSelectLineID[playerid] = FDIALOG_INVALID_LINE_ID;
	gSelectLineName[playerid][0] = '\0';

	for(new i = 0; i < FDIALOG_MAX_LINES; i++) {
		gListLineID[playerid][i] = FDIALOG_INVALID_LINE_ID;
		gListLineName[playerid][i][0] =
		gLineBuffer[playerid][i][0] = '\0';
	}

	for(new i = 0; i < FDIALOG_MAX_STATIC_LINES; i++) {
		gStaticLineBuffer[playerid][i][0] = '\0';
	}

	gTablistBuffer[playerid][0] =
	gDialogBuffer[playerid][0] = '\0';
}

static stock _FDialog_ProcessPagination(playerid, pageid)
{
	static
		offset;

	offset = gPaginData[playerid][e_fpListOffset];

	switch (pageid) {
		case FDIALOG_PAGE_OPEN: {
			offset = 0;
		}
		case FDIALOG_PAGE_NEXT: {
			offset += gPaginData[playerid][e_fpMaxLinesOnPage];
		}
		case FDIALOG_PAGE_BACK: {
			offset -= gPaginData[playerid][e_fpMaxLinesOnPage];

			if (offset < 0) {
				offset = 0;
			}
		}
		case FDIALOG_PAGE_CURRENT: {
			return _FDialog_OpenDialog(playerid);
		}
	}

	gPaginData[playerid][e_fpListOffset] = offset;

	// Buttons
	if (gPaginData[playerid][e_fpMode] == FDIALOG_MODE_AUTO) {
		if (!((gPaginData[playerid][e_fpListOffset] + gPaginData[playerid][e_fpMaxLinesOnPage]) >= gPaginData[playerid][e_fpTotalLines])) {
			gPaginData[playerid][e_fpIsButtonNext] = true;
		}
		else {
			gPaginData[playerid][e_fpIsButtonNext] = false;
		}

		if (!(gPaginData[playerid][e_fpListOffset] <= 0)) {
			gPaginData[playerid][e_fpIsButtonBack] = true;
		}
		else {
			gPaginData[playerid][e_fpIsButtonBack] = false;
		}
	}

	_FDialog_ProcessText(playerid);
	return _FDialog_OpenDialog(playerid);
}

static stock _FDialog_ProcessText(playerid)
{
	gPaginData[playerid][e_fpLinesOnPage] =
	gPaginData[playerid][e_fpStaticLinesOnPage] = 0;

	gDialogBuffer[playerid][0] = '\0';

	static
		DIALOG_STYLE:style,
		bool:is_not_total_lines,
		bool:is_static_lines_on_page,
		bool:is_line_none;

	style = gDialogStyle[playerid];

	if (style == DIALOG_STYLE_TABLIST_HEADERS) {
		strcat(gDialogBuffer[playerid], gTablistBuffer[playerid]);
	}

	if (gPaginData[playerid][e_fpTotalLines] <= 0
	&& gPaginData[playerid][e_fpTotalStaticLines] <= 0) {
	#if defined MDIALOG_ZLANG_MODE
		static
			string_empty[FDIALOG_MAX_FORMAT_STRING + 1];

		if (Lang_GetPlayerText(playerid, FDIALOG_TEXT_EMPTY, string_empty)) {
			strcat(string_empty, "\n");
			strcat(gDialogBuffer[playerid], string_empty);
		}
		else {
			strcat(gDialogBuffer[playerid], ""FDIALOG_TEXT_EMPTY"\n");
		}
	#else
		strcat(gDialogBuffer[playerid], ""FDIALOG_TEXT_EMPTY"\n");
	#endif
		is_not_total_lines = true;
	}
	else {
		is_not_total_lines = false;
	}

	if (!is_not_total_lines) {
		is_static_lines_on_page = false;
		if (gPaginData[playerid][e_fpIsInitStaticLines]) {
			if (!gPaginData[playerid][e_fpIsButtonBack]) {
				if (gPaginData[playerid][e_fpTotalStaticLines] > 0) {
					is_static_lines_on_page = true;

					for (new i = 0; i < gPaginData[playerid][e_fpTotalStaticLines]; i++) {
						gPaginData[playerid][e_fpStaticLinesOnPage]++;
						strcat(gDialogBuffer[playerid], gStaticLineBuffer[playerid][i]);
					}
				}
			}
		}

		is_line_none = false;
		if (gPaginData[playerid][e_fpIsInitLines]) {
			static
				offset,
				count_showing_lines,
				total_count;

			offset = gPaginData[playerid][e_fpListOffset];
			count_showing_lines = gPaginData[playerid][e_fpListOffset] + gPaginData[playerid][e_fpMaxLinesOnPage];
			total_count = gPaginData[playerid][e_fpTotalLines];

			for (new i = offset; i < count_showing_lines; i++) {
				if (i >= total_count) {
					break;
				}

				if (is_static_lines_on_page) {
					if (!is_line_none) {
						strcat(gDialogBuffer[playerid], " \n");
						is_line_none = true;
					}
				}

				gPaginData[playerid][e_fpLinesOnPage]++;
				strcat(gDialogBuffer[playerid], gLineBuffer[playerid][i]);
			}
		}
	}

	// Buttons
	switch (style) {
		case FDIALOG_STYLE_LIST: {
			if (gPaginData[playerid][e_fpLinesOnPage] > 0) {
				if (gPaginData[playerid][e_fpIsButtonNext]) {
					#if defined MDIALOG_ZLANG_MODE
						static
							button_next[FDIALOG_MAX_FORMAT_STRING + 1];

						if (Lang_GetPlayerText(playerid, FDIALOG_LIST_TEXT_NEXT, button_next)) {
							strins(button_next, "\n", 0);
							strcat(gDialogBuffer[playerid], button_next);
						}
						else {
							strcat(gDialogBuffer[playerid], "\n"FDIALOG_LIST_TEXT_NEXT"");
						}
					#else
						strcat(gDialogBuffer[playerid], "\n"FDIALOG_LIST_TEXT_NEXT"");
					#endif
				}

				if (gPaginData[playerid][e_fpIsButtonBack]) {
					#if defined MDIALOG_ZLANG_MODE
						static
							button_back[FDIALOG_MAX_FORMAT_STRING + 1];

						if (Lang_GetPlayerText(playerid, FDIALOG_LIST_TEXT_BACK, button_back)) {
							strins(button_back, "\n", 0);
							strcat(gDialogBuffer[playerid], button_back);
						}
						else {
							strcat(gDialogBuffer[playerid], "\n"FDIALOG_LIST_TEXT_BACK"");
						}
					#else
						strcat(gDialogBuffer[playerid], "\n"FDIALOG_LIST_TEXT_BACK"");
					#endif
				}
			}
		}
	}

	_FDialog_GetButtonText(playerid, style, FDIALOG_BUTTON_1, gDialogButton1[playerid]);
	_FDialog_GetButtonText(playerid, style, FDIALOG_BUTTON_2, gDialogButton2[playerid]);
}

static stock _FDialog_ProcessButtons(playerid, &response, listitem)
{
	if (gPaginData[playerid][e_fpLinesOnPage] <= 0
	&& gPaginData[playerid][e_fpStaticLinesOnPage] <= 0) {
		response = FDIALOG_RESPONSE_CLOSE;
		return 1;
	}

	switch (gDialogStyle[playerid]) {
		case FDIALOG_STYLE_MESSAGE: {
			if (response) {
				if (gPaginData[playerid][e_fpIsButtonBack]) {
					response = FDIALOG_RESPONSE_BACK_PAGE;
				}
				else {
					response = FDIALOG_RESPONSE_CLOSE;
				}
			}
			else {
				if (gPaginData[playerid][e_fpIsButtonNext]) {
					response = FDIALOG_RESPONSE_NEXT_PAGE;
				}
				else {
					response = FDIALOG_RESPONSE_CLOSE;
				}
			}
		}
		case FDIALOG_STYLE_LIST: {
			if (!response) {
				response = FDIALOG_RESPONSE_CLOSE;
				return 1;
			}

			static
				lines_on_page,
				static_lines_on_page,
				button_position;

			lines_on_page = gPaginData[playerid][e_fpLinesOnPage];
			static_lines_on_page = gPaginData[playerid][e_fpStaticLinesOnPage];
			button_position = static_lines_on_page > 0 ? lines_on_page + static_lines_on_page + 1 : lines_on_page + static_lines_on_page;

			// Defining the next and back buttons
			if (listitem == button_position) {
				if (gPaginData[playerid][e_fpIsButtonNext]) {
					response = FDIALOG_RESPONSE_NEXT_PAGE;
				}
				else {
					response = FDIALOG_RESPONSE_BACK_PAGE;
				}
				return _FDialog_ReturnResponse(playerid, response);
			}
			else if (listitem == button_position + 1) {
				response = FDIALOG_RESPONSE_BACK_PAGE;
				return _FDialog_ReturnResponse(playerid, response);
			}

			response = FDIALOG_RESPONSE_SELECT;

			static
				index;

			if (static_lines_on_page > 0) {
				if (listitem < static_lines_on_page) {
					return 1;
				}
				else if (listitem == static_lines_on_page) {
					_FDialog_ProcessPagination(playerid, FDIALOG_PAGE_CURRENT);
					return 0;
				}

				index = gPaginData[playerid][e_fpListOffset] + listitem - static_lines_on_page - 1;
			}
			else {
				index = gPaginData[playerid][e_fpListOffset] + listitem;
			}

			if (gIsInitLinesID{playerid}
			&& gTotalLinesID[playerid] > 0) {
				gSelectLineID[playerid] = gListLineID[playerid][index];
			}

			if (gIsInitLinesName{playerid}
			&& gTotalLinesName[playerid] > 0) {
				_FDialog_strcpy(gSelectLineName[playerid], gListLineName[playerid][index]);
			}
		}
	}
	return _FDialog_ReturnResponse(playerid, response);
}

static stock _FDialog_ReturnResponse(playerid, response)
{
	if (gPaginData[playerid][e_fpMode] == FDIALOG_MODE_MANUAL) {
		switch (response) {
			case FDIALOG_RESPONSE_BACK_PAGE: {
				gPaginData[playerid][e_fpRowCount] -= gPaginData[playerid][e_fpLinesOnPage] + gPaginData[playerid][e_fpMaxLinesOnPage];

				if (gPaginData[playerid][e_fpRowCount] < 0) {
					gPaginData[playerid][e_fpRowCount] = 0;
				}
			}
		}
		return 1;
	}

	switch (response) {
		case FDIALOG_RESPONSE_NEXT_PAGE: {
			_FDialog_ProcessPagination(playerid, FDIALOG_PAGE_NEXT);
			return 0;
		}
		case FDIALOG_RESPONSE_BACK_PAGE: {
			_FDialog_ProcessPagination(playerid, FDIALOG_PAGE_BACK);
			return 0;
		}
	}
	return 1;
}

static stock _FDialog_ProcessResponse(playerid, &response, listitem)
{
	if (!_FDialog_ProcessButtons(playerid, response, listitem)) {
		return 0;
	}

	if (gPaginData[playerid][e_fpMode] == FDIALOG_MODE_MANUAL) {
		if (response != FDIALOG_RESPONSE_CLOSE
		&& response != FDIALOG_RESPONSE_SELECT) {
			gPaginData[playerid][e_fpIsProcessResponse] = true;
		}
	}

	_FDialog_CopyData(playerid);
	_FDialog_ResetData(playerid);
	return 1;
}

static stock _FDialog_GetButtonText(playerid, style, buttonid, output[], const size = sizeof(output))
{
	switch (style) {
		case FDIALOG_STYLE_MESSAGE: {
			if (buttonid == FDIALOG_BUTTON_1) {
				if (gPaginData[playerid][e_fpIsButtonBack]) {
					_FDialog_strcpy(output, FDIALOG_MESSAGE_TEXT_BACK, size);
				}
				else {
					_FDialog_strcpy(output, FDIALOG_TEXT_CLOSE, size);
				}
			}
			else {
				if (gPaginData[playerid][e_fpIsButtonNext]) {
					_FDialog_strcpy(output, FDIALOG_MESSAGE_TEXT_NEXT, size);
				}
				else {
					if (gPaginData[playerid][e_fpIsButtonBack]) {
						_FDialog_strcpy(output, FDIALOG_TEXT_CLOSE, size);
					}
					else {
						output[0] = '\0';
					}
				}
			}
		}
		case FDIALOG_STYLE_LIST: {
			if (gPaginData[playerid][e_fpLinesOnPage] > 0
			|| gPaginData[playerid][e_fpStaticLinesOnPage] > 0) {
				if (buttonid == FDIALOG_BUTTON_1) {
					_FDialog_strcpy(output, FDIALOG_TEXT_SELECT, size);
				}
				else {
					_FDialog_strcpy(output, FDIALOG_TEXT_CLOSE, size);
				}
			}
			else {
				if (buttonid == FDIALOG_BUTTON_1) {
					_FDialog_strcpy(output, FDIALOG_TEXT_CLOSE, size);
				}
				else {
					output[0] = '\0';
				}
			}
		}
	}
}

static stock _FDialog_IsValidStyle(style)
{
	switch (style) {
		case FDIALOG_STYLE_MESSAGE: {
			return 1;
		}
		case FDIALOG_STYLE_LIST: {
			return 1;
		}
	}
	return 0;
}

/*
	Other functions
*/

static stock _FDialog_strcpy(result[], const source[], const size = sizeof(result))
{
	result[0] = 0;
	// strcat - does not work on the old compiler for three-dimensional arrays
	return strins(result, source, 0, size);
}

static stock _FDialog_IntToHex(result[], color, const size = sizeof(result))
{
	format(result, size, "{%02x%02x%02x}", color & 0xFF, (color >> 16) & 0xFF, (color >> 8) & 0xFF);
}

// taken from YSI
stock DialogPagin_format(out[], size, const fmat[], dialog_pagin_:STATIC_ARGS)
{
	static
		YSI_g_sHeap,
		YSI_g_sStack,
		YSI_g_sArgCount,
		YSI_g_sArgs[5];

	//P:C(if (_:STATIC_ARGS < 1) P:W("No static args found, please add a dummy local"););
	// Get the number of parameters.
	#emit LOAD.S.alt   STATIC_ARGS
	#emit DEC.alt      // 2 - n
	#emit SHL.C.alt    2
	// "alt" now contains the number of static arguments in bytes - 4.

	// Get the previous parameter count.
	#emit LOAD.S.pri   0
	#emit ADD.C        8
	#emit LOAD.I
	#emit SUB
	#emit ADD.C        8
	#emit STOR.pri     YSI_g_sArgCount // "format"s parameter count.

	// Get the address of the arguments we are replacing.
	#emit LOAD.S.pri   0
	#emit ADD

	// Copy them to our temporary buffer.
	#emit CONST.alt    YSI_g_sArgs
	#emit MOVS         16 // (n + 1) * 4

	// Go to the new "top" of the stack.
	#emit STACK        0
	#emit STOR.alt     YSI_g_sStack    // Store it.
	#emit ADD.C        16 // (n + 1) * 4
	#emit SCTRL        4

	// "frm" is still valid.
	#emit PUSH.S       fmat
	#emit PUSH.S       size
	#emit PUSH.S       out
	#emit PUSH         YSI_g_sArgCount // Push the parameter count.

	// Modify the heap to hold "locals".
	#emit HEAP         0
	#emit STOR.alt     YSI_g_sHeap
	#emit LCTRL        4
	#emit SCTRL        2

	// Call the function.
	#emit SYSREQ.C     format
	#emit STOR.pri     YSI_g_sArgCount

	// Copy the data back.
	#emit LOAD.pri     YSI_g_sHeap
	#emit SCTRL        2
	#emit STACK        0
	#emit CONST.pri    YSI_g_sArgs
	#emit MOVS         16
	#emit LOAD.pri     YSI_g_sStack
	#emit SCTRL        4

	#emit LOAD.pri     YSI_g_sArgCount
	#emit RETN

	return 0;
}