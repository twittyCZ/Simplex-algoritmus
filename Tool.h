/**
 * @file Tool.h
 * @brief Hlavičkový soubor pro pomocné funkce
 * @version 1.0
 * @date 2024-12-31
 */
#ifndef TOOL_H
#define TOOL_H
#include "Description.h"
#include "Matrix.h"
#include "Bounds.h"
#include "Logger.h"
#include "Result.h"
#define MAX 100
/**
 * @brief Struktura reprezentující zásobník pro znaky (char), závorky, písmena, operátory.
 */
typedef struct {
    char items[MAX]; /**< Pole pro uložení prvků zásobníku */
    int top;         /**< Indikátor vrcholu zásobníku, který ukazuje na poslední přidaný prvek */
} CharStack;
/**
 * @brief Struktura reprezentující zásobník pro desetinná čísla (double).
 */
typedef struct {
    double items[MAX]; /**< Pole pro uložení prvků zásobníku */
    int top;           /**< Indikátor vrcholu zásobníku, který ukazuje na poslední přidaný prvek */
} DoubleStack;
/**
 * @brief Vloží prvek typu char na vrchol zásobníku.
 * @param stack Ukazatel na zásobník typu `CharStack`.
 * @param value Znak, který má být přidán na zásobník.
 */
void pushChar(CharStack *stack, char value);
/**
 * @brief Určí precedenci operátoru.
 * @param op Operátor, pro který je určena precedenční hodnota.
 * @return Precedenční hodnota operátoru (0 pro neznámý operátor).
 */
int precedence(char op);
/**
 * @brief Odstraní a vrátí prvek typu char z vrcholu zásobníku.
 * @param stack Ukazatel na zásobník typu `CharStack`.
 * @return Znak na vrcholu zásobníku.
 */
char popChar(CharStack *stack);
/**
 * @brief Vloží prvek typu double na vrchol zásobníku.
 * @param stack Ukazatel na zásobník typu `DoubleStack`.
 * @param value Číslo typu double, které má být přidáno na zásobník.
 */
void pushDouble(DoubleStack *stack, double value);
/**
 * @brief Odstraní a vrátí prvek typu double z vrcholu zásobníku.
 * @param stack Ukazatel na zásobník typu `DoubleStack`.
 * @return Číslo typu double na vrcholu zásobníku.
 */
double popDouble(DoubleStack *stack);
/**
 * @brief Aplikuje operátor na dvě hodnoty.
 * @param a První operand (double).
 * @param b Druhý operand (double).
 * @param op Operátor (char), který určuje, jaká operace bude provedena.
 * @return Výsledek operace mezi operandem a operátorem.
 */
double applyOperator(double a, double b, char op);
/**
 * @brief Kontroluje, zda rovnice obsahuje nerovnost a vrací typ nerovnosti.
 * @param equation Řetězec obsahující rovnici.
 * @return 1 pro "<=", -1 pro ">=", 0 pokud nerovnost není přítomna.
 */
int contains_inequality(const char *equation);
/**
 * @brief Odstraní přebytečné mezery na konci řádku.
 * @param line Řetězec obsahující text řádku.
 */
void trimLine(char* line);
/**
 * @brief Odstraní komentář začínající zpětným lomítkem (\) z řetězce.
 * @param str Řetězec obsahující text s komentářem.
 */
void removeComment(char *str);
/**
 * @brief Rozdělí řetězec podle daného znaku.
 * @param string Vstupní řetězec.
 * @param element Znak, podle kterého se řetězec rozdělí.
 * @return Ukazatel na část řetězce za prvním výskytem znaku.
 */
char* splitBy(const char* string, char element);
/**
 * @brief Resetuje příznaky pro zpracování různých sekcí.
 * @param inConstraints Ukazatel na příznak pro omezení.
 * @param inBounds Ukazatel na příznak pro hranice.
 * @param inGenerals Ukazatel na příznak pro generály.
 * @param inType Ukazatel na příznak pro typ funkce.
 */
void resetFlags(int* inConstraints, int* inBounds, int* inGenerals, int* inType);
/**
 * @brief Odstraní všechny mezery z řetězce.
 * @param str Řetězec, který bude upraven.
 */
void removeWhitespace(char* str);
/**
 * @brief Přidá symbol násobení (*) tam, kde je implicitní (např. mezi číslem a proměnnou).
 * @param input Vstupní matematický výraz.
 */
void insert_multiplication(char* input);
/**
 * @brief Získá koeficient proměnné v generální rovnici.
 * @param expression Matematický výraz.
 * @param token Název proměnné.
 * @return Koeficient proměnné nebo INT_MIN při chybě.
 */
float getGeneralsCoeficient(const char* expression, const char* token);
/**
 * @brief Získá pravou stranu rovnice (hodnotu za operátorem nerovnosti).
 * @param expression Matematický výraz.
 * @return Hodnota na pravé straně rovnice.
 */
float getRightSide(char* expression);
/**
 * @brief Odstraní pravou stranu rovnice včetně operátoru nerovnosti.
 * @param expression Matematický výraz.
 */
void removeRightSide(char* expression);
/**
 * @brief Inverzuje číslo (změní znaménko).
 * @param number Číslo, které bude invertováno.
 * @return Inverzní hodnota čísla.
 */
float invertNumber(float number);
/**
 * @brief Analyzuje hranici a přidá ji do struktury bounds.
 * @param bounds Ukazatel na strukturu hranic.
 * @param boundEquation Řetězec obsahující rovnici hranice.
 * @param general Název proměnné.
 * @param index Index hranice.
 */
void parseBound(struct bounds** bounds, const char* boundEquation, const char* general, int index);
/**
 * @brief Získá název vstupního souboru ze seznamu argumentů.
 * @param arguments Pole argumentů příkazové řádky.
 * @param numArguments Počet argumentů.
 * @return Ukazatel na název vstupního souboru nebo NULL, pokud není nalezen.
 */
const char* getInputFileName(const char** arguments, int numArguments);
/**
 * @brief Kontroluje, zda je znak platný pro proměnnou (písmeno, číslice nebo podtržítko).
 * @param c Znak k ověření.
 * @return 1, pokud je znak platný, jinak 0.
 */
int is_valid_variable_char(char c);
/**
 * @brief Extrahuje proměnné z rovnice a validuje jejich přítomnost ve struktuře description.
 * @param equation Matematická rovnice.
 * @param description Struktura obsahující seznam generálů.
 */
void extract_variables(const char *equation, struct description* description);
#endif
