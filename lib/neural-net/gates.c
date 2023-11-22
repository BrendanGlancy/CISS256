#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * Condenses values from -oo to oo from 0 to 1
 * @params float x
 */
float sigmoidf(float x) { return 1.f / (1.f + expf(-x)); }

float train[][3] = {
    {0, 0, 0},
    {0, 1, 1},
    {1, 0, 1},
    {1, 1, 1},
};
#define TRAIN_COUNT ((float)sizeof(train) / sizeof(train[0]))

float rand_float() { return (float)rand() / (float)RAND_MAX; }

float cost(float weight1, float weight2, float bias) {
  float result = 0.0f;
  for (size_t i = 0; i < TRAIN_COUNT; ++i) {
    float input1 = train[i][0];
    float input2 = train[i][1];
    float y = sigmoidf(input1 * weight1 + input2 * weight2 + bias);
    float d = y - train[i][2];
    result += d * d;
  }
  result /= TRAIN_COUNT;
  return result;
}

int main() {
  srand(time(0));
  float weight1 = rand_float();
  float weight2 = rand_float();
  float bias = rand_float();

  float epsilon = 1e-1;
  float learning_rate = 1e-1;

  for (size_t i = 0; i < 100 * 1000; ++i) {
    float costs = cost(weight1, weight2, bias);

    float distance_weight1 =
        (cost(weight1 + epsilon, weight2, bias) - costs) / epsilon;

    float distance_weight2 =
        (cost(weight1, weight2 + epsilon, bias) - costs) / epsilon;

    float distance_bias =
        (cost(weight1, weight2, bias + epsilon) - costs) / epsilon;

    weight1 -= learning_rate * distance_weight1;
    weight2 -= learning_rate * distance_weight2;
    bias -= learning_rate * distance_bias;
  }
  printf("weight1 = %f, weight2 = %f, bias = %f costs = %f\n", weight1, weight2,
         bias, cost(weight1, weight2, bias));

  for (size_t i = 0; i < 2; ++i) {
    for (size_t j = 0; j < 2; ++j) {
      printf("%zu | %zu = %f\n", i, j,
             sigmoidf(i * weight1 + j * weight2 + bias));
    }
  }

  return EXIT_SUCCESS;
}
