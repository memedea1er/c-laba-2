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
        double ar[l];
        double r = 0;
        for (int i = 0; i < l; i++) { 
            r = (double)(rand())/(double)(rand());
            r = r - (int)r;
            ar[i] = r;
            printf("%lf\n", ar[i]);
        }
        double temp = 0;
        for (int i = 0; i < l; i++) {     
            for (int j = i+1; j < l; j++) {     
                if(ar[i] > ar[j]) {    
                    temp = ar[i];    
                    ar[i] = ar[j];    
                    ar[j] = temp;    
                }     
            }
        }     
        fp = fopen(argv[1], "w");
        for (int i = 0; i < l; i++) { 
            fprintf(fp, "%lf", ar[i]); // запись в файл
            fprintf(fp, "%s", "\n"); // запись в файл
        }
        fclose(fp); // закрытие файла
    }
    else{
        puts("Enter a file name: ./a.out filename.txt\n"); // вывод сообщения об ошибке
    }
    return 0;
}
