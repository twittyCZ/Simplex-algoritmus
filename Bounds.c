#include <limits.h>
#include "Bounds.h"
#include "Tool.h"

void boundsAllocate(struct bounds** bounds, int numBounds){
    if(!bounds || numBounds <= 0) {
        return;
    }
    (*bounds) = malloc(sizeof (struct bounds));
    if(! (*bounds)){
        return;
    }
    boundsInnit(bounds, numBounds);
}

void boundsInnit(struct bounds** bounds, int numBounds){
    int index;
    if(! bounds ||! (*bounds) || numBounds <= 0){
        return;
    }
    (*bounds)->lowerBounds = malloc(sizeof (float) * numBounds);
    (*bounds)->upperBounds = malloc(sizeof (float) * numBounds);
    (*bounds)->lowerEquals = malloc(sizeof (int) * numBounds);
    (*bounds)->upperEquals = malloc(sizeof (int) * numBounds);

    if(! (*bounds)->lowerEquals || ! (*bounds)->upperEquals || ! (*bounds)->upperBounds || ! (*bounds)->lowerBounds){
        return;
    }
    for (index = 0; index < numBounds; index++){
        (*bounds)->lowerBounds[index] = INT_MIN;
        (*bounds)->upperBounds[index] = (float) INT_MAX;
        (*bounds)->upperEquals[index] = 0;
        (*bounds)->lowerEquals[index] = 0;
    }
    (*bounds)->numBounds = numBounds;
}

void boundsFree(struct bounds** bounds){
    if(! bounds ||! (*bounds)){
        return;
    }
    boundsDeinnit(bounds);
    free(*bounds);
    (*bounds) = NULL;
}

void boundsDeinnit(struct bounds** bounds){
    if(! bounds ||! (*bounds)){
        return;
    }
    free((*bounds)->lowerBounds);
    free((*bounds)->upperBounds);
    free((*bounds)->upperEquals);
    free((*bounds)->lowerEquals);
    (*bounds)->numBounds = 0;
}

void addBound(struct bounds** bounds, float lowerBound, int lowerEqual, float upperBound, int upperEqual, int index){
    if(! bounds ||! (*bounds)){
        return;
    }
    (*bounds)->lowerBounds[index] = lowerBound;
    (*bounds)->upperBounds[index] = upperBound;
    (*bounds)->upperEquals[index] = upperEqual;
    (*bounds)->lowerEquals[index] = lowerEqual;
}