#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
  float or_w1;
  float or_w2;
  float or_b;

  float nand_w1;
  float nand_w2;
  float nand_b;

  float and_w1;
  float and_w2;
  float and_b;
} Xor;

/**
 * Condenses values from -oo to oo from 0 to 1
 * @params float x
 */
float sigmoidf(float x) { return 1.f / (1.f + expf(-x)); }

float forward(Xor model, float x, float y) {
  float a = sigmoidf(model.or_w1 * x + model.or_w2 * y + model.or_b);
  float b = sigmoidf(model.nand_w1 * x + model.nand_w2 * y + model.nand_b);
  return sigmoidf(a * model.and_w1 + b * model.and_w2 + model.and_b);
}

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

sample *train = xor_train;

float rand_float() { return (float)rand() / (float)RAND_MAX; }

float cost(Xor model) {
  float result = 0.0f;
  for (size_t i = 0; i < TRAIN_COUNT; ++i) {
    float input1 = train[i][0];
    float input2 = train[i][1];
    float y = forward(model, input1, input2);
    float d = y - train[i][2];
    result += d * d;
  }
  result /= TRAIN_COUNT;
  return result;
}

Xor rand_xor(void) {
  Xor model;
  model.or_w1 = rand_float();
  model.or_w2 = rand_float();
  model.or_b = rand_float();
  model.nand_w1 = rand_float();
  model.nand_w2 = rand_float();
  model.nand_b = rand_float();
  model.and_w1 = rand_float();
  model.and_w2 = rand_float();
  model.and_b = rand_float();
  return model;
}

void print_xor(Xor m) {
  printf("or_w1 = %f\n", m.or_w1);
  printf("or_w2 = %f\n", m.or_w2);
  printf("or_b = %f\n", m.or_b);

  printf("nand_w1 = %f\n", m.nand_w1);
  printf("nand_w2 = %f\n", m.nand_w2);
  printf("nand_b = %f\n", m.nand_b);

  printf("and_w1 = %f\n", m.and_w1);
  printf("and_w2 = %f\n", m.and_w2);
  printf("and_b = %f\n", m.and_b);
}

Xor learn(Xor model, Xor g, float learning_rate) {
  model.or_w1 -= learning_rate * g.or_w1;
  model.or_w2 -= learning_rate * g.or_w2;
  model.or_b -= learning_rate * g.or_b;
  model.nand_w1 -= learning_rate * g.nand_w1;
  model.nand_w2 -= learning_rate * g.nand_w2;
  model.nand_b -= learning_rate * g.nand_b;
  model.and_w1 -= learning_rate * g.and_w1;
  model.and_w2 -= learning_rate * g.and_w2;
  model.and_b -= learning_rate * g.and_b;

  return model;
}

Xor finite_diff(Xor m) {
  float eps = 1e-1;

  Xor g;
  float c = cost(m);
  float saved;

  saved = m.or_w1;
  m.or_w1 += eps;
  g.or_w1 = (cost(m) - c) / eps;
  m.or_w1 = saved;

  saved = m.or_w2;
  m.or_w2 += eps;
  g.or_w2 = (cost(m) - c) / eps;
  m.or_w2 = saved;

  saved = m.or_b;
  m.or_b += eps;
  g.or_b = (cost(m) - c) / eps;
  m.or_b = saved;

  saved = m.nand_w1;
  m.nand_w1 += eps;
  g.nand_w1 = (cost(m) - c) / eps;
  m.nand_w1 = saved;

  saved = m.nand_w2;
  m.nand_w2 += eps;
  g.nand_w2 = (cost(m) - c) / eps;
  m.nand_w2 = saved;

  saved = m.nand_b;
  m.nand_b += eps;
  g.nand_b = (cost(m) - c) / eps;
  m.nand_b = saved;

  saved = m.and_w1;
  m.and_w1 += eps;
  g.and_w1 = (cost(m) - c) / eps;
  m.and_w1 = saved;

  saved = m.and_w2;
  m.and_w2 += eps;
  g.and_w2 = (cost(m) - c) / eps;
  m.and_w2 = saved;

  saved = m.and_b;
  m.and_b += eps;
  g.and_b = (cost(m) - c) / eps;
  m.and_b = saved;

  return g;
}

int main() {
  Xor m = rand_xor();

  float learning_rate = 1e-1;

  for (size_t i = 0; i < 1000000; ++i) {
    Xor g = finite_diff(m);
    m = learn(m, g, learning_rate);
    printf("cost: %f\n", cost(m));
  }

  for (size_t i = 0; i < 2; ++i) {
    for (size_t j = 0; j < 2; ++j) {
      printf("%zu | %zu = %f\n", i, j, forward(m, i, j));
    }
  }

  return EXIT_SUCCESS;
}
