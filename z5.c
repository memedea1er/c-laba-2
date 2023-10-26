#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct stack // структура данных для представления stack
{
    int maxsize; // максимальная емкость stack
    int top;     // индекс вершины stack
    double *items;  // массив элементов stack
};
struct stack *newStack(int capacity) // функция для инициализации stack
{
    struct stack *pt = (struct stack *)malloc(sizeof(struct stack)); // выделение динамической памяти для stack
    pt->maxsize = capacity;                                          // определение емкости
    pt->top = -1;                                                    // определение индекса вершины
    pt->items = (double *)malloc(sizeof(double) * capacity);               // выделение динамической памяти для массива элементов
    return pt;
}
int size(struct stack *pt) // функция для возврата размера stack
{
    return pt->top + 1; // возвращение текущего индекса вершины
}
int isEmpty(struct stack *pt) // функция для проверки, пуст stack или нет
{
    return pt->top == -1; // возвращение равенства индекса вершины -1
}
int isFull(struct stack *pt) // функция для проверки, заполнен ли stack или нет
{
    return pt->top == pt->maxsize - 1; // возвращение максимальной емкости stack
}
void push(struct stack *pt, double x) // функция для добавления элемента `x` в stack
{
    if (isFull(pt)) // проверка, не заполнен ли уже stack
    {
        printf("Overflow\nProgram Terminated\n"); // вывод информации о том, что stack заполнен
        exit(EXIT_FAILURE);                       // завершение программы
    }
    pt->items[++pt->top] = x;    // добавление элемента и увеличиние индекса вершины
}
int peek(struct stack *pt) // функция для возврата верхнего элемента stack
{
    if (!isEmpty(pt)) // проверка на пустой stack
    {
        return pt->items[pt->top]; // возврат верхнего элемента
    }
    else
    {
        exit(EXIT_FAILURE); // завершение программы
    }
}
double pop(struct stack *pt) // функция для извлечения верхнего элемента из stack
{
    if (isEmpty(pt)) // проверка на пустой stack
    {
        printf("Underflow\nProgram Terminated\n"); // вывод информации о том, что stack пустой
        exit(EXIT_FAILURE);                        // завершение программы
    }
    return pt->items[pt->top--];       // уменьшение размер stack на 1
}
int polish(struct stack *pt, FILE *fp, char *filename)
{
    char ch; // переменная для чтения файла
    fp = fopen(filename, "r");
    while (!feof(fp)) // цикл для чтения файла
    { 
        char str[10]; // строка для записи числа
        ch = fgetc(fp);  // посимвольное чтение файла
        if (isdigit(ch)) // проверка символа на число
        {
            strncat(str, &ch, 1); // добавление char в строку
        }
        else
        {
            if (ch == ' ') // проверка символа на пробел
            {
                if (strlen(str) > 0)
                {
                    double numb = (double)atoi(str);
                    push(pt, numb); // добавление в стек
                    strcpy(str, "");
                }
            }
            else if (ch == '+') // проверка символа на оператор +
            {
                double first = pop(pt);      // извлечение элемента из стека
                double second = pop(pt);     // извлечение элемента из стека
                push(pt, second + first); // занесение элемента в стек
            }
            else if (ch == '-') // проверка символа на оператор -
            {
                double first = pop(pt);      // извлечение элемента из стека
                double second = pop(pt);     // извлечение элемента из стека
                push(pt, second - first); // занесение элемента в стек
            }
            else if (ch == '*') // проверка символа на оператор *
            {
                double first = pop(pt);      // извлечение элемента из стека
                double second = pop(pt);     // извлечение элемента из стека
                push(pt, second * first); // занесение элемента в стек
            }
            else if (ch == '/') // проверка символа на оператор /
            {
                double first = pop(pt);      // извлечение элемента из стека
                double second = pop(pt);     // извлечение элемента из стека
                push(pt, second / first); // занесение элемента в стек
            }
        }
    }
    fclose(fp); // закрытие файла
}
int main(int argc, char *argv[])
{
    if (argc == 2) // проверка количества аргументов
    {
        struct stack *pt = newStack(4); // создание stack емкостью 5
        FILE *fp;                       // создание поинтера на файл
        push(pt, 0);                    // добавление в стек 0
        polish(pt, fp, argv[1]);        // вычисление выражения
        double result = pop(pt);           // присвоение результата
        printf("Result: %lf\n", result); // вывод результата
    }
    return 0;
}
