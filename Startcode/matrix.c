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
    unsigned int cause1 = (matrix1.rows != matrix2.rows);
    unsigned int cause2= ((matrix1.cols != matrix2.cols) && ((matrix1.cols != 1) && (matrix2.cols != 1)));
    
    if(cause1 || cause2){ //Prüfe ob Matrixaddition möglich ist
        return empty;
    }
    
    unsigned int var; //Vergleicht, welche Matrix mehr Spalten hat damit eine evtl. breitere Matrix an der korrekten Stelle steht
    var = (matrix1.cols > matrix2.cols) ? matrix1.cols : matrix2.cols;

    Matrix result = createMatrix(matrix1.rows, var); //Erstellt Zielmatrix
    if(result.buffer == NULL){
        return empty;
    }
    
    for(unsigned int i = 0; i < matrix1.rows; i++) //Einzelnes einsetzen der Summe in die Zielmatrix
    {
        for(unsigned int j = 0; j < var; j++)
        {
            unsigned int col1, col2;
            col1 = (matrix1.cols == 1) ? 0 : j;
            col2 = (matrix2.cols == 1) ? 0 : j;
            
            temp1 = getMatrixAt(matrix1, i, col1) + getMatrixAt(matrix2, i, col2);
            
            setMatrixAt(temp1, result, i, j);
        }
    }

    return result;

}

Matrix multiply(const Matrix matrix1, const Matrix matrix2)
{
    Matrix empty = {0, 0, NULL};

    if(matrix1.cols != matrix2.rows){ //Prüfe ob Matrixmultiplikation möglich ist
        return empty;
    }

    Matrix result = createMatrix(matrix1.rows, matrix2.cols); //Erstellt Zielmatrix
    if(result.buffer == NULL){
        return empty;
    }

    for(unsigned int i = 0; i < matrix1.rows; i++)
    {
        for(unsigned int j = 0; j < matrix2.cols; j++)
        {
            MatrixType sum = 0; //Summe wird regelmäßig zurückgesetzt
            
            for(unsigned int k = 0; k < matrix1.cols; k++)
            {
                sum = sum + (getMatrixAt(matrix1, i, k) * getMatrixAt(matrix2, k, j)); //Berechne erst Produkt, dann Summe
            }
            setMatrixAt(sum, result, i, j);
        }
    }

    return result;
}