#include "vec2d.h"

Vec2d_i addVec2d_i(Vec2d_i v, Vec2d_i w) {
  return (Vec2d_i){.x = v.x + w.x, .y = v.y + w.y};
}

Vec2d_i subVec2d_i(Vec2d_i v, Vec2d_i w) {
  return (Vec2d_i){.x = v.x - w.x, .y = v.y - w.y};
}

Vec2d_i rotate90ccwVec2d_i(Vec2d_i v){
  return (Vec2d_i){.x = -v.y, .y=v.x};
}

Vec2d_i mirrorVertVec2d_i(Vec2d_i v){
  return (Vec2d_i){.x = -v.x, .y = v.y};
}
