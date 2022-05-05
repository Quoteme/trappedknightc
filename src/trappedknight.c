#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <threads.h>
#include "stack.h"
#include "trappedknight.h"

#define NUMOFKNIGHTS 100

#ifndef NUM_THREADS
#define NUM_THREADS 4
#endif

int square(int x) { return x * x; }

/**
 * @brief get the value of a position on the chessboard
 *
 * @param x x-Position
 * @param y y-Position
 * @return spiral value of position. 1 is for (0,0), 2 for (0,1), 3 for (1,1)
 * ...
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

TrappedKnight *newTrappedKnight(Vec2d_i start, Vec2d_i step){
  TrappedKnight *t = malloc(sizeof(TrappedKnight));
  if (!t) {
    fprintf(stderr, "Memory allocation failed!\n");
  }
  t->trapped = false;
  t->step = step;
  t->pos = start;
  t->steps = newStack(spirale(start.x, start.y));
  /* free(t); */
  return t;
}

void freeTrappedKnight(TrappedKnight* k){
  freeStack_i(k->steps);
  free(k);
}

void *runTrappedKnight(TrappedKnight *k) {
  thrd_exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
  /* for (int i=0; i<5; i++) { */
  /*   for (int j=0; j<5; j++) { */
  /*     printf("%d ", spirale(j, i)); */
  /*   } */
  /*   printf("\n"); */
  /* } */
  /* Stack_i *s = newStack(5); */
  /* addToStack_i(6, s); */
  /* addToStack_i(7, s); */
  /* addToStack_i(8, s); */
  /* addToStack_i(9, s); */
  /* freeStack_i(s); */
  TrappedKnight *k = newTrappedKnight(
    (Vec2d_i) {.x=0, .y=0},
    (Vec2d_i) {.x=2, .y=1}
  );
  freeTrappedKnight(k);
  return 0;
}
