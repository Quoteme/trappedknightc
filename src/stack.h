#ifndef STACKI
#define STACKI

struct Stack_i {
  int val;
  struct Stack_i *next;
};
typedef struct Stack_i Stack_i;

Stack_i *newStack(int);
void addToStack_i(Stack_i*, int);
void freeStack_i(Stack_i*);
bool checkInStack(Stack_i*, int);
int stackSize(Stack_i*);

#endif // !STACKI
