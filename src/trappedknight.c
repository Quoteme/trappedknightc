#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <threads.h>
#include <stdatomic.h>
#include "stack.h"
#include "vec2d.h"
#include "trappedknight.h"

#define NUMOFKNIGHTS 100

#ifndef NUM_THREADS
#define NUM_THREADS 16
#endif

#define MAXKNIGHTSTEPS 15000

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

/**
 * @brief Let a knigt run according to his rules. After this function
 * is finished, the knight will have his past, trapped, position etc set
 *
 * @param k pointer to a knight
 */
void runTrappedKnight(TrappedKnight *k) {
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
  int stepsTaken = 0;
  while (!k->trapped && stepsTaken<MAXKNIGHTSTEPS) {
    stepsTaken++;
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
  if (stepsTaken==MAXKNIGHTSTEPS) {
    printf("knight (%d, %d) did not get trapped in %d steps.\n",
      k->step.x,
      k->step.y,
      MAXKNIGHTSTEPS);
  } else {
    printf("knight (%d, %d) got trapped at step %d.\n",
      k->step.x,
      k->step.y,
      stackSize(k->past));
    k->trapped = true;
  }
}

struct ThreadData {
  TrappedKnight *knights[NUMOFKNIGHTS];
  atomic_bool runningKnights[NUMOFKNIGHTS];
};
typedef struct ThreadData ThreadData;

int newThread(void *td){
  ThreadData *d = (ThreadData*) td;
  printf("thread started...\n");
  int i=0;
  while (i<NUMOFKNIGHTS) {
    if (!d->runningKnights[i]) {
      d->runningKnights[i] = true;
      /* printf("running knight %d\n", i); */
      runTrappedKnight(d->knights[i]);
    }
    i++;
  }
  /* runTrappedKnight(knights); */
  thrd_exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
  ThreadData td;
  for (int i=0; i<NUMOFKNIGHTS; i++) {
    td.knights[i] = newTrappedKnight(
      (Vec2d_i) {.x=0, .y=0},
      (Vec2d_i) {.x=i, .y=1}
    );
  }
  thrd_t threads[NUM_THREADS];
  int threadResult;
  for (long i=0; i<NUM_THREADS; i++) {
    thrd_create(&threads[i], newThread, (void*) &td);
  }
  for (long i=0; i<NUM_THREADS; i++) {
    thrd_join(threads[i], &threadResult);
  }
  for (int i=0; i<NUMOFKNIGHTS; i++) {
    freeTrappedKnight(td.knights[i]);
  }
  // check skipped knights
  for (int i=0; i<NUMOFKNIGHTS; i++) {
    if (!td.runningKnights[i]) printf("not called: %d", i);
  }
  return 0;
}
