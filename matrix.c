#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "matrix.h"

struct _matrix {
  int rows, cols;
  int * data;
};

int getE(matrix const * mtx, int row, int col) {
  return mtx->data[(col-1) * mtx->rows + row - 1];
}

void setE(matrix * mtx, int row, int col, int val) {
  mtx->data[(col-1) * mtx->rows + row - 1] = val;
}

int badArgs(matrix const * mtx, int row, int col) {
  if (!mtx || !mtx->data)
    return -1;
  if (row <= 0 || row > mtx->rows ||
      col <= 0 || col > mtx->cols)
    return -2;
  return 0;
}

matrix * newMatrix(int rows, int cols) {
  int i;
  matrix * m;
  if (rows <=0 || cols <= 0) return NULL;

  /* allocate a matrix structure */
  m = malloc(sizeof(matrix));
  if (!m) return NULL;

  /* set dimensions */
  m->rows = rows;
  m->cols = cols;

  /* allocate a int array of length rows * cols */
  m->data = malloc(rows*cols*sizeof(int));
  if (!m->data) {
    free(m);
    return NULL;
  }
  /* set all data to 0 */
  for (i = 0; i < rows*cols; i++)
    m->data[i] = 0.0;

  return m;
}

void deleteMatrix(matrix * mtx) {
  if (mtx) {
    /* free mtx's data */
    free(mtx->data);
    /* free mtx itself */
    free(mtx);
  }
}

int setElement(matrix * mtx, int row, int col,
               int val) {
  int err = badArgs(mtx, row, col);
  if (err) return err;
  setE(mtx, row, col, val);
  return 0;
}

int getElement(matrix const * mtx, int row, int col,
               int * val) {
  int err = badArgs(mtx, row, col);
  if (err) return err;
  if (!val) return -1;

  *val = getE(mtx, row, col);
  return 0;
}

int printMatrix(matrix const * mtx) {
  int row, col;

  if (!mtx) return -1;

  for (row = 1; row <= mtx->rows; row++) {
    for (col = 1; col <= mtx->cols; col++) {
      /* Print the floating point element with
       *  - either a - if negative of a space if positive
       *  - at least 3 spaces before the .
       *  - precision to the hundredths place */
      printf("% 6d ", getE(mtx, row, col));
    }
    /* separate rows by newlines */
    printf("\n");
  }
  return 0;
}

int isSquare(matrix const * mtx) {
  return mtx && mtx->rows == mtx->cols;
}

/*
int main() {
    matrix * R;
    int err;
    R = newMatrix(4, 4);
    err = setElement(R, 1, 1, 2048);
    err = setElement(R, 2, 3, 256);
    err = setElement(R, 2, 4, 2);
    err = setElement(R, 3, 1, 2);
    err = setElement(R, 3, 2, 2);
    err = setElement(R, 4, 3, 2);

    err = printMatrix(R); assert(!err);
    printf("\n");

    return 0;
} 
*/
