#ifndef NEURALNET_H_
#define NEURALNET_H_

#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#ifndef NN_ACT
#define NN_ACT ACTIVATION_SIGMOID
#endif  // NN_ACT

#ifndef NN_RELU_PARAM
#define NN_RELU_PARAM 0.01f
#endif  // NN_RELU_PARAM

#ifndef NN_MALLOC
#include <stdlib.h>
#define NN_MALLOC malloc
#endif  // NN_MALLOC

#ifndef NN_ASSERT
#include <assert.h>
#define NN_ASSERT assert
#endif  // NN_ASSERT

#define ARRAY_LEN(a) (sizeof(a) / sizeof(a[0]))

typedef enum {
  ACTIVATION_SIGMOID,
  ACTIVATION_RELU,
  ACTIVATION_TANH,
  ACTIVATION_SIN,
} ACTIVATION;

float rand_float(void);

/**
 * Takes values from -oo to +oo and maps them to 0 to 1
 * @param float x
 */
float sigmoidf(float x);

/**
 * F(x) = x if x > 0 else x * NN_RELU_PARAM
 * @param float x
 */
float reluf(float x);

/**
 * Hyperbolic time chamber tanh
 * @param float x
 * @return float
 */
float tanhf(float x);

/**
 * Dispatch to the corresponding activation function
 * @param float x
 * @param ACTIVATION act
 * @return float
 */
float activationf(float x, ACTIVATION act);

/**
 * Derivative of the activation function
 * @param float x
 * @param ACTIVATION activations
 * @return float
 */
float activationdf(float x, ACTIVATION act);

/**
 * A region is a block of memory that can be allocated from
 * @param Region *r
 * @param size_t size
 * @param uintptr_t elements
 * @return void *
 */
typedef struct {
  size_t capacity;
  size_t size;
  uintptr_t *elements;
} Region;

// capacity is in bytes
Region region_alloc_alloc(size_t capacity_bytes);
void *region_alloc(Region *r, size_t size_bytes);
#define region_reset(r) (NN_ASSERT((r) != NULL), (r)->size = 0)
#define region_occupied_bytes(r) \
  (NN_ASSERT((r) != NULL), (r)->size * sizeof(*(r)->elements))
#define region_save(r) (NN_ASSERT((r) != NULL), (r)->size)
#define region_rewind(r, s) (NN_ASSERT((r) != NULL), (r)->size = s)

typedef struct {
  size_t rows;
  size_t cols;
  float *elements;
} Matrix;

typedef struct {
  size_t cols;
  float *elements;
} Row;

#define ROW_AT(row, col) (row).elements[(col)]

Matrix row_as_matrix(Row row);
#define row_alloc(r, cols) matrix_row(matrix_alloc(r, 1, cols), 0)
Row row_slice(Row row, size_t i, size_t cols);
#define row_rand(row, low, high) matrix_randomize(row_as_matrix(row), low, high)
#define row_fill(row, x) matrix_fill(row_as_matrix(row), x);
#define row_print(row, name, padding) \
  matrix_print(row_as_matrix(row), name, padding)
#define row_copy(dst, src) matrix_copy(row_as_matrix(dst), row_as_matrix(src))

#define MAT_AT(m, i, j) (m).elements[(i) * (m).cols + (j)]

/**
 * Allocates memory for our matrix
 * @param size_t rows
 * @param size_t cols
 */
Matrix matrix_alloc(Region *r, size_t rows, size_t cols);

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
 * Matrix summation
 * @param Matrix dest
 * @param Matrix a
 * @param Matrix b
 */
void matrix_sum(Matrix dest, Matrix a);

/**
 * Matrix activation, applies the activation function to our matrix
 * @param Matrix m
 */
void matrix_activation(Matrix m);

/**
 * Returns a single row of a matrix
 */
Row matrix_row(Matrix m, size_t row);

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

/**
 * Shuffles the rows of a matrix
 * @param Matrix m
 */
void mat_shuffle_rows(Matrix m);

#define MAT_PRINT(m) matrix_print(m, #m);

typedef struct {
  size_t *arch;
  size_t arch_count;

  Matrix *weights;
  Row *biases;

  Row *activations;  // the amount of activations is count + 1
} NN;

#define NN_INPUT(nn) (NN_ASSERT((nn).arch_count > 0), (nn).activations[0])
#define NN_OUTPUT(nn) \
  (NN_ASSERT((nn).arch_count > 0), (nn).activations[(nn).arch_count - 1])

/**
 * Allocates memory for a neural network
 * @param size_t arch_count
 * @param size_t *arch
 */
NN nn_alloc(Region *r, size_t *arch, size_t arch_count);
void nn_zero(NN nn);

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
 * @param Matrix ti
 * @param Matrix to
 * @return float
 */
float nn_cost(NN nn, Matrix t);

/**
 * Backpropagation
 * @param NN nn
 * @param Matrix ti
 * @param Matrix to
 */
NN nn_backprop(Region *r, NN nn, Matrix t);

void nn_learn(NN nn, NN g, float rate);

typedef struct {
  size_t begin;
  float cost;
  bool finished;
} Batch;

void batch_process(Region *r, Batch *b, size_t batch_size, NN nn, Matrix t,
                   float rate);

#endif  // NEURALNET_H_

#ifdef NN_IMPLEMENTATION

float sigmoidf(float x) { return 1.f / (1.f + expf(-x)); }

float reluf(float x) { return x > 0 ? x : x * NN_RELU_PARAM; }

float tanhf(float x) {
  float ex = expf(x);
  float emx = expf(-x);
  return (ex - emx) / (ex + emx);
}

float activationf(float x, ACTIVATION act) {
  switch (act) {
    case ACTIVATION_SIGMOID:
      return sigmoidf(x);
    case ACTIVATION_RELU:
      return reluf(x);
    case ACTIVATION_TANH:
      return tanhf(x);
    case ACTIVATION_SIN:
      return sinf(x);
    default:
      NN_ASSERT(0 && "Invalid activation function");
      return 0;
  }
}

float activationdf(float x, ACTIVATION act) {
  switch (act) {
    case ACTIVATION_SIGMOID:
      return x * (1 - x);
    case ACTIVATION_RELU:
      return x >= 0 ? 1 : NN_RELU_PARAM;
    case ACTIVATION_TANH:
      return 1 - x * x;
    case ACTIVATION_SIN:
      return cosf(asinf(x));
    default:
      NN_ASSERT(0 && "Invalid activation function");
      return 0;
  }
}

float rand_float(void) { return (float)rand() / (float)RAND_MAX; }

Matrix matrix_alloc(Region *r, size_t rows, size_t cols) {
  Matrix m;
  m.rows = rows;
  m.cols = cols;
  m.elements = region_alloc(r, rows * cols * sizeof(*m.elements));
  NN_ASSERT(m.elements != NULL);

  return m;
}

void matrix_multi(Matrix dst, Matrix a, Matrix b) {
  NN_ASSERT(a.cols == b.rows);
  size_t n = a.cols;
  NN_ASSERT(dst.rows == a.rows);
  NN_ASSERT(dst.cols == b.cols);

  for (size_t i = 0; i < dst.rows; ++i) {
    for (size_t j = 0; j < dst.cols; ++j) {
      MAT_AT(dst, i, j) = 0;
      for (size_t k = 0; k < n; ++k) {
        MAT_AT(dst, i, j) += MAT_AT(a, i, k) * MAT_AT(b, k, j);
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

void matrix_activation(Matrix m) {
  for (size_t i = 0; i < m.rows; ++i) {
    for (size_t j = 0; j < m.cols; ++j) {
      MAT_AT(m, i, j) = activationf(MAT_AT(m, i, j), NN_ACT);
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

void matrix_sig(Matrix m) {
  for (size_t i = 0; i < m.rows; ++i) {
    for (size_t j = 0; j < m.cols; ++j) {
      MAT_AT(m, i, j) = sigmoidf(MAT_AT(m, i, j));
    }
  }
}

Row matrix_row(Matrix m, size_t row) {
  return (Row){
      .cols = m.cols,
      .elements = &MAT_AT(m, row, 0),
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

NN nn_alloc(Region *r, size_t *arch, size_t arch_count) {
  NN_ASSERT(arch_count > 0);

  NN nn;
  nn.arch = arch;
  nn.arch_count = arch_count;

  nn.weights = region_alloc(r, sizeof(*nn.weights) * nn.arch_count - 1);
  NN_ASSERT(nn.weights != NULL);
  nn.biases = region_alloc(r, sizeof(*nn.biases) * nn.arch_count - 1);
  NN_ASSERT(nn.biases != NULL);
  nn.activations = region_alloc(r, sizeof(*nn.activations) * (nn.arch_count));
  NN_ASSERT(nn.activations != NULL);

  nn.activations[0] = row_alloc(r, arch[0]);

  for (size_t i = 1; i < arch_count; ++i) {
    nn.weights[i - 1] = matrix_alloc(r, nn.activations[i - 1].cols, arch[i]);
    nn.biases[i - 1] = row_alloc(r, arch[i]);
    nn.activations[i] = row_alloc(r, arch[i]);
  }

  return nn;
}

void nn_zero(NN nn) {
  for (size_t i = 0; i < nn.arch_count; ++i) {
    matrix_fill(nn.weights[i], 0);
    row_fill(nn.biases[i], 0);
    row_fill(nn.activations[i], 0);
  }
  row_fill(nn.activations[nn.arch_count], 0);
}

void nn_print(NN nn, const char *name) {
  char buf[256];
  printf("%s = [\n", name);
  for (size_t i = 0; i < nn.arch_count; ++i) {
    snprintf(buf, sizeof(buf), "weights%zu", i);
    matrix_print(nn.weights[i], buf, 4);
    snprintf(buf, sizeof(buf), "biases%zu", i);
    row_print(nn.biases[i], buf, 4);
  }
  printf("]\n");
}

void nn_rand(NN nn, float low, float high) {
  for (size_t i = 0; i < nn.arch_count; ++i) {
    matrix_randomize(nn.weights[i], low, high);
    row_rand(nn.biases[i], low, high);
  }
}

void nn_forward(NN nn) {
  for (size_t i = 0; i < nn.arch_count - 1; ++i) {
    matrix_multi(row_as_matrix(nn.activations[i + 1]),
                 row_as_matrix(nn.activations[i]), nn.weights[i]);
    matrix_sum(row_as_matrix(nn.activations[i + 1]),
               row_as_matrix(nn.biases[i]));
    matrix_activation(row_as_matrix(nn.activations[i + 1]));
  }
}

float nn_cost(NN nn, Matrix t) {
  NN_ASSERT(NN_INPUT(nn).cols + NN_OUTPUT(nn).cols == t.cols);
  size_t n = t.rows;

  float c = 0;
  for (size_t i = 0; i < n; ++i) {
    Row row = matrix_row(t, i);
    Row x = row_slice(row, 0, NN_INPUT(nn).cols);
    Row y = row_slice(row, NN_INPUT(nn).cols, NN_OUTPUT(nn).cols);

    row_copy(NN_INPUT(nn), x);
    nn_forward(nn);
    size_t q = y.cols;
    for (size_t j = 0; j < q; ++j) {
      float d = ROW_AT(NN_OUTPUT(nn), j) - ROW_AT(y, j);
      c += d * d;
    }
  }

  return c / n;
}

/**
 * TODO HAYDEN: Refactor this
 * integrate dericvative activation function activationdf()
 * Better variable names
 *
 */
NN nn_backprop(Region *r, NN nn, Matrix t) {
  size_t n = t.rows;
  NN_ASSERT(NN_INPUT(nn).cols + NN_OUTPUT(nn).cols == t.cols);

  NN gradient = nn_alloc(r, nn.arch, nn.arch_count);
  nn_zero(gradient);

  // i - current sample
  // l - current layer
  // j - current activation
  // k - previous activation

  for (size_t i = 0; i < n; ++i) {
    Row row = matrix_row(t, i);
    Row in = row_slice(row, 0, NN_INPUT(nn).cols);
    Row out = row_slice(row, NN_INPUT(nn).cols, NN_OUTPUT(nn).cols);

    row_copy(NN_INPUT(nn), in);
    nn_forward(nn);

    for (size_t j = 0; j < nn.arch_count; ++j) {
      row_fill(gradient.activations[j], 0);
    }

    for (size_t j = 0; j < out.cols; ++j) {
      ROW_AT(NN_OUTPUT(gradient), j) =
          ROW_AT(NN_OUTPUT(nn), j) - ROW_AT(out, j);
    }

    float s = 2;

    for (size_t l = nn.arch_count - 1; l > 0; --l) {
      for (size_t j = 0; j < nn.activations[l].cols; ++j) {
        float a = ROW_AT(nn.activations[l], j);
        float da = ROW_AT(gradient.activations[l], j);
        float qa = activationdf(a, NN_ACT);
        ROW_AT(gradient.biases[l - 1], j) += s * da * qa;
        for (size_t k = 0; k < nn.activations[l - 1].cols; ++k) {
          // j - weigradientht matrix col
          // k - weigradientht matrix row
          float pa = ROW_AT(nn.activations[l - 1], k);
          float w = MAT_AT(nn.weights[l - 1], k, j);
          MAT_AT(gradient.weights[l - 1], k, j) += s * da * qa * pa;
          ROW_AT(gradient.activations[l - 1], k) += s * da * qa * w;
        }
      }
    }
  }

  for (size_t i = 0; i < gradient.arch_count - 1; ++i) {
    for (size_t j = 0; j < gradient.weights[i].rows; ++j) {
      for (size_t k = 0; k < gradient.weights[i].cols; ++k) {
        MAT_AT(gradient.weights[i], j, k) /= n;
      }
    }
    for (size_t k = 0; k < gradient.biases[i].cols; ++k) {
      ROW_AT(gradient.biases[i], k) /= n;
    }
  }

  return gradient;
}

void nn_learn(NN nn, NN gradient, float rate) {
  for (size_t i = 0; i < nn.arch_count; ++i) {
    for (size_t j = 0; j < nn.weights[i].rows; ++j) {
      for (size_t k = 0; k < nn.weights[i].cols; ++k) {
        MAT_AT(nn.weights[i], j, k) -= rate * MAT_AT(gradient.weights[i], j, k);
      }
    }

    for (size_t k = 0; k < nn.biases[i].cols; ++k) {
      ROW_AT(nn.biases[i], k) -= rate * ROW_AT(gradient.biases[i], k);
    }
  }
}

/**
 * Actual alloc
 */
Region region_alloc_alloc(size_t capacity_bytes) {
  Region r = {0};

  size_t elements_size = sizeof(*r.elements);
  size_t capacity = (capacity_bytes + elements_size - 1) / elements_size;

  void *elements = NN_MALLOC(capacity * elements_size);
  NN_ASSERT(elements != NULL);
  r.elements = elements;
  r.capacity = capacity;

  return r;
}

void *region_alloc(Region *r, size_t size) {
  if (r == NULL) return NN_MALLOC(size);
  size_t word_size = sizeof(*r->elements);
  size_t count = (size + word_size - 1) / word_size;

  NN_ASSERT(r->size + count <= r->capacity);
  if (r->size + count > r->capacity) return NULL;
  void *result = &r->elements[r->size];
  r->size += count;
  return result;
}

void mat_shuffle_rows(Matrix m) {
  for (size_t i = 0; i < m.rows; ++i) {
    size_t j = i + rand() % (m.rows - i);
    if (i != j) {
      for (size_t k = 0; k < m.cols; ++k) {
        float t = MAT_AT(m, i, k);
        MAT_AT(m, i, k) = MAT_AT(m, j, k);
        MAT_AT(m, j, k) = t;
      }
    }
  }
}

void batch_process(Region *r, Batch *b, size_t batch_size, NN nn, Matrix t,
                   float rate) {
  if (b->finished) {
    b->finished = false;
    b->begin = 0;
    b->cost = 0;
  }

  size_t size = batch_size;
  if (b->begin + batch_size >= t.rows) {
    size = t.rows - b->begin;
  }

  // TODO: introduce similar to row_slice operation but for Mat that will give
  // you subsequence of rows
  Matrix batch_t = {
      .rows = size,
      .cols = t.cols,
      .elements = &MAT_AT(t, b->begin, 0),
  };

  NN g = nn_backprop(r, nn, batch_t);
  nn_learn(nn, g, rate);
  b->cost += nn_cost(nn, batch_t);
  b->begin += batch_size;

  if (b->begin >= t.rows) {
    size_t batch_count = (t.rows + batch_size - 1) / batch_size;
    b->cost /= batch_count;
    b->finished = true;
  }
}

Matrix row_as_matrix(Row row) {
  return (Matrix){
      .rows = 1,
      .cols = row.cols,
      .elements = row.elements,
  };
}

Row row_slice(Row row, size_t i, size_t cols) {
  NN_ASSERT(i < row.cols);
  NN_ASSERT(i + cols <= row.cols);
  return (Row){
      .cols = cols,
      .elements = &ROW_AT(row, i),
  };
}

#endif  // NN_IMPLEMENTATION
