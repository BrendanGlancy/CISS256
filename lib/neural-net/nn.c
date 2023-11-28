#include <stdlib.h>
#include <time.h>
#define NN_IMPLEMENTATION
#include "neuralnet.h"

typedef struct {
  Matrix x;

  Matrix a0;
  Matrix w1, b1, a1;
  Matrix w2, b2, a2;
} XOR;

typedef float sample[3];
sample xor_train[] = {
    {0, 0, 0},
    {1, 0, 1},
    {0, 1, 1},
    {1, 1, 0},
};

sample and_train[] = {
    {0, 0, 0},
    {0, 1, 1},
    {1, 0, 1},
    {1, 1, 1},
};

sample or_train[] = {
    {0, 0, 0},
    {0, 1, 1},
    {1, 0, 1},
    {1, 1, 1},
};
#define TRAIN_COUNT 4

void forward_xor(XOR model) {
  matrix_multi(model.a1, model.a0, model.w1);
  matrix_sum(model.a1, model.b1);
  matrix_sig(model.a1);

  matrix_multi(model.a2, model.a1, model.w2);
  matrix_sum(model.a2, model.b2);
  matrix_sig(model.a2);
}

float cost(XOR model, Matrix ti, Matrix to) {
  assert(ti.rows == to.rows);
  assert(to.rows == model.a2.cols);
  size_t n = ti.rows;
  size_t m = to.cols;

  float c = 0;
  for (size_t i = 0; i < n; ++i) {
    Matrix x = matrix_row(ti, i);
    Matrix y = matrix_row(to, i);

    matrix_copy(model.a0, x);
    forward_xor(model);

    size_t q = to.cols;
    for (size_t j = 0; j < q; ++j) {
      float d = MAT_AT(model.a2, 0, j) - MAT_AT(y, 0, j);
      c += d * d;
    }
  }

  return c / n;
}

float td[] = {
    0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0,
};

int main() {
  srand(time(0));

  XOR model;

  model.x = matrix_alloc(1, 2);
  model.w1 = matrix_alloc(2, 2);
  model.b1 = matrix_alloc(1, 2);
  model.a1 = matrix_alloc(1, 2);
  model.w2 = matrix_alloc(2, 1);
  model.b2 = matrix_alloc(1, 1);
  model.a2 = matrix_alloc(1, 1);

  matrix_randomize(model.w1, 0, 1);
  matrix_randomize(model.b1, 0, 1);
  matrix_randomize(model.w2, 0, 1);
  matrix_randomize(model.b2, 0, 1);

  printf("cost = %f\n", cost(model, ti, to));

  for (size_t i = 0; i < 2; ++i) {
    for (size_t j = 0; j < 2; ++j) {
      MAT_AT(model.a0, 0, 0);
      MAT_AT(model.a0, 0, 1);
      forward_xor(model);
      float y = *model.a2.es;

      printf("%zu ^ %zu %f\n", i, j, y);
    }
  }

  return 0;
}
