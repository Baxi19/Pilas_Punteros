/*--------------------------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
/*--------------------------------------------------------------------------------------------------------------------*/
/*Randald Villegas Brenes*/
/*Practica para la casa de lenguaje C*/
/*06/05/2020*/
/*--------------------------------------------------------------------------------------------------------------------*/
#define MAXCHAR 10000
/*--------------------------------------------------------------------------------------------------------------------*/
/*structs*/
struct structNodo{
    char simbolo;
    struct structNodo *siguiente;
};
typedef struct structNodo nodo;
/*--------------------------------------------------------------------------------------------------------------------*/
/*Declaracion de los Metodos*/
nodo *crearLista(nodo *lista);
nodo *push(char simbolo, nodo*pila);
nodo *insertNodoFinal(char simbolo, nodo *lista);
nodo *pop(char *valor, nodo *pila);
nodo imprimirExpression(nodo *lista);

int expresionBalanceada(char expresion[]);
int esOperador(char simbolo);/*1 si es operador, 0 si no*/
int prioridad(char operador);
nodo *infijaPostfija(char expresion[]);

/*--------------------------------------------------------------------------------------------------------------------*/
/*Applicacion*/
/*--------------------------------------------------------------------------------------------------------------------*/
int main(){

    /*----------------------------------------------------------------------------------------------------------------*/
    /*VARS*/
    char path[MAXCHAR];
    char cwd[PATH_MAX];
    nodo *postFija;
    /*----------------------------------------------------------------------------------------------------------------*/
    /*Se intenta tomar el path del proyecto*/
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        strcpy(path, cwd);
        strcat(path, "\\archivo.txt");
        printf("\n\nLa ubicacion del archivo de texto es: %s\n", path);
    } else {
        perror("\n\nError al ubicar del archivo");
        return 1;
    }
    /*----------------------------------------------------------------------------------------------------------------*/
    /*Intentamos abrir el archivo*/
    FILE *fp;
    char str[MAXCHAR];
    char* filename = path;
    /*modo de lectura*/
    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("\n\nNo se pudo abrir el archivo %s",filename);
        return 1;
    }
    /*----------------------------------------------------------------------------------------------------------------*/
    /*ciclo para leer cada renglon del archivo*/
    while (fgets(str, MAXCHAR, fp) != NULL){
        printf("\nEXPRESION: %s",str);
        if(expresionBalanceada(str)){
            postFija = infijaPostfija(str);
            imprimirExpression(postFija);
        }else{
            printf("Expresion no valida!");
        }
    }
    fclose(fp);

    return 0;
}
/*--------------------------------------------------------------------------------------------------------------------*/
/*METODOS*/
/*--------------------------------------------------------------------------------------------------------------------*/
/*Nueva lista*/
nodo *crearLista(nodo *lista){
    return lista = NULL;
}
/*--------------------------------------------------------------------------------------------------------------------*/
/*insertar al inicio*/
nodo *push(char simbolo, nodo *pila){
    nodo *nodoNuevo;
    nodoNuevo = (nodo*) malloc (sizeof(nodo));
    if(nodoNuevo != NULL){
        nodoNuevo->simbolo = simbolo;
        nodoNuevo->siguiente= pila;
        pila= nodoNuevo;
    }
    return  pila;
}
/*--------------------------------------------------------------------------------------------------------------------*/
/*insertar al final*/
nodo *insertNodoFinal(char simbolo, nodo *lista){
    nodo *nodoNuevo, *nodoAuxiliar;
    nodoNuevo = (nodo*) malloc (sizeof(nodo));
    if(nodoNuevo != NULL){
        nodoNuevo->simbolo=simbolo;
        nodoNuevo->siguiente= NULL;
        if(lista == NULL){
            lista = nodoNuevo;
        }else{
            nodoAuxiliar = lista;
            while(nodoAuxiliar->siguiente != NULL){
                nodoAuxiliar= nodoAuxiliar->siguiente;
            }
            nodoAuxiliar->siguiente = nodoNuevo;
        }
    }
    return lista;
}
/*--------------------------------------------------------------------------------------------------------------------*/
/*retirar al inicio de la lista*/
nodo *pop(char *valor, nodo *pila){
    nodo *nodoAuxiliar;
    char dato;
    if(pila == NULL){
        printf("\nPILA VACIA");
    }else{
        nodoAuxiliar = pila;
        dato = nodoAuxiliar->simbolo;
        pila = nodoAuxiliar->siguiente;
        *valor = dato;
        free(nodoAuxiliar);
    }
    return pila;
}
/*--------------------------------------------------------------------------------------------------------------------*/
/*mostrar expresion*/
nodo imprimirExpression(nodo *lista){
    nodo *nodoAuxiliar;
    nodoAuxiliar = lista;
    printf("\nPOSTFIJA:");
    while(nodoAuxiliar !=NULL){
        printf("%c ", nodoAuxiliar->simbolo);
        nodoAuxiliar=nodoAuxiliar->siguiente;
    }
}
/*--------------------------------------------------------------------------------------------------------------------*/
/*verificar los parentisis*/
int expresionBalanceada(char expresion[]){
    nodo *pilaAuxiliar;
    int longitudExpresion;
    char valor;
    pilaAuxiliar = crearLista(pilaAuxiliar);
    longitudExpresion = strlen(expresion);
    for (int i = 0; i < longitudExpresion; ++i) {
        if(expresion[i]=='('){
            pilaAuxiliar=push(expresion[i], pilaAuxiliar);
        }else if(expresion[i]==')'){
            pilaAuxiliar=pop(&valor, pilaAuxiliar);
        }
    }
    if(pilaAuxiliar == NULL){
        return 1;
    }
    return 0;
}
/*--------------------------------------------------------------------------------------------------------------------*/
/*verifica si es un operador*/
int esOperador(char simbolo){
    if((simbolo == '+') ||(simbolo == '-') || (simbolo == '*') || (simbolo == '/') || (simbolo == '^')){
        return 1;
    }
    return 0;
}
/*--------------------------------------------------------------------------------------------------------------------*/
/*verificar la prioridad de las operaciones*/
int prioridad(char operador){
    if(operador == '^'){
        return 3;
    }else if((operador == '*') || (operador == '/')){
        return 2;
    }else if((operador == '-') || (operador == '+')){
        return 1;
    }else if(operador == '('){
        return 0;
    }

}
/*--------------------------------------------------------------------------------------------------------------------*/
nodo *infijaPostfija(char expresion[]){
    nodo * pila, *postFija;
    int longitudExpresion;
    char valor;

    pila = crearLista(pila);
    postFija = crearLista(postFija);

    longitudExpresion = strlen(expresion);
    for (int i = 0; i < longitudExpresion; ++i) {
        if(((expresion[i]>=48) && (expresion[i]<=57))/*0-9*/
                || ((expresion[i]>= 65) && (expresion[i]<=90))/*A-Z*/
                || ((expresion[i]>= 97) && (expresion[i]<=122)))/*a-z*/{
            postFija = insertNodoFinal(expresion[i],postFija);
        }else{
            if(expresion[i] == '('){
                pila=push(expresion[i], pila);
            }else{
                if(esOperador(expresion[i])){
                    if(pila == NULL){
                        pila = push(expresion[i],pila);
                    }else{
                        while(pila != NULL){
                            if(prioridad(pila->simbolo) >= prioridad(expresion[i])){
                                pila = pop(&valor, pila);
                                postFija = insertNodoFinal(valor, postFija);
                            }else{
                                break;
                            }
                        }
                        pila = push(expresion[i], pila);
                    }
                }
            }
        }
        if(expresion[i] == ')'){
            while ((pila->simbolo != '(') && (pila != NULL)){
                pila = pop(&valor, pila);
                postFija=insertNodoFinal(valor, postFija);
            }
            pila = pop(&valor, pila);
        }
    }
    while(pila != NULL){
        pila = pop(&valor, pila);
        postFija = insertNodoFinal(valor, postFija);
    }
    return postFija;
}
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/