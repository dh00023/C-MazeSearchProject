#include "stack.h"

StackType *makeStack() { //스택 생성
	return (StackType *)calloc(1, sizeof(StackType));
}

StackNode *makeStackNode() { //스택노드 생성
	return (StackNode *)calloc(1, sizeof(StackNode));
}

void initStack(StackType **s) { //스택 초기화
	free(*s);
	*s = NULL;
}

int isEmptyStack(StackType *s) { //스택이 비어있는지 확인
	return (s->top == NULL);
}

void push(StackType *s, element data) { //스택의 data를 push

	StackNode *node = makeStackNode();

	if (node == NULL)
		return;

	node->data = data;
	node->link = s->top;
	s->top = node;
}

element pop(StackType *s) { //스택의 data를 pop

	StackNode *tempStackNode = makeStackNode();
	element data;

	if (isEmptyStack(s))
		return;

	tempStackNode = s->top;
	data = tempStackNode->data;
	s->top = tempStackNode->link;
	free(tempStackNode);

	return data;
}

element peek(StackType *s) { //스택의 data를 peek

	if (isEmptyStack(s))
		return;

	return s->top->data;
}