#include "makeMaze.h"


int main() {
	

	int maze[10][10] = {
	{ 1,1,1,1,1,1,1,1,1,0 },
	{ 1,0,0,1,0,0,1,0,0,0 },
	{ 1,1,0,1,0,1,1,1,1,0 },
	{ 1,0,1,0,1,0,0,1,1,1 },
	{ 1,1,1,0,1,0,1,1,0,1 },
	{ 1,0,1,0,1,1,1,1,0,1 },
	{ 1,0,0,0,1,0,1,1,0,0 },
	{ 1,0,1,1,1,0,0,0,1,0 },
	{ 1,1,1,0,1,1,1,0,1,0 },
	{ 1,0,0,0,1,0,1,1,1,1 } };
	int num;
	while (1) {
		
		printf("1. DFS \n");
		printf("2. Dijikstra \n");
		printf("번호 : ");
		scanf_s("%d", &num, sizeof(int));

		if (num == 1) {
			Stack*s;
			int**route;
			init1(&s);
			//printMaze(maze, size);
			route = routeInit();
			//1이 통로 0 벽

			search(maze, route, s);
			printSearch(maze, s);
		}
		else if (num == 2) {
			init();
			dijikstra(maze, 0);
			mazeSearch(maze);

		}
		system("cls");
		if (num == 99)break;
	}
	system("pause>>null");




}