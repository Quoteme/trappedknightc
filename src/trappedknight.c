#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMOFKNIGHTS 100

int square(int x) { return x * x; }

/**
 * @brief get the value of a position on the chessboard
 *
 * @param x x-Position
 * @param y y-Position
 * @return spiral value of position. 1 is for (0,0), 2 for (0,1), 3 for (1,1) ...
 */
int spirale(int x, int y) {
  if (x == 0 && y == 0)
    return 1;
  else if (abs(x) >= abs(y)) {
    if (x < 0)
      return square(2 * (abs(x) + 1) - 1) - abs(x) - y;
    else
      return square(2 * (abs(x) + 1) - 1) - 5 * abs(x) + y;
  } else {
    if (y < 0)
      return square(2 * (abs(y)) - 1) + abs(y) + x;
    else
      return square(2 * (abs(y)) - 1) + 5 * abs(y) + x;
  }
}

struct Stack_i {
  int val;
  struct Stack_i *next;
};
typedef struct Stack_i Stack_i;

/**
 * @brief create a new stack of integers in the heap
 *
 * @param val integer to store
 * @return pointer to a new stack of integers
 */
Stack_i * newStack(int val) {
  Stack_i *s = malloc(sizeof(Stack_i));
  if (!s) {
    fprintf(stderr, "Memory allocation failed!\n");
  }
  s->val = val;
  /* free(s); */
  return s;
}

/**
 * @brief add a value to a stack of integers
 *
 * @param val value to append to stack
 * @param s pointer to the stack which we will append to
 */
void addToStack_i(int val, Stack_i * s) {
  while (s->next) {
    s = s->next;
  }
  Stack_i *ns = malloc(sizeof(Stack_i));
  if (!ns) {
    fprintf(stderr, "Memory allocation failed!\n");
  }
  ns->val = val;
  s->next = ns;
  /* free(ns); */
}

/**
 * @brief free all the memory allocated to a stack
 *
 * @param s pointer to the stack which should be freed
 */
void freeStack_i(Stack_i * s) {
  Stack_i * ns = s->next;
  free(s);
  while (ns) {
    s = ns;
    ns = s->next;
    free(s);
  }
}

int main(int argc, char *argv[]) {
  /* for (int i=0; i<5; i++) { */
  /*   for (int j=0; j<5; j++) { */
  /*     printf("%d ", spirale(j, i)); */
  /*   } */
  /*   printf("\n"); */
  /* } */
  Stack_i * s = newStack(5);
  addToStack_i(6, s);
  addToStack_i(7, s);
  addToStack_i(8, s);
  addToStack_i(9, s);
  freeStack_i(s);
  return 0;
}
