#include <stdio.h>
#include "FileReader.h"
#include "Description.h"
#include "Tool.h"
#include "MathCaltulations.h"
#include "ResultWriter.h"
#include "Global.h"
#include "Exit.h"

int main(int argc, char const *argv[])
{
    if(argc < 2) {
        printf("Input file not found!\n");
        return 1;
    }
    readFromFile(&description1, getInputFileName(argv, argc));
    saveOutputFile(argc, argv, &logger1);
    assignmentCheck(description1);
    prepareForCalculations(description1, &matrix1, &bounds1, &result1);
    simplexMethod(description1, matrix1, &result1);
    printOutResults(result1, logger1, description1, matrix1, bounds1);
    freeStructures();
    return 0;
}


