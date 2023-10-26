#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct arr // структура данных для представления массива
{
    int size;         // емкость массива
    int maxlength;    // максимальная длина строки
    char **prodnames; // массив элементов названий
    int *prices;      // массив элементов цен
};
struct arr *newArray(int strc, int strl) // функция для инициализации массива
{
    struct arr *pt = (struct arr *)malloc(sizeof(struct arr)); // выделение динамической памяти для массива
    pt->size = strc;                                           // переменная длины массива
    pt->maxlength = strl;                                      // переменная максимальной длины строки
    pt->prodnames = (char **)malloc(strc * sizeof(char *));    // выделение динамической памяти для массива элементов
    pt->prices = (int *)malloc(sizeof(int) * strc);            // выделение динамической памяти для массива элементов
    return pt;
}
void selectionsort(struct arr *pt) // сортировка массива с помощью selection sort
{
    int tempprice = 0;                 // переменная для сортировки
    char tempname[pt->maxlength];      // переменная для сортировки
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
int *checkstr(FILE *fp, char *filename) // функция для подсчета количества строк и максимальной длины строки
{
    int strc = 1;              // количество строк файла
    int strl = 1;              // максимальная длина строки файла
    int curstrl = 1;           // текущая длина строки файла
    fp = fopen(filename, "r"); // открытие файла
    while (!feof(fp))          // цикл для подсчета количества строк и макисмальной длины строки
    {
        if (fgetc(fp) == '\n') // чтение файла посимвольно и проверка на равенство переносу строки
        {
            strc++;      // увеличение переменной
            curstrl = 0; // обновление длины строки
        }
        else
        {
            curstrl++;          // увеличение переменной
            if (curstrl > strl) // сравнение текущей длины строки и максимальной
            {
                strl = curstrl; // обновление макисмыльнойд лины строки
            }
        }
    }
    fclose(fp);               // закрытие файла
    int *strings = malloc(2); // массив для вывода
    strings[0] = strc;        // добавление количества строк в массив
    strings[1] = strl;        // добавление длины строки в массив
    return strings;
}
void addarray(struct arr *pt, FILE *fp, char *filename)
{                                                     // функция для переноса файла в массив
    char prodname[pt->size];                          // строка для чтения
    int price;                                        // переменная для чтения
    int i = 0;                                        // переменная для перебора
    fp = fopen(filename, "r");                        // открытие файла
    while (fscanf(fp, "%s %i", prodname, &price) > 0) // цикл для чтения файла
    {
        pt->prodnames[i] = prodname; // добавление элемента
        pt->prices[i] = price;       // добавление элемента
        i++;                         // увеличение переменной
    }
    fclose(fp); // закрытие файла
}
void tofile(struct arr *pt, FILE *fp, char *filename)
{                                      // функция для переноса массива в файл
    fp = fopen(filename, "w");         // открытие файла для записи
    for (int i = 0; i < pt->size; i++) // перебор всех чисел массива
    {
        fprintf(fp, "%s %i\n", pt->prodnames[i], pt->prices[i]); // запись в файл
    }
    fclose(fp); // закрытие файла
}
int main(int argc, char *argv[])
{
    if (argc == 3)
    {                                                                                  // проверка количества аргументов
        FILE *fp;                                                                      // создание поинтера на файл
        struct arr *pt = newArray(checkstr(fp, argv[1])[0], checkstr(fp, argv[1])[1]); // создание массива емкостью strc
        addarray(pt, fp, argv[1]);                                                     // добавление элементов из файла в массива
        selectionsort(pt);                                                             // сортировка элементов массива
        tofile(pt, fp, argv[2]);                                                       // вывод элементов из массива в файл
    }
    else
    {
        puts("Enter a file name: ./a.out filename.txt\n"); // вывод сообщения об ошибке
    }
    return 0;
}
