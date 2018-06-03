//
//  stack.h
//  maze
//
//  Created by dahye Jeong on 2018. 5. 7..
//  Copyright © 2018년 dahye Jeong. All rights reserved.
//

#ifndef stack_h
#define stack_h

#include <stdio.h>
#include <stdlib.h>
#include "position.h"

//typedef struct s{
//    Position pos;
//    struct s * next;
//}Stack_pos;
//
//Stack * new_node(Position p);
//void init(Stack *s);
//int is_empty(Stack *s);
//Position peak(Stack *s);
//void push(Stack ** top, Position p);
//void pop(Stack ** top);

typedef struct s{
    int dir;
    struct s * next;
}Stack;

Stack * new_node(int dir);
void init(Stack **s);
int is_empty(Stack *s);
int peak(Stack *s);
void push(Stack ** top, int dir);
void pop(Stack ** top);

#endif /* stack_h */
