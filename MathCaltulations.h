/**
* @file MathCalculations.h
* @author twitty
* @brief Hlavičkový soubor pro matematické operace
* @version 1.0
* @date 2025-12-31
*/
#ifndef UNTITLED8_MATHCALTULATIONS_H
#define UNTITLED8_MATHCALTULATIONS_H
#include "Matrix.h"
#include "Bounds.h"
#include "Logger.h"
#include "Description.h"
#include "Result.h"
#define MAX 100
/**
 * @brief Kontrola správnosti matematických výrazů ve struktuře popisu
 * @param description Struktura popisu obsahující objektivní funkci a omezení
 */
void mathExpressionCheck(struct description* description);
/**
 * @brief Formátování rovnic odstraněním mezer a přidáním násobení
 * @param desc Struktura popisu obsahující rovnice k úpravě
 */
void formatEquations(struct description* desc);
/**
 * @brief Konverze rovnic do maticové reprezentace
 * @param desc Struktura popisu obsahující rovnice
 * @param matrix Ukazatel na ukazatel matice pro výstup
 */
void convertEquationsIntoMatrix(struct description* desc, struct matrix** matrix);
/**
 * @brief Konverze omezení do odpovídající struktury
 * @param desc Struktura popisu obsahující omezení
 * @param bounds Ukazatel na ukazatel struktury omezení
 */
void convertBounds(struct description* desc, struct bounds** bounds);
/**
 * @brief Kontrola integrity popisu, matice a omezení
 * @param desc Struktura popisu
 * @param matrix Ukazatel na strukturu matice
 * @param bounds Ukazatel na strukturu omezení
 * @return EXIT_SUCCESS při úspěchu, EXIT_FAILURE při chybě
 */
int integrationCheck(struct description* desc, struct matrix* matrix, struct bounds* bounds);
/**
 * @brief Příprava dat pro výpočty
 * @param description Struktura popisu obsahující vstupy
 * @param matrix Ukazatel na ukazatel matice
 * @param bounds Ukazatel na ukazatel omezení
 * @param result Ukazatel na ukazatel struktury výsledků
 */
void prepareForCalculations(struct description* description, struct matrix** matrix, struct bounds** bounds, struct result** result);
/**
 * @brief Určuje prioritu operátoru
 * @param op Operátor pro kontrolu
 * @return Celé číslo reprezentující prioritu operátoru
 */
int precedence(char op);
/**
 * @brief Validace matematického výrazu
 * @param expression Řetězec obsahující výraz k validaci
 */
void isValidExpresion(const char *expression);
/**
 * @brief Kontrola, zda je proměnná použita v matici
 * @param matrix Ukazatel na matici
 * @param foundedVariable Index nalezené proměnné
 * @return EXIT_SUCCESS při nepoužití, EXIT_FAILURE při použití
 */
int isVariableUsed(struct matrix* matrix, int foundedVariable);
/**
 * @brief Najde ideální sloupec pro další iteraci simplexové tabulky
 * @param matrix Ukazatel na matici
 * @return Index sloupce nebo -1 při chybě
 */
int findPivotFromObject(struct matrix* matrix);
/**
 * @brief Najde řádek odpovídající pivotu ve sloupci
 * @param matrix Ukazatel na matici
 * @param columnIndex Index sloupce pivotu
 * @return Index řádku pivotu
 */
int findPivotRowConstraint(struct matrix* matrix, int columnIndex);
/**
 * @brief Vydělí řádek daným číslem
 * @param matrix Ukazatel na matici
 * @param rowIndex Index řádku
 * @param divider Dělitel
 */
void divideTheRow(struct matrix* matrix, int rowIndex, float divider);
/**
 * @brief Získá násobitel pro operaci s řádkem
 * @param pivot Hodnota pivotu
 * @param number Číslo k úpravě
 * @return Vypočítaný násobitel
 */
float getMultiplier(float pivot, float number);
/**
 * @brief Zjistí, zda je potřeba další iterace simplexové metody
 * @param matrix Ukazatel na matici
 * @return 1 pokud je potřeba další iterace, 0 jinak
 */
int doNextIteration(struct matrix* matrix);
/**
 * @brief Kontrola simplexové tabulky pro proměnné a záporné hodnoty
 * @param matrix Ukazatel na matici
 * @param indexColumn Index sloupce
 * @param numberOfVariables Ukazatel na počet proměnných
 * @param numberOfNegative Ukazatel na počet záporných hodnot
 */
void simplexTableCheck(struct matrix* matrix, int indexColumn, int* numberOfVariables, int* numberOfNegative);
/**
 * @brief Získá všechny koeficienty z matice
 * @param matrix Ukazatel na matici
 * @param coeficients Pole pro uložení koeficientů
 */
void getAllCoeficients(struct matrix *matrix, float* coeficients);
/**
 * @brief Získá index koeficientu v matici
 * @param matrix Ukazatel na matici
 * @param foundedIndexRow Index nalezeného řádku
 * @return Index koeficientu nebo -1 při chybě
 */
int getCoeficientIndex (struct matrix* matrix, int foundedIndexRow);
/**
 * @brief Získá výsledek ze simplexové tabulky
 * @param matrix Ukazatel na matici
 * @param result Ukazatel na ukazatel výsledků
 */
void getResult(struct matrix* matrix, struct result** result);
/**
 * @brief Odečte násobek jednoho řádku od jiného
 * @param matrix Ukazatel na matici
 * @param multiplierOfNulledRow Násobitel nulovaného řádku
 * @param indexRow Index řádku
 * @param indexOfNulledRow Index nulovaného řádku
 */
void substractRow(struct matrix* matrix, float multiplierOfNulledRow, int indexRow, int indexOfNulledRow);
/**
 * @brief Implementace simplexové metody
 * @param description Struktura popisu
 * @param matrix Ukazatel na matici
 * @param result Ukazatel na ukazatel výsledků
 */
void simplexMethod(struct description* description, struct matrix* matrix, struct result** result);
/**
 * @brief Výpočet objektivní funkce
 * @param description Struktura popisu
 * @param matrix Ukazatel na matici
 * @param coeficients Pole koeficientů
 */
void objectiveFunctionCalculation(struct description* description, struct matrix* matrix, const float* coeficients);
#endif
