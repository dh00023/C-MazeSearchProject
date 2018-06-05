#pragma once
#include <stdlib.h>
#include "point.h"

typedef struct stackNode {

	element data;
	struct stackNode *link;

}StackNode;

typedef struct stackType {

	StackNode *top;

}StackType;

StackType *makeStack();
StackNode *makeStackNode();
void initStack(StackType **s);
int isEmptyStack(StackType *s);
void push(StackType *s, element data);
element pop(StackType *s);
element peek(StackType *s);