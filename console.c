#include "console.h"

void set() { //�ܼ�â ũ�� ����
	system("mode con: cols=50 lines=25");
}

void gotoxy(int x, int y) { //Ŀ�� ��ġ ���� (0,0)���� �������� ����
	COORD Pos = { x , y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
} 

void cursorView(char view) { // view�� ���ڰ� 0(FALSE) ����������, 1(TRUE) �����麸�̱�
	HANDLE hConsole; //����ü ����
	CONSOLE_CURSOR_INFO ConsoleCursor;   //����ü ����
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  //����ü ����
	ConsoleCursor.bVisible = view;  //Ŀ��ǥ�� ���� ����
	ConsoleCursor.dwSize = 100;   //Ŀ��ǥ�� �β� ����
	SetConsoleCursorInfo(hConsole, &ConsoleCursor); //�Լ��� ���� ����
}