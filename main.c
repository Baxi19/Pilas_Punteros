/*--------------------------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
/*--------------------------------------------------------------------------------------------------------------------*/
/*Randald Villegas Brenes*/
/*Practica de pila y punteros para la casa de lenguaje C*/
/*06/05/2020*/
/*--------------------------------------------------------------------------------------------------------------------*/
#define MAXCHAR 10000
/*--------------------------------------------------------------------------------------------------------------------*/
/*structs y definiciones*/
struct structNodo{
    char simbolo;
    struct structNodo *siguiente;
};
struct structNodoFloat{
    float valor;
    struct structNodoFloat *siguiente;
};

typedef struct structNodo nodo;
typedef struct structNodoFloat nodoFloat;
/*--------------------------------------------------------------------------------------------------------------------*/
/*Declaracion de los Metodos*/
void leerArchivo();

nodo *crearLista(nodo *lista);
nodo *push(char simbolo, nodo*pila);
nodo *insertNodoFinal(char simbolo, nodo *lista);
nodo *pop(char *valor, nodo *pila);
nodo imprimirExpression(nodo *lista);
char* obtenerExpression(nodo *lista);

int expresionBalanceada(char expresion[]);
int esOperador(char simbolo);/*1 si es operador, 0 si no*/
int prioridad(char operador);
nodo *infijaPostfija(char expresion[]);

nodoFloat *crearPilaFloat(nodoFloat *pila);
nodoFloat *pushFloat(float valor, nodoFloat *pila);
nodoFloat *popFloat(float *valor, nodoFloat *pila);

float sumar(float operando1, float operando2);
float restar(float operando1, float operando2);
float multiplicar(float operando1, float operando2);
float dividir(float operando1, float operando2);
float potencia(float operando1, float operando2);
float calcular(float operando1, float operando2,float (*calcula)(float a,float b));

float operacion(float operando1, float operando2, char operador);
float evaluarPostfija(char expresion[]);

/*--------------------------------------------------------------------------------------------------------------------*/
/*Applicacion*/
/*--------------------------------------------------------------------------------------------------------------------*/
int main(){

    /*----------------------------------------------------------------------------------------------------------------*/
    /*Menu para el usuario final*/
    int  opcion;
    do
    {   printf("\n\n*********************************************************************************");
        printf( "\n   1. Convertir Expresion de Infija a Postfija");
        printf( "\n   2. Salir." );
        printf( "\n\n   Introduzca opci%cn (1-2): ", 162 );
        scanf( "%d", &opcion );

        switch ( opcion ){
            case 1:
                leerArchivo();
                break;
        }
    } while ( opcion != 2 );
    printf("Gracias por utilizar el programa!");
    return 0;
}
/*--------------------------------------------------------------------------------------------------------------------*/
/*METODOS*/
/*--------------------------------------------------------------------------------------------------------------------*/
void leerArchivo(){
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
        return ;
    }
    /*----------------------------------------------------------------------------------------------------------------*/
    FILE *fp;
    char str[MAXCHAR];
    char* filename = path;
    /*----------------------------------------------------------------------------------------------------*/
    /*modo de lectura*/
    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("\n\nNo se pudo abrir el archivo %s",filename);
        return ;
    }
    /*----------------------------------------------------------------------------------------------------*/
    /*ciclo para leer cada renglon del archivo*/
    while (fgets(str, MAXCHAR, fp) != NULL){
        printf("\nEXPRESION: %s",str);
        if(expresionBalanceada(str)){
            postFija = infijaPostfija(str);
            printf("\nPOSTFIJA:");
            imprimirExpression(postFija);
            printf("\nResultado: %f", evaluarPostfija(obtenerExpression(postFija)));
        }else{
            printf("Expresion no valida!");
        }
    }
    fclose(fp);
}
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
/*copiar expresion*/
char* obtenerExpression(nodo *lista){
    char* expresion = (char *) malloc(1);
    char str[MAXCHAR] ;
    int index = 0;

    nodo *nodoAuxiliar;
    nodoAuxiliar = lista;
    while(nodoAuxiliar != NULL){
        str[index] = nodoAuxiliar->simbolo;
        nodoAuxiliar=nodoAuxiliar->siguiente;
        index++;
    }
    strcpy(expresion, str);
    return expresion;
}
/*--------------------------------------------------------------------------------------------------------------------*/
/*mostrar expresion*/
nodo imprimirExpression(nodo *lista){
    nodo *nodoAuxiliar;
    nodoAuxiliar = lista;
    while(nodoAuxiliar != NULL){
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
/*Logica del algoritmo*/
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
/*nueva pila tipo float*/
nodoFloat *crearPilaFloat(nodoFloat *pila){
    return pila =NULL;
}
/*--------------------------------------------------------------------------------------------------------------------*/
/*Empujar dato a la pila*/
nodoFloat *pushFloat(float valor, nodoFloat *pila){
    nodoFloat *nodoNuevo;
    nodoNuevo = (nodoFloat*) malloc (sizeof(nodoFloat));
    if(nodoNuevo != NULL){
        nodoNuevo->valor = valor;
        nodoNuevo->siguiente= pila;
        pila= nodoNuevo;
    }
    return  pila;
}
/*--------------------------------------------------------------------------------------------------------------------*/
/*sacar dato de pila*/
nodoFloat *popFloat(float *valor, nodoFloat *pila){
    nodoFloat *nodoAuxiliar;
    float dato;
    if(pila == NULL){
        printf("\nPILA VACIA");
    }else{
        nodoAuxiliar = pila;
        dato = nodoAuxiliar->valor;
        pila = nodoAuxiliar->siguiente;
        *valor = dato;
        free(nodoAuxiliar);
    }
    return pila;
}
/*--------------------------------------------------------------------------------------------------------------------*/
/*suma*/
float sumar(float operando1, float operando2){
    return operando1+operando2;
}
/*--------------------------------------------------------------------------------------------------------------------*/
/*resta*/
float restar(float operando1, float operando2){
    return operando1-operando2;
}
/*--------------------------------------------------------------------------------------------------------------------*/
/*multiplicar*/
float multiplicar(float operando1, float operando2){
    return operando1*operando2;
}
/*--------------------------------------------------------------------------------------------------------------------*/
/*dividir*/
float dividir(float operando1, float operando2){
    return operando1/operando2;
}
/*--------------------------------------------------------------------------------------------------------------------*/
/*potencia*/
float potencia(float operando1, float operando2){
    return pow(operando1 , operando2);
}
/*--------------------------------------------------------------------------------------------------------------------*/
/*calcular*/
float calcular(float operando1, float operando2,float (*calcula)(float a,float b)){
    return calcula(operando1,operando2);
}
/*--------------------------------------------------------------------------------------------------------------------*/
/*calcula el tipo de operacion*/
float operacion(float operando1, float operando2, char operador){
    switch(operador) {
        case '+' :
            return calcular(operando1,operando2,sumar);

        case '-' :
            return calcular(operando1,operando2,restar);

        case '*' :
            return calcular(operando1,operando2,multiplicar);

        case '/' :
            return calcular(operando1,operando2,dividir);

        case '^' :
            return calcular(operando1,operando2,potencia);

    }
}
/*--------------------------------------------------------------------------------------------------------------------*/
/*calcular el resultado*/
float evaluarPostfija(char expresion[]){
    nodoFloat *pila;
    int longitudExpresion;
    char valor;
    float operando1, operando2, resultado;

    pila = crearPilaFloat(pila);

    longitudExpresion = strlen(expresion);
    for (int i = 0; i < longitudExpresion; ++i) {
        if((expresion[i] >= 48) && (expresion[i] <= 57)){
            valor = expresion[i];
            pila=pushFloat(atof(&valor), pila);
        }else {
            if(esOperador(expresion[i])){
                pila = popFloat(&operando2, pila);
                pila = popFloat(&operando1, pila);
                resultado = operacion(operando1, operando2, expresion[i]);
                pila = pushFloat(resultado, pila);
            }
        }
    }
    return pila->valor;
}
/*--------------------------------------------------------------------------------------------------------------------*/