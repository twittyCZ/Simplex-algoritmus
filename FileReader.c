#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Description.h"
#include "FileReader.h"
#include "Tool.h"
#include "Logger.h"
#include "Exit.h"

#define LINE_LEN 256

int readFromFile(struct description** desc, const char* fileName) {
    FILE* file; char line[LINE_LEN];
    int inConstraints, inBounds, inGenerals, inType;
    if (!fileName || !desc) {
        ext(1, "Input file not found!\n");
    }
    file = fopen(fileName, "r");
    if (!file) {
        ext(1, "Input file not found!\n");
    }
    inBounds = 0, inConstraints = 0, inGenerals = 0, inType = 0;
    descriptionAllocate(desc, NULL, NULL, 0, NULL, 0, NULL, 0, 0);

    while (fgets(line, LINE_LEN, file)) {
        trimLine(line);
        removeComment(line);
        if (line[0] == '\0' || line[0] == '\\') continue;
        if (strncmp(line, "Maximize", 8) == 0 || strncmp(line, "Minimize", 8) == 0) {
            handleMaximizeMinimize(&inConstraints, &inBounds, &inGenerals, &inType, desc, line);
        } else if (strncmp(line, "Subject To", 10) == 0) {
            handleSubjectTo(&inConstraints, &inBounds, &inGenerals, &inType);
        } else if (strncmp(line, "Bounds", 6) == 0) {
            handleBounds(&inConstraints, &inBounds, &inGenerals, &inType);
        } else if (strncmp(line, "Generals", 8) == 0) {
            handleGenerals(&inConstraints, &inBounds, &inGenerals, &inType);
        } else if (strncmp(line, "End", 3) == 0) {
            break;
        } else if (inConstraints) {
            if(processConstraints(desc, line) == EXIT_FAILURE) {
                fclose(file);
                ext(11, "Syntax error!\n");
            }
        } else if (inBounds) {
            processBounds(desc, line);
        } else if (inGenerals) {
            processGenerals(desc, line);
        } else if (inType) {
            processObjective(desc, line);
        } else {
            fclose(file);
            ext(11, "Syntax error!\n");
        }
    }
    fclose(file);
    return EXIT_SUCCESS;
}

void handleMaximizeMinimize(int* inConstraints, int* inBounds, int* inGenerals, int* inType, struct description** desc, const char* line) {
    resetFlags(inConstraints, inBounds, inGenerals, inType);
    *inType = 1;
    if (strncmp(line, "Maximize", 8) == 0) {
        descriptionMaxOrMintReinit(desc, 1);
    } else if (strncmp(line, "Minimize", 8) == 0) {
        descriptionMaxOrMintReinit(desc, 0);
    }
}

void handleSubjectTo(int* inConstraints, int* inBounds, int* inGenerals, int* inType) {
    resetFlags(inConstraints, inBounds, inGenerals, inType);
    *inConstraints = 1;
}

void handleBounds(int* inConstraints, int* inBounds, int* inGenerals, int* inType) {
    resetFlags(inConstraints, inBounds, inGenerals, inType);
    *inBounds = 1;
}

void handleGenerals(int* inConstraints, int* inBounds, int* inGenerals, int* inType) {
    resetFlags(inConstraints, inBounds, inGenerals, inType);
    *inGenerals = 1;
}

int processConstraints(struct description** desc, const char* line) {
    char *splitResult = splitBy(line, ':');
    if (splitResult != NULL) {
        char temp[LINE_LEN];
        strncpy(temp, splitResult, LINE_LEN - 1);
        temp[LINE_LEN - 1] = '\0';
        descriptionConstraintReinit(desc, temp);
    } else {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

void processBounds(struct description** desc, const char* line) {
    descriptionBoundsReinit(desc, line);
}

void processGenerals(struct description** desc, const char* line) {
    char *token = strtok(line, " ");
    while (token) {
        descriptionGeneralsReinit(desc, token);
        token = strtok(NULL, " ");
    }
}

void processObjective(struct description** desc, const char* line) {
    descriptionObjectiveReinit(desc, line);
}

void saveOutputFile(int argc, char const* argv[], struct logger** logger) {
    char* lastOutputFileName = getOutputFileName(argc, argv);
    validateOutputFile(lastOutputFileName);
    loggerAllocate(logger, lastOutputFileName);
}

char* getOutputFileName(int argc, char const* argv[]) {
    char* lastOutputFileName;
    int i;
    if(argc < 2 || !argv) {
        return NULL;
    }
    lastOutputFileName = NULL;
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
            if (i + 1 < argc) {
                lastOutputFileName = (char*) argv[i + 1];
                i++;
            }
        }
    }
    return lastOutputFileName;
}

void validateOutputFile(const char* fileName) {
    if(!fileName) {
        return;
    }
    FILE* file = fopen(fileName, "w");
    if (!file) {
        ext(2, "Invalid output destination!\n");
    }
    fclose(file);
}



