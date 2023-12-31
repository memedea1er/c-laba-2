#include <stdio.h>
#include <stdlib.h>

struct Item // структура для представления элемента стека
{
    int data;          // значение элемента
    struct Item *prev; // указатель на предыдущий элемент
};
struct Stack // структура данных для представления стека
{
    struct Item *top; // указатель на вершину стека
    int maxsize;      // максималньый размер
    int cursize;      // текущий размер
};
struct Stack *newStack(int size) // функция для инициализации стека
{
    struct Stack *pt = (struct Stack *)malloc(sizeof(struct Stack));
    pt->top = NULL; // инициализация вершины как пустого списка
    pt->maxsize = 0;
    pt->maxsize = size;
    return pt;
}
int isEmpty(struct Stack *pt) // функция для проверки, пуст ли стек
{
    return pt->top == NULL;
}
void push(struct Stack *pt, int x) // функция для добавления элемента в стек
{
    if (pt->cursize++ == pt->maxsize)
    {
        printf("Overflow\nProgram Terminated\n");
        exit(EXIT_FAILURE);
    }
    struct Item *pti = (struct Item *)malloc(sizeof(struct Item)); // выделение памяти для элемента стека
    pti->data = x;                                                 // присвоение значения элементу стека
    pti->prev = pt->top;                                           // присвоение значения указателю
    pt->top = pti;                                                 // присвоение значения вершине
    printf("Inserting %d\n", x);
}
int peek(struct Stack *pt) // функция для возврата верхнего элемента стека
{
    pt->cursize--;
    if (!isEmpty(pt))
    {
        return pt->top->data;
    }
    else
    {
        exit(EXIT_FAILURE);
    }
}
int pop(struct Stack *pt) // функция для извлечения верхнего элемента из стека
{
    if (isEmpty(pt))
    {
        printf("Underflow\nProgram Terminated\n");
        exit(EXIT_FAILURE);
    }
    int data = pt->top->data; // извлечение элемента
    pt->top = pt->top->prev;  // изменение значения вершины
    printf("Removing %d\n", data);
    return data;
}
void printStack(struct Stack *pt) // функция для вывода всех элементов стека
{
    struct Item *current = pt->top;
    printf("Stack: ");
    while (current != NULL)
    {
        printf("%d ", current->data);
        current = current->prev;
    }
    printf("\n");
}
int main()
{
    struct Stack *pt = newStack(3); // создание стека
    push(pt, 1);                    // добавление 1 в стек
    push(pt, 2);                    // добавление 2 в стек
    push(pt, 3);                    // добавление 3 в стек
    printStack(pt);                 // вывод стека
    if (isEmpty(pt))                // проверка, пуст ли стек
    {
        printf("The stack is empty\n");
    }
    else
    {
        printf("The stack is not empty\n");
    }
    return 0;
}
