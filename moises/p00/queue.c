// typedef struct queue_t
// {
//    struct queue_t *prev ;  // aponta para o elemento anterior na fila
//    struct queue_t *next ;  // aponta para o elemento seguinte na fila
// } queue_t ;

#include "queue.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
//------------------------------------------------------------------------------
// Insere um elemento no final da fila.
void queue_append(queue_t **queue, queue_t *elem)
{
    // - a fila deve existir
    assert(queue != NULL);

    // - o elemento deve existir
    assert(elem != NULL);

    // - o elemento nao deve estar em outra fila
    if(elem->next != NULL || elem->prev != NULL){
        return;
    }
    // assert(elem->next == NULL);
    // assert(elem->prev == NULL);

    // - checando se o elemento já está na fila
    if(*queue) {

        bool elementInQueue = false;
        queue_t *aux = *queue;

        // - testando com um elemento
        if (elem == aux) {
            elementInQueue = true;
        }
        // colocar um else aqui
        do {
            aux = aux->next;
            if (aux == elem) {
                elementInQueue = true;
                break;
            }
        } while (aux->next != *queue);

        //assert(elementInQueue);
        if (elementInQueue) {
            return;
        }
    }





    // - se a fila estiver vazia
    if (*queue == NULL)
    {
        *queue = elem;
        elem->next = elem;
        elem->prev = elem;
    }
    else
    {
        // primeiro.prev = elem
        (*queue)->prev = elem;

        // elem.next = primeiro
        elem->next = (*queue);

        queue_t *aux = *queue;
        while (aux->next != *queue)
        {
            aux = aux->next;
        }

        // ultimo.next = elem
        aux->next = elem;

        // elem.prev = ultimo
        elem->prev = aux;
    }
}
//------------------------------------------------------------------------------
// Remove o elemento indicado da fila, sem o destruir.

// Retorno: apontador para o elemento removido, ou NULL se erro

queue_t *queue_remove(queue_t **queue, queue_t *elem)
{

    // - a fila deve existir
    assert(queue != NULL);

    // - a fila nao deve estar vazia
    assert(*queue != NULL);

    // - o elemento deve existir
    assert(elem != NULL);

    // - o elemento deve pertencer a fila indicada
    bool elementInQueue = false;
    queue_t *aux = *queue;

    // - testando com um elemento
    if(elem == aux){
        elementInQueue = true;
    }

    do {
        aux = aux->next;
        if(aux == elem){
            elementInQueue = true;
            break;
        }
    }while(aux->next != *queue);

    //assert(elementInQueue);
    if(!elementInQueue){
        return NULL;
    }
    //como retornar nulo se o elemento n tiver na fila?


    // - se só tiver um na fila
    if(elem->next == elem) {
        *queue = NULL;
        elem->next = NULL;
        elem->prev = NULL;
    }
    else{
        if(elem == *queue) {
            *queue = elem->next;
        }
        elem->prev->next = elem->next;
        elem->next->prev = elem->prev;
        elem->next = NULL;
        elem->prev = NULL;
    }

    return elem;
  
}

int queue_size(queue_t *queue) {

    int size = 0;

    // - se estiver vazia:
    if (queue == NULL){
        return size;
    }

    size++;

    queue_t *aux = queue;

    while(aux->next != queue) {
        size++;
        aux = aux->next;
    }

    return size;
}


// Percorre a fila e imprime na tela seu conteúdo. A impressão de cada
// elemento é feita por uma função externa, definida pelo programa que
// usa a biblioteca. Essa função deve ter o seguinte protótipo:
//
// void print_elem (void *ptr) ; // ptr aponta para o elemento a imprimir
void queue_print(char *name, queue_t *queue, void print_elem(void *)) {
    if (queue == NULL){
        return;
    }
    queue_t *aux = queue;
    do {
        print_elem(aux);
        aux = aux->next;
    }while(aux != queue);
    return;
}
