#ifndef TRAPPEDKNIGHT
#define TRAPPEDKNIGHT

#include "stack.h"
#include "vec2d.h"

struct TrappedKnight {
  bool trapped;
  Vec2d_i step;
  Vec2d_i pos;
  Stack_i *past;
};
typedef struct TrappedKnight TrappedKnight;

TrappedKnight *newTrappedKnight(Vec2d_i, Vec2d_i);
void freeTrappedKnight(TrappedKnight*);

#endif // !TRAPPEDKNIGHT
