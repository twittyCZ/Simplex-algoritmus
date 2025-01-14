/**
 * @file Result.h
 * @author twitty
 * @brief Hlavičkový soubor pro práci s výsledky
 * @version 1.0
 * @date 2024-12-31
 */
#include "stdio.h"
#include "Description.h"
#ifndef UNTITLED8_RESULT_H
#define UNTITLED8_RESULT_H
/**
 * @brief Struktura reprezentující výsledky výpočtu
 */
struct result {
    char** variables; /*! názvy proměnných */
    size_t numVariables; /*! počet proměnných */
    float* results; /*! výsledné hodnoty proměnných */
};
/**
 * @brief Alokace paměti pro výsledky
 * @param result ukazatel na strukturu výsledků
 * @param description ukazatel na strukturu popisu úlohy
 * @param variables názvy proměnných
 * @param numVariables počet proměnných
 * @param results hodnoty proměnných
 */
void resultAllocate(struct result** result, struct description* description, const char** variables, int numVariables, float* results);
/**
 * @brief Inicializace parametrů struktury výsledků
 * @param result ukazatel na strukturu výsledků
 * @param description ukazatel na strukturu popisu úlohy
 * @param variables názvy proměnných
 * @param numVariables počet proměnných
 * @param results hodnoty proměnných
 */
void resultInnit(struct result** result, struct description* description, const char** variables, int numVariables, float* results);
/**
 * @brief Dealokace paměti pro výsledky
 * @param result ukazatel na strukturu výsledků
 */
void resultFree(struct result** result);
/**
 * @brief Deinicializace parametrů struktury výsledků
 * @param result ukazatel na strukturu výsledků
 */
void resultDeinnit(struct result** result);
/**
 * @brief Přidání hodnoty na specifikovanou pozici ve výsledcích
 * @param result ukazatel na strukturu výsledků
 * @param position index pozice v poli výsledků
 * @param value hodnota, která má být přidána
 */
void resultAdd(struct result** result, int position, float value);
#endif
