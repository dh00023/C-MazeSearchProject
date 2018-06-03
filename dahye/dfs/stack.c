//
//  stack.c
//  maze
//
//  Created by dahye Jeong on 2018. 5. 7..
//  Copyright © 2018년 dahye Jeong. All rights reserved.
//

#include "stack.h"

Stack * new_node(int dir){
    Stack * new = (Stack *)malloc(sizeof(Stack));
    new->dir = dir;
    new->next=NULL;
    return new;
}
void init(Stack **s){
    *s = NULL; //스택초기화
}
int is_empty(Stack *s){
    // NULL이면 1(true)  아니면 0(false)
    return (s==NULL);
}
int peak(Stack *s){
    if(is_empty(s))return -1;
    return s->dir;
}
void push(Stack ** top,int dir){
    Stack * new = NULL;
    if(is_empty(*top)){
        new = new_node(dir);
    }else{
        new = new_node(dir);
        new->next=*top;
    }
    (*top)=new;
}
void pop(Stack ** top){
    Stack * p = *top;
    
    if(is_empty(*top))return;
    
    *top = p->next;
    free(p);
}
