#include "console.h"

void set() { //콘솔창 크기 조정
	system("mode con: cols=50 lines=25");
}

void gotoxy(int x, int y) { //커서 위치 조정 (0,0)부터 시작으로 설정
	COORD Pos = { x , y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
} 

void cursorView(char view) { // view에 인자값 0(FALSE) 넣으면숨기기, 1(TRUE) 넣으면보이기
	HANDLE hConsole; //구조체 선언
	CONSOLE_CURSOR_INFO ConsoleCursor;   //구조체 선언
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  //구조체 대입
	ConsoleCursor.bVisible = view;  //커서표시 유무 결정
	ConsoleCursor.dwSize = 100;   //커서표시 두께 조정
	SetConsoleCursorInfo(hConsole, &ConsoleCursor); //함수에 인자 전달
}