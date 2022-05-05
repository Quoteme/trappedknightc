#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

/**
 * @brief create a new stack of integers in the heap
 *
 * @param val integer to store
 * @return pointer to a new stack of integers
 */
Stack_i *newStack(int val) {
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
void addToStack_i(int val, Stack_i *s) {
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
void freeStack_i(Stack_i *s) {
  Stack_i *ns = s->next;
  free(s);
  while (ns) {
    s = ns;
    ns = s->next;
    free(s);
  }
}
