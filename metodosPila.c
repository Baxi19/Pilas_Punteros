#include "pila.h"

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
