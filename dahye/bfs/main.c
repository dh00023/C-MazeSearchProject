//
//  main.c
//  maze_queue
//
//  Created by dahye Jeong on 2018. 5. 20..
//  Copyright © 2018년 dahye Jeong. All rights reserved.
//

#include "queue.h"
#include "position.h"
#include "color.h"
#include <unistd.h>

#define MAX 10
#define PATH 0              // 지나갈 수 있는 길
#define WALL 1              // 지나갈 수 없는 길 == 벽 흰색!
#define FINAL 2
#define EDGE 4              // 테두리
#define clear() printf("\033[H\033[J")


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
void final_path(Position pos);
int movable(Position pos,int dir);
int n = MAX+2;

int main(int argc, const char * argv[]) {
    
    
    Queue *q = creat_queue();
    
    Position cur;
    cur.x=1;
    cur.y=1;

    
   enQueue(q,cur);

   // 추가 배열을 사용하지 않기 위해 방문 표시를 음수로 저장
   maze[1][1]=-1;
   int found = 0;

   while(!is_empty(q)){
       Position cur = front(q);
       deQueue(q);
       for(int dir=0;dir<4;dir++){
           //그 셀이 1(벽)이 아니면서 방문하지 않은 곳인지 검사!
           if(movable(cur,dir)){
               //move_to도 동일한 함수
               Position pos = move_to(cur,dir);
               // 추가 배열을 사용하지 않기 위해 방문 표시를 음수로 저장
               maze[pos.x][pos.y] = maze[cur.x][cur.y]-1;

               if(pos.x==MAX&&pos.y==MAX){
                   printf("미로를 찾았습니다.\n");
                   final_path(pos);
                   found=1;
                   exit(0);
               }
               enQueue(q,pos);
           }
       }
   }

    return 0;
}


int movable(Position pos, int dir){
    Position tmp = move_to(pos, dir);
    //1. dir방향으로 이동한 좌표가 1~MAX이내에 있어야한다.
    print_maze(tmp.x,tmp.y);
    printf("maze[%d][%d]=%d\n",tmp.x,tmp.y,maze[tmp.x][tmp.y]);
    
    if( tmp.x<1 || tmp.x>MAX){
        printf("x범위초과\n");
        return 0;
    }
    if(tmp.y<1||tmp.y>MAX){
        printf("y범위초과\n");
        return 0;
    }
    //2. wall이 아니고, 벽이아니어야한다.
    switch (maze[tmp.x][tmp.y]) {
        case 0:
            printf("갈 수 있는 길입니다.\n");
            return 1;
        case 1:
            printf("벽입니다. 갈 수 없습니다.\n");
            return 0;
        default:
            printf("이미 방문한 길입니다. 갈 수 없습니다.\n");
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

void final_path(Position pos){
    
    Position cur = pos;
    Position next;
    
    int num=maze[cur.x][cur.y]+1;
    
    maze[cur.x][cur.y]=FINAL;
    
    while(1){
        for(int i=0;i<4;i++){
            next = move_to(cur,i);
            if(maze[next.x][next.y]==num){
                maze[next.x][next.y]=FINAL;
                cur=next;
                num++;
                break;
            }
        }
        if(cur.x==1&&cur.y==1)break;
    }
    print_maze(n-2, n-2);
}

