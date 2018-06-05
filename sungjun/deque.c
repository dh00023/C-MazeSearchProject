#include "deque.h"

DequeType *makeDeque() { //�� ����
	return (DequeType *)calloc(1, sizeof(DequeType));
}

DequeNode *makeDequeNode() { //����� ����
	return (DequeNode *)calloc(1, sizeof(DequeNode));
}

void initDeque(DequeType **d) { //�� ���ֱ�
	free(*d);
	*d = NULL;
}

int isEmptyDeque(DequeType *d) { //���� ����ִ��� Ȯ��
	return (d->front == NULL);
}

void enqueueFront(DequeType *d, element data) { //���� front�� data�� �߰��Ѵ�

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

void enqueueRear(DequeType *d, element data) { //���� rear�� data�� �߰��Ѵ�

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

element dequeueFront(DequeType *d) { //���� front�� �ִ� data�� ��ȯ�ϰ� �����Ѵ�

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

element dequeueRear(DequeType *d) { //���� rear�� �ִ� data�� ��ȯ�ϰ� �����Ѵ�

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

element peekFront(DequeType *d) { //���� front�� �ִ� data�� peek

	if (isEmptyDeque(d))
		return;

	return d->front->data;
}

element peekRear(DequeType *d) { //���� rear�� �ִ� data�� peek

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