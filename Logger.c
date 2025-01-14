#include "stdlib.h"
#include "string.h"
#include "Logger.h"

void loggerAllocate(struct logger** logger, const char* outputFileName) {
    (*logger) = malloc(sizeof(struct logger));
    if ((*logger) == NULL) {
        return;
    }
    loggerInnit(logger, outputFileName);
}

void loggerInnit(struct logger** logger, const char* outputFileName) {
    if (!logger ||! (*logger)) {
        return;
    }
    if(outputFileName == NULL) {
        (*logger)->outputFileName = NULL;
        return;
    }
    (*logger)->outputFileName = strdup(outputFileName);
}

void loggerFree(struct logger** logger) {
    if(!logger ||! (*logger)){
        return;
    }
    loggerDeinnit(logger);
    free(*logger);
    *logger = NULL;
}

void loggerDeinnit(struct logger** logger) {
    if(!logger ||! (*logger)){
        return;
    }
    free((*logger)->outputFileName);
}
