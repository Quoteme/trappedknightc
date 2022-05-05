#ifndef STACKI
#define STACKI

struct Stack_i {
  int val;
  struct Stack_i *next;
};
typedef struct Stack_i Stack_i;

Stack_i *newStack(int);
void addToStack_i(int, Stack_i*);
void freeStack_i(Stack_i*);

#endif // !STACKI
