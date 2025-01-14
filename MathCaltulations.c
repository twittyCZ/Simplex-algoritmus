#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Description.h"
#include "MathCaltulations.h"
#include "Matrix.h"
#include "Bounds.h"
#include "Result.h"
#include "Tool.h"
#include "Exit.h"
#include <limits.h>

void formatEquations(struct description* desc) {
    size_t index;
    if(! desc) {
        return;
    }
    removeWhitespace(desc->objective);
    insert_multiplication(desc->objective);
    for(index = 0; index < desc->numConstraints; index++) {
        removeWhitespace(desc->constraints[index]);
        insert_multiplication(desc->constraints[index]);
    }
    for(index = 0; index < desc->numBounds; index++) {
        removeWhitespace(desc->bounds[index]);
        insert_multiplication(desc->bounds[index]);
    }
    for(index = 0; index < desc->numGenerals; index++) {
        removeWhitespace(desc->generals[index]);
        insert_multiplication(desc->generals[index]);
    }
}

void isValidExpresion(const char *expression) {
    int len = (int) strlen(expression);
    int prevWasClosedBracket = 0;
    int prevWasOperator = 0;
    int hasVariableOrNumber = 0;
    int parenthesesBalance = 0;
    int squareBracketBalance = 0;
    int curlyBraceBalance = 0;
    int i;
    for (i = 0; i < len; i++) {
        char c = expression[i];
        if (isspace(c)) {
            ext(11, "Syntax error!\n");

        } else if (isalpha(c) || c == '_') {
            hasVariableOrNumber = 1;
            prevWasOperator = 0;
        } else if (isdigit(c)) {
            hasVariableOrNumber = 1;
            prevWasOperator = 0;
        } else if (c == '(') {
            parenthesesBalance++;
            prevWasOperator = 0;
        } else if (c == ')') {
            prevWasClosedBracket = 1;
            parenthesesBalance--;
            if (parenthesesBalance < 0) {
                ext(11, "Syntax error!\n");
            }
            prevWasOperator = 1;
        } else if (c == '[') {
            squareBracketBalance++;
            prevWasOperator = 0;
        } else if (c == ']') {
            prevWasClosedBracket = 1;
            squareBracketBalance--;
            if (squareBracketBalance < 0) {
                ext(11, "Syntax error!\n");
            }
            prevWasOperator = 1;
        } else if (c == '{') {
            curlyBraceBalance++;
            prevWasOperator = 0;
        } else if (c == '}') {
            prevWasClosedBracket = 1;
            curlyBraceBalance--;
            if (curlyBraceBalance < 0) {
                ext(11, "Syntax error!\n");
            }
            if(prevWasOperator == 1) {
                ext(11, "Syntax error!\n");
            }
            prevWasOperator = 1;
        } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '=' || c == '<' || c == '>') {
            if (prevWasOperator && (c != '>' && c != '<' && c) && (c != '+') && (c != '-') && !prevWasClosedBracket) {
                ext(11, "Syntax error!\n");
            }
            if ((c == '<' || c == '>') && (i + 1 < len) && expression[i + 1] == '=') {
                i++;
            }
            prevWasOperator = 1;
        }
        else {
            ext(11, "Syntax error!\n");
        }
    }
    if (!hasVariableOrNumber) {
        ext(11, "Syntax error!\n");
    }
}

void prepareForCalculations(struct description* description, struct matrix** matrix, struct bounds** bounds, struct result** result) {
    if (! description || ! matrix || ! bounds || ! result) {
        return;
    }
    convertEquationsIntoMatrix(description, matrix);
    convertBounds(description, bounds);
    if(integrationCheck(description, *matrix, *bounds) == EXIT_FAILURE) {
        ext(11, "Syntax error!\n");
    }
    resultAllocate(result, description, (const char **) description->generals, (int) description->numGenerals, NULL);
}

void convertEquationsIntoMatrix(struct description* desc, struct matrix** matrix) {
    int index; int general;
    if(! desc) {
        return;
    }
    matrixAllocate(matrix, (int) desc->numConstraints + 1, (int) (desc->numGenerals * 2) + 2);
    for(index = 0; index < desc->numConstraints; index++) {
        for (general = 0; general < desc->numGenerals; general++) {
            float number = getGeneralsCoeficient(desc->constraints[index], desc->generals[general]);
            matrixAddNumber(matrix, number, index, general);
        }
    }

    for (general = 0; general < desc->numGenerals; general++) {
        float number = getGeneralsCoeficient(desc->objective, desc->generals[general]);
        matrixAddNumber(matrix, (float) invertNumber(number), (int) desc->numConstraints, general);
    }
    addUnitMatrix(matrix, desc);
    addRightSide(matrix, desc);
}

void convertBounds(struct description* desc, struct bounds** bounds){
    int index;
    if(! desc) {
        return;
    }
    boundsAllocate(bounds, (int) desc->numBounds);
    for (index = 0; index < desc->numBounds; index++) {
        const char* variable = desc->generals[index];
        parseBound(bounds, desc->bounds[index], variable, index);
    }
}

int integrationCheck(struct description* desc, struct matrix* matrix, struct bounds* bounds){
    int index;
    if(! desc ||! matrix ||! bounds){
        return EXIT_FAILURE;
    }
    for(index = 0; index < bounds->numBounds; index++){
        if(bounds->upperEquals < bounds->lowerEquals){
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

void mathExpressionCheck(struct description* description) {
    int index;
    if (!description) {
        ext(11, "Syntax error!\n");
    }
    isValidExpresion(description->objective);
    extract_variables(description->objective, description);
    for (index = 0; index < description->numConstraints; index++) {
        isValidExpresion(description->constraints[index]);
    }
    for (index = 0; index < description->numBounds; index++) {
        isValidExpresion(description->bounds[index]);
    }
}

int getCoeficientIndex (struct matrix* matrix, int foundedIndexRow){
    int index, indexRow, spatne = 0;
    for (index = 0; index < matrix->numCols - 1; index++) {
        if(matrix->board[foundedIndexRow][index] == 1) {
            for (indexRow = 0; indexRow < matrix->numRows - 1; indexRow++) {
                if(indexRow == foundedIndexRow){
                    continue;
                }
                if (matrix->board[indexRow][index] != 0) {
                    spatne = 1;
                }
            }
            if(spatne == 0) {
                return index;
            }
            spatne = 0;
        }
    }
    return -1;
}

void objectiveFunctionCalculation(struct description* description, struct matrix* matrix, const float* coeficients) {
    int indexRow, indexColumn;
    float vysledek = 0;
    if(!description || !matrix || !coeficients) {
        return;
    }
    for (indexColumn = 0; indexColumn < matrix->numCols - 1; indexColumn++) {
        for (indexRow = 0; indexRow < matrix->numRows - 1; indexRow++) {
            int coeficientIndex = getCoeficientIndex(matrix, indexRow);
            vysledek += coeficients[coeficientIndex] * matrix->board[indexRow][indexColumn];
        }
        matrix->board[matrix->numRows - 1][indexColumn] = vysledek - coeficients[indexColumn];
        vysledek = 0;
    }
    if(description->maxOrMin == 1) {
        for (indexColumn = 0; indexColumn < matrix->numCols; indexColumn++) {
            matrix->board[matrix->numRows-1][indexColumn] = -matrix->board[matrix->numRows - 1][indexColumn];
        }
    }
}

void getAllCoeficients(struct matrix *matrix, float* coeficients) {
    size_t index;
    for (index = 0; index < matrix->numCols - 1; index++) {
        coeficients[index] = matrix->board[matrix->numRows - 1][index];
    }
}

void simplexMethod(struct description* description, struct matrix* matrix, struct result** result) {
    int columnIndex, rowIndex, index;
    float divider, multiplier;
    float coeficients[matrix->numCols - 1];
    getAllCoeficients(matrix, coeficients);
    while(doNextIteration(matrix) == 1) {
        columnIndex = findPivotFromObject(matrix);
        rowIndex = findPivotRowConstraint(matrix, columnIndex);
        divider = matrix->board[rowIndex][columnIndex];
        divideTheRow(matrix, rowIndex, divider);
        for (index = 0; index < matrix->numRows; index++) {
            if(index == rowIndex) {
                continue;
            }
            if(index == matrix->numRows - 1) {
                objectiveFunctionCalculation(description, matrix, coeficients);
            }
            multiplier = getMultiplier(matrix->board[rowIndex][columnIndex], matrix->board[index][columnIndex]);
            substractRow(matrix, multiplier, rowIndex, index);
        }
    }
    getResult(matrix, result);
}

void simplexTableCheck(struct matrix* matrix, int indexColumn, int* numberOfVariables, int* numberOfNegative) {
    int indexRow;
    if(!matrix || indexColumn < 0) {
        return;
    }
    for (indexRow = 0; indexRow < matrix->numRows - 1; indexRow++) {
        if (matrix->board[indexRow][indexColumn] == 1) {
            (*numberOfVariables)++;
        }
        if(matrix->board[indexRow][indexColumn] < 0) {
            (*numberOfNegative)++;
        }
    }
}

int isVariableUsed(struct matrix* matrix, int foundedVariable) {
    size_t indexColumn, indexRow;
    int used = 0;
    if (! matrix) {
        return -1;
    }
    for (indexColumn = 0; indexColumn < (matrix->numCols - 1) / 2; indexColumn++) {
        for (indexRow = 0; indexRow < matrix->numRows; indexRow++) {
            if(matrix->board[indexRow][indexColumn] != 0) {
                used = 1;
            }
        }
        if(used == 0 && indexColumn == foundedVariable) {
            return EXIT_SUCCESS;
        }
        used = 0;
    }
    return EXIT_FAILURE;
}

void getResult(struct matrix* matrix, struct result** result) {
    size_t indexColumn; size_t indexRow;
    int usedVariable = 0; int numberOfNegative = 0; int numberOfVariables = 0;
    if (!matrix || !result) {
        return;
    }
    for (indexColumn = 0; indexColumn < (matrix->numCols - 1) / 2; indexColumn++) {
        simplexTableCheck(matrix, (int) indexColumn, &numberOfVariables, &numberOfNegative);
        if(numberOfVariables == 1) {
            for (indexRow = 0; indexRow < matrix->numRows - 1; indexRow++) {
                if (matrix->board[indexRow][indexColumn] == 1) {
                    resultAdd(result, (int) indexColumn, matrix->board[indexRow][matrix->numCols - 1] / matrix->board[indexRow][indexColumn]);
                    usedVariable = 1;
                }
            }
            if (usedVariable == 0 && isVariableUsed(matrix, (int) indexColumn) == 0) {
              ext(21, "No feasible solution exists.\n");
            }
        }
        if(numberOfNegative > 1) {
          ext(21, "No feasible solution exists.\n");
        }
        numberOfVariables = 0;
        numberOfNegative = 0;
        usedVariable = 0;
    }
}

void substractRow(struct matrix* matrix, float multiplierOfNulledRow, int indexRow, int indexOfNulledRow){
    size_t index;
    for(index = 0; index < matrix->numCols; index++){
        matrix->board[indexOfNulledRow][index] = matrix->board[indexOfNulledRow][index] + matrix->board[indexRow][index] * multiplierOfNulledRow;
    }
}

int doNextIteration(struct matrix* matrix){
    size_t index;
    int nekdeMensiNezNula = 0;
    for (index = 0; index < matrix->numCols; index++) {
        if(matrix->board[matrix->numRows - 1][index] < 0){
            nekdeMensiNezNula = 1;
        }
    }
    return nekdeMensiNezNula;
}

float getMultiplier(float pivot, float number) {
    return -number / pivot;
}

void divideTheRow(struct matrix* matrix, int rowIndex, float divider){
    size_t index;
    for(index = 0; index < matrix->numCols; index++){
        matrix->board[rowIndex][index] = matrix->board[rowIndex][index] / divider;
    }
}

int findPivotRowConstraint(struct matrix* matrix, int columnIndex){
    size_t index;
    float result = (float) INT_MAX;
    int resutIndex;
    for(index = 0; index < matrix->numRows - 1; index++){
        float kandidat = matrix->board[index][matrix->numCols - 1] / matrix->board[index][columnIndex];
        if(kandidat < result && kandidat >= 0){
            result = kandidat;
            resutIndex = (int) index;
        }
    }
    if (result == (float) INT_MAX) {
        if(columnIndex >= (matrix->numCols - 1) / 2) {
        ext(20, "Objective function is unbounded.\n");
        }
    ext(21, "No feasible solution exists.\n");
    }
    return resutIndex;
}

int findPivotFromObject(struct matrix* matrix) {
    size_t index;
    float result = (float) INT_MAX;
    int resultIndex = -1;
    size_t numVariables = matrix->numCols - 1;
    for (index = 0; index < numVariables; index++) {
        if(matrix->board[matrix->numRows - 1][index] < result) {
            result = matrix->board[matrix->numRows - 1][index];
            resultIndex = (int) index;
        }
    }
    if(result == (float) INT_MAX || result == 0) {
        ext(21,"No feasible solution exists.\n");
    }
    return resultIndex;
}