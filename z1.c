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
        srand(time(NULL));
        int l = rand()%20+20;
        int ar[l];   
        for (int i = 0; i < l; i++) { 
            ar[i] = rand();
            printf("%i\n", ar[i]);
        }
        fp = fopen(argv[1], "w");
        for (int i = 0; i < l; i++) { 
            fprintf(fp, "%i", ar[l-i-1]); // запись в файл
            fprintf(fp, "%s", "\n"); // запись в файл
        }
        fclose(fp); // закрытие файла
    }
    else{
        puts("Enter a file name: ./a.out filename.txt\n"); // вывод сообщения об ошибке
    }
    return 0;
}
