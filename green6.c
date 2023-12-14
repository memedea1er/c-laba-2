#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SIZE 100

char infix[MAX_SIZE]; // Инфиксное выражение
int indexPos = 0;     // Позиция символа в инфиксном выражении
char postfix[MAX_SIZE];// Постфиксное выражение
int postfixPos = 0;    // Позиция символа в постфиксном выражении

void match(char c) {
   if (c==infix[indexPos]) indexPos++; else printf("SyntaxError");
}

void handleFactor() { // Обработка скобок и цифр		
   	// if (isdigit(infix[indexPos])) {
   	// 	postfix[postfixPos++] = infix[indexPos++];
    // } else if (infix[indexPos] == '(') {
    //    	indexPos++;
   	//     handleExpr();
    //     if (infix[indexPos] == ')') {
 	  //       indexPos++;
    //     } else {
    //          perror("Ошибка расположения скобок");
    //          exit(EXIT_FAILURE);
    //    	}
    // } else {
    // 	perror("Встреча неожиданного символа");
    // 	exit(EXIT_FAILURE);
    // }
   if (isdigit(infix[indexPos]))
      match(infix[indexPos]);printf("%c",infix[indexPos-1]);
   else if
      match('(');handleExpr();match(')');
   else
      ;
}

void handleTerm() { // Обработка умножения и деления
    handleFactor(); // Обработка первого фактора
    while (infix[indexPos] == '*' || infix[indexPos] == '/') {
        char op = infix[indexPos++];
        handleFactor(); // Обработка следующего фактора
        postfix[postfixPos++] = op; // Добавление операции в постфиксное выражение
    }
}
void handleExpr() { // Обработка сложения и вычитания
    handleTerm(); // Обработка первого терма
    while (infix[indexPos] == '+' || infix[indexPos] == '-') {
        char op = infix[indexPos++];
        handleTerm(); // Обработка следующего терма
        postfix[postfixPos++] = op; // Добавление операции в постфиксное выражение
    }
}

void convertToPostfix() { // Преобразование в постфиксное выражение и вывод
    handleExpr();
    printf("Постфиксное выражение: %s\n", postfix);
}

int main() {
    printf("Введите инфиксное выражение: ");
    scanf("%s", infix);
    convertToPostfix();
    return 0;
}
