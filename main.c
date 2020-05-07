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
void fillPila();
void pilaVacia();
void numeroTopePila();


/*--------------------------------------------------------------------------------------------------------------------*/
int main(){
    /*----------------------------------------------------------------------------------------------------------------*/
    //loadPila();
    //fillPila();
    //pilaVacia();
    //numeroTopePila();


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
    int depth = 0;
    int depthMax = 0;
    /*For in every char*/
    for (int i = 0; i < strlen(string); ++i) {
        if (string[i] =='('){
            open++;
            depth++;
            if(depth > depthMax){
                depthMax = depth;
            }
            printf("\nProfundidad: %d, index: %d", depth, i);
        }else if (string[i] ==')'){
            close++;
            depth--;
        }
    }
    if(depthMax > 0){
        printf("\nProfundidad Maxima: %d", depthMax);
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

    apilar(&aux,desapilar(&pila));
    mostrar(&pila);
    mostrar(&aux);
}
/*--------------------------------------------------------------------------------------------------------------------*/
void fillPila(){
    Pila pila, aux;
    char continuar = 's';

    inicpila(&pila);
    do{
        leer(&pila);
        printf("Para continuar presione s/n");
        fflush(stdin);
        scanf("%c", &continuar);
    }while(continuar == 's');
    mostrar(&pila);

}

/*--------------------------------------------------------------------------------------------------------------------*/
void pilaVacia(){
    Pila pila, aux;
    char continuar = 's';

    inicpila(&pila);
    inicpila(&aux);

    do{
        leer(&pila);
        printf("Para continuar presione s/n");
        fflush(stdin);
        scanf("%c", &continuar);
    }while(continuar == 's');
    mostrar(&pila);

    while(!pilavacia(&pila)){
        apilar(&aux, desapilar(&pila));
    }
    mostrar(&aux);
}
/*--------------------------------------------------------------------------------------------------------------------*/
void numeroTopePila(){
    Pila pila, aux, basura;
    char continuar = 's';

    inicpila(&pila);
    inicpila(&aux);
    inicpila(&basura);

    do{
        leer(&pila);
        printf("Para continuar presione s/n");
        fflush(stdin);
        scanf("%c", &continuar);
    }while(continuar == 's');
    mostrar(&pila);

    while(!pilavacia(&pila)){
        if(tope(&pila) == 5){
            apilar(&basura, desapilar(&pila));
        }else{
            apilar(&aux, desapilar(&pila));
        }

    }
    mostrar(&basura);
    mostrar(&aux);
}
/*--------------------------------------------------------------------------------------------------------------------*/


