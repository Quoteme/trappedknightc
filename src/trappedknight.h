#ifndef TRAPPEDKNIGHT
#define TRAPPEDKNIGHT

#include "stack.h"

struct Vec2d_i {
  int x;
  int y;
};
typedef struct Vec2d_i Vec2d_i;

struct TrappedKnight {
  bool trapped;
  Vec2d_i step;
  Vec2d_i pos;
  Stack_i *steps;
};
typedef struct TrappedKnight TrappedKnight;

TrappedKnight *newTrappedKnight(Vec2d_i, Vec2d_i);
void freeTrappedKnight(TrappedKnight*);

#endif // !TRAPPEDKNIGHT
