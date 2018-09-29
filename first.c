#include <string.h>
#include <stdio.h>
#include <stdlib.h>


// Структура, которая хранит в себе массив строк и его размер
typedef struct {
    int size;
    char** value;
} lines;


// Парсер нужных строк
char** parser(char** input, int size){
    char** output = NULL;
    int outsize = 0;
    char *find[4] = {"Date:", "From:", "To:", "Subject"};
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < 4; j++) {
            if (strstr(input[i], find[j])) {
                if (strlen(input[i]) == strlen(strstr(input[i], find[j]))) {
                    outsize++;
                    output = (char**)realloc(output, outsize*sizeof(char*));
                    output[outsize - 1] = (char*)malloc(sizeof(input[i]) + 5);
                    strcpy(output[outsize - 1], input[i]);
                }
            }
        }
    }
    outsize++;
    output = (char**)realloc(output, outsize*sizeof(char*));
    output[outsize - 1] = NULL;
    return output;
}



// Функция считывания строк с stdin
lines* getlines() {
    lines* inputlines = (lines*)malloc(sizeof(lines));
    if (!inputlines) {
        printf("%s\n", "[error]");
        return NULL;
    }
    inputlines->value = (char**)malloc(sizeof(char*));
    if (!inputlines->value) {
        free(inputlines);
        printf("%s\n", "[error]");
        return NULL;
    }
    char c = 0;
    
    //размер массива строк
    int sizeoa = 1;
    inputlines->value[sizeoa -1] = NULL;
    //размер строки
    int sizeos = 0;
    //считываем поток
    while ((c = getchar()) != EOF) {
        
        if (c == '\n') { // записывем строку str в массив строк

            // без этих трех строк валгринд меня опрокидывает
            // 
            sizeos++;
            inputlines->value[sizeoa - 1] = (char*)realloc(inputlines->value[sizeoa - 1], sizeos*sizeof(char));
            if (!inputlines->value[sizeoa -1]) {
                for(int i = 0; i < sizeoa - 1; i++) {
                    free(inputlines->value[i]);
                }
                free(inputlines->value);
                free(inputlines);
                printf("%s\n", "[error]");
                return NULL;
            }
            inputlines->value[sizeoa - 1][sizeos - 1]  = '\0';
            sizeos = 0;
            sizeoa++;
            inputlines->value = (char**)realloc(inputlines->value, sizeoa * sizeof(char*));
            if (!inputlines->value) {
                for(int i = 0; i < sizeoa - 1; i++) {
                    free(inputlines->value[i]);
                }
                free(inputlines->value);
                free(inputlines);
                printf("%s\n", "[error]");
                return NULL;
            }

            //  И без этой тоже 
            inputlines->value[sizeoa - 1] = NULL;
        }
        else { // Считываем строку
            sizeos++;
            inputlines->value[sizeoa - 1] = (char*)realloc(inputlines->value[sizeoa - 1], sizeos * sizeof(char));
            if (!inputlines->value[sizeoa - 1]) {
                for(int i = 0; i < sizeoa - 1; i++) {
                    free(inputlines->value[i]);
                }
                free(inputlines->value);
                free(inputlines);
                printf("%s\n", "[error]");
                return NULL;
            }
            inputlines->value[sizeoa - 1][sizeos - 1]  = c;
        }
    }
    inputlines->size = sizeoa - 1;
    // Заносим массив строк и его размер в структуру
    return inputlines;
}



int main() {
    //считытваем поток stdin
    lines* inputlines = getlines();

    //Парсим нужные строки
    char** array = parser(inputlines->value, inputlines->size);

    //Чистка памяти
    int i = 0;
    while (array[i]) {
        printf("%s\n", array[i]);
        free(array[i]);
        i++;
    }
    free(array[i]);
    free(array);

    for (int i = 0; i < inputlines->size+1; i++){
        free(inputlines->value[i]);
    }
    free (inputlines->value);
    free (inputlines);

    return 0;
}