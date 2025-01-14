/**
 * @file Bounds.h
 * @author twitty
 * @brief Hlavičkový soubor pro práci se strukturou pro hledané hodnoty
 * @version 1.0
 * @date 2025-12-31
 */
#ifndef UNTITLED8_BOUNDS_H
#define UNTITLED8_BOUNDS_H
/**
 * @brief Struktura reprezentující meze hledaných hodnot
 */
struct bounds {
    float* lowerBounds; /*! spodní meze */
    int* lowerEquals; /*! otevřenost či uzavřenost spodní meze 0 -> >, 1 -> >= */
    float* upperBounds; /*! horní meze */
    int* upperEquals; /*! otevřenost či uzavřenost horní meze 0 -> <, 1 -> <=  */
    int numBounds; /*! počet mezí, je stejný jak počet proměnných  */
};
/**
 * @brief Alokace paměti pro meze
 * @param bounds ukazatel na astrukturu
 * @param numBounds počet mezí = počet proměnných
 */
void boundsAllocate(struct bounds** bounds, int numBounds);
/**
 * @brief Inicializace parametrů struktury
 * @param bounds ukazatel na astrukturu
 * @param numBounds počet mezí = počet proměnných
 */
void boundsInnit(struct bounds** bounds, int numBouds);
/**
 * @brief Dealokace paměti
 * @param bounds ukazatel na strukturu
 */
void boundsFree(struct bounds** bounds);
/**
 * @brief Deinicializace parametrů struktury
 * @param bounds ukazatel na strukturu
 */
void boundsDeinnit(struct bounds** bounds);
/**
 * @brief Přidání meze do struktury
 * @param bounds ukazatel na strukturu
 * @param lowerBound dolní meze
 * @param lowerEqual otevřenost či uzavřenost dolní meze
 * @param upperBound horní meze
 * @param upperEqual otevřenost či uzavřenost horní meze
 * @param index index do pole proměnných
 */
void addBound(struct bounds** bounds, float lowerBound, int lowerEqual, float upperBound, int upperEqual, int index);
#endif
