#include <stdlib.h>
#include "position.h"

#define stack_h

#include <stdio.h>
#include <stdlib.h>
#include "position.h"


typedef struct stack {
	Position pos;
	struct stack * next;
}Stack;

Stack * new_stack_node(Position pos);
void init(Stack **s);
int is_empty_stack(Stack *s);
Position peek(Stack *s);
void push(Stack * top, Position pos);
void pop(Stack *s);

