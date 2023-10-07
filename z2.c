#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc == 2){ // проверка количества аргументов     
        FILE *fp; // создание поинтера на файл
        fp = fopen(argv[1], "r"); // открытие файла
        if (fp == NULL){ // проверка файла на существование
            printf("Enter a file name: ./a.out filename.txt\n"); // вывод сообщения об ошибке
        }
        srand(time(NULL)); // инициализация генератора случайных чисел
        int l = rand()%20+20; // генерация размера массива
        double ar[l]; // создание массива
        double r = 0; // создание переменной для генерации случайных чисел
        for (int i = 0; i < l; i++) { 
            r = (double)(rand())/(double)(rand()); // генерация случайного double
            r = r - (int)r; // удаление целочисленной части из double
            ar[i] = r; // запись числа в массив
            printf("%lf\n", ar[i]); // вывод мыссива
        }
        // сортировка массива с помощью selection sort
        double temp = 0; // переменная для сортировки
        for (int i = 0; i < l; i++) { // перебор всех чисел массива
            for (int j = i+1; j < l; j++) { // перебор всех чисел массива, начиная с позиции i
                if(ar[i] > ar[j]) { // сравнение чисел
                    temp = ar[i]; // замена чисел при удовлетворении условию
                    ar[i] = ar[j]; 
                    ar[j] = temp; 
                }     
            }
        }     
        fp = fopen(argv[1], "w"); // открытие файла для записи
        for (int i = 0; i < l; i++) { // цикл для записи чисел из массива в файл
            fprintf(fp, "%lf", ar[i]); // запись в файл случайного числа
            fprintf(fp, "%s", "\n"); // запись в файл переноса строки
        }
        fclose(fp); // закрытие файла
    }
    else{
        puts("Enter a file name: ./a.out filename.txt\n"); // вывод сообщения об ошибке
    }
    return 0;
}
