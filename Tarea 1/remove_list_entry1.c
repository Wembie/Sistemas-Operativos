/*
Listas enlazadas- Dos metodos
Integrantes: Juan Esteban Acosta Lopez
             Maria Del Mar Villaquiran Davila
Clase: Sistemas operativos
Profesor: Carlos Alberto Llanos
*/

#include "stdio.h"
#include <stdlib.h>
typedef struct nodo{
    int dato;
    struct nodo *siguiente;
}TNodo; //Tipo de nodos
typedef TNodo *pNodo; //Puntero a un nodo
typedef TNodo *Lista; //Lista de los nodos

int ListaVacia(Lista l) {
   return (l == NULL);
}

void agregarElemento(Lista *l, int elemento){
    pNodo nuevo, anterior;
    nuevo = (pNodo)malloc(sizeof(TNodo));
    nuevo->dato = elemento;
    if(ListaVacia(*l) || (*l)->dato > elemento){
        nuevo->siguiente = *l;
        *l = nuevo;
    }else{
        anterior = *l;
        while(anterior->siguiente && anterior->siguiente->dato <= elemento){
            anterior = anterior->siguiente;
            
        }
        nuevo->siguiente = anterior->siguiente;
        anterior->siguiente = nuevo;
    }
}

void remove_list_entry1(Lista *l, int elemento){
    pNodo anterior, nodo;
    anterior = NULL;
    nodo = *l;
    while(nodo->dato != elemento){
        anterior = nodo;
        nodo = nodo->siguiente;
    }
    if(!anterior){
        *l = nodo->siguiente;
    }
    else{
        anterior->siguiente = nodo->siguiente;
    }
}

void remove_list_entry2(Lista *l, int elemento){
    pNodo indirect;
    indirect = *l;
    while((indirect->dato)!= (elemento)){
        indirect = &(*indirect->siguiente);
    }
    *indirect = *indirect->siguiente;
}

void mostrarElementos(Lista l){
    pNodo nodo = l;
    if(ListaVacia(l)){
        printf("Vacia\n");
    } 
    else{
        while(nodo){
            printf("%d -> ",nodo->dato);
            nodo = nodo->siguiente;
        }
    }
}

int main(){
    Lista lista = NULL;
    printf("Metodo elegante\n");
    agregarElemento(&lista, 20);
    agregarElemento(&lista, 10);
    agregarElemento(&lista, 40);
    agregarElemento(&lista, 30);
    agregarElemento(&lista, 15);
    agregarElemento(&lista, 50);
    mostrarElementos(lista);
    remove_list_entry2(&lista, 40);
    printf("\nEliminando...\n");
    mostrarElementos(lista);
    printf("\nMetodo tipico\n");
    lista = NULL;
    agregarElemento(&lista, 20);
    agregarElemento(&lista, 10);
    agregarElemento(&lista, 40);
    agregarElemento(&lista, 30);
    agregarElemento(&lista, 15);
    agregarElemento(&lista, 50);
    mostrarElementos(lista);
    remove_list_entry1(&lista, 40);
    printf("\nEliminando...\n");
    mostrarElementos(lista);
    return 0;
}