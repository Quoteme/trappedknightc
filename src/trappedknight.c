#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <threads.h>
#include "stack.h"
#include "vec2d.h"
#include "trappedknight.h"

#define NUMOFKNIGHTS 100

#ifndef NUM_THREADS
#define NUM_THREADS 1
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
      return square(2 * (abs(y)) - 1) + 5 * abs(y) - x;
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
  t->past = newStack(spirale(start.x, start.y));
  /* free(t); */
  return t;
}

void freeTrappedKnight(TrappedKnight* k){
  freeStack_i(k->past);
  free(k);
}

void *runTrappedKnight(void *knight) {
  TrappedKnight *k = (TrappedKnight*) knight;
  // The position the knight will jump to next
  Vec2d_i nextPos;
  // The value of the position the knight will jump to next
  int nextFieldNum;
  // position the knight __might__ jump to
  // Only used for calculations
  Vec2d_i tmpPos;
  // value of the field the knight __might__ jump to
  // Only used for calculations
  int tmpFieldNum;
  // Step the knight might take
  // Only used for calculations
  Vec2d_i tmpStep;
  bool nextPosAlreadyVisited = true;
  while (!k->trapped) {
    // We first want to find the position which can be jumped to,
    // that has the smallest number as a spiral value,
    // which has not been visited yet.
    // After we have found this position and its value, we will append
    // this value to the knights past stack and set his current position
    // to this tile
    tmpStep = k->step;
    nextPos = addVec2d_i(k->pos, tmpStep);
    nextFieldNum = spirale(nextPos.x, nextPos.y);
    if (checkInStack(k->past, nextFieldNum)) nextPosAlreadyVisited=true;
    // Try out all rotations
    for (int i=1; i<4; i++) {
      // rotate step by 90°
      tmpStep = rotate90ccwVec2d_i(tmpStep);
      tmpPos = addVec2d_i(k->pos, tmpStep);
      tmpFieldNum = spirale(tmpPos.x, tmpPos.y);
      if (!checkInStack(k->past, tmpFieldNum)
      && (tmpFieldNum<nextFieldNum || nextPosAlreadyVisited)) {
        nextPos = tmpPos;
        nextFieldNum = tmpFieldNum;
        nextPosAlreadyVisited = false;
      }
    }
    // Mirror and try with mirrored rotations
    tmpStep = mirrorVertVec2d_i(k->step);
    tmpPos = addVec2d_i(k->pos, tmpStep);
    tmpFieldNum = spirale(tmpPos.x, tmpPos.y);
    if (!checkInStack(k->past, tmpFieldNum)
    && (tmpFieldNum<nextFieldNum || nextPosAlreadyVisited)) {
      nextPos = tmpPos;
      nextFieldNum = tmpFieldNum;
      nextPosAlreadyVisited = false;
    }
    // Try out all mirrored rotations
    for (int i=1; i<4; i++) {
      // rotate step by 90°
      tmpStep = rotate90ccwVec2d_i(tmpStep);
      tmpPos = addVec2d_i(k->pos, tmpStep);
      tmpFieldNum = spirale(tmpPos.x, tmpPos.y);
      if (!checkInStack(k->past, tmpFieldNum)
      && (tmpFieldNum<nextFieldNum || nextPosAlreadyVisited)) {
        nextPos = tmpPos;
        nextFieldNum = tmpFieldNum;
        nextPosAlreadyVisited = false;
      }
    }
    if (nextPosAlreadyVisited) break;
    k->pos = nextPos;
    addToStack_i(k->past, nextFieldNum);
  }
  printf("The knight sadly died :(\n");
  printf("His resting place is on: %d %d\n", k->pos.x, k->pos.y);
  printf("His journey took him : %d : steps.\n", stackSize(k->past));
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
  /* addToStack_i(s, 6); */
  /* addToStack_i(s, 7); */
  /* addToStack_i(s, 8); */
  /* addToStack_i(s, 9); */
  /* freeStack_i(s); */
  thrd_t threads[NUM_THREADS];
  int rc;
  TrappedKnight *k = newTrappedKnight(
    (Vec2d_i) {.x=0, .y=0},
    (Vec2d_i) {.x=2, .y=1}
  );
  for (long t; t<NUM_THREADS; t++) {
    rc = thrd_create(&threads[t], (thrd_start_t) runTrappedKnight, (void *)k);
    if (rc == thrd_error) {
      printf("ERORR: thrd_create call failed\n");
      exit(EXIT_FAILURE);
    }
    thrd_exit(EXIT_SUCCESS);
  }
  freeTrappedKnight(k);
  return 0;
}
