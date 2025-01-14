/**
 * @file FileReader.h
 * @author twitty
 * @brief Hlavičkový soubor pro načtení dat ze vstupního souboru
 * @version 1.0
 * @date 2024-12-31
 */
#ifndef FILEREADER_H
#define FILEREADER_H
#include "Logger.h"
/**
 * @brief Uloží název výstupního souboru a inicializuje logger
 * @param argc Počet argumentů příkazového řádku
 * @param argv Pole argumentů příkazového řádku
 * @param logger Ukazatel na logger
 */
void saveOutputFile(int argc, char const* argv[], struct logger** logger);
/**
 * @brief Načte data ze vstupního souboru a naplní strukturu popisu úlohy
 * @param desc Ukazatel na strukturu popisu úlohy
 * @param fileName Název vstupního souboru
 * @return EXIT_SUCCESS v případě úspěchu, jinak EXIT_FAILURE
 */
int readFromFile(struct description** desc, const char* fileName);
/**
 * @brief Získá název výstupního souboru z argumentů příkazového řádku
 * @param argc Počet argumentů příkazového řádku
 * @param argv Pole argumentů příkazového řádku
 * @return Název výstupního souboru nebo NULL, pokud nebyl zadán
 */
char* getOutputFileName(int argc, char const* argv[]);
/**
 * @brief Validuje název výstupního souboru a ověří, že je možné jej otevřít k zápisu
 * @param fileName Název výstupního souboru
 */
void validateOutputFile(const char* fileName);
/**
 * @brief Zpracuje řádek obsahující příkaz Maximize nebo Minimize
 * @param inConstraints Ukazatel na příznak indikující část Constraints
 * @param inBounds Ukazatel na příznak indikující část Bounds
 * @param inGenerals Ukazatel na příznak indikující část Generals
 * @param inType Ukazatel na příznak indikující část typu úlohy
 * @param desc Ukazatel na strukturu popisu úlohy
 * @param line Aktuální zpracovávaný řádek
 */
void handleMaximizeMinimize(int* inConstraints, int* inBounds, int* inGenerals, int* inType, struct description** desc, const char* line);
/**
 * @brief Zpracuje začátek sekce Subject To
 * @param inConstraints Ukazatel na příznak indikující část Constraints
 * @param inBounds Ukazatel na příznak indikující část Bounds
 * @param inGenerals Ukazatel na příznak indikující část Generals
 * @param inType Ukazatel na příznak indikující část typu úlohy
 */
void handleSubjectTo(int* inConstraints, int* inBounds, int* inGenerals, int* inType);
/**
 * @brief Zpracuje začátek sekce Bounds
 * @param inConstraints Ukazatel na příznak indikující část Constraints
 * @param inBounds Ukazatel na příznak indikující část Bounds
 * @param inGenerals Ukazatel na příznak indikující část Generals
 * @param inType Ukazatel na příznak indikující část typu úlohy
 */
void handleBounds(int* inConstraints, int* inBounds, int* inGenerals, int* inType);
/**
 * @brief Zpracuje začátek sekce Generals
 * @param inConstraints Ukazatel na příznak indikující část Constraints
 * @param inBounds Ukazatel na příznak indikující část Bounds
 * @param inGenerals Ukazatel na příznak indikující část Generals
 * @param inType Ukazatel na příznak indikující část typu úlohy
 */
void handleGenerals(int* inConstraints, int* inBounds, int* inGenerals, int* inType);
/**
 * @brief Zpracuje řádek s omezením (constraint)
 * @param desc Ukazatel na strukturu popisu úlohy
 * @param line Aktuální zpracovávaný řádek
 * @return EXIT_SUCCESS v případě úspěchu, jinak EXIT_FAILURE
 */
int processConstraints(struct description** desc, const char* line);
/**
 * @brief Zpracuje řádek s mezemi (bounds)
 * @param desc Ukazatel na strukturu popisu úlohy
 * @param line Aktuální zpracovávaný řádek
 */
void processBounds(struct description** desc, const char* line);
/**
 * @brief Zpracuje řádek s obecnými proměnnými (generals)
 * @param desc Ukazatel na strukturu popisu úlohy
 * @param line Aktuální zpracovávaný řádek
 */
void processGenerals(struct description** desc, const char* line);
/**
 * @brief Zpracuje řádek s účelovou funkcí (objective)
 * @param desc Ukazatel na strukturu popisu úlohy
 * @param line Aktuální zpracovávaný řádek
 */
void processObjective(struct description** desc, const char* line);
#endif
