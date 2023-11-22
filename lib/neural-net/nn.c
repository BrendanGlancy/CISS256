#include <stdlib.h>
#include <time.h>
#define NN_IMPLEMENTATION
#include "neuralnet.h"

int main() {
  srand(time(0));

  Matrix w1 = matrix_alloc(2, 2);
  Matrix b1 = matrix_alloc(1, 2);
  Matrix w2 = matrix_alloc(2, 1);
  Matrix b2 = matrix_alloc(1, 1);

  matrix_randomize(w1, 0, 1);
  matrix_randomize(b1, 0, 1);
  matrix_randomize(w2, 0, 1);
  matrix_randomize(b2, 0, 1);

  MAT_PRINT(w1);
  MAT_PRINT(b1);
  MAT_PRINT(w2);
  MAT_PRINT(b2);

  return 0;
}
