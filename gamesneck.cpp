#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <string.h>

#pragma warning( disable : 4996 )
int mssv[7] = { 1,6,6,0,2,2,2 };
bool gate = false;
int max_row = 50, min_row = 4;
int max_col = 78, min_col = 0;
int speed, max_level = 5, level;
int x1, y1, xF, yF, d, score, dscore, dlevel, key;
int x[50];
int y[50];

// Khai báo các hàm ph?
void hidecursor(){
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}
void clrscr() {
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
void gotoxy(int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void textcolor(int x)
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}
void FixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}
// K?t thúc khai báo

// Khai báo (dòng 115)
void Start();
// Khai báo (dòng 258)
void LoseGame();
// Khai báo (dòng 228)
void Collision();

// Hàm kh?i t?o (NEW GAME)
void Initialize() {
	clrscr();	d = 6; level = 0; score = 1;
	
	x[0] = max_col / 2;
	y[0] = max_row / 2;
	xF = min_col + 1 + rand() % (max_col - 2 - min_col + 1);
	yF = min_row + 1 + rand() % (max_row - 2 - min_row + 1);
	x1 = 1;	y1 = 0;
}

// Hàm LOAD game
void LoadGame() {
	clrscr();
	FILE *data;
	char name[30];	int i = 20;
	textcolor(10);
	gotoxy(10, 12);
	printf("Nhap 'thoat' de quay lai !");
	gotoxy(10, 10);
	printf("Nhap ten tap tin : ");
	gets(name);
	if (strcmp(name, "thoat") == 0) Start();
	else {
		data = fopen(name, "rt");
		if (data == NULL) {
			clrscr();
			gotoxy(max_row / 2, max_col / 2);
			printf("Tap tin khong ton tai !");
			Sleep(1000);
			Start();
		}
		if (data != NULL)
			fscanf(data, "%d %d ", &score, &level);
		fclose(data);
		clrscr();
		d = 6 + score;
		x[0] = max_col / 2;
		y[0] = max_row / 2;
		xF = min_col + 1 + rand() % (max_col - 2 - min_col + 1);
		yF = min_row + 1 + rand() % (max_row - 2 - min_row + 1);
		x1 = 1;	y1 = 0;
	}
}

// Màn hình b?t d?u
void Start() {
	int key;
	clrscr();
	textcolor(7);
	gotoxy(23, 9);	for (int i = 0; i < 30; i++) {
		putchar('_');
	}
	textcolor(10);
	gotoxy(25, 11);	printf("NEW GAME\tPress any key");
	gotoxy(25, 13);	printf("LOAD GAME\t\tT");
	gotoxy(25, 15);	printf("EXIT\t\t\tEsc\n");
	while (!_kbhit()) {
	gotoxy(13, 1);	printf(" SSSSSS    NN     NN    AAAAAA    KK    KK   EEEEEEE");
	gotoxy(13, 2);	printf("SS    SS   NNN    NN   AA    AA   KK   KK    EE");
	gotoxy(13, 3);	printf(" SS        NN NN  NN   AA    AA   KK  KK     EE");
	gotoxy(13, 4);	printf("  SS       NN  NN NN   AAAAAAAA   KKKK       EEEEEEE");
	gotoxy(13, 5);	printf("    SS     NN   N NN   AA    AA   KK  KK     EE");
	gotoxy(13, 6);	printf("SS    SS   NN    NNN   AA    AA   KK   KK    EE");
	gotoxy(13, 7);	printf(" SSSSSS    NN     NN   AA    AA   KK    KK   EEEEEEE");
	textcolor(8 + rand() % 8);
	Sleep(1000);
	}
	key = _getch();
	switch (key)
	{
	case 'T':
	case 't': LoadGame(); break;
	case 27: exit(0);	break;
	default: {
		clrscr();
		Initialize();
	}; break;
	}
}

void Display() {
	textcolor(10);
	gotoxy(8, 2); printf("SCORE: %d", score - 1);
	gotoxy(19, 2); printf("LEVEL: %d", level);
	gotoxy(30, 2); printf("MAX LEVEL: 5");
	textcolor(15);
	for (int i = min_col; i < max_col + 1; i++) {
		gotoxy(i, min_row);	putchar(219);
		gotoxy(i, max_row);	putchar(219);
	}
	for (int i = min_row; i < max_row; i++) {
		gotoxy(min_col, i);	putchar(219);
		gotoxy(max_col, i);	putchar(219);
	}
}

// Hàm x? lý hình ?nh khi va ch?m
void Collision() {
	Sleep(100);
	while (1)
	{
		textcolor(8 + rand() % 8);
		gotoxy(x[0], y[0]);
		putchar(177);
		Sleep(50);
		textcolor(7);
		gotoxy(25, max_row / 2 - 2);
		printf("GAME OVER . . . Press Enter");
		Sleep(950);
		textcolor(0);
		gotoxy(25, max_row / 2 - 2);
		printf("GAME OVER . . . Press Enter");
		Sleep(500);
		if (_kbhit()) {
			LoseGame();
			break;
		}
	}
}

// V? r?n
void DrawSnake() {
	for (int i = 0, j = 0; i < d; i++, j++) {
		if (j > 6) j = 0;
		gotoxy(x[i], y[i]);
		printf("%d", mssv[j]);
	}
	// Xóa duôi m?i l?n r?n di chuy?n d? không b? gi?t nhu khi s? d?ng clrscr()
	gotoxy(x[d], y[d]);
	putchar(32);
}

// Hàm hi?n th? sau khi qua C?NG
void OutGate() {
	clrscr();
	gotoxy(10, max_row / 2 - 1);	printf("%c%c", 201, 187);
	gotoxy(10, max_row / 2);		printf("%c", 186);
	gotoxy(10, max_row / 2 + 1);	printf("%c%c", 200, 188);
	d = 6 + score;  level++;	score++;	speed += 2;
	x[0] = 11;
	y[0] = max_row / 2;
	xF = min_col + 1 + rand() % (max_col - 2 - min_col + 1);
	yF = min_row + 1 + rand() % (max_row - 2 - min_row + 1);
	x1 = 1;	y1 = 0;
	gotoxy(68, max_row / 2 - 1);	printf("%c%c", 201, 187);
	gotoxy(69, max_row / 2);		printf("%c", 186);
	gotoxy(68, max_row / 2 + 1);	printf("%c%c", 200, 188);
	// Reset khi MAX SPEED
	if (level == max_level) {
		clrscr();
		gotoxy(10, max_row / 2 - 1);	printf("%c%c", 201, 187);
		gotoxy(10, max_row / 2);		printf("%c", 186);
		gotoxy(10, max_row / 2 + 1);	printf("%c%c", 200, 188);
		gotoxy(68, max_row / 2 - 1);	printf("%c%c", 201, 187);
		gotoxy(69, max_row / 2);		printf("%c", 186);
		gotoxy(68, max_row / 2 + 1);	printf("%c%c", 200, 188);
		d = 6;	speed = 0;	level = 0;	score = 1;
	}
}

// Hàm hi?n C?NG khi an 4 FOOD
void Gate() {
	int i = 0;
	// In C?NG
	gotoxy(68, max_row / 2 - 1);	printf("%c%c", 201, 187);
	gotoxy(69, max_row / 2);		printf("%c", 186);
	gotoxy(68, max_row / 2 + 1);	printf("%c%c", 200, 188);
	// X? lý khi va ch?m C?NG
	if (x[0] == 68 && y[0] == max_row / 2 - 1 ||
		x[0] == 69 && y[0] == max_row / 2 - 1 ||
		x[0] == 69 && y[0] == max_row / 2 ||
		x[0] == 68 && y[0] == max_row / 2 + 1 ||
		x[0] == 69 && y[0] == max_row / 2 + 1)
		Collision();
	// X? lý khi di vào C?NG
	if (x[i] == 68 && y[i] == max_row / 2) {
		gate = false;
		while (x[i] == 68 && y[i] == max_row / 2) {
			if (x[i] == 68 && y[i] == max_row / 2) break;
			/*gotoxy(x[i], y[i]);
			putchar(32);*/
			x[i] = x[i - 1];
			y[i] = y[i - 1];
			i++;
		}
		OutGate();
	}
}

// Hàm di?u khi?n
void Control() {
	// Truy?n v? trí d?t tru?c cho d?t sau
	for (int i = d; i > 0; i--) {
		x[i] = x[i - 1];
		y[i] = y[i - 1];
	}
	// Ði?u khi?n
	if (kbhit()) {
		key = getch();
		if (GetAsyncKeyState(VK_LEFT) && x1 != 1) {
			x1 = -1; y1 = 0;
		}
		if (GetAsyncKeyState(VK_RIGHT) && x1 != -1) {
			x1 = 1; y1 = 0;
		}
		if (GetAsyncKeyState(VK_UP) && y1 != 1) {
			x1 = 0; y1 = -1;
		}
		if (GetAsyncKeyState(VK_DOWN) && y1 != -1) {
			x1 = 0; y1 = 1;
		}
	}
	// Hu?ng di chuy?n khi nh?n phím ÐI?U KHI?N
	x[0] += x1;
	y[0] += y1;
}

// Màn hình Save game
void SaveGame() {
	clrscr();
	FILE *data;
	char name[20];
	gotoxy(10, 15);
	printf("Nhap 'thoat' de quay lai !");
	gotoxy(10, 13);
	printf("Nhap ten tap tin: ");
	gets(name);
	if (strcmp(name, "thoat") == 0) LoseGame();
	else {
		data = fopen(name, "a");
		if (data == NULL) {
			gotoxy(10, 13);
			printf("Da luu tap tin !");
			Sleep(900);
		}
		else if (data != NULL) {
			clrscr();
			gotoxy(10, 13);
			printf("Tap tin da ton tai !");
			Sleep(1050);
			LoseGame();
		}
		fprintf(data, "%d %d ", dscore, dlevel);
		fclose(data);
		exit(0);
	}
}

// Màn hình Thua game
void LoseGame() {
	dscore = score; dlevel = level;
	char cont;
	clrscr();
	textcolor(7);
	gotoxy(20, 4);
	printf("G A M E   O V E R   !");
	textcolor(13);
	gotoxy(21, 10);	printf("NEW GAME\t\tY");
	gotoxy(21, 12);	printf("SAVE\t\tS");
	gotoxy(21, 14);	printf("QUIT\t\tN\n");
	cont = _getch();
	switch (cont) {
	case 'N':
	case 'n':	exit(0);	break;
	case 'S':
	case 's':	SaveGame();	break;
	case 'Y':
	case 'y': {
		score = 0;	level = 0;
		Initialize();
	};	break;
	default: LoseGame();
	}
}

// Hàm x? lý va ch?m & an FOOD
void Handling() {
	textcolor(11);
	DrawSnake();
	if (score % 5 != 0 || score < 1) {
		gotoxy(xF, yF);
		putchar(3);
	}
	else {
		Gate();
	}
	// X? lý an FOOD

	if (x[0] == xF && y[0] == yF) {
		xF = min_col + 2 + rand() % (max_col - 3 - min_col + 1);
		yF = min_row + 2 + rand() % (max_row - 3 - min_row + 1);
		score++;	d++;
	}
	// Xóa c?ng khi R?N ra h?t
	if (x[d] == 11 && y[d] == max_row / 2) {
		gotoxy(10, max_row / 2 - 1);	printf("%c%c", 32, 32);
		gotoxy(10, max_row / 2);		printf("%c", 32);
		gotoxy(10, max_row / 2 + 1);	printf("%c%c", 32, 32);
		gotoxy(68, max_row / 2 - 1);	printf("%c%c", 32, 32);
		gotoxy(69, max_row / 2);		printf("%c", 32);
		gotoxy(68, max_row / 2 + 1);	printf("%c%c", 32, 32);
	}

	// X? lý ch?m BIÊN và ch?m THÂN
	for (int i = 1; i < d; i++) {
		if (x[0] == min_col || x[0] == max_col ||
			y[0] == min_row || y[0] == max_row ||
			x[0] == x[i] && y[0] == y[i]) {
			// X? lý thua
			Collision();
		}
	}
}

// MAIN
int main() {
	srand(time(NULL));
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	hidecursor();
	clrscr();
	Start();
	while (1) {
		Display();
		Handling();
		Control();
		Sleep(50 + speed);
	}
	hidecursor();
return 0;}
