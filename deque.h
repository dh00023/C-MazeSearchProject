#pragma once
#include <stdlib.h>
#include "point.h"

typedef struct dequeNode { //������ Front �������� rear��� �����Ѵ�

	element data;
	struct dequeNode *leftLink;
	struct dequeNode *rightLink;

}DequeNode;

typedef struct dequeType {

	DequeNode *front;
	DequeNode *rear;

}DequeType;

DequeType *makeDeque();
DequeNode *makeDequeNode();
void initDeque(DequeType **d);
int isEmptyDeque(DequeType *d);
void enqueueFront(DequeType *d, element data);
void enqueueRear(DequeType *d, element data);
element dequeueFront(DequeType *d);
element dequeueRear(DequeType *d);
element peekFront(DequeType *d);
element peekRear(DequeType *d);