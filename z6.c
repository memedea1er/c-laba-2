#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
struct stack // структура данных для представления stack
{
    int maxsize;  // максимальная емкость stack
    int top;      // индекс вершины stack
    char **items; // массив элементов stack
};
struct stack *newStack(int capacity) // функция для инициализации stack
{
    struct stack *pts = (struct stack *)malloc(sizeof(struct stack)); // выделение динамической памяти для stack
    pts->maxsize = capacity;                                          // определение емкости
    pts->top = -1;                                                    // определение индекса вершины
    pts->items = (char **)malloc(sizeof(char *) * capacity);          // выделение динамической памяти для массива элементов
    for (int i = 0; i < capacity; i++)                                // выделение динамической памяти для строк
    {
        pts->items[i] = (char *)malloc(sizeof(char) * 10);
    }
    return pts;
}
void stack_push(struct stack *pts, char *x) // функция для добавления элемента `x` в stack
{
    if (pts->top == pts->maxsize - 1) // проверка, не заполнен ли уже stack
    {
        printf("Overflow\nProgram Terminated\n"); // вывод информации о том, что stack заполнен
        exit(EXIT_FAILURE);                       // завершение программы
    }
    strcpy(pts->items[++pts->top], x); // добавление элемента и увеличиние индекса вершины
}
char *stack_peek(struct stack *pts) // функция для возврата верхнего элемента stack
{
    if (pts->top != -1) // проверка на пустой stack
    {
        return pts->items[pts->top]; // возврат верхнего элемента
    }
    else
    {
        exit(EXIT_FAILURE); // завершение программы
    }
}
char *stack_pop(struct stack *pts) // функция для извлечения верхнего элемента из stack
{
    if (pts->top == -1) // проверка на пустой stack
    {
        printf("Underflow\nProgram Terminated\n"); // вывод информации о том, что stack пустой
        exit(EXIT_FAILURE);                        // завершение программы
    }
    return pts->items[pts->top--]; // уменьшение размер stack на 1
}
struct queue
{
    char **items; // указатель на данные
    int bottom;   // указатель на нижнюю границу
    int top;      // указатель на верхнюю границу
    int amount;   // количество элементов в очереди
    int maxsize;  // максимальное количество элементов
};
struct queue *newQueue(int capacity) // функция для инициализации очереди
{
    struct queue *ptq = (struct queue *)malloc(sizeof(struct queue)); // выделение динамической памяти для очереди
    ptq->maxsize = capacity;                                          // определение емкости
    ptq->bottom = -1;                                                 // определение нижней границы
    ptq->top = -1;                                                    // определение верхней границы
    ptq->amount = 0;                                                  // определение количества элементов
    ptq->items = (char **)malloc(sizeof(char *) * capacity);          // выделение динамической памяти для массива элементов
    for (int i = 0; i < capacity; i++)                                // выделение динамической памяти для строк
    {
        ptq->items[i] = (char *)malloc(sizeof(char) * 10);
    }
    return ptq;
}
void queue_push(struct queue *ptq, char *x) // функция для добавления элемента `x` в очередь
{
    if (ptq->amount == ptq->maxsize) // проверка не заполнена ли уже очередь
    {
        printf("Overflow\nProgram Terminated\n"); // вывод информации о том, что stack заполнен
        exit(EXIT_FAILURE);                       // завершение программы
    }
    strcpy(ptq->items[++ptq->top], x); // добавление элемента и увеличиние верхней границы
    ptq->amount++;                     // увеличение количества элементов
    if (ptq->top > ptq->maxsize - 1)   // обнуление верхней границы при переходе за максимальный размер
    {
        ptq->top = -1;
    }
}
char *queue_pop(struct queue *ptq) // функция для извлечения верхнего элемента из очередь
{
    if (ptq->amount == 0) // проверка на пустую очередь
    {
        printf("Underrflow\nProgram Terminated\n"); // вывод информации о том, что stack заполнен
        exit(EXIT_FAILURE);                         // завершение программы
    }
    char *a = ptq->items[++ptq->bottom]; // присвоение элемента нижней границы
    ptq->amount--;                       // уменьшение количества элементов
    if (ptq->bottom > ptq->maxsize - 1)  // обнуление нижней границы при переходе за максимальный размер
    {
        ptq->bottom = -1;
    }
    return a;
}
void polish(struct stack *pts, struct queue *ptq, char *sum) // перевод выражения в обратную польскую запись
{
    char ch;      // переменная для чтения файла
    char str[20]; // строка для записи числа
    char *endptr; // символ, следующий за числом после выполнения функции strtod
    for (int i = 0; i < strlen(sum); i++)
    {
        ch = sum[i];   // посимвольное чтение файла
        if (ch != ' ') // проверка символа на пробел
        {
            strncat(str, &ch, 1); // добавление char в строку
        }
        else
        {
            double numb = strtod(str, &endptr); // генерация числа из строки для проверки, чем она является
            if (endptr != str)                  // если endptr не указывает на тот же адрес, что и str, то строка - число
            {
                queue_push(ptq, str); // добавление числа в очередь
            }
            else
            {
                if (strcmp(str, "+") == 0 || strcmp(str, "-") == 0 || strcmp(str, "*") == 0 || strcmp(str, "/") == 0) // проверка на равенство строки оператору "+-*/"
                {
                    if (pts->top == -1 || strcmp(str, "(") == 0) // проверка вершины стека на равенство "(" или на пустой стек
                    {
                        stack_push(pts, str); // добавление оператора в стек
                    }
                    else if ((strcmp(str, "*") == 0 || strcmp(str, "/") == 0) & (strcmp(stack_peek(pts), "+") == 0 || strcmp(stack_peek(pts), "-") == 0)) // сравнение приоритета оператора из вершины стека с оператором из строки
                    {
                        stack_push(pts, str); // добавление оператора в стек
                    }
                    else // остальные случаи
                    {
                        while (!(pts->top == -1)) // цикл пока вершина стека не равна 0
                        {
                            if (strcmp(stack_peek(pts), "(") == 0 || ((strcmp(str, "*") == 0 || strcmp(str, "/") == 0) & ((strcmp(stack_peek(pts), "+") == 0 || strcmp(stack_peek(pts), "-") == 0)))) // проверка вершины на равенство "(" или оператору с проядком ниже
                            {
                                break; // конец цикла
                            }
                            queue_push(ptq, stack_pop(pts)); // добавление оператора в очередь
                        }
                        stack_push(pts, str); // добавление оператора в стек
                    }
                }
                else if (strcmp(str, "(") == 0) // проверка на равенство строки левой скобке
                {
                    stack_push(pts, str); // добавление левой скобки в стек
                }
                else if (strcmp(str, ")") == 0) // проверка на равенство строки правой скобке
                {
                    while (!(strcmp(stack_peek(pts), "(") == 0)) // цикл пока вершина не левая скобка
                    {
                        queue_push(ptq, stack_pop(pts)); // перенос стека в очередь
                    }
                    stack_pop(pts); // удаление левой скобки из стека
                }
            }
            strcpy(str, ""); // обнуление строки
        }
    }
    while (pts->top > -1) // перенос оставшихся элементов из стека в очередь
    {
        queue_push(ptq, stack_pop(pts));
    }
}
int lencount(FILE *fp, char *filename) // подсчет длины файла
{
    fp = fopen(filename, "r"); // открытие файла
    int count = 0;             // переменная для длины строки
    while (!feof(fp))          // цикл для подсчета длины строки
    {
        char ch = fgetc(fp); // чтение файла посимвольно
        count++;             // увеличение длины
    }
    fclose(fp); // закрытие файла
    return count;
}
char *trueform(FILE *fp, char *filename)
{
    fp = fopen(filename, "r");                                      // открытие файла
    char str[lencount(fp, filename)];                               // создание строки длиной аналогичной строке из файла
    fgets(str, sizeof(str), fp);                                    // извлечение строки из файла
    char *truestr = (char *)malloc(sizeof(str) * 2 * sizeof(char)); // строка для форматирования
    int j = 0;                                                      // переменная счетчик
    for (int i = 0; i < sizeof(str); i++)                           // цикл форматирования
    {
        if (str[i+1] == ',') // проверка ch на равенство точке
        {
            str[i+1] = '.'; // замена ch на запятой
        }
        if ((isdigit(str[i]) || str[i] == '.') & (isdigit(str[i + 1]) || str[i + 1] == '.')) // если символ - число и после него число
        {
            truestr[j] = str[i]; // добавление в отформатированную строку символа
            j++;                 // увеличение счетчика
        }
        else if (str[i] != ' ' & str[i + 1] != ' ') // если символ не равен пробелу и после него нет пробела
        {
            truestr[j] = str[i];  // добавление в отформатированную строку символа
            truestr[j + 1] = ' '; // добавление в отформатированную строку пробела после символа
            j += 2;               // увеличение счетчика на 2
        }
        else // остальные случаи
        {
            truestr[j] = str[i]; // добавление в отформатированную строку символа
            j++;                 // увеличение счетчика
        }
    }
    return truestr;
}
int main(int argc, char *argv[])
{
    if (argc == 2) // проверка количества аргументов
    {
        FILE *fp;                                  // создание поинтера на файл
        char *sum = trueform(fp, argv[1]);         // построение строки из файла
        struct stack *pts = newStack(strlen(sum)); // создание stack с вычислением емкости
        struct queue *ptq = newQueue(strlen(sum)); // создание queue с вычислением емкости
        polish(pts, ptq, sum);                     // вычисление выражения
        while (ptq->amount > 0)                    // цикл для вывода результата
        {
            printf("%s ", queue_pop(ptq)); // извлечения нижнего элемента из stack
        }
        puts("");
    }
    return 0;
}
