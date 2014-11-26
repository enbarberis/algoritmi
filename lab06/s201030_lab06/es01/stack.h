#ifndef STACK_H_DEFINED
#define STACK_H_DEFINED

typedef struct stack *Stack;

Stack stack_init();
int stack_empty(Stack s);
int stack_size(Stack s);
void stack_push(Stack s, Item i);
Item stack_pop(Stack s);
Item stack_top(Stack s);
void stack_print(Stack s);
void stack_destroy(Stack s);

#endif
