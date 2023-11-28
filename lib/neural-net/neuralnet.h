#ifndef NEURALNET_H_
#define NEURALNET_H_

#include <math.h>
#include <stddef.h>
#include <stdio.h>

#ifndef NN_ASSERT
#include <assert.h>
#define NN_ASSERT assert
#endif  // NN_ASSERT

#define ARRAY_LEN(a) (sizeof(a) / sizeof(a[0]))

typedef enum {
  ACT_SIGMOID,
  ACT_RELU,
  ACT_TANH,
  ACT_SIN,
} Act;

/**
 * generates a random number from 0-1
 */
float rand_float(void);

/**
 * Condenses values from -oo to oo from 0 to 1
 * @params float x
 */
float sigmoidf(float x);

typedef struct {
  size_t capacity;
  size_t size;
  // uintptr_t *words;
} Region;

#ifndef NN_MALLOC
#include <stdlib.h>
#define NN_MALLOC malloc
#endif  // NN_MALLOC

typedef struct {
  size_t rows;
  size_t cols;
  size_t stride;
  float *es;
} Matrix;

typedef struct {
  size_t cols;
  float *elements;
} Row;

#define MAT_AT(m, i, j) (m).es[(i) * (m).stride + j]
#define ROW_AT(row, col) (row).elements[col]

/**
 * Returns a row as a matrix
 */
Matrix row_as_matrix(Row row);

/**
 * Allocates memory for our matrix
 * @param size_t rows
 * @param size_t cols
 */
Matrix matrix_alloc(size_t rows, size_t cols);

/**
 * Fills a matrix with a number
 * @param Matrix m
 * @param float num
 */
void matrix_fill(Matrix m, float num);

/**
 * Randomize our matrix
 * @param Matrix m
 */
void matrix_randomize(Matrix m, float low, float high);

/**
 * Matrix Multiplication
 * @param size_t rows
 * @param size_t cols
 */
void matrix_multi(Matrix dest, Matrix a, Matrix b);

/**
 * Subsection of a matrix
 * @param Matrix dest
 * @param size_t rows
 */
void matrix_sub(Matrix dest, size_t rows);

/**
 * Matrix summation
 * @param Matrix dest
 * @param Matrix a
 * @param Matrix b
 */
void matrix_sum(Matrix dest, Matrix a);

/**
 * Returns a single row of a matrix
 */
Matrix matrix_row(Matrix m, size_t row);

/**
 * memcopy a matrix
 */
void matrix_copy(Matrix dst, Matrix src);

/**
 * Applies sigmoid to our matrix
 * @param Matrix m
 */
void matrix_sig(Matrix m);

/**
 * Prints our matrix, and the name
 * @param Matrix m
 * @param char name
 */
void matrix_print(Matrix m, const char *name, size_t padding);
#define MAT_PRINT(m) matrix_print(m, #m);

typedef struct {
  size_t *arch;
  size_t arch_count;
  Matrix *weights;
  Matrix *biases;

  Matrix *activations;  // the amount of activations is count + 1
} NN;

#define NN_INPUT(nn) (nn).activations[0]
#define NN_OUTPUT(nn) (nn).activations[(nn).arch_count]

/**
 * Allocates memory for a neural network
 * @param size_t arch_count
 * @param size_t *arch
 */
NN nn_alloc(size_t arch_count, size_t *arch);

/**
 * Prints a neural network
 * @param NN nn
 * @param char name
 */
void nn_print(NN nn, const char *name);
#define NN_PRINT(nn) nn_print(nn, #nn);

/**
 * Randomizes a neural network
 * @param NN nn
 * @param float low
 * @param float high
 */
void nn_randomize(NN nn, float low, float high);

/**
 * Forward propagation
 * @param NN nn
 */
void nn_forward(NN nn);

/**
 * Cost function
 * @param NN nn
 */
void nn_finite_diff(NN nn, float epsilon, Matrix ti, Matrix to, NN grad);

/**
 * Cost function
 * @param NN nn
 * @param Matrix ti
 * @param Matrix to
 */
float nn_cost(NN m, Matrix ti, Matrix to);
float nn_learn(NN nn, NN g, float rate);

#endif  // NEURALNET_H_

#ifdef NN_IMPLEMENTATION

float sigmoidf(float x) { return 1.f / (1.f + expf(-x)); }

float rand_float(void) { return (float)rand() / (float)RAND_MAX; }

Matrix matrix_alloc(size_t rows, size_t cols) {
  Matrix m;
  m.rows = rows;
  m.cols = cols;
  m.stride = cols;
  m.es = NN_MALLOC(sizeof(*m.es) * rows * cols);
  NN_ASSERT(m.es != NULL);

  return m;
}

void matrix_multi(Matrix dest, Matrix a, Matrix b) {
  NN_ASSERT(a.cols == b.rows);
  size_t n = a.cols;
  NN_ASSERT(dest.rows == a.rows);
  NN_ASSERT(dest.cols == b.cols);

  for (size_t i = 0; i < dest.rows; ++i) {
    for (size_t j = 0; j < dest.cols; ++j) {
      MAT_AT(dest, i, j);
      for (size_t k = 0; k < n; ++k) {
        MAT_AT(dest, i, j) += MAT_AT(a, i, k) * MAT_AT(b, k, j);
      }
    }
  }
}

void matrix_sum(Matrix dest, Matrix a) {
  NN_ASSERT(dest.rows == a.rows);
  NN_ASSERT(dest.cols == a.cols);

  for (size_t i = 0; i < dest.rows; ++i) {
    for (size_t j = 0; j < dest.cols; ++j) {
      MAT_AT(dest, i, j) += MAT_AT(a, i, j);
    }
  }
}

void matrix_print(Matrix m, const char *name, size_t padding) {
  printf("%*s%s = [\n", (int)padding, "", name);
  for (size_t i = 0; i < m.rows; ++i) {
    printf("%*s", (int)padding, "");
    for (size_t j = 0; j < m.cols; ++j) {
      printf("%f ", MAT_AT(m, i, j));
    }
    printf("\n");
  }
  printf("%*s]\n", (int)padding, "");
}

void matrix_fill(Matrix m, float num) {
  for (size_t i = 0; i < m.rows; ++i) {
    for (size_t j = 0; j < m.cols; ++j) {
      MAT_AT(m, i, j) = num;
    }
  }
}

void matrix_randomize(Matrix m, float low, float high) {
  for (size_t i = 0; i < m.rows; ++i) {
    for (size_t j = 0; j < m.cols; ++j) {
      MAT_AT(m, i, j) = rand_float() * (high - low) + low;
    }
  }
}

NN nn_alloc(size_t arch_count, size_t *arch) {
  NN_ASSERT(arch_count > 0);

  NN nn;
  nn.arch = arch;
  nn.arch_count = arch_count - 1;

  nn.weights = NN_MALLOC(sizeof(*nn.weights) * nn.arch_count);
  NN_ASSERT(nn.weights != NULL);

  nn.biases = NN_MALLOC(sizeof(*nn.biases) * nn.arch_count);
  NN_ASSERT(nn.biases != NULL);

  nn.activations = NN_MALLOC(sizeof(*nn.activations) * (nn.arch_count + 1));
  NN_ASSERT(nn.activations != NULL);

  nn.activations[0] = matrix_alloc(1, arch[0]);
  for (size_t i = 1; i < arch_count; ++i) {
    nn.weights[i - 1] = matrix_alloc(nn.activations[i - 1].cols, arch[i]);
    nn.biases[i - 1] = matrix_alloc(1, arch[i]);
    nn.activations[i] = matrix_alloc(1, arch[i]);
  }

  return nn;
}

void matrix_sig(Matrix m) {
  for (size_t i = 0; i < m.rows; ++i) {
    for (size_t j = 0; j < m.cols; ++j) {
      MAT_AT(m, i, j) = sigmoidf(MAT_AT(m, i, j));
    }
  }
}

Matrix matrix_row(Matrix m, size_t row) {
  return (Matrix){
      .rows = 1,
      .cols = m.cols,
      .stride = m.stride,
      .es = &MAT_AT(m, row, 0),
  };
}

void matrix_copy(Matrix dst, Matrix src) {
  NN_ASSERT(dst.rows == src.rows);
  NN_ASSERT(dst.cols == src.cols);

  for (size_t i = 0; i < dst.rows; ++i) {
    for (size_t j = 0; j < dst.cols; ++j) {
      MAT_AT(dst, i, j) = MAT_AT(src, i, j);
    }
  }
}

void nn_print(NN nn, const char *name) {
  char buf[256];
  printf("%s = [\n", name);
  for (size_t i = 0; i < nn.arch_count - 1; ++i) {
    snprintf(buf, sizeof(buf), "ws%zu", i);
    mat_print(nn.weights[i], buf, 4);
    snprintf(buf, sizeof(buf), "bs%zu", i);
    row_print(nn.biases[i], buf, 4);
  }
  printf("]\n");
}

void nn_randomize(NN nn, float low, float high) {
  for (size_t i = 0; i < nn.arch_count; ++i) {
    matrix_randomize(nn.weights[i], low, high);
    matrix_randomize(nn.biases[i], low, high);
  }
}

void nn_forward(NN nn) {
  for (size_t i = 0; i < nn.arch_count; ++i) {
    matrix_multi(nn.activations[i + 1], nn.activations[i], nn.weights[i]);
    matrix_sum(nn.activations[i + 1], nn.biases[i]);
    matrix_sig(nn.activations[i + 1]);
  }
}

float nn_cost(NN nn, Matrix ti, Matrix to) {
  NN_ASSERT(ti.rows == to.rows);
  size_t n = ti.rows;

  float c = 0;
  for (size_t i = 0; i < n; ++i) {
    Matrix x = matrix_row(ti, i);
    Matrix y = matrix_row(to, i);

    matrix_copy(NN_INPUT(nn), x);
    nn_forward(nn);
    NN_OUTPUT(nn);

    size_t q = to.cols;
    for (size_t j = 0; j < q; ++j) {
      float d = MAT_AT(NN_OUTPUT(nn), 0, j) - MAT_AT(y, 0, j);
      c += d * d;
    }
  }

  return c / n;
}

void nn_finite_diff(NN nn, float epsilon, Matrix ti, Matrix to, NN grad) {
  float saved;
  float c = nn_cost(nn, epsilon, ti, to, grad);

  NN g = nn_alloc(nn.arch, nn.arch_count);

  for (size_t i = 0; i < m.count; ++i) {
    Matrix w = nn.weights[i];
    for (size_t j = 0; j < w.rows; ++j) {
      for (size_t k = 0; k < w.cols; ++k) {
        saved = MAT_AT(w, j, k);
        MAT_AT(w, j, k) += epsilon;
        MAT_AT(nn_cost(g.weights[i], j, k) = (nn_cost(m, epsilon, t) - c) / epsilon;
        MAT_AT(nn.weights, j, k) = saved;
      }
    }

    for (size_t k = 0; i < length; k++) {
      saved = MAT_AT(nn.biases, i, k);
      ROW_AT(nn.biases, i, k) += epsilon;
      ROW_AT(g.biases[i], k) = (nn_cost(nn, t) - c) / epsilon;
      ROW_AT(nn.biases, i, k) = saved;
    }
  }
}

void nn_learn(NN nn, NN g, float rate) {
  for (size_t i = 0; i < nn.count; ++i) {
    for (size_t j = 0; j < nn.weights[i].rows; ++j) {
      for (size_t k = 0; k < nn.weights[i].cols; ++k) {
        MAT_AT(nn.weights[i], j, k) -= MAT_AT(g.weights[i], j, k) * rate;
      }
    }

    for (size_t k = 0; k < nn.biases[i].cols; ++k) {
      for (size_t k = 0; k < nn.biases[i].cols; ++k) {
        MAT_AT(nn.biases[i], k) -= MAT_AT(g.biases[i], k) * rate;
      }
    }
  }
}

#endif  // NN_IMPLEMENTATION
