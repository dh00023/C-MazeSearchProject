#include "stack.h"

Stack * new_stack_node(Position pos) {
	Stack * new = (Stack *)malloc(sizeof(Stack));
	new->pos = pos;
	new->next = NULL;
	return new;
}
void init(Stack **s) {
	free(*s);
	*s = NULL; 

}
int is_empty_stack(Stack *s) {
	
	return (s == NULL);
}
Position peek(Stack *s) {
	if (is_empty_stack(s))
		return;
	return s->pos;
}
void push(Stack * top, Position pos) {
	Stack * new = NULL;
	if (is_empty_stack(top)) {
		new = new_stack_node(pos);
	}
	else {
		new = new_stack_node(pos);
		new->next = top;
	}
	top = new;
}
void pop(Stack * top) {
	Stack * p = top;

	if (is_empty_stack(top))
		return;

	top = p->next;
	free(p);
}