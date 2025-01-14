#include "Description.h"
#include "ResultWriter.h"
#include "Matrix.h"
#include "Bounds.h"
#include "Logger.h"
#include "Result.h"
#include "Exit.h"
#include "MathCaltulations.h"

void checkResults(struct matrix* matrix, struct description* description, struct result* result, struct bounds* bounds) {
    int index;
    for (index = 0; index < result->numVariables; index++) {
        if(isVariableUsed(matrix, index) == 0) {
            printf("Warning: unused variable '%s'!\n", description->generals[index]);
            continue;
        }
        if (result->results[index] <= bounds->lowerBounds[index] && bounds->lowerEquals[index] == 0){
            ext(20, "Objective function is unbounded.\n");
        } else if (result->results[index] < bounds->lowerBounds[index] && bounds->lowerEquals[index] == 1){
            ext(20, "Objective function is unbounded.\n");
        }
        if(result->results[index] >= bounds->upperBounds[index] && bounds->upperEquals[index] == 0){
            ext(20, "Objective function is unbounded.\n");
        } else if(result->results[index] > bounds->upperBounds[index] && bounds->upperEquals[index] == 1){
            ext(20, "Objective function is unbounded.\n");
        }
    }
}

void printOutResults(struct result* result, struct logger* logger, struct description* description, struct matrix* matrix, struct bounds* bounds) {
    if(!result) {
        return;
    }
    checkResults(matrix, description, result, bounds);
    if(!logger ||! logger->outputFileName) {
        printToCommandLine(result);
    } else {
        printToFile(result, logger);
    }
}

void printToFile(struct result *result, struct logger *logger) {
    int index;
    if(!result || !logger) {
        return;
    }
    FILE* file= fopen(logger->outputFileName, "w");
    if(! file){
        return;
    }
    for (index = 0; index < result->numVariables; index++) {
        fprintf(file, "%s = %.4f\n", result->variables[index], result->results[index]);
    }
    fclose(file);
}

void printToCommandLine(struct result *result) {
    int index;
    if(! result){
        return;
    }
    for(index = 0; index < result->numVariables; index++) {
        printf("%s = %.4f\n", result->variables[index], result->results[index]);
    }
}
