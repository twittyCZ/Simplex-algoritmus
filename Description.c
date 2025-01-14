#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Description.h"
#include "MathCaltulations.h"
#include "Exit.h"

void descriptionAllocate(struct description** description, const char* objective, const char** constraints, int numConstraints, const char** bounds, int numBounds, const char** generals, int numGenerals, int maxOrMin) {
    if(! description) {
        return;
    }
    (*description) = malloc(sizeof(struct description));
    if (!(*description)) {
        return;
    }
    (*description)->objective = NULL;
    (*description)->constraints = NULL;
    (*description)->bounds = NULL;
    (*description)->generals = NULL;
    (*description)->numGenerals = 0;
    (*description)->numBounds = 0;
    (*description)->numConstraints = 0;
    (*description)->maxOrMin = 1;
    if (descriptionInit(description, objective, constraints, numConstraints, bounds, numBounds, generals, numGenerals, maxOrMin)) {
        ext(11, "Syntax error!\n");
    }
}

void descriptionObjectiveReinit(struct description** description, const char* objective) {
    if (!(*description) || !objective) {
        return;
    }
    if(objective[0] =='\0') {
        ext(11, "Syntax error!\n");
    }
    free((*description)->objective);
    (*description)->objective = malloc(strlen(objective) + 1);
    strcpy((*description)->objective, objective);
}


void descriptionConstraintReinit(struct description** description, const char* constraints) {
    char** temp;
    if (!*description || !constraints) {
        return;
    }
    if(constraints[0] =='\0') {
        ext(11, "Syntax error!\n");
    }
    if (!(*description)->constraints) {
        (*description)->constraints = malloc(sizeof(char*));
        if (!(*description)->constraints) {
            return;
        }
        (*description)->constraints[0] = strdup(constraints);
        if (!(*description)->constraints[0]) {
            free((*description)->constraints);
            (*description)->constraints = NULL;
            return;
        }
        (*description)->numConstraints = 1;
        return;
    }

    temp = realloc((*description)->constraints, ((*description)->numConstraints + 1) * sizeof(char*));
    if (!temp) {
        return;
    }
    (*description)->constraints = temp;
    (*description)->constraints[(*description)->numConstraints] = strdup(constraints);
    if (!(*description)->constraints[(*description)->numConstraints]) {
        return;
    }

    (*description)->numConstraints++;
}

void descriptionGeneralsReinit(struct description** description, const char* generals) {
    char** temp;
    if (!(*description) || !generals) {
        return;
    }
    if(generals[0] =='\0') {
        ext(11, "Syntax error!\n");
    }
    if (!(*description)->generals) {
        (*description)->generals = malloc(sizeof(char*));
        if (!(*description)->generals) {
            return;
        }
        (*description)->generals[0] = strdup(generals);
        if (!(*description)->generals[0]) {
            free((*description)->generals);
            (*description)->generals = NULL;
            return;
        }
        (*description)->numGenerals = 1;
        return;
    }

    temp = realloc((*description)->generals, ((*description)->numGenerals + 1) * sizeof(char*));
    if (!temp) {
        return;
    }
    (*description)->generals = temp;

    (*description)->generals[(*description)->numGenerals] = strdup(generals);
    if (!(*description)->generals[(*description)->numGenerals]) {
        return;
    }

    (*description)->numGenerals++;
}

void descriptionCheck(struct description* description) {
    if(! description || description->numGenerals == 0 || description->numConstraints == 0 || description->numBounds == 0) {
        ext(11,"Syntax error!\n");
    }
}

void descriptionMaxOrMintReinit(struct description** description, int maxOrMin){
    if(! description || ! (*description)) {
        return;
    }
    (*description)->maxOrMin = maxOrMin;
}

void descriptionBoundsReinit(struct description** description, const char* bounds) {
    char** temp;
    if (!(*description) || !bounds){
        return;
    }
    if(bounds[0] =='\0') {
        ext(11, "Syntax error!\n");
    }
    if (!(*description)->bounds) {
        (*description)->bounds = malloc(sizeof(char*));
        if (!(*description)->bounds) {
            return;
        }
        (*description)->bounds[0] = strdup(bounds);
        if (!(*description)->bounds[0]) {
            free((*description)->bounds);
            (*description)->bounds = NULL;
            return;
        }
        (*description)->numBounds = 1;
        return;
    }

    temp = realloc((*description)->bounds, ((*description)->numBounds + 1) * sizeof(char*));
    if (!temp) {
        return;
    }
    (*description)->bounds = temp;

    (*description)->bounds[(*description)->numBounds] = strdup(bounds);
    if (!(*description)->bounds[(*description)->numBounds]) {
        return;
    }

    (*description)->numBounds++;

}

int descriptionInit(struct description** description, const char* objective, const char** constraints, int numConstraints, const char** bounds, int numBounds, const char** generals, int numGenerals, int maxOrMin) {
    if(!description || !objective || !constraints || !bounds || ! generals) {
        return 0;
    }

    (*description)->objective = malloc(strlen(objective) + 1);
    if(!(*description)->objective){
        return 0;
    }

    (*description)->constraints = (char**) malloc(numConstraints * sizeof(char*));
    if(!(*description)->constraints){
        return 0;
    }

    (*description)->bounds = (char**) malloc(numBounds * sizeof(char*));
    if(!(*description)->bounds){
        return 0;
    }

    (*description)->generals = (char**) malloc(numGenerals * sizeof(char*));
    if(!(*description)->generals){
        return 0;
    }

    (*description)->numConstraints = numConstraints;
    (*description)->numBounds = numBounds;
    (*description)->numGenerals = numGenerals;
    (*description)->maxOrMin = maxOrMin;

    return 1;
}

void descriptionFree(struct description** description){
    if(!description || !*description){
        return;
    }
    descriptionDeinit(description);

    free((*description));
    *description = NULL;
}

void descriptionDeinit(struct description** description) {
    size_t index;
    if(! (*description)){
        return;
    }

    if((*description)->objective) {
        free((*description)->objective);
        (*description)->objective = NULL;
    }

    if((*description)->constraints) {
        for (index = 0; index < (*description)->numConstraints; index++) {
        free((*description)->constraints[index]);
        }
        free((*description)->constraints);
    }

    if((*description)->bounds) {
        for (index = 0; index < (*description)->numBounds; index++) {
        free((*description)->bounds[index]);
        }
        free((*description)->bounds);
    }

    if((*description)->generals){
        for (index = 0; index < (*description)->numGenerals; index++) {
        free((*description)->generals[index]);
        }
        free((*description)->generals);
    }

    (*description)->maxOrMin = 0;
    (*description)->numBounds = 0;
    (*description)->numGenerals = 0;
    (*description)->numConstraints = 0;
}


void assignmentCheck(struct description* description) {
    if(! description) {
        return;
    }
    formatEquations(description);
    mathExpressionCheck(description);
    descriptionCheck(description);
}
