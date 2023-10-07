#include <stdio.h>
#include <stdlib.h>

struct stack // структура данных для представления stack
{
    int maxsize; // максимальная емкость stack
    int top;     // индекс вершины stack
    int *items;  // массив элементов stack
};
struct stack *newStack(int capacity) // функция для инициализации stack
{
    struct stack *pt = (struct stack *)malloc(sizeof(struct stack)); // выделение динамической памяти для stack
    pt->maxsize = capacity;                                          // определение емкости
    pt->top = -1;                                                    // определение индекса вершины
    pt->items = (int *)malloc(sizeof(int) * capacity);               // выделение динамической памяти для массива элементов
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
void push(struct stack *pt, int x) // функция для добавления элемента `x` в stack
{
    if (isFull(pt)) // проверка, не заполнен ли уже stack
    {
        printf("Overflow\nProgram Terminated\n"); // вывод информации о том, что stack заполнен
        exit(EXIT_FAILURE);                       // завершение программы
    }
    printf("Inserting %d\n", x); // вывод информации о том, что элемент добавляется в stack
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
int pop(struct stack *pt) // функция для извлечения верхнего элемента из stack
{
    if (isEmpty(pt)) // проверка на пустой stack
    {
        printf("Underflow\nProgram Terminated\n"); // вывод информации о том, что stack пустой
        exit(EXIT_FAILURE);                        // завершение программы
    }
    printf("Removing %d\n", peek(pt)); // вывод сообщения о извлечении элемента
    return pt->items[pt->top--];       // уменьшение размер stack на 1
}
int main()
{
    struct stack *pt = newStack(5);              // создание stack емкостью 5
    push(pt, 1);                                 // добавление 1 в stack
    push(pt, 2);                                 // добавление 2 в stack
    push(pt, 3);                                 // добавление 3 в stack
    printf("The top element is %d\n", peek(pt)); // вывод верхнего элемента
    pop(pt);                                     // удаление верхнего элемента из stack
    pop(pt);                                     // удаление верхнего элемента из stack
    pop(pt);                                     // удаление верхнего элемента из stack
    if (isEmpty(pt))                             // проверка, пуст stack или нет
    {
        printf("The stack is empty"); // вывод сообщения
    }
    else
    {
        printf("The stack is not empty"); // вывод сообщения
    }
    return 0;
}
