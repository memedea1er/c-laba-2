#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    if (argc == 2) // проверка количества аргументов
    {
        FILE *fp;                 // создание поинтера на файл
        fp = fopen(argv[1], "r"); // открытие файла
        if (fp == NULL)           // проверка файла на существование
        {
            printf("Enter a file name: ./a.out filename.txt\n"); // вывод сообщения об ошибке
        }
        srand(time(NULL));          // инициализация генератора случайных чисел
        int l = rand() % 20 + 20;   // генерация размера массива
        int ar[l];                  // создание массива
        for (int i = 0; i < l; i++) // цикл для заполнения массива случайными числами
        {
            ar[i] = rand();        // генерация случайного числа и запись в массив
            printf("%i\n", ar[i]); // вывод мыссива
        }
        fp = fopen(argv[1], "w");   // открытие файла для записи
        for (int i = 0; i < l; i++) // цикл для записи чисел из массива в файл
        {
            fprintf(fp, "%i", ar[l - i - 1]); // запись в файл случайного числа
            fprintf(fp, "%s", "\n");          // запись в файл переноса строки
        }
        fclose(fp); // закрытие файла
    }
    else
    {
        puts("Enter a file name: ./a.out filename.txt\n"); // вывод сообщения об ошибке
    }
    return 0;
}
