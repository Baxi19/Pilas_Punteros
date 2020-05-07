#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include "pila.h"

#define MAXCHAR 10000
/*--------------------------------------------------------------------------------------------------------------------*/
int checkParentheses(char string[MAXCHAR]);
void loadPila();


/*--------------------------------------------------------------------------------------------------------------------*/
int main(){
    /*----------------------------------------------------------------------------------------------------------------*/
    /*Pila test*/
    loadPila();
    /*----------------------------------------------------------------------------------------------------------------*/
    /*VARS*/
    char path[MAXCHAR];
    char cwd[PATH_MAX];

    /*----------------------------------------------------------------------------------------------------------------*/
    /*Check if is possible to get the proyect path*/
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        strcpy(path, cwd);
        strcat(path, "\\archivo.txt");
        printf("\n\nLa ubicacion del archivo de texto es: %s\n", path);
    } else {
        perror("\n\nError al ubicar del archivo");
        return 1;
    }
    /*----------------------------------------------------------------------------------------------------------------*/
    /*Try to open the file*/
    FILE *fp;
    char str[MAXCHAR];
    char* filename = path;
    /*open in read mode*/
    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("\n\nNo se pudo abrir el archivo %s",filename);
        return 1;
    }
    /*----------------------------------------------------------------------------------------------------------------*/
    /*loop to read line by line in File*/
    while (fgets(str, MAXCHAR, fp) != NULL){
        printf(str);
        if(checkParentheses(str)){
            printf("\nParentisis correctos");
        }else{
            printf("\nParentisis incorrectos");
        }

    }
    fclose(fp);

    return 0;
}
/*--------------------------------------------------------------------------------------------------------------------*/
int checkParentheses(char string[MAXCHAR]){
    int open = 0;
    int close = 0;
    /*For in every char*/
    for (int i = 0; i < strlen(string); ++i) {
        if (string[i] =='('){
            open++;
        }else if (string[i] ==')'){
            close++;
        }
    }
    if(open == close){

        return 1;
    }

    return 0;

}
/*--------------------------------------------------------------------------------------------------------------------*/
void loadPila(){
    Pila pila, aux;

    inicpila(&pila);
    inicpila(&aux);

    apilar(&pila, 5);
    apilar(&pila, 6);
    apilar(&pila, 7);
    apilar(&pila, 8);
    
    mostrar(&pila);

}
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/


