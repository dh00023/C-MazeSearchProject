/*
출발점으로 부터 모든노드의 최단거리
다익스트라 인접리스트로 미로찾기 최단거리 구함!
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "color.h"
#define MAX 10
#define PATH 0
#define WALL 1
#define VISITED 2
#define FINAL 3
#define EDGE 4

int maze[MAX+2][MAX+2]={
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
int parent[100];

void print_maze(int x, int y);
typedef struct node{
    int dest;       //목적노드
    int weight;     //가중치
    struct node * next;
} Node;

typedef struct list{
    Node * head;
}List;

typedef struct graph{
    int V;
    List * array;
}Graph;

Node * new_node(int dest, int weight){
    Node * new = (Node*)malloc(sizeof(Node));
    new->dest=dest;
    new->weight=weight;
    new->next=NULL;
    return new;
}

Graph * create_graph(int V){
    Graph * g = (Graph*)malloc(sizeof(Graph));
    g->V = V;
    g->array = (List*)malloc(V*sizeof(List));
    for(int i=0;i<V;i++){
        g->array[i].head=NULL;
    }
    return g;
}

void add_edge(Graph *g,int src, int dest, int weight){
    Node * new = new_node(dest, weight);
    new->next=g->array[src].head;
    g->array[src].head=new;
    
    new=new_node(src, weight);
    new->next = g->array[dest].head;
    g->array[dest].head = new;
}

typedef struct hnode{
    int v;
    int dis;
}HNode;

typedef struct heap{
    int size;
    int capacity;
    int *pos;       //decrease key()에 필요하다.
    HNode **array;
}Heap;

HNode * new_hnode(int v, int dis){
    HNode * new = (HNode*)malloc(sizeof(HNode));
    new->v=v;
    new->dis=dis;
    return new;
}

Heap * create_heap(int capacity){
    Heap * heap = (Heap*)malloc(sizeof(Heap));
    heap->pos=(int*)malloc(capacity*sizeof(int));
    heap->size=0;
    heap->capacity=capacity;
    heap->array=(HNode**)malloc(capacity*sizeof(HNode*));
    return heap;
}


void swap_node(HNode ** a, HNode **b){
    HNode * tmp =*a;
    *a=*b;
    *b=tmp;
}

void heapify(Heap* heap,int i){
    int min,left,right;
    min=i;
    left = i*2+1;
    right = i*2+2;
    
    if(left < heap->size && (heap->array[left]->dis < heap->array[min]->dis))min=left;
    if(right<heap->size && heap->array[right]->dis<heap->array[min]->dis)min=right;
    if(min!=i){
        HNode * smallest = heap->array[min];
        HNode * inode = heap->array[i];
        heap->pos[smallest->v]=i;
        heap->pos[inode->v]=min;
        
        swap_node(&heap->array[min], &heap->array[i]);
        heapify(heap,min);
    }
}

int is_empty(Heap * h){
    return h->size==0;
}

HNode * delete(Heap * h){
    if(is_empty(h))return NULL;
    
    HNode * root = h->array[0];
    HNode * last = h->array[h->size - 1];
    
    h->array[0]=last;
    
    h->pos[root->v]=h->size-1;
    h->pos[last->v]=0;
    
    --h->size;
    heapify(h, 0);
    
    return root;
}


void decrease_key(Heap * h, int v, int dis){
    
    // heap array의 정점 v에 대한 index
    int i = h->pos[v];
    
    h->array[i]->dis = dis; //distance update
    while(i && ( h->array[i]->dis < h->array[(i-1)/2]->dis)){
        h->pos[h->array[i]->v] = (i-1)/2;
        h->pos[h->array[(i-1)/2]->v] = i;
        swap_node(&h->array[i], &h->array[(i-1)/2]);
        i=(i-1)/2;
    }
}

int is_min(Heap * h, int v){
    if(h->pos[v] < h->size) return 1;
    else return 0;
}

void backtracking(int end,int n){
    int i, j, back;
    back = end;
    if(parent[back]==0){
        printf("경로가 없습니다.\n");
        return;
    }
    while( parent[back] != -1)
    {
        i  = back / n;
        j  = back % n;
        maze[i][j] = FINAL;
        back = parent[back];
    }
    maze[1][1] = FINAL;
}

void print_array(int dis[],int n){
    printf("정점\t\t시작노드로부터거리\n");
    for(int i=0;i<n;i++)
        printf("%d\t\t\t%d\n",i,dis[i]);

    
}

void dijkstra(Graph * g,int src){
    int V= g->V;
    int dis[V];
    
    Heap * heap = create_heap(V);
    
    for(int i=0;i<V;i++){
        dis[i]=INT_MAX;
        heap->array[i]=new_hnode(i, dis[i]);
        heap->pos[i]=i;
    }
    
    // 출발점의 거리를 0으로 만듦
    heap->array[src]=new_hnode(src, dis[src]);
    heap->pos[src]=src;
    dis[src]=0;
    maze[src/(MAX+2)][src%(MAX+2)]=VISITED;
    decrease_key(heap,src,dis[src]);
    
    heap->size=V;
    
    while(!is_empty(heap)){
        HNode * min = delete(heap);
        int u = min->v;
        Node * trav = g->array[u].head;
        while(trav!=NULL){
            int v = trav->dest;
            if(is_min(heap, v)&&dis[u]!=INT_MAX && trav->weight+dis[u]<dis[v]){
                
                dis[v] = dis[u] + trav->weight;
                parent[v]=u;
                print_maze(u/(MAX+2), u%(MAX+2));
                decrease_key(heap,v,dis[v]);
            }
            trav=trav->next;
        }
    }
    print_array(dis, V);
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
                    
                    if(i==x&&j==y){
                        printf(BOLDRED);
                    }
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

int main()
{
    // create the graph given in above fugure
    
    int m = MAX+2, s;
    Graph * graph = create_graph(m*m);
    
    int start = m*1+1;
    int end = m*10+10;
    
    parent[start] = -1;
    for(int i=1;i<m-1;i++){
        for(int j=1;j<m-1;j++){
            s=i*m+j;
            if(maze[i][j]==PATH){
                if(i==1){
                    if(maze[i+1][j]==PATH)add_edge(graph, s, s+m, 1);
                    if(j==1){
                        if(maze[i][j+1]==PATH)add_edge(graph, s, s+1, 1);
                    }else if(j==m-1){
                        if(maze[i][j+1]==PATH)add_edge(graph, s, s-1, 1);
                    }else{
                        if(maze[i][j+1]==PATH)add_edge(graph, s, s-1, 1);
                        if(maze[i][j+1]==PATH)add_edge(graph, s, s+1, 1);
                    }
                }else if(i==m-2){
                    if(maze[i-1][j]==PATH)add_edge(graph, s, s-m, 1);
                    if(j==1){
                        if(maze[i][j+1]==PATH)add_edge(graph, s, s+1, 1);
                    }else if(j==m-1){
                        if(maze[i][j+1]==PATH)add_edge(graph, s, s-1, 1);
                    }else{
                        if(maze[i][j+1]==PATH)add_edge(graph, s, s-1, 1);
                        if(maze[i][j+1]==PATH)add_edge(graph, s, s+1, 1);
                    }
                }else if(j==1){
                    if(maze[i][j+1]==PATH)add_edge(graph, s, s+1, 1);
                    if(i!=1&&i!=m-2){
                        if(maze[i+1][j]==PATH)add_edge(graph, s, s+m, 1);
                        if(maze[i-1][j]==PATH)add_edge(graph, s, s-m, 1);
                    }
                }else if(j==m-2){
                    if(maze[i][j-1]==PATH)add_edge(graph, s, s-1, 1);
                    if(i!=1&&i!=m-2){
                        if(maze[i+1][j]==PATH)add_edge(graph, s, s+m, 1);
                        if(maze[i-1][j]==PATH)add_edge(graph, s, s-m, 1);
                    }
                }else{
                    if(maze[i+1][j]==PATH)add_edge(graph, s, s+m, 1);
                    if(maze[i-1][j]==PATH)add_edge(graph, s, s-m, 1);
                    if(maze[i][j+1]==PATH)add_edge(graph, s, s+1, 1);
                    if(maze[i][j-1]==PATH)add_edge(graph, s, s-1, 1);
                }
            }
            
        }
    }
    print_maze(start/m, start%m);
    dijkstra(graph, start);
    backtracking(end,m);
    print_maze(end/m, end%m);
    
    return 0;
}

