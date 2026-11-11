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
    
}

void setMatrixAt(MatrixType value, Matrix matrix, unsigned int rowIdx, unsigned int colIdx)
{
    
}

MatrixType getMatrixAt(const Matrix matrix, unsigned int rowIdx, unsigned int colIdx)
{
    
}

Matrix add(const Matrix matrix1, const Matrix matrix2)
{
    
}

Matrix multiply(const Matrix matrix1, const Matrix matrix2)
{
    
}