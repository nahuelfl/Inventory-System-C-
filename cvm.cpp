#include < windows.h >
// --- Définitions des fonctions

/**************************************************************************************/

void clrscr(void)
{
	CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;
	HANDLE	hConsoleOut;
	COORD	Home = { 0,0 };
	DWORD	dummy;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

	FillConsoleOutputCharacter(hConsoleOut, ' ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy);
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
}

/**************************************************************************************/

void clreol(void)
{
	CONSOLE_SCREEN_BUFFER_INFO  csbiInfo;
	HANDLE	hConsoleOut;
	COORD	Home, pos;
	DWORD	dummy;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

	Home = csbiInfo.dwCursorPosition;
	pos.X = 80 - csbiInfo.dwCursorPosition.X;

	FillConsoleOutputCharacter(hConsoleOut, ' ', pos.X, Home, &dummy);
}

/**************************************************************************************/

void clreoscr(void)
{
	CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;
	HANDLE	hConsoleOut;
	COORD	Home;
	DWORD	dummy;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

	Home = csbiInfo.dwCursorPosition;
	FillConsoleOutputCharacter(hConsoleOut, ' ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy);
}

/**************************************************************************************/

void gotoxy(int x, int y)
{
	CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;
	HANDLE	hConsoleOut;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

	csbiInfo.dwCursorPosition.X = x;
	csbiInfo.dwCursorPosition.Y = y;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
}

/**************************************************************************************/

int wherex(void)
{
	CONSOLE_SCREEN_BUFFER_INFO  csbiInfo;
	HANDLE	hConsoleOut;
	int X;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

	X = csbiInfo.dwCursorPosition.X;

	//FillConsoleOutputCharacter(hConsoleOut,' ',pos.X,Home,&dummy);

	return X;
}


/**************************************************************************************/

int wherey(void)
{
	CONSOLE_SCREEN_BUFFER_INFO  csbiInfo;
	HANDLE	hConsoleOut;
	int Y;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

	Y = csbiInfo.dwCursorPosition.Y;

	return Y;
}
