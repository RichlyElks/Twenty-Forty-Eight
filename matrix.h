#ifndef MATRIX_H_
#define MATRIX_H_

typedef struct _matrix matrix;

matrix * newMatrix(int rows, int cols);
void deleteMatrix(matrix * mtx);
int setElement(matrix * mtx, int row, int col, int val);
int getElement(matrix const * mtx, int row, int col, int * val);
int printMatrix(matrix const * mtx);
int isSquare(matrix const * mtx);
int product(matrix const * mtx1, matrix const * mtx2, matrix * prod);
int isIdentity(matrix const * m);
/* Copies a submatrix of A to B starting at element
 * (row,col) and filling B.  Returns 0 if successful
 * and -1 otherwise.
 */
int submatrix(matrix const * A, matrix * B, int row, int col);
/* Performs Gauss-Jordan elimination of A putting
 * result in GJ.  Matrix A should have at least as
 * many columns as rows.  Matrix GJ should have the
 * same dimensions as A.  Returns 0 if successful
 * and -1 otherwise. */
int gaussJordan(matrix const * A, matrix * GJ);

#endif
