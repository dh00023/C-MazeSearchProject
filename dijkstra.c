
#include "makeMaze.h"
int stack[MAX] = { 0 };
int index[4] = { -V,-1,V,1 };
int position[4][2] = { { -1,0 },{ 0,-1 },{ 1,0 },{ 0,1 } };

void init() {
	top = -1;
}


void push(int dis) {
	stack[++top] = dis;
	return;
}

void pop() {
	stack[top--];
	return;
}



int minDistance(int dist[size], int sptSet[size]) {
	int min = 99999;
	int min_index = 0;
	for (int v = 0; v < size; v++) {
		if (sptSet[v] == 0 && min > dist[v]) {
			min_index = v;
			min = dist[v];
			//�湮�� �� ����, min�� �� ������ �ִܰŸ����� ũ��
			//min �����ϰ� �� ���� min_index�� ����
		}
	}
	return min_index;
}

void print(int dist[], int before[])
{//���������� �� �������� �ִ� �Ÿ� ��� 
	printf("Vertex   Distance from Source\n");
	for (int i = 0; i < size; i++)
		printf("%d \t\t %d  <--%d \n", i, dist[i], before[i]);
}


void route(int before[size], int dist[size]) {
	top = -1;
	int z = size - 1;
	int i;
	int end = dist[size - 1];
	int visit = size - 1;
	push(size - 1); //�ⱸ �־����
	for (i = end; i >= 0; i--) {
		visit = before[visit];
		push(visit);
	}
}

void mazeSearch(int maze[V][V]) {
	int i, j, k, s;
	for (k = top; k >= 0; k--) {
		Sleep(300);
		system("cls");
		for (i = 0; i < V; i++) {
			for (j = 0; j < V; j++) {
				s = (i*V) + j;
				if (s == stack[top]) printf("��");
				else if (maze[i][j] == 0) printf("��");
				else if (s == size-1) printf("��");
				else printf("��");
			}
			printf("\n");
		}
		pop();

	}
}


void dijikstra(int maze[V][V], int src) {
	int i, j, v;
	int dist[size];//�ִܰŸ� �ľ��ϴ� �迭
	int before[size]; //���� ��� ���
	int sptSet[size] = { 0 };//�湮�ߴ��� üũ�ϴ� �迭
	for (int i = 0; i < size; i++)
		dist[i] = INF, sptSet[i] = 0, before[i] = 0; //�� �ʱ�ȭ

	dist[src] = 0;
	//print(dist,before);

	int k;//�ε���
	for (i = 0; i < size; i++) {
		int u = minDistance(dist, sptSet);
		int x = u / V;
		int y = u % V;
		if (maze[x][y] == 0) continue;
		for (k = 0; k< 4; k++) {
			int a = x + position[k][0];
			int b = y + position[k][1];
			if (a >= V || a < 0 || b >= V || b < 0) continue;
			int v = u + index[k]; //�������迭 5*5 ->0~24�� ���� �� 
			if (maze[a][b] == 1 && sptSet[v] == 0 && dist[u] != INF && dist[v] > dist[u] + maze[a][b]) {
				before[v] = u;
				dist[v] = dist[u] + maze[a][b];
			}

			//���� ó���� ���� ���� ��忩�� �ϰ� 
			//u-v���� edge�� �����ϰ�
			//src���� u������ ��ΰ� �����ϰ�
			//������ v�������� �ִܰŸ������� ���� ���Ǵ� �ִܰŸ��� �� ª�� ���

		}
		sptSet[u] = 1;
		//printSolution(dist,before);

	}
	route(before, dist);
}


