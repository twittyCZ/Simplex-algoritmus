/**
 * @file Exit.h
 * @author twitty
 * @brief Hlavičkový soubor pro uvolnění dynamicky alokované paměti a ukončení programu
 * @version 1.0
 * @date 2023-12-31
 */
#ifndef UNTITLED8_EXIT_H
#define UNTITLED8_EXIT_H
/**
 * @brief Uvolnění dynamicky alokované paměti všech globálních struktur
 */
void freeStructures();
/**
 * @brief Ukončení programu
 * @param problem návratová hodnota programu
 * @param message hláška při vypsání programu
 */
void ext(int problem, const char* message);
#endif
