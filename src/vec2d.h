#ifndef VEC2D_I
#define VEC2D_I

typedef struct Vec2d_i Vec2d_i;
struct Vec2d_i {
  int x;
  int y;
};

Vec2d_i addVec2d_i(Vec2d_i, Vec2d_i);
Vec2d_i subVec2d_i(Vec2d_i, Vec2d_i);
Vec2d_i rotate90ccwVec2d_i(Vec2d_i);
Vec2d_i mirrorVertVec2d_i(Vec2d_i);

#endif // !VEC2D_I
