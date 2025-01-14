/**
 * @file Logger.h
 * @author twitty
 * @brief Hlavičkový soubor pro práci s loggerem
 * @version 1.0
 * @date 2024-12-31
 */
#ifndef UNTITLED8_LOGGER_H
#define UNTITLED8_LOGGER_H
/**
 * @brief Struktura reprezentující logger
 */
struct logger {
    char* outputFileName; /*! název souboru pro výstup logů */
};
/**
 * @brief Alokace paměti pro logger
 * @param logger ukazatel na strukturu loggeru
 * @param outputFileName název souboru pro výstup logů
 */
void loggerAllocate(struct logger** loger, const char* outputFileName);
/**
 * @brief Inicializace parametrů struktury loggeru
 * @param logger ukazatel na strukturu loggeru
 * @param outputFileName název souboru pro výstup logů
 */
void loggerInnit(struct logger** logger, const char* outputFileName);
/**
 * @brief Dealokace paměti pro logger
 * @param logger ukazatel na strukturu loggeru
 */
void loggerFree(struct logger** logger);
/**
 * @brief Deinicializace parametrů struktury loggeru
 * @param logger ukazatel na strukturu loggeru
 */
void loggerDeinnit(struct logger** logger);
#endif
