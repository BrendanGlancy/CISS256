#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Training data
float train[][2] = {
    {0, 0}, {1, 2}, {2, 4}, {3, 6}, {4, 8},
};
#define TRAIN_COUNT ((float)sizeof(train) / sizeof(train[0]))

float rand_float() { return (float)rand() / (float)RAND_MAX; }

// input1, input2, input3 ..., b
// weight1, weight2, weight3
// input1 * weight1 ... + b

float cost(float weight, float bias) {
  float result = 0.0f;
  for (size_t i = 0; i < TRAIN_COUNT; ++i) {
    float x = train[i][0];
    float y = x * weight + bias;
    float d = y - train[i][1];
    result += d * d;
  }
  result /= TRAIN_COUNT;
  return result;
}

int main() {
  // stir the pile of linear algeabra
  srand(time(0));
  float weight = rand_float() * 10.0f;
  float bias = rand_float() * 5.0f;

  // finite difference -- approximation of deriatives
  float epsilon = 1e-3;
  float learning_rate = 1e-3;

  for (size_t i = 0; i < 1000; ++i) {
    float c = cost(weight, bias);
    float distance_weight = (cost(weight + epsilon, bias) - c) / epsilon;
    float distance_bias = (cost(weight, bias + epsilon) - c) / epsilon;
    weight -= learning_rate * distance_weight;
    printf("weight = %f -- cost = %f -- bias = %f\n", weight, c, bias);
  }

  printf("--------------\n");
  printf("%f\n", weight);

  return EXIT_SUCCESS;
}
