#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct arr // структура данных для представления массива
{
    int size; // емкость массива
    int maxlength; // максимальная длина строки
    char **prodnames;  // массив элементов 
    int *prices;  // массив элементов stack
};
struct arr *newArray(int strc, int strl) // функция для инициализации массива
{
    struct arr *pt = (struct arr *)malloc(sizeof(struct arr)); // выделение динамической памяти для массива
    pt->size = strc;
    pt->maxlength = strl;
    pt->prodnames = (char **)malloc(strc * sizeof(char *));               // выделение динамической памяти для массива элементов
    pt->prices = (int *)malloc(sizeof(int) * strc);               // выделение динамической памяти для массива элементов
    return pt;
}
void push(struct arr *pt, char *x, int y, int i) // функция для добавления элемента `x` в stack
{
    pt->prodnames[i] = x;
    pt->prices[i] = y;    // добавление элемента и увеличиние индекса вершины
}
void selectionsort(struct arr *pt) // сортировка массива с помощью selection sort
{
    int tempprice = 0; // переменная для сортировки
    char tempname[pt->maxlength]; // переменная для сортировки
    for (int i = 0; i < pt->size; i++) // перебор всех чисел массива
        {
            for (int j = i + 1; j < pt->size; j++) // перебор всех чисел массива, начиная с позиции i
            {
                if (pt->prices[i] > pt->prices[j]) // сравнение чисел
                {                         
                    tempprice = pt->prices[i]; // замена чисел при удовлетворении условию
                    pt->prices[i] = pt->prices[j];
                    pt->prices[j] = tempprice;
                    strcpy(tempname, pt->prodnames[i]); // замена строк при удовлетворении условию
                    strcpy(pt->prodnames[i], pt->prodnames[j]);
                    strcpy(pt->prodnames[j], tempname);
                }
            }
        }
}
void add(struct arr *pt, char *prodname, int price, int i)
{
    char *new_prodname = (char *)malloc((strlen(prodname) + 1) * sizeof(char)); // Выделение памяти для новой строки
    strcpy(new_prodname, prodname); // Копирование строки
    push(pt, new_prodname, price, i);
}
char *display(struct arr *pt, int i) // функция для возврата верхнего элемента stack
{
    // Создаем временную строку, в которую будет форматироваться результат
    char result[100]; // Предполагаем максимальную длину строки 100 символов (задайте значение в зависимости от вашего конкретного случая)
    // Форматируем строку
    snprintf(result, sizeof(result), "%s %i", pt->prodnames[i], pt->prices[i]);
    // Динамически выделяем память для результата и копируем в неё отформатированную строку
    char *result_str = (char *)malloc(strlen(result) + 1);
    strcpy(result_str, result);
    return result_str;
}
int main(int argc, char *argv[])
{
    if (argc == 3)
    {                             // проверка количества аргументов
        FILE *fp;                 // создание поинтера на файл
        int strc = 0;             // количество строк файла
        int strl = 0;             // максимальная длина строки файла
        int curstrl = 0;          // текущая длина строки файла
        fp = fopen(argv[1], "r"); // открытие файла
        while (!feof(fp))         // цикл для подсчета количества строк и макисмальной длины строки
        {
            if (fgetc(fp) == '\n') // чтение файла посимвольно и проверка на равенство переносу строки
            {                
                strc++;      // увеличение переменной
                curstrl = 0; // обновление длины строки
            }
            else
            {
                curstrl++; // увеличение переменной
                if (curstrl > strl) // сравнение текущей длины строки и максимальной
                {                   
                    strl = curstrl; // обновление макисмыльнойд лины строки
                }
            }
        }
        fclose(fp);                // закрытие файла
        struct arr *pt = newArray(strc, strl);              // создание массива емкостью strc
        char prodname[strl]; // строка для чтения
        int price;           // создание массива символов
        int i = 0;                 // переменная для записи файла в массивы
        fp = fopen(argv[1], "r");  // открытие файла
        while (fscanf(fp, "%s %i", prodname, &price) > 0) // цикл для чтения файла
        { 
            add(pt, prodname, price, i);
            i++;
        }
        fclose(fp); // закрытие файла
        selectionsort(pt);
        fp = fopen(argv[2], "w"); // открытие файла для записи
        for (int i = 0; i < strc; i++) // перебор всех чисел массива
        {                                                  
            fprintf(fp, "%s\n", display(pt,i)); // запись в файл
        }
        fclose(fp); // закрытие файла
    }
    else
    {
        puts("Enter a file name: ./a.out filename.txt\n"); // вывод сообщения об ошибке
    }
    return 0;
}
