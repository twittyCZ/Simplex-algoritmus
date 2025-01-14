#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "limits.h"
#include "ctype.h"
#include <float.h>
#include "Tool.h"
#include "Description.h"
#include "MathCaltulations.h"
#include "Bounds.h"
#include "Result.h"
#include "Exit.h"

int contains_inequality(const char *equation) {
    if (strstr(equation, "<=") != NULL) {
        return 1;
    }
    if (strstr(equation, ">=") != NULL) {
        return -1;
    }
    return 0;
}

void trimLine(char* line) {
    char* end = line + strlen(line) - 1;
    while (end > line && isspace((unsigned char)*end)) {
        *end = '\0';
        end--;
    }
}

void removeComment(char *str) {
    char *commentStart = strchr(str, '\\');
    if (commentStart) {
        *commentStart = '\0';
    }
}

char* splitBy(const char* string, char element) {
    if (string == NULL || strlen(string) == 0) {
        return NULL;
    }
    char *elementPos = strchr(string, element);
    if (elementPos == NULL) {
        return NULL;
    }
    if (strcmp(elementPos + 1, ":") == 1) {
        return NULL;
    }
    return elementPos + 1;
}

void resetFlags(int* inConstraints, int* inBounds, int* inGenerals, int* inType) {
    *inConstraints = 0;
    *inBounds = 0;
    *inGenerals = 0;
    *inType = 0;
}

void removeWhitespace(char* str) {
    if (!str) {
        return;
    }
    char* src = str;
    char* dst = str;
    while (*src != '\0') {
        if (!isspace((unsigned char)*src)) {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';
}

void insert_multiplication(char* input) {
    int i, j;
    int length = (int) strlen(input);
    if (length == 0) {
        return;
    }
    for (i = length - 1; i >= 0; i--) {
        if (isdigit(input[i]) && i + 1 < length && (isalpha(input[i + 1]) || input[i + 1] == '(' || input[i + 1] == '[' || input[i + 1] == '{')) {
            for (j = length; j > i; j--) {
                input[j] = input[j - 1];
            }
            input[i + 1] = '*';
            length++;
        }
    }
    input[length] = '\0';
}

void pushChar(CharStack *stack, char value) {
    stack->items[++stack->top] = value;
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

char popChar(CharStack *stack) {
    return stack->items[stack->top--];
}

void pushDouble(DoubleStack *stack, double value) {
    stack->items[++stack->top] = value;
}

double popDouble(DoubleStack *stack) {
    return stack->items[stack->top--];
}

double applyOperator(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) {
                fprintf(stderr, "Error: Division by zero!\n");
                exit(EXIT_FAILURE);
            }
            return a / b;
        default:
            fprintf(stderr, "Error: Invalid operator '%c'!\n", op);
            exit(EXIT_FAILURE);
    }
}

double evaluateExpression(const char *expression) {
    CharStack operators = { .top = -1 };
    DoubleStack values = { .top = -1 };

    int i = 0;
    while (expression[i] != '\0') {
        if (isspace(expression[i])) {
            i++;
            continue;
        }

        if (expression[i] == '(' || expression[i] == '[' || expression[i] == '{') {
            pushChar(&operators, expression[i]);
        } else if (isdigit(expression[i]) || (expression[i] == '-' && (i == 0 || strchr("([{", expression[i-1])))) {
            char buffer[MAX];
            int j = 0;
            if (expression[i] == '-') buffer[j++] = expression[i++];
            while (isdigit(expression[i]) || expression[i] == '.') {
                buffer[j++] = expression[i++];
            }
            buffer[j] = '\0';
            pushDouble(&values, atof(buffer));
            i--;
        } else if (expression[i] == ')' || expression[i] == ']' || expression[i] == '}') {
            char expectedOpen = expression[i] == ')' ? '(' : (expression[i] == ']' ? '[' : '{');
            while (operators.top != -1 && operators.items[operators.top] != expectedOpen) {
                char op = popChar(&operators);
                double b = popDouble(&values);
                double a = popDouble(&values);
                pushDouble(&values, applyOperator(a, b, op));
            }
            if (operators.top == -1 || popChar(&operators) != expectedOpen) {
                fprintf(stderr, "Error: Mismatched parentheses!\n");
                exit(EXIT_FAILURE);
            }
        } else if (strchr("+-*/", expression[i])) {
            while (operators.top != -1 && precedence(operators.items[operators.top]) >= precedence(expression[i])) {
                char op = popChar(&operators);
                double b = popDouble(&values);
                double a = popDouble(&values);
                pushDouble(&values, applyOperator(a, b, op));
            }
            pushChar(&operators, expression[i]);
        } else {
            fprintf(stderr, "Error: Invalid character '%c' in expression!\n", expression[i]);
            exit(EXIT_FAILURE);
        }
        i++;
    }
    while (operators.top != -1) {
        char op = popChar(&operators);
        double b = popDouble(&values);
        double a = popDouble(&values);
        pushDouble(&values, applyOperator(a, b, op));
    }

    if (values.top != 0) {
        fprintf(stderr, "Error: Invalid expression!\n");
        exit(EXIT_FAILURE);
    }
    return popDouble(&values);
}

float getGeneralsCoeficient(const char* expression, const char* token) {
    if (!expression || !token) {
        return INT_MIN;
    }
    char* newExpression = (char*)malloc(strlen(expression) * 2 + 1);
    if (!newExpression) {
        return INT_MIN;
    }
    newExpression[0] = '\0';
    const char* p = expression;
    while (*p) {
        if (isalpha(*p) || *p == '_') {
            char varName[128];
            size_t varLen = 0;
            while (isalnum(*p) || *p == '_') {
                varName[varLen++] = *p;
                p++;
            }
            varName[varLen] = '\0';
            if (strcmp(varName, token) == 0) {
                strcat(newExpression, "1");
            } else {
                strcat(newExpression, "0");
            }
        } else {
            strncat(newExpression, p, 1);
            p++;
        }
    }

    removeRightSide(newExpression);
    float result = (float) evaluateExpression(newExpression);
    free(newExpression);
    return result;
}

float getRightSide(char* expression) {
    const char* operators[] = {">=", "<=", ">", "<", "="};
    size_t numOperators = sizeof(operators) / sizeof(operators[0]);
    size_t i;

    for (i = 0; i < numOperators; i++) {
        const char* opPosition = strstr(expression, operators[i]);
        if (opPosition) {
            opPosition += strlen(operators[i]);
            return strtof(opPosition, NULL);
        }
    }
    return 0.0f;
}

void removeRightSide(char* expression) {
    const char* operators[] = {">=", "<=", ">", "<", "="};
    size_t numOperators = sizeof(operators) / sizeof(operators[0]);
    size_t i;

    for (i = 0; i < numOperators; i++) {
        char* opPosition = strstr(expression, operators[i]);
        if (opPosition) {
            *opPosition = '\0';
            break;
        }
    }
}
float invertNumber(float number) {
    if (number == 0) return number;
    return -number;
}

void parseBound(struct bounds** bounds, const char* boundEquation, const char* general, int index) {
    float lower = -FLT_MAX;
    float upper = FLT_MAX;
    int upperEqual = 1, lowerEqual = 1;
    char general_copy[100];
    strcpy(general_copy, general);

    if (strstr(boundEquation, "<=")) {
        if (sscanf(boundEquation, "%f<=%[^<=]<=%f", &lower, general_copy, &upper) == 3) {}
        else if (sscanf(boundEquation, "%[^<=]<=%f", general_copy, &upper) == 2) {
            lower = -FLT_MAX;
        }
    } else if (strstr(boundEquation, ">=")) {
        if (sscanf(boundEquation, "%[^>=]>=%f", general_copy, &lower) == 2) {
            upper = FLT_MAX;
        }
    } else if (strchr(boundEquation, '>')) {
        if (sscanf(boundEquation, "%[^>]>%f", general_copy, &lower) == 2) {
            lowerEqual = 0;
            upper = FLT_MAX;
        }
    } else if (strchr(boundEquation, '<')) {
        if (sscanf(boundEquation, "%[^<]<%f", general_copy, &upper) == 2) {
            lower = -FLT_MAX;
            upperEqual = 0;
        }
    } else {
        fprintf(stderr, "Unknown format: %s\n", boundEquation);
    }

    if (strlen(general_copy) == 0) {
        fprintf(stderr, "Invalid format: %s\n", boundEquation);
        return;
    }

    addBound(bounds, lower, lowerEqual, upper, upperEqual, index);
}

const char* getInputFileName(const char** arguments, int numArguments) {
    int index;
    if (!arguments || numArguments < 2) {
        return NULL;
    }
    for (index = 1; index < numArguments; index++) {
        if (strcmp(arguments[index], "-o") != 0 && strcmp(arguments[index], "--output") != 0) {
            return arguments[index];
        } else {
            index++;
        }
    }
    return NULL;
}

int is_valid_variable_char(char c) {
    return (isalnum(c) || c == '_');
}

void extract_variables(const char *equation, struct description* description) {
    int succes;
    size_t k;
    char variables[100][50];
    int var_count = 0;
    int i = 0, j;
    int len = (int)strlen(equation);
    char current_var[50];
    int var_index = 0;
    int is_in_var = 0;

    while (i < len) {
        if (isalpha(equation[i]) || equation[i] == '_') {
            is_in_var = 1;
            current_var[var_index] = equation[i];
            var_index++;
        } else if (is_valid_variable_char(equation[i]) && is_in_var) {
            current_var[var_index++] = equation[i];
            current_var[var_index] = '\0';

            int is_duplicate = 0;
            for (j = 0; j < var_count; j++) {
                if (strcmp(variables[j], current_var) == 0) {
                    is_duplicate = 1;
                    break;
                }
            }

            if (!is_duplicate) {
                strcpy(variables[var_count], current_var);
                var_count++;
            }

            is_in_var = 0;
            var_index = 0;
        }
        if (strchr("+-*/(){}[]", equation[i])) {
            current_var[var_index] = '\0';
            is_in_var = 0;
            var_index = 0;
        }
        i++;
    }for (i = 0; i < var_count; i++) {
        for (k = 0; k < description->numGenerals; k++) {
            if (strcmp(variables[i], description->generals[k]) == 0) {
                succes = 1;
            }
        }
        if (!succes) {
            char message[100];
            sprintf(message, "Unknown variable '%s'!\n", variables[i]);
            ext(10, message);
        }
        succes = 0;
    }
}
