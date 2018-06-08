//
//  main.c
//  maze_recursive
//
//  Created by dahye Jeong on 2018. 5. 27..
//  Copyright © 2018년 dahye Jeong. All rights reserved.
//

#include <stdio.h>
#include "color.h"


#define MAX 10
#define PATH 0
#define WALL 1
#define BLOCKED 2  // 방문+경로상에 있지 않은 것
#define VISITED 3  // 방문+경로가 될 가능성이 있는것

int maze[MAX+2][MAX+2]= {
    {4,4,4,4,4,4,4,4,4,4,4,4},
    {4,0,0,0,0,0,0,0,0,0,1,4},
    {4,0,1,1,0,1,1,0,1,1,1,4},
    {4,0,0,1,0,1,0,0,0,0,1,4},
    {4,0,1,0,1,0,1,1,1,0,0,4},
    {4,0,0,0,1,0,1,0,0,1,0,4},
    {4,0,1,0,1,0,0,0,1,1,0,4},
    {4,0,1,1,1,0,1,0,0,1,1,4},
    {4,0,1,0,0,0,1,1,1,0,1,4},
    {4,0,0,0,1,0,0,0,1,0,1,4},
    {4,0,1,1,1,0,1,0,0,0,0,4},
    {4,4,4,4,4,4,4,4,4,4,4,4}
};

void print_maze(int x, int y);

int find_path(int x, int y){
    print_maze(x,y);
    if(x<1 ||y<1||x>MAX||y>MAX)return 0;
    else if(maze[x][y] != PATH)return 0;
    else if(x==MAX&&y==MAX){
        maze[x][y]=VISITED;
        return 1;
    }else{
        maze[x][y] = VISITED;
        // 북동남서 순으로 길을 갈 수 있으면 순환!
        if(find_path(x-1, y)||find_path(x, y+1)||find_path(x+1, y)||find_path(x, y-1)) return 1;
        maze[x][y]=BLOCKED;
        return 0;
    }
}

void print_maze(int x,int y){
    //    sleep(1);
    //    clear();
    for(int i=0;i<MAX+2;i++){
        for(int j=0;j<MAX+2;j++){
            switch (maze[i][j]) {
                case 0:
                    printf(BLACK);
                    if(i==x&&j==y){
                        printf(BOLDRED);
                    }
                    
                    printf("[]");
                    printf(RESET);
                    break;
                case 1:
                    if(i==x&&j==y){
                        printf(BOLDRED);
                    }
                    printf("[]");
                    break;
                case 3:
                    printf(BOLDGREEN);
                    printf("[]");
                    printf(RESET);
                    break;
                    
                case 4:
                    printf(BOLDBLUE);
                    if(i==x&&j==y){
                        printf(BOLDRED);
                        printf("[]");
                    }else
                        printf("[]");
                    printf(RESET);
                    break;
                default:
                    printf(BOLDYELLOW);
                    if(i==x&&j==y){
                        printf(BOLDRED);
                    }
                    printf("[]");
                    printf(RESET);
                    break;
                    
                    break;
            }
            printf(RESET);
            if(j==MAX+1)printf("\n");
        }
    }
    printf(RESET);
}

int main(int argc, const char * argv[]) {
    print_maze(1, 1);
    find_path(1, 1);
    print_maze(MAX, MAX);
    return 0;
}
