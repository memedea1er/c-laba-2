#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct stack // структура данных для представления stack
{
    int maxsize;   // максимальная емкость stack
    int top;       // индекс вершины stack
    double *items; // массив элементов stack
};
struct stack *newStack(int capacity) // функция для инициализации stack
{
    struct stack *pt = (struct stack *)malloc(sizeof(struct stack)); // выделение динамической памяти для stack
    pt->maxsize = capacity;                                          // определение емкости
    pt->top = -1;                                                    // определение индекса вершины
    pt->items = (double *)malloc(sizeof(double) * capacity);         // выделение динамической памяти для массива элементов
    return pt;
}
void push(struct stack *pt, double x) // функция для добавления элемента `x` в stack
{
    if (pt->top == pt->maxsize - 1) // проверка, не заполнен ли уже stack
    {
        printf("Overflow\nProgram Terminated\n"); // вывод информации о том, что stack заполнен
        exit(EXIT_FAILURE);                       // завершение программы
    }
    pt->items[++pt->top] = x; // добавление элемента и увеличиние индекса вершины
}
double peek(struct stack *pt) // функция для возврата верхнего элемента stack
{
    if (pt->top == -1) // проверка на пустой stack
    {
        exit(EXIT_FAILURE); // завершение программы
    }
    else
    {
        return pt->items[pt->top]; // возврат верхнего элемента
    }
}
double pop(struct stack *pt) // функция для извлечения верхнего элемента из stack
{
    if (pt->top == -1) // проверка на пустой stack
    {
        printf("Underflow\nProgram Terminated\n"); // вывод информации о том, что stack пустой
        exit(EXIT_FAILURE);                        // завершение программы
    }
    return pt->items[pt->top--]; // уменьшение размер stack на 1
}
int polish(struct stack *pt, FILE *fp, char *filename) // решение выражения в обратной польской записи
{
    char ch;                   // переменная для чтения файла
    char str[10];              // строка для записи числа
    fp = fopen(filename, "r"); // открытие файла
    while (!feof(fp))          // цикл для чтения файла
    {
        ch = fgetc(fp);  // посимвольное чтение файла
        if (isdigit(ch)) // проверка символа на число
        {
            strncat(str, &ch, 1); // добавление char в строку
        }
        else
        {
            if (ch == ' ') // проверка символа на пробел
            {
                if (strlen(str) > 0) // проверка длины строки
                {
                    double numb = (double)atoi(str); // генерация числа из строки
                    push(pt, numb);                  // добавление в стек
                    strcpy(str, "");                 // обнуление строки
                }
            }
            else if (ch == '+') // проверка символа на оператор +
            {
                double first = pop(pt);   // извлечение элемента из стека
                double second = pop(pt);  // извлечение элемента из стека
                push(pt, second + first); // занесение элемента в стек
            }
            else if (ch == '-') // проверка символа на оператор -
            {
                double first = pop(pt);   // извлечение элемента из стека
                double second = pop(pt);  // извлечение элемента из стека
                push(pt, second - first); // занесение элемента в стек
            }
            else if (ch == '*') // проверка символа на оператор *
            {
                double first = pop(pt);   // извлечение элемента из стека
                double second = pop(pt);  // извлечение элемента из стека
                push(pt, second * first); // занесение элемента в стек
            }
            else if (ch == '/') // проверка символа на оператор /
            {
                double first = pop(pt);   // извлечение элемента из стека
                double second = pop(pt);  // извлечение элемента из стека
                push(pt, second / first); // занесение элемента в стек
            }
        }
    }
    fclose(fp); // закрытие файла
}
int numbinarow(FILE *fp, char *filename) // проверка максимального количество чисел в записи под ряд
{
    fp = fopen(filename, "r"); // открытие файла
    int curr = 1;              // переменная для текущей длины строки
    int maximum = 1;           // переменная для максимальной длины строки
    while (!feof(fp))          // цикл для подсчета количества чисел под ряд
    {
        char ch = fgetc(fp); // чтение файла посимвольно
        if (ch == ' ')       // проверка на равенство пробелу
        {
            curr += 1;          // увеличение переменной
            if (curr > maximum) // сравнение текущей числа чисел под ряд и максимально
            {
                maximum = curr; // обновление максимального количества
            }
        }
        else if (!isdigit(ch)) // проверка на неравенство символу
        {
            curr = 1; // обновление переменной
        }
    }
    return maximum;
}
int main(int argc, char *argv[])
{
    if (argc == 2) // проверка количества аргументов
    {
        FILE *fp;                                             // создание поинтера на файл
        struct stack *pt = newStack(numbinarow(fp, argv[1])); // создание stack с вычислением емкости
        push(pt, 0);                                          // добавление в стек 0
        polish(pt, fp, argv[1]);                              // вычисление выражения
        printf("Result: %lf\n", peek(pt));                    // вывод результата
    }
    return 0;
}
