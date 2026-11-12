#include <stdlib.h>
#include <string.h>
#include "matrix.h"

// TODO Matrix-Funktionen implementieren

Matrix createMatrix(unsigned int rows, unsigned int cols)
{
    Matrix empty = {0, 0, NULL};
    
    if(rows == 0 || cols == 0){
        return empty;
    }
    MatrixType *buffer = calloc((rows * cols), sizeof(MatrixType));
    if(buffer == NULL){
        return empty;
    }
    Matrix result;

    result.rows = rows;
    result.cols = cols;
    result.buffer = buffer; 

    return result;
}

void clearMatrix(Matrix *matrix)
{
    if(matrix == NULL){
        return;
    }
    free(matrix->buffer);

    matrix->rows = 0;
    matrix->cols = 0;
    matrix->buffer = NULL;
}

void setMatrixAt(MatrixType value, Matrix matrix, unsigned int rowIdx, unsigned int colIdx)
{
    if(rowIdx >= matrix.rows || colIdx >= matrix.cols){
        return;
    }
    matrix.buffer[rowIdx * matrix.cols + colIdx] = value;
}

MatrixType getMatrixAt(const Matrix matrix, unsigned int rowIdx, unsigned int colIdx)
{
    if(rowIdx >= matrix.rows || colIdx >= matrix.cols){
        return UNDEFINED_MATRIX_VALUE;
    }
    return matrix.buffer[rowIdx * matrix.cols + colIdx];
}

Matrix add(const Matrix matrix1, const Matrix matrix2)
{
    Matrix empty = {0, 0, NULL};
    MatrixType temp1;
    
    if(matrix1.rows != matrix2.rows || matrix1.cols != matrix2.cols){
        return empty;
    }
    Matrix result = createMatrix(matrix1.rows, matrix1.cols);
    if(result.buffer == NULL){
        return empty;
    }

    for(unsigned int i = 0; i < matrix1.rows; i++)
    {
        for(unsigned int j = 0; j < matrix1.cols; j++)
        {
            temp1 = getMatrixAt(matrix1, i, j) + getMatrixAt(matrix2, i, j);
            
            setMatrixAt(temp1, result, i, j);
        }
    }

    return result;

}

Matrix multiply(const Matrix matrix1, const Matrix matrix2)
{
    
}