#include "stack.h"

StackType *makeStack() { //���� ����
	return (StackType *)calloc(1, sizeof(StackType));
}

StackNode *makeStackNode() { //���ó�� ����
	return (StackNode *)calloc(1, sizeof(StackNode));
}

void initStack(StackType **s) { //���� �ʱ�ȭ
	free(*s);
	*s = NULL;
}

int isEmptyStack(StackType *s) { //������ ����ִ��� Ȯ��
	return (s->top == NULL);
}

void push(StackType *s, element data) { //������ data�� push

	StackNode *node = makeStackNode();

	if (node == NULL)
		return;

	node->data = data;
	node->link = s->top;
	s->top = node;
}

element pop(StackType *s) { //������ data�� pop

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

element peek(StackType *s) { //������ data�� peek

	if (isEmptyStack(s))
		return;

	return s->top->data;
}