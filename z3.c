#include <stdio.h>
#include <string.h>

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
        char prodname[strc][strl]; // строка для чтения
        int price[strc];           // создание массива символов
        int i = 0;                 // переменная для записи файла в массивы
        fp = fopen(argv[1], "r");  // открытие файла
        while (fscanf(fp, "%s %i", prodname[i], &price[i]) > 0) // цикл для чтения файла
        { 
            i++;
        }
        fclose(fp); // закрытие файла
        // сортировка массива с помощью selection sort
        int tempprice = 0; // переменная для сортировки
        char tempname[strl];
        for (int i = 0; i < strc; i++) // перебор всех чисел массива
        {
            for (int j = i + 1; j < strc; j++) // перебор всех чисел массива, начиная с позиции i
            {
                if (price[i] > price[j]) // сравнение чисел
                {                         
                    tempprice = price[i]; // замена чисел при удовлетворении условию
                    price[i] = price[j];
                    price[j] = tempprice;
                    strcpy(tempname, prodname[i]); // замена строк при удовлетворении условию
                    strcpy(prodname[i], prodname[j]);
                    strcpy(prodname[j], tempname);
                }
            }
        }
        fp = fopen(argv[2], "w"); // открытие файла для записи
        for (int i = 0; i < strc; i++) // перебор всех чисел массива
        {                                                  
            fprintf(fp, "%s %i\n", prodname[i], price[i]); // запись в файл
        }
        fclose(fp); // закрытие файла
    }
    else
    {
        puts("Enter a file name: ./a.out filename.txt\n"); // вывод сообщения об ошибке
    }
    return 0;
}
