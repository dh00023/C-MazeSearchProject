#include <stdio.h>
#include <limits.h>
#include "point.h"
#include "stack.h"
#include "deque.h"
#include "console.h"

#define MAX 12

Point moveNESW(Point point, int dir);
void dfsRecursion(int maze[][MAX], Point point);
void dfsStack(int maze[][MAX], Point point);
void bfsQueue(int maze[][MAX], Point point);
void shortestWay(int maze[][MAX], int depth[][MAX], Point point);
void printDepth(int depth[][MAX]);
void dijkstra(int maze[][MAX], Point point);
void initDistance(int distance[][MAX]);
void initWeight(int weight[][MAX][MAX][MAX]);
void printDistance(int distance[][MAX]);
void printMaze(int maze[][MAX], Point point);

int main() {

	int maze[MAX][MAX] = { // 0�� 1�� 2������ 3���������ư��� 4�ܺ� 5���� 6�ִܰŸ� 9�ⱸ
		{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
		{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 4 },
		{ 4, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 4 },
		{ 4, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 4 },
		{ 4, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 4 },
		{ 4, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 4 },
		{ 4, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 4 },
		{ 4, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 4 },
		{ 4, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 4 },
		{ 4, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 4 },
		{ 4, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
		{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 }
	};

	Point point = { 1, 1 }; // Ž�� ��� ��ġ

	set();

	//dfsRecursion(maze, point); // ���ȣ���� �̿��� ���
	//dfsStack(maze, point); // ������ �̿��� ���
	//bfsQueue(maze, point); // ť�� �̿��ѹ��
	dijkstra(maze, point); // ���ͽ�Ʈ�� �˰����� �̿��� ���
	//A��Ÿ
	//�÷��̵�
	
}

Point moveNESW(Point point, int dir) { // dir�� 0�� 1�� 2�� 3�� point�� ��ȯ 

	if (dir == 0) 
		point.x--;
	else if (dir == 1) 
		point.y++;
	else if (dir == 2) 
		point.x++;
	else if (dir == 3) 
		point.y--;

	return point;
}

void dfsRecursion(int maze[][MAX], Point point) { // point��ġ ��������� Ž���ϱ�(DFS)

	int dir = 0;
	int x = point.x;
	int y = point.y;

	if (maze[x][y] == 9) { // Ž���� ���� �ⱸ�� ��߲Ȱ� ������
		maze[x][y] = 5;
		printMaze(maze, point);
		gotoxy(0, MAX);
		exit(1);
	}

	if (maze[x][y] == 0) { // Ž���Ѱ��� ���̸�
		maze[x][y] = 2; // ����� ǥ���ϰ�
		printMaze(maze, point);

		for (dir = 0; dir < 4; dir++) { // ��������� �ϵ������� Ž���Ѵ�
			point = moveNESW(point, dir);
			dfsRecursion(maze, point);
			point.x = x;
			point.y = y;
		}

		maze[x][y] = 3; // point���� �ϵ����� ���� ���ȣ�� Ž���� ������ �Ǹ� ���Ƴ����� ������ ǥ���Ѵ�
		printMaze(maze, point);
	}
}

void dfsStack(int maze[][MAX], Point point) { // point��ġ���� ������ �̿��Ͽ� Ž���ϱ�(DFS)

	int dir = 0, canMove = 0, x = 0, y = 0;
	StackType *s = makeStack(); // ���� ����

	push(s, point); // ���� ��ġ push
	while (!isEmptyStack(s)) { // ������ ��������� ���� �ݺ�
		canMove = 0;
		x = point.x;
		y = point.y;

		if (maze[x][y] == 9) { // ���� ��ġ�� ���� �ⱸ�� ��߲Ȱ� ������
			maze[x][y] = 5;
			printMaze(maze, point);
			gotoxy(0, MAX);
			return;
		}

		else if (maze[x][y] == 0) { // ���� ��ġ�Ѱ��� ���̸�
			maze[x][y] = 2; // ������ġ�� �������� ǥ���Ѵ�
			printMaze(maze, point);
		}

		for (dir = 3; dir >= 0; dir--) { // ���� ��ġ����
			point = moveNESW(point, dir);
			if (maze[point.x][point.y] == 0 || maze[point.x][point.y] == 9) { // ���� ��ġ���� �������ϼ����� �˻��Ͽ� ���̳� �ⱸ�� �� ��ġ�� push�Ѵ�
				push(s, point);
				canMove++; // ������ �� �ִ�
			}
			point.x = x;
			point.y = y;
		}
		if (canMove == 0) { // ���� ��ġ���� �����ϰ��� ���ٸ� ���Ƴ����� ������ ǥ���Ѵ�
			maze[point.x][point.y] = 3;
			printMaze(maze, point);
			pop(s); // ���� ��ġ ������ pop�Ѵ�.
		}
		point = peek(s); // ���� ��ġ�� ������ top�̴�
	}

	gotoxy(0, MAX); // ������ ���� ���� �ⱸ�� ã�� ���ߴٸ� 
	printf("�ⱸ�� ���� �� ����!\n");
}

void bfsQueue(int maze[][MAX], Point point) { // point��ġ���� ť(��)�� �̿��Ͽ� Ž���ϱ�(BFS)

	int dir = 0, x = 0, y = 0;
	int depth[MAX][MAX] = { 0 }; // ���������� �� �� ��ġ������ ������ ���� (����)
	memset(depth, -1, sizeof(depth)); //���� �迭�� -1�� ��� �ʱ�ȭ
	depth[1][1] = 0; //������ġ�� ���̴� 0�̴�
	DequeType *d = makeDeque(); // �� ����

	enqueueFront(d, point); // ���� ��ġ�� �� front�� �ִ´�
	while (!isEmptyDeque(d)) { // ���� ���� ���� �ݺ��Ѵ�
		x = point.x;
		y = point.y;

		if (maze[x][y] == 9) { // ���� ��ġ�� ���� �ⱸ�� ��߲ȴ´�
			maze[x][y] = 5;
			printMaze(maze, point);
			shortestWay(maze, depth, point); // �����ġ���� �ⱸ�� ���� ����ª�� ���� ǥ�����ش�
			gotoxy(0, MAX*2);
			return; // �Լ� ����
		}

		else if (maze[x][y] == 2) { // ���� ��ġ�Ѱ��� �ѹ� �����̸� 
			dequeueFront(d); // ������ġ�� ���� ��带 ����
		}

		else if (maze[x][y] == 0) { // ���� ��ġ�Ѱ��� ���̸� 
			maze[x][y] = 2; // ������ġ�� �������� ǥ���Ѵ�
			printMaze(maze, point);
			dequeueFront(d); // ������ġ�� ���� ��带 ����

			for (dir = 0; dir <= 3; dir++) { // ���� ��ġ����
				point = moveNESW(point, dir);
				if (maze[point.x][point.y] == 0 || maze[point.x][point.y] == 9) { // ���� ��ġ���� �ϵ����������� �˻��Ͽ� ���̳� �ⱸ��
					enqueueRear(d, point); // �� ��ġ�� ���� ������ �ִ´�
					depth[point.x][point.y] = depth[x][y] + 1; // �ϵ������� ��ġ�� ���� ������ġ���� ���̰� 1�� ���
					printDepth(depth); //���� �迭�� ����Ѵ�
				}
				point.x = x;
				point.y = y;
			}
		}

		point = peekFront(d); // ������ġ�� ����� ��ġ�̴�.
	}
	
	gotoxy(0, MAX*2); // ���� ���� ���� �ⱸ�� ã�� ���ߴٸ� 
	printf("�ⱸ�� ���� �� ����!\n");
}

void shortestWay(int maze[][MAX], int depth[][MAX], Point point) { //������� �������� ���� �ִܰŸ��� �Ųٷ� Ž���Ͽ� ǥ���Ѵ�

	int dir = 0, x = 0, y = 0;
	while (point.x != 1 || point.y != 1) { // ������ġ�� ������� �ƴϸ� �ݺ��Ѵ�
		x = point.x;
		y = point.y;

		for (dir = 0; dir <= 3; dir++) { // ���� ��ġ����
			point = moveNESW(point, dir); // ���� ��ġ���� �ϵ����������� �˻��Ͽ�
			if (depth[point.x][point.y] == depth[x][y] - 1) { // �װ��� ���̰� ������ġ���� �ϳ� ������
				maze[point.x][point.y] = 6; //�� ��ġ�� �ִܰŸ��� ǥ���Ѵ�
				printMaze(maze, point);
				break; //for���� ���������� ������ġ�� �ִܰŸ��� ǥ���� ��ġ�� �ȴ�
			}
			point.x = x;
			point.y = y;
		}
	}
}

void printDepth(int depth[][MAX]) { //���� �迭�� ������ִ� �Լ�

	int i = 0, j = 0;
	gotoxy(0, MAX);
	cursorView(0);

	for (i = 0; i < MAX; i++) {
		for (j = 0; j < MAX; j++)
			printf("%-3d", depth[i][j]);
		printf("\n");
	}
	cursorView(1);
}

void dijkstra(int maze[][MAX], Point point) { // point��ġ���� ���ͽ�Ʈ�� �̿��Ͽ� Ž���ϱ�

	int dir = 0, x = 0, y = 0, canMove = 0;
	int distance[MAX][MAX] = { 0 }; // ���������� �� �� ��ġ������ ���� ����ġ������ ������ ��
	initDistance(distance); // �� ������ �Ÿ��� �����ϴٰ� �����Ͽ� �ʱ�ȭ
	int weight[MAX][MAX][MAX][MAX] = { 0 }; // ��������� ����������� ����ġ
	initWeight(weight);
	weight[2][3][3][3] = 100; 
	weight[3][2][3][3] = 100; 
	distance[1][1] = 0; // ������ġ�� �Ÿ��� 0�̴�
	DequeType *d = makeDeque(); // �� ����

	enqueueFront(d, point); // ���� ��ġ�� �� front�� �ִ´�
	while (!isEmptyDeque(d)) { // ���� ���� ���� �ݺ��Ѵ�
		x = point.x;
		y = point.y;
		canMove = 0;

		for (dir = 0; dir <= 3; dir++) { // ���� ��ġ���� �ϵ����������� �˻��Ͽ�
			point = moveNESW(point, dir);
			if(maze[point.x][point.y] == 0 || maze[point.x][point.y] == 9 || maze[point.x][point.y] == 2) // �˻��Ѱ��� ���̰ų� �ⱸ�̰ų� �������̸�
				distance[point.x][point.y] = min(distance[x][y] + weight[x][y][point.x][point.y], distance[point.x][point.y]); // �˻��Ѱ��� ��ġ�� ���� �Ÿ��� ����Ͽ� �װŸ��� �����ϴ� �ּڰ��� �����Ѵ�.
			if (maze[point.x][point.y] == 2 && (distance[point.x][point.y] == distance[x][y] + weight[x][y][point.x][point.y])) { // �˻��Ѱ��� �ѹ� ���� �������� ��ȸ�Ͽ� �Ÿ��� ª�� ���̶��
				enqueueRear(d, point); // �� ��ġ�� ���� ������ �־� ��ȸ�Ͽ� ���� �Ÿ��� �˻����ش�
				canMove++;
			}
			else if (maze[point.x][point.y] == 0 || maze[point.x][point.y] == 9) { // ���̳� �ⱸ���
				enqueueRear(d, point); // �� ��ġ�� ���� ������ �ִ´� 
				canMove++;
			}
			point.x = x;
			point.y = y;
		}
	
		printDistance(distance);

		if (maze[x][y] == 9 && canMove == 0) {
			return;
		}

		if (maze[x][y] == 0) { // ���� ��ġ�Ѱ��� ���̸� 
			maze[x][y] = 2; // ������ġ�� �������� ǥ���Ѵ�
			printMaze(maze, point);
		}
		dequeueFront(d); // ������ġ�� ���� ��带 ����
		
		point = peekFront(d); // ������ġ�� ����� ��ġ�̴�.
	}

}

void initDistance(int distance[][MAX]) {

	int i = 0, j = 0;

	for (i = 0; i < MAX; i++) 
		for (j = 0; j < MAX; j++) 
			distance[i][j] = INT_MAX;
}

void initWeight(int weight[][MAX][MAX][MAX]) {

	int i = 0, j = 0, x = 0, y = 0;

	for (i = 0; i < MAX; i++) 
		for (j = 0; j < MAX; j++) 
			for (x = 0; x < MAX; x++)
				for (y = 0; y < MAX; y++)
					weight[i][j][x][y] = 1;
}

void printDistance(int distance[][MAX]) { // �Ÿ� �迭�� ������ִ� �Լ�

	int i = 0, j = 0;
	gotoxy(0, MAX);
	cursorView(0);

	for (i = 0; i < MAX; i++) {
		for (j = 0; j < MAX; j++) {
			if (distance[i][j] == INT_MAX)
				printf("%-4d", -1);
			else
				printf("%-4d", distance[i][j]);
		}
		printf("\n");
	}
	cursorView(1);
}

void printMaze(int maze[][MAX], Point point) {

	cursorView(0);
	gotoxy(0, 0);

	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			switch (maze[i][j]) {
			case 0: //���̸�
				printf("��");
				break;
			case 1: //���̸�
				printf("��");
				break;
			case 2: //�����̸�
				printf("��");
				break;
			case 3: //���Ƴ����� ���̸�
				printf("��");
				break;
			case 4: //�ܺ��̸�
				printf("��");
				break;
			case 5: //��߲��� �ⱸ��
				printf("��");
				break;
			case 6: //�ִ� �Ÿ��� ���̸�
				printf("��");
				break;
			case 9: //�ⱸ��
				printf("��");
				break;
			}
		}
		printf("\n");
	}

	gotoxy(point.y * 2, point.x);
	cursorView(1); //���� ��ġ�� Ŀ���� ǥ���Ѵ�
	Sleep(5); //���
}