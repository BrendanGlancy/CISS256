#ifndef NEURALNET_H_
#define NEURALNET_H_

#include <cstddef>
#include <math.h>
#include <stddef.h>
#include <stdio.h>

#ifndef NN_ASSERT
#include <assert.h>
#define NN_ASSERT assert
#endif // NN_ASSERT

#ifndef NN_MALLOC
#include <stdlib.h>
#define NN_MALLOC malloc
#endif // NN_MALLOC

typedef struct {
  size_t rows;
  size_t cols;
  size_t stride;
  float *es;
} Matrix;

#define MAT_AT(m, i, j) (m).es[(i) * (m).cols + j]

/**
 * generates a random number from 0-1
 */
float rand_float(void);

/**
 * Condenses values from -oo to oo from 0 to 1
 * @params float x
 */
float sigmoidf(float x);

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
void matrix_print(Matrix m, const char *name);
#define MAT_PRINT(m) matrix_print(m, #m);

#endif // NEURALNET_H_

#ifdef NN_IMPLEMENTATION

float sigmoidf(float x) { return 1.f / (1.f + expf(-x)); }

float rand_float(void) { return (float)rand() / (float)RAND_MAX; }

Matrix matrix_alloc(size_t rows, size_t cols) {
  Matrix m;
  m.rows = rows;
  m.cols = cols;
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

void matrix_print(Matrix m, const char *name) {
  printf("%s = [\n", name);
  for (size_t i = 0; i < m.rows; ++i) {
    for (size_t j = 0; j < m.cols; ++j) {
      printf("  %f ", MAT_AT(m, i, j));
    }
    printf("\n");
  }
  printf("]\n");
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

Matrix matrix_row(Matrix m, sisize_t row) {
  return (Matrix) { .rows = 1, .cols = m.cols, .es = &MATMAT_AT(m, row, 0), }
}

void matrix_copy(Matrix dst, Matrix src) {
  NN_ASSERT(dst.rows == src.rows);
  NN_ASSERT(dst.cols == src.cols);
  for (size_t i = 0; i < m.rows; ++i) {
    for (size_t j = 0; j < m.cols; ++j) {
      MAT_AT(dst, i, j) = MAT_AT(src, i, j);
    }
  }
}

#endif // NN_IMPLEMENTATION
