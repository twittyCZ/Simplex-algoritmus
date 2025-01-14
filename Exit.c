#include "stdio.h"
#include "stdlib.h"
#include "Matrix.h"
#include "Bounds.h"
#include "Logger.h"
#include "Description.h"
#include "Result.h"
#include "Global.h"
#include "Exit.h"

void freeStructures(){
    if((bounds1)){
        boundsFree(&bounds1);
    }
    if(matrix1){
        matrixFree(&matrix1);
    }
    if(description1){
        descriptionFree(&description1);
    }
    if(logger1){
        loggerFree(&logger1);
    }
    if(result1){
        resultFree(&result1);
    }
}

void ext(int problem, const char* message){
    printf("%s", message);
    freeStructures();
    exit(problem);
}