#include "main_h.h"
#include "color.h"
#include <unistd.h>
#define clear() printf("\033[H\033[J")
int maze[MAX+2][MAX+2]= {
    { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
    { 4, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 4 },
    { 4, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 4 },
    { 4, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 4 },
    { 4, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 4 },
    { 4, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 4 },
    { 4, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 4 },
    { 4, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 4 },
    { 4, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 4 },
    { 4, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 4 },
    { 4, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 4 },
    { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 }
    
};
Vertex start,end;

// heuristic함수로 가중치를 계산하는 함수
// 여기서 pre는 이전정점의 gx값을 받아온다.
int heuristic(Vertex v, int x,int y, int *pre){
    int res;
    
    // h(x)함수 즉, 출구에서 얼마나 걸리는지 계산한다.(맨하탄)
    res = ((abs(end.x-x)+abs(end.y-y))*10);
    
    *pre = v.g_x;
    
    // 대각선인 경우
    if(abs(v.x-x)==abs(v.y-y)){
        *pre = *pre +14;
    }else{
        *pre = *pre +10;
    }
    // f(x) = g(x) + h(x)
    return res+(*pre);
}

// 인접노드를 queue에 추가하기
void add_openlist(Queue * q,Vertex v){
    Vertex tmp;
    
    // pw는 이전 weigt
    int i,j,w,pre;
    
    // 인접한 정점 확인
    for(i=v.x-1;i<=v.x+1;i++){
        
        if(i<1||i>MAX)continue;             // 범위를 벗어나면 통과한다.
        for(j=v.y-1;j<=v.y+1;j++){
            
            if(j<1||j>MAX)continue;         // 범위를 벗어나면 통과한다.
            if(i==v.x&&j==v.y)continue;     // i와 j가 현재 노드랑 같으면 통과
            if(maze[i][j]!=0)continue;      // 길이 아니면 통과
            
            // 가중치 f(x)
            w = heuristic(v, i, j, &pre);
            // printf("i : %d j: %d\n",i,j );
            // 가중치가 현재보다 낮거나 기록이 안되어있으면 갱신
            if(w<weight[i][j]||weight[i][j]==0){
                weight[i][j]=w;
                // 부모 노드의 정보를 저장한다.
                parent[i][j] = (v.x*MAX)+v.y;
                
                // 출구를 찾으면 종료
                if(i==end.x && j==end.y ){
                    printf("1.출구를 찾음\n");
                    return;
                }
            }
            print_maze(i,j);
            tmp.x = i;
            tmp.y = j;
            tmp.g_x = pre;
            enQueue(q, tmp);
        }
    }
    
}


void astar(Vertex s,Vertex e){
    
    Queue * q = creat_queue();
    
    Vertex v;
    
    // 시작점의 weight는 0이다.
    weight[s.x][s.y] = 0;
    // 시작점은 부모노드를 갖고 있지 않는다.
    parent[s.x][s.y]=-1;
    // 시작점에서 움직인 거리(gx)는 0이다.
    s.g_x = 0;
    
    v = s;
    
    add_openlist(q,v);
    
    while(!is_empty(q)){
        
        
        // 현재 점을 Closed list에 추가 >> maze에 바로표시
        maze[v.x][v.y]=CLOSED;
        v = front(q);
        deQueue(q);
        if(v.x==end.x && v.y==end.y)return;
        
        // 새로운 인접노드를 추가해준다.
        add_openlist(q, v);
        
    }
    
}
void print_weight(){
    int i,j;
    for(i=0;i<MAX+2;i++){
        for(j=0;j<MAX+2;j++)
            printf("%6d",weight[i][j]);
        printf("\n");
    }
    
}
void backtracking(){
    int i, j, back;
    
    i  = parent[end.x][end.y] / 10;
    j  = parent[end.x][end.y] % 10;
    
    while( parent[i][j] != -1)
    {
        back = parent[i][j];
        
        maze[i][j] = FINAL;
        
        i  = back / 10;
        j  = back % 10;
    }
    maze[start.x][start.y] = FINAL;
}
void print_maze(int x,int y){
    // sleep(1);
    // clear();

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
int main(){
    start.x=1;start.y=1;
    end.x=1;end.y=MAX;
    astar(start, end);
    print_weight();
    print_maze(end.x,end.y);
    backtracking();
    print_maze(end.x,end.y);
}

QNode * new_node(Vertex v){
    QNode * new = (QNode *)malloc(sizeof(QNode));
    new->ver.x = v.x;
    new->ver.y = v.y;
    new->ver.g_x = v.g_x;
    new->next=NULL;
    return new;
}

Queue * creat_queue(void){
    Queue * new = (Queue *)malloc(sizeof(Queue));
    new->front = new->rear= NULL;
    return new;
}


Vertex front(Queue *q){
    return q->front->ver;
}

Vertex rear(Queue *q){
    return q->rear->ver;
}

int is_empty(Queue * q){
    return (q->front==NULL && q->rear==NULL);
}


//front 포인터는 삭제,  rear 포인터는 삽입할 때 사용
void enQueue(Queue * q,Vertex v){
    QNode * new = new_node(v);
    QNode * tq  =q->front;
    Vertex tmp;
    int key;
    
    if(is_empty(q)){
        q->front = q->rear = new;
        return;
    }
    
    //우선순위큐
    // with insertion-sort, begin sorting process.
    while( tq!= NULL){
        key = weight[v.x][v.y];
        
        if( key < weight[tq->ver.x][tq->ver.y]){
            tmp = tq->ver;
            tq->ver = v;
            v  = tmp;
        }
        tq = tq->next;
    }
    new->ver = v;
    q->rear->next= new;
    q->rear=new;
}

void deQueue(Queue * q){
    if(q->front==NULL){
        return;
    }
    q->front = q->front->next;
    if(q->front==NULL) q->rear=NULL;
}

