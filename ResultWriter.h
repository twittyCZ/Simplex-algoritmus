/**
 * @file ResultWriter.h
 * @brief Hlavičkový soubor pro funkce související s výstupem výsledků a kontrolou správnosti
 * @version 1.0
 * @date 2024-12-31
 */
#ifndef UNTITLED8_RESULTWRITER_H
#define UNTITLED8_RESULTWRITER_H
#include "Description.h"
#include "Matrix.h"
#include "Bounds.h"
#include "Logger.h"
#include "Result.h"
/**
 * @brief Vypíše výsledky úlohy
 * @param result struktura výsledků
 * @param logger logger obsahující informace o výstupním souboru
 * @param description popis úlohy
 * @param matrix struktura matice
 * @param bounds struktura mezí
 */
void printOutResults(struct result* result, struct logger* logger, struct description* description, struct matrix* matrix, struct bounds* bounds);
/**
 * @brief Vypíše výsledky na příkazovou řádku
 * @param result výsledky
 */
void printToCommandLine(struct result* result);
/**
 * @brief Vypíše výsledky do souboru
 * @param result výsledky
 */
void printToFile(struct result* result, struct logger* logger);
/**
 * @brief Zkontroluje, zda výsledky odpovídají zadaným mezím
 * @param result Ukazatel na strukturu výsledků
 * @param bounds Ukazatel na strukturu mezí
 * @throws Pokud je funkce neomezená, program ukončí s kódem 20
 */
void checkResults(struct matrix* matrix, struct description* description, struct result* result, struct bounds* bounds);
#endif
