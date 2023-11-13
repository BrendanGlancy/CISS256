#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Training data
float train[][2] = {
    {0, 0}, {1, 2}, {2, 4}, {3, 6}, {4, 8},
};
#define TRAIN_COUNT ((float)sizeof(train) / sizeof(train[0]))

float rand_float() { return (float)rand() / (float)RAND_MAX; }

float cost(float w) {
  float result = 0.0f;
  for (size_t i = 0; i < TRAIN_COUNT; ++i) {
    float x = train[i][0];
    float y = x * w;
    float d = y - train[i][1];
    result += d * d;
  }
  result /= TRAIN_COUNT;
  return result;
}

int main() {
  srand(time(0));
  float w = rand_float() * 10.0f;

  // finite difference -- approximation of deriatives
  float epsilon = 1e-3;
  float learning_rate = 1e-3;

  for (size_t i = 0; i < 10000; ++i) {
    float distance_cost = (cost(w + epsilon) - cost(w)) / epsilon;
    w -= learning_rate * distance_cost;
    printf("w = %f -- cost = %f\n", w, cost(w));
  }

  printf("--------------\n");
  printf("%f\n", w);

  return EXIT_SUCCESS;
}
