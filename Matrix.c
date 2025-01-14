#include "Description.h"
#include "Matrix.h"
#include "Tool.h"

void matrixAllocate(struct matrix** matrix, int numRows, int numCols) {
    if (! matrix) {
        return;
    }
    (*matrix) = malloc(sizeof(struct matrix));
    if (!(*matrix)) {
        return;
    }
    matrixInnit(matrix, numRows, numCols -1);
}

void matrixInnit(struct matrix** matrix, int numRows, int numCols) {
    int index, col, row;
    if (!(*matrix)) {
        return;
    }
    (*matrix)->numCols = numCols;
    (*matrix)->numRows = numRows;
    (*matrix)->board = malloc(numRows * sizeof(float *));
    if (!(*matrix)->board) {
        free(*matrix);
        *matrix = NULL;
        return;
    }
    for ( row = 0; row < numRows; row++) {
        (*matrix)->board[row] = malloc(numCols * sizeof(float));
        if (!(*matrix)->board[row]) {
            for (index = 0; index < row; index++) {
                free((*matrix)->board[index]);
            }
            free((*matrix)->board);
            free(*matrix);
            *matrix = NULL;
            return;
        }
        for (col = 0; col < numCols; col++) {
            (*matrix)->board[row][col] = 0.0f;
        }
    }
}

void matrixFree(struct matrix** matrix){
    if(!matrix || !*matrix){
        return;
    }
    matrixDeinnit(matrix);
    free((*matrix));
    *matrix = NULL;
}

void matrixDeinnit(struct matrix** matrix){
    size_t index;
    if(!matrix || !*matrix || ! (*matrix)->board){
        return;
    }
    for (index = 0; index < (*matrix)->numRows; index++) {
        free((*matrix)->board[index]);
    }
    free((*matrix)->board);
    (*matrix)->numCols = 0;
    (*matrix)->numRows = 0;
}

void addUnitMatrix(struct matrix** matrix, struct description* description){
    size_t column, row, endingRow, endingColumn;
    int startingColumn, startingRow;
    if(! matrix ||! (*matrix) ||! description) {
        return;
    }
    startingColumn = (int) description->numGenerals;
    endingColumn = (*matrix)->numCols-2;
    startingRow = 0;
    endingRow = (*matrix)->numRows-1;
    for(row = startingRow; row <= endingRow; row++) {
        for (column = startingColumn; column <= endingColumn; column++) {
            if(column - description->numGenerals == row) {
                if(row < description->numConstraints){
                    (*matrix)->board[row][column] = 1;
                        if(description->maxOrMin == 0) {
                            if (contains_inequality(description->constraints[row]) == 1) {
                                (*matrix)->board[row][column] = 1;
                            } else if (contains_inequality(description->constraints[row]) == -1) {
                                (*matrix)->board[row][column] = -1;
                            } else {
                                (*matrix)->board[row][column] = 0;
                            }
                        }
                }
            }
        }
    }
}

void matrixAddNumber(struct matrix** matrix, float number, int row, int column) {
    (*matrix)->board[row][column] = number;
}

void addRightSide(struct matrix** matrix, struct description* description){
    size_t index;
    if(! matrix ||! (*matrix) ||! description) {
        return;
    }
    for(index = 0; index < description->numConstraints; index++) {
        float rightSide = getRightSide(description->constraints[index]);
        (*matrix)->board[index][(*matrix)->numCols-1] = rightSide;
    }
}

void printMatrix(struct matrix* matrix){
    size_t column, row;
    if(! matrix) {
        return;
    }
    for (row = 0; row < matrix->numRows; row++){
        for(column = 0; column < matrix->numCols; column++){
            printf("%f ", matrix->board[row][column]);
        }
        printf("\n");
    }
}
