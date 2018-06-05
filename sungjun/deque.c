#include "deque.h"

DequeType *makeDeque() { //덱 생성
	return (DequeType *)calloc(1, sizeof(DequeType));
}

DequeNode *makeDequeNode() { //덱노드 생성
	return (DequeNode *)calloc(1, sizeof(DequeNode));
}

void initDeque(DequeType **d) { //덱 없애기
	free(*d);
	*d = NULL;
}

int isEmptyDeque(DequeType *d) { //덱이 비어있는지 확인
	return (d->front == NULL);
}

void enqueueFront(DequeType *d, element data) { //덱의 front에 data를 추가한다

	DequeNode *node = makeDequeNode();

	if (node == NULL)
		return;

	node->data = data;
	if (d->front == NULL) {
		d->rear = node;
	}
	else {
		node->rightLink = d->front;
		d->front->leftLink = node;
	}
	d->front = node;
}

void enqueueRear(DequeType *d, element data) { //덱의 rear에 data를 추가한다

	DequeNode *node = makeDequeNode();

	if (node == NULL)
		return;

	node->data = data;
	if (d->rear == NULL) {
		d->front = node;
	}
	else {
		node->leftLink = d->rear;
		d->rear->rightLink = node;
	}
	d->rear = node;
}

element dequeueFront(DequeType *d) { //덱의 front에 있는 data를 반환하고 삭제한다

	DequeNode *tempNode = makeDequeNode();
	element data;

	if (isEmptyDeque(d))
		return;

	if (d->front == d->rear)
		d->rear = NULL;

	tempNode = d->front;
	data = tempNode->data;
	d->front = tempNode->rightLink;
	free(tempNode);

	return data;
}

element dequeueRear(DequeType *d) { //덱의 rear에 있는 data를 반환하고 삭제한다

	DequeNode *tempNode = makeDequeNode();
	element data;

	if (isEmptyDeque(d))
		return;

	if (d->front == d->rear)
		d->front = NULL;

	tempNode = d->rear;
	data = tempNode->data;
	d->rear = tempNode->leftLink;
	free(tempNode);

	return data;
}

element peekFront(DequeType *d) { //덱의 front에 있는 data를 peek

	if (isEmptyDeque(d))
		return;

	return d->front->data;
}

element peekRear(DequeType *d) { //덱의 rear에 있는 data를 peek

	if (isEmptyDeque(d))
		return;

	return d->rear->data;
}

void printDeque(DequeType *d) {

	DequeNode *node = d->front;

	while (node != NULL) {
		printf("%d ", node->data);
		node = node->rightLink;
	}
	printf("\n");
}