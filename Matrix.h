/**
 * @file Matrix.h
 * @author twitty
 * @brief Hlavičkový soubor pro práci s maticemi
 * @version 1.0
 * @date 2024-12-31
 */
#ifndef UNTITLED8_MATRIX_H
#define UNTITLED8_MATRIX_H
#include "stdlib.h"
#include "stdio.h"
#include "Description.h"
/**
 * @brief Struktura reprezentující matici
 */
struct matrix {
    float** board; /*! 2D pole reprezentující prvky matice */
    size_t numRows; /*! počet řádků matice */
    size_t numCols; /*! počet sloupců matice */
};
/**
 * @brief Alokace paměti pro matici
 * @param matrix ukazatel na strukturu matice
 * @param numRows počet řádků matice
 * @param numCols počet sloupců matice
 */
void matrixAllocate(struct matrix** matrix, int numRows, int numCols);
/**
 * @brief Inicializace parametrů matice
 * @param matrix ukazatel na strukturu matice
 * @param numRows počet řádků matice
 * @param numCols počet sloupců matice
 */
void matrixInnit(struct matrix** matrix, int numRows, int numCols);
/**
 * @brief Dealokace paměti pro matici
 * @param matrix ukazatel na strukturu matice
 */
void matrixFree(struct matrix** matrix);
/**
 * @brief Deinicializace parametrů matice
 * @param matrix ukazatel na strukturu matice
 */
void matrixDeinnit(struct matrix** matrix);
/**
 * @brief Výpis matice na standardní výstup
 * @param matrix matice
 */
void printMatrix(struct matrix* matrix);
/**
 * @brief Přidání čísla do matice na specifikovaný index
 * @param matrix ukazatel na strukturu matice
 * @param number číslo, které má být přidáno
 * @param row index řádku
 * @param column index sloupce
 */
void matrixAddNumber(struct matrix** matrix, float number, int row, int column);
/**
 * @brief Přidání jednotkové matice do matice
 * @param matrix ukazatel na strukturu matice
 * @param description popis úlohy, ze které se najde konkrétní místo pro přidání jednotkové matice
 */
void addUnitMatrix(struct matrix** matrix, struct description* description);
/**
 * @brief Přidání pravé strany rovnic do matice
 * @param matrix ukazatel na strukturu matice
 * @param description popis úlohy pro získání pravé strany
 */
void addRightSide(struct matrix** matrix, struct description* description);
#endif
