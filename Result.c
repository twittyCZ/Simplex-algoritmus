#include "stdlib.h"
#include "string.h"
#include "Description.h"
#include "Result.h"

void resultAllocate(struct result** result, struct description* description, const char** variables, int numVariables, float* results){
    if(! result || ! description) {
        return;
    }
    (*result) = malloc(sizeof(struct result));
    if(! (*result)) {
        return;
    }
    resultInnit(result, description, variables, numVariables, results);
}

void resultInnit(struct result** result, struct description* description, const char** variables, int numVariables, float* results){
    int index;
    if(! result ||! (*result)) {
        return;
    }
    (*result)->numVariables = numVariables;
    (*result)->results = malloc(sizeof (float) * numVariables);
    if(! (*result)->results){
        return;
    }
    (*result)->variables = (char**) malloc(numVariables * sizeof(char*));
    if(! (*result)->variables) {
        return;
    }
    for (index = 0; index < numVariables; index++) {
        (*result)->variables[index] = strdup(description->generals[index]);
        if (! (*result)->variables[index]) {
            return;
        }
    }
    for (index = 0; index < numVariables; index++) {
        (*result)->results[index] = 0;
    }
}

void resultAdd(struct result** result, int position, float value){
    if(! result ||! (*result) ||  position >= (*result)->numVariables) {
        return;
    }
    (*result)->results[position] = value;
}

void resultFree(struct result** result){
    if (! result ||! (*result)) {
        return;
    }
    resultDeinnit(result);
    free(*result);
    (*result) = NULL;
}

void resultDeinnit(struct result** result) {
    int index;
    if (!result || !(*result)) {
        return;
    }
    if ((*result)->variables) {
        for (index = 0; index < (*result)->numVariables; index++) {
            free((*result)->variables[index]);
        }
        free((*result)->variables);
        (*result)->variables = NULL;
    }
    if ((*result)->results) {
        free((*result)->results);
        (*result)->results = NULL;
    }
    (*result)->numVariables = 0;
}