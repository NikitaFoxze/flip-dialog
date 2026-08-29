![](media/LogoBig.png)

:u6e80: [English](/README.md) | [Russian](/README.ru.md)

:eyes: [Pawn-Wiki](https://pawn.wiki/index.php?/topic/63084-flip-dialog/#entry313669) | [open.mp](https://forum.open.mp/showthread.php?tid=6244)

# flip-dialog
Система пагинации для диалогов в `SA-MP` & `open.mp` на языке `Pawn`. Разбивает заданный большой текст на страницы диалога в различных режимах.

Поддерживает стили диалогов: `DIALOG_STYLE_MSGBOX`, `DIALOG_STYLE_LIST`, `DIALOG_STYLE_TABLIST`, `DIALOG_STYLE_TABLIST_HEADERS`.

## Особенности
- Поддержка [mdialog](https://github.com/Open-GTO/mdialog) (опционально).
- Поддержка [zlang](https://github.com/Open-GTO/zlang) (опционально).
- Статичные поля на первую страницу.
- Ручной режим для модулей.

## Установка
Просто установите в свой проект:
```txt
sampctl package install NikitaFoxze/flip-dialog
```

Включите в свой код и начните использовать библиотеку:
```Pawn
#include <flip-dialog>
```

## Функции
<details>
<summary>Нажмите, чтобы развернуть список</summary>

**DialogPagin_Open(playerid, const function[], style, max_lines_on_page, const caption[], {Float, _}:...)**
> Открыть диалог с пагинацией
> * `playerid` - Идентификатор игрока, открывающий диалог
> * `style` - Стиль диалога
> * `max_lines_on_page` - Максимальное количество строк на странице
> * `caption[]` - Заголовок диалога
> * Возвращает `1 (true)` если функция выполнена успешно, или `0 (false)` если диалог не был открыт

**DialogPagin_AddLine(playerid, color, const text[], {Float, _}:...)**
> Добавить строку
> * `playerid` - Идентификатор игрока, добавляющий строку
> * `color` - Цвет нумерации `[%i]`
> * `text[]` - Текст строки
> * Возвращает `1 (true)` если функция выполнена успешно, или `0 (false)` если строка не была добавлена

**DialogPagin_AddStaticLine(playerid, color, const text[], {Float, _}:...)**
> Добавить статичную строку
> * `playerid` - Идентификатор игрока, добавляющий статичную строку
> * `color` - Цвет нумерации `[%i]`
> * `text[]` - Текст статичной строки
> * Возвращает `1 (true)` если функция выполнена успешно, или `0 (false)` если статичная строка не была добавлена

**DialogPagin_SetTablist(playerid, const text[], {Float, _}:...)**
> Добавить список вкладок (для `DIALOG_STYLE_TABLIST_HEADERS`)
> * `playerid` - Идентификатор игрока, добавляющий список вкладок
> * `text[]` - Текст списка вкладок
> * Ничего не возвращает

**DialogPagin_SetLineID(playerid, abstractid)**
> Задать абстрактное ID строке (используется вместе с `DialogPagin_AddLine`)
> * `playerid` - Идентификатор игрока, добавляющий абстрактное ID
> * `abstractid` - Абстрактное ID для дальнейшего использования
> * Возвращает `1 (true)` если функция выполнена успешно, или `0 (false)` если ID не было задано

**DialogPagin_GetSelectLineID(playerid)**
> Вернуть ID выбранной игроком строки, заданный при её добавлении (используется в `OnDialogResponse`)
> * `playerid` - Идентификатор игрока, получающий абстрактный ID
> * Возвращает ранее добавленный абстрактный ID

**DialogPagin_SetLineName(playerid, const abstract_name[])**
> Задать абстрактное имя строке (используется вместе с `DialogPagin_AddLine`)
> * `playerid` - Идентификатор игрока, добавляющий абстрактное имя
> * `abstract_name[]` - Абстрактное имя для дальнейшего использования
> * Возвращает `1 (true)` если функция выполнена успешно, или `0 (false)` если имя не было задано

**DialogPagin_GetSelectLineName(playerid, output[], const size = sizeof(output))**
> Вернуть имя выбранной игроком строки, заданный при её добавлении (используется в `OnDialogResponse`)
> * `playerid` - Идентификатор игрока, получающий абстрактное имя
> * `output[]` - Возвращаемая строка с абстрактным именем
> * `size` - Размер строки
> * Ничего не возвращает

**DialogPagin_ChangeCaption(playerid, const text[], {Float, _}:...)**
> Изменить заголовок диалога
> * `playerid` - Идентификатор игрока, изменяющий заголовок
> * `text[]` - Текст заголовка
> * Ничего не возвращает

**DialogPagin_IsOpen(playerid, const function[] = "")**
> Проверить, открыт ли диалог с пагинацией (при использовании `mdialog` функция `Dialog_IsOpen` будет работать корректно)
> * `playerid` - Идентификатор игрока, проверяющий диалог
> * `function[]` - Название диалога, необязательный аргумент
> * Возвращает `1 (true)` если открыт диалог с пагинацией, или `0 (false)` если нет

**DialogPagin_GetTotalLines(playerid)**
> Вернуть количество всех строк
> * `playerid` - Идентификатор игрока, получающий количество строк
> * Возвращает количество всех строк

**DialogPagin_GetMaxLinesOnPage(playerid)**
> Вернуть максимальное количество строк на странице
> * `playerid` - Идентификатор игрока, получающий количество строк
> * Возвращает максимальное количество строк на странице

**DialogPagin_IsFirstPage(playerid)**
> Проверить на открытую первую страницу
> * `playerid` - Идентификатор игрока, получающий страницу
> * Возвращает `1 (true)` если открыта первая страница, или `0 (false)` если нет

**DialogPagin_IsLastPage(playerid)**
> Проверить на открытую последнюю страницу
> * `playerid` - Идентификатор игрока, получающий страницу
> * Возвращает `1 (true)` если открыта последняя страница, или `0 (false)` если нет

**DialogPagin_ReOpen(playerid)**
> Открыть последний закрытый диалог с пагинацией
> * `playerid` - Идентификатор игрока, открывающий диалог
> * Возвращает `1 (true)` если функция выполнена успешно, или `0 (false)` если дилаог не был открыт

**DialogPagin_SetMode(playerid, modeid)**
> Задать режим пагинации (использовать до всех функций)
> * `playerid` - Идентификатор игрока, открывающий диалог
> * `modeid` - Идентификатор режима пагинации (`FDIALOG_MODE_AUTO`, `FDIALOG_MODE_MANUAL`)
> * Ничего не возвращает

**DialogPagin_ProcessManual(playerid, total_lines = 0)**
> Обработать и открыть диалог с ручным режимом (использовать в `OnDialogResponse`)
> * `playerid` - Идентификатор игрока, открывающий диалог
> * `total_lines` - Количество всех строк. Если ничего не вводить, то будет учитываться максимальное количество строк на странице и + 1. Если ввести количество вообще всех строк, например, из массива, то тоже будет работать 
> * Возвращает `1 (true)` если функция выполнена успешно, или `0 (false)` если дилаог не был открыт

**DialogPagin_ResetData(playerid)**
> Сбросить все данные пагинации при необходимости
> * `playerid` - Идентификатор игрока, сбрасывающий данные
> * Ничего не возвращает

</details>

## Базовое использование
```Pawn
// Если вы хотите изменить текст, то просто задайте эти параметры
#define FDIALOG_TEXT_EMPTY "{FFFFFF}Empty..."
#define FDIALOG_TEXT_SELECT "O"
#define FDIALOG_TEXT_CLOSE "X"
#define FDIALOG_TEXT_NUMERATION "[%i]"

// Для стиля DIALOG_STYLE_MSGBOX
#define FDIALOG_MESSAGE_TEXT_NEXT "››"
#define FDIALOG_MESSAGE_TEXT_BACK "‹‹"

// Для остальных стилей
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

CMD:fdtest(playerid) // Требуется Pawn.CMD
{
	for (new i; i < sizeof(nicknames); i++) {
		DialogPagin_AddLine(playerid, 0xFF6347FF, // 0x00000000 - убирает нумерацию
			"{FFFFFF}Nickname - %s",
			nicknames[i]);
	}

	DialogPagin_Open(playerid, Dialog:TestDialog, DIALOG_STYLE_LIST, 10,
		"{FF6347}Basic usage");

	return 1;
}

DialogResponse:TestDialog(playerid, response, listitem, inputtext[])
{
	if (!response) {
		// Ваш код...
		return 1;	
	}

	// Ваш код...
	return 1;
}
```
<img src="media/001_BasicUsage.gif" width="500" height="400" />

## Поддержка [mdialog](https://github.com/Open-GTO/mdialog)
```Pawn
#include <mdialog>
#include <flip-dialog>

DialogCreate:TestDialog(playerid)
{
	for (new i; i < 100; i++) {
		DialogPagin_AddLine(playerid, 0xFF6347FF,
			"{FFFFFF}Number - %i", i);
	}

	DialogPagin_Open(playerid, Dialog:TestDialog, DIALOG_STYLE_LIST, 10,
		"{FF6347}Basic usage");

	return 1;
}

DialogResponse:TestDialog(playerid, response, listitem, inputtext[])
{
	if (!response) {
		// Ваш код...
		return 1;	
	}

	// Ваш код...
	return 1;
}
```

## Статичные строки
Статичные строки можно добавить только один раз для каждого диалога. Они отображаются только на первой странице.
```Pawn
CMD:fdtest(playerid)
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

	DialogPagin_Open(playerid, Dialog:TestDialog, DIALOG_STYLE_LIST, 10,
		"{FF6347}Static lines");

	return 1;
}

DialogResponse:TestDialog(playerid, response, listitem, inputtext[])
{
	if (!response) {
		// Ваш код...
		return 1;	
	}

	// Статичные строки
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

	// Ваш код...
	return 1;
}
```
<img src="media/002_StaticLines.gif" width="500" height="400" />

## Хранение данных для строк
Для каждой строки можно задать абстрактный ID или имя, что позволяет определить, какие данные содержала выбранная игроком строка.
```Pawn
CMD:fdtest(playerid)
{
	for (new i; i < sizeof(nicknames); i++) {
		DialogPagin_AddLine(playerid, 0xFF6347FF,
			"{FFFFFF}Nickname - %s", nicknames[i]);

		// Задаём строке нужное имя
		DialogPagin_SetLineName(playerid,
			nicknames[i]);
	}

	DialogPagin_Open(playerid, Dialog:TestDialog, DIALOG_STYLE_LIST, 10,
		"{FF6347}Data storage for lines");

	return 1;
}

DialogResponse:TestDialog(playerid, response, listitem, inputtext[])
{
	if (!response) {
		// Ваш код...
		return 1;	
	}

	new
		string[64],
		playerName[MAX_PLAYER_NAME + 1];

	// Берём имя из выбранной игроком строки
	DialogPagin_GetSelectLineName(playerid, playerName);

	format(string, sizeof(string), "Select %s", playerName);
	SendClientMessage(playerid, 0xFFFFFFFF, string);
	return 1;
}
```

## Ручной режим
Зачем это? Данный режим предназначен для работы с гигантскими текстами и случаев, когда требуется полный контроль над пагинацией.

В ручном режиме пагинация отображает только одну страницу и не хранит информацию о предыдущих или следующих страницах. Вы самостоятельно определяете, какую страницу необходимо отобразить, вместо того чтобы заранее передавать в пагинацию весь массив текстов.

Также этот режим удобен для загрузки данных асинхронными частями: можно загружать определённое количество данных, отображать их, а после следующей загрузки продолжать работу пагинации.

В данном режиме необходимо самостоятельно объявить переменную для управления `Offset` пагинации. Система не знает, сколько всего строк необходимо обработать: она работает только с текущей страницей и обрабатывает столько строк, сколько было задано вами.

При этом системе можно сообщить только одно из двух состояний: существует ли следующая страница или её больше нет.

**Первый вариант** - передать в функцию `DialogPagin_ProcessManual` размер массива, например `sizeof(nicknames)`, или общее количество строк.

**Второй вариант** - если общее количество строк неизвестно, добавьте через `DialogPagin_AddLine` на одну строку больше, чем максимально может отображаться на одной странице. Это позволит системе пагинации определить, существует ли следующая страница.

> **Примечание:** Если в `DialogResponse` вам необходимо приостановить текущий процесс или открыть другой диалог с помощью `ShowPlayerDialog`, рекомендуется использовать `DialogPagin_ResetData`. Функцию обнуления данных можно не использовать при `response` - `FDIALOG_RESPONSE_CLOSE` и `FDIALOG_RESPONSE_SELECT`, а также при открытии диалога функцией из `mdialog` - `Dialog_Show`.

В этом примере будет показан первый вариант, но а второй представлен в файле `flip-dialog-mysql.inc`.
```Pawn
// Объявляем переменную для offset
new
	test_offset[MAX_PLAYERS];

CMD:fdtest(playerid)
{
	// Задаём режим
	DialogPagin_SetMode(playerid, FDIALOG_MODE_MANUAL);

	DialogPagin_Open(playerid, Dialog:TestDialog, DIALOG_STYLE_LIST, 6,
		"{FF6347}Manual mode");

	return 1;
}

DialogResponse:TestDialog(playerid, response, listitem, inputtext[])
{
	// Объявляем переменные для offset
	new
		start_offset,
		next_offset,
		max_lines_on_page = DialogPagin_GetMaxLinesOnPage(playerid);

	switch (response) {
		// Закрытие диалога
		case FDIALOG_RESPONSE_CLOSE: {
			// Ваш код...
			return 1;
		}
		// Выбор строки
		case FDIALOG_RESPONSE_SELECT: {
			// Ваш код...
			return 1;
		}
		// Первое открытие диалога
		case FDIALOG_RESPONSE_INIT: {
			start_offset = 0;
			next_offset = max_lines_on_page;

			test_offset[playerid] = start_offset;
		}
		// Следующая страница
		case FDIALOG_RESPONSE_NEXT_PAGE: {
			start_offset = test_offset[playerid] + max_lines_on_page;
			next_offset = start_offset + max_lines_on_page;

			test_offset[playerid] = start_offset;
		}
		// Предыдущая страница
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

	// Добавление строк
	for (new i = start_offset; i < next_offset && i < total_lines; i++) {
		DialogPagin_AddLine(playerid, 0xFF6347FF,
			"{FFFFFF}%s",
			nicknames[i]);
	}

	// Обработка и показ диалога
	DialogPagin_ProcessManual(playerid, total_lines);
	return 1;
}
```

# flip-dialog-mysql
Отдельный модуль ручного режима для загрузки данных через `LIMIT` в `MySQL-запросах`. Предназначен для удобной работы с постраничной загрузкой без лишней логики.
```Pawn
#include <flip-dialog>
#include <flip-dialog-mysql>

CMD:fdtest(playerid)
{
	DPMySQL_Open(playerid, Dialog:TestDialog, DIALOG_STYLE_LIST,
		10, db_handle,
		"SELECT \
    		`nickname` \
		FROM `player_accounts` \
		ORDER BY `id` ASC",
		"Nicknames from the database");

	return 1;
}

DialogResponse:TestDialog(playerid, response, listitem, inputtext[])
{
	switch (response) {
		case FDIALOG_RESPONSE_CLOSE: {
			// Ваш код...
			return 1;
		}
		case FDIALOG_RESPONSE_SELECT: {
			// Ваш код...
			return 1;
		}
		case FDIALOG_RESPONSE_LOAD_DATA: {
			new
				playerName[MAX_PLAYER_NICKNAME + 1];

			for (new i; i < cache_num_rows(); i++) {
				cache_get_value(i, "nickname", playerName);

				DialogPagin_AddLine(playerid,
					0xFF6347FF,
					"{FFFFFF}%s",
					playerName);
			}
		}
	}

	DialogPagin_ProcessManual(playerid);
	return 1;
}
```
