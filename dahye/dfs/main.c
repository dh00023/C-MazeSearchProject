#include "stack.h"
#include "position.h"
#include "color.h"
#include <unistd.h>

#define MAX 10
#define PATH 0              // 지나갈 수 있는 길
#define WALL 1              // 지나갈 수 없는 길 == 벽 흰색!
#define VISITED 3           // 이미 방문한 위치(DFS) , 최종경로(BFS)
#define BACKTRACKED 2       // 방문했다 되돌아 나온 위치
#define EDGE 4              // 테두리
#define clear() printf("\033[H\033[J")

int maze[MAX+2][MAX+2]={
    { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
{ 4, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 4 },
{ 4, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 4 },
{ 4, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 4 },
{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4 },
{ 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 }




};
int n=MAX+2; // 미로의 크기
void print_maze(int x, int y);
int movable(Position pos,int dir);
void final_path(Position pos);
void dfs(int maze[][n],Position start,Position end);

int main(int argc, const char * argv[]) {
    // insert code here...
    
    Position start,end;
    start.x=1;
    start.y=1;
    end.x = 6;
    end.y = 6;

   dfs(maze, start,end);
    
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
    if(maze[tmp.x][tmp.y])return 0;
    else return 1;

//    switch (maze[tmp.x][tmp.y]) {
//        case 0:
//            printf("갈 수 있는 길입니다.\n");
//            return 1;
//        case 1:
//            printf("벽입니다. 갈 수 없습니다.\n");
//            return 0;
//
//        default:
//            printf("이미 방문한 길입니다. 갈 수 없습니다.\n");
//            return 0;
//    }
    
}




void print_maze(int x,int y){
//    sleep(1);
//    clear();
    for(int i=0;i<MAX+2;i++){
        for(int j=0;j<MAX+2;j++){
            switch (maze[i][j]) {
                case 0:
                    printf(BLACK);
                    if(i==x&&j==y)printf(BOLDRED);
                    printf("[]");
                    printf(RESET);
                    break;
                case 1:
                    if(i==x&&j==y)printf(BOLDRED);
                    printf("[]");
                    break;
                case 2:
                    printf(BOLDGREEN);
                    if(i==x&&j==y)printf(BOLDRED);
                    printf("[]");
                    printf(RESET);
                    break;
                    
                case 3: default:
                    printf(BOLDYELLOW);
                    if(i==x&&j==y)printf(BOLDRED);
                    printf("[]");
                    printf(RESET);
                    break;
                case 4:
                    printf(BOLDBLUE);
                    if(i==x&&j==y)printf(BOLDRED);
                    printf("[]");
                    printf(RESET);
                    break;
            }
            if(j==MAX+1)printf("\n");
        }
        printf(RESET);
    }
}
void dfs(int maze[][n],Position start,Position end){
    Stack * top;
    init(&top); // 이동할 방향의 정수를 저장한다.
    
    Position cur; // 항상 현재 위치를 표현
    cur = start;
    
    int init_dir = 0; //한 위치에 도착했을 때 처음으로 시도해 볼 이동 방향
    
    while(1){
        maze[cur.x][cur.y] = VISITED;
        if(cur.x == end.x && cur.y == end.y){
            print_maze(cur.x,cur.y);
            printf("미로를 찾았습니다!\n");
            break;
        }
        // 방문했는지 기록하는 변수
        int forwarded = 0;
        
        // 북 동 서 남 순서대로 0, 1, 2, 3
        for(int dir = init_dir; dir<4;dir++){
            if(movable(cur,dir)){ //이동가능한지 검사
                push(&top,dir); // 스택에 현재 위치 대신 이동하는 방향을 push
                cur = move_to(cur,dir);
                forwarded = 1;
                init_dir = 0; //처음 방문하는 위치에서는 항상 0부터 시도
                break;
            }
        }
        // 4방향중 아무곳도 가지 못했다면
        if(!forwarded){
            // 왔다가 되돌아간 곳임을 표시
            maze[cur.x][cur.y]=BACKTRACKED;
            //원래 출구가 없는 미로
            if(is_empty(top)){
                printf("길이 없습니다.\n");
                break;
            }
            int d = peak(top);
            pop(&top);
            // 이전 위치에서 지금 위치에 올때 d방향으로 이동했다면 (d+2)%4번 방향으로 이동하면된다.
            // 되돌아가는 방향!
            cur = move_to(cur, (d+2)%4);
            // 위치에서 d+1번방향부터 시도하면된다.
            init_dir = d+1;
            print_maze(cur.x, cur.y);
            printf("길이없습니다. 되돌아갑니다.\n");
        }
    }
}
