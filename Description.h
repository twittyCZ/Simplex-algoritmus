/**
* @file Description.h
* @author twitty
* @brief Hlavičkový soubor pro práci se strukturou zadání úlohy
* @version 1.0
* @date 2025-12-31
*/
#ifndef FILEDESCRIPTION_H
#define FILEDESCRIPTION_H
#include "stdio.h"
/**
 * @brief Struktura reprezentující zadání úlohy
 */
struct description{
    char* objective; /*! účelová funkce */
    char** constraints;  /*! omezující rovnice */
    size_t numConstraints;  /*! počet omezujících rovnic */
    char** bounds;  /*! mezní rovnice */
    size_t numBounds; /*! počet mezí */
    char** generals;  /*! neznámé */
    size_t numGenerals; /*! počet neznámých */
    int maxOrMin; /*! maximalizující úloha = 1, minimalizující = 0 */
};
/**
 * @brief Alokace paměti pro popis úlohy
 * @param description ukazatel na strukturu popisu úlohy
 * @param objective účelová funkce
 * @param constraints omezující rovnice
 * @param numConstraints počet omezujících rovnic
 * @param bounds meze pro neznámé
 * @param numBounds počet mezí
 * @param generals neznámé
 * @param numGenerals počet neznámých
 * @param maxOrMin minimalizující úloha = 0, či maximalizující = 1
 */
void descriptionAllocate(struct description** description, const char* objective, const char** constraints, int numConstraints, const char** bounds, int numBounds, const char** generals, int numGenerals, int maxOrMin);
/**
 * @brief Iniciaizace parametrů struktury pro popis úlohy
 * @param description ukazatel na strukturu popisu úlohy
 * @param objective účelová funkce
 * @param constraints omezující rovnice
 * @param numConstraints počet omezujících rovnic
 * @param bounds meze pro neznámé
 * @param numBounds počet mezí
 * @param generals neznámé
 * @param numGenerals počet neznámých
 * @param maxOrMin minimalizující úloha = 0, či maximalizující = 1
 * @return 1 pokud se povedlo, jinak 0
 */
int descriptionInit(struct description** description, const char* objective, const char** constraints, int numConstraints, const char** bounds, int numBounds, const char** generals, int numGenerals, int maxOrMin);
/**
 * @brief Dealokace paměti
 * @param description ukazatel na strukturu popisu úlohy
 */
void descriptionFree(struct description** description);
/**
 * @brief Deinicializace paramtetrů struktury
 * @param description ukazatel na strukturu popisu úlohy
 */
void descriptionDeinit(struct description** description);
/**
 * @brief Funkce pro reinicializaci účelové funkce
 * @param description ukazatel na strukturu popisu úlohy
 * @param objective účelová funkce
 */
void descriptionObjectiveReinit(struct description** description, const char* objective);
/**
 * @brief Funkce pro reinicializaci meze
 * @param description ukazatel na strukturu popisu úlohy
 * @param bounds meze
 */
void descriptionBoundsReinit(struct description** description, const char* bounds);
/**
 * @brief Funkce pro reinicializaci neznámé
 * @param description ukazatel na strukturu popisu úlohy
 * @param objective neznámá
 */
void descriptionGeneralsReinit(struct description** description, const char* generals);
/**
 * @brief Funkce pro reinicializaci omezující rovnice
 * @param description ukazatel na strukturu popisu úlohy
 * @param constraints omezující rovnice
 */
void descriptionConstraintReinit(struct description** description, const char* constraints);
/**
 * @brief Funkce pro reinicializaci maximalizace/minimalizace
 * @param description ukazatel na strukturu popisu úlohy
 * @param maxOrMin maximalizace/minimalizace
 */
void descriptionMaxOrMintReinit(struct description** description, int maxOrMin);
/**
 * @brief Kontrola, zda zadání obsahuje všechny potřebné informaci
 * @param description popis úlohy
 */
void descriptionCheck(struct description* description);
/**
 * @brief Kontrola smysluplnosti/správnosti zadání
 * @param description popis úlohy
 */
void assignmentCheck(struct description* description);
#endif
