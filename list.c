#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node 
{
    void* data;
    Node* next;
    Node* prev;
};

struct List 
{
    Node* head;
    Node* tail;
    Node* current;
};

typedef List List;

Node* createNode(void* data) 
{
    Node* new = (Node*)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List* createList() 
{
    List* list = (List*) calloc (1, sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;
    return list;
}

void* firstList(List* list) 
{
    if (list->head != NULL)
    {
        list->current = list->head;
        return list->head->data;
    }
    return NULL;
}

void* nextList(List* list) 
{
    if (!list->current) return NULL;
    if (list->current->next != NULL)
    {
        list->current = list->current->next;
        return list->current->data;
    }
    return NULL;
}

void* lastList(List* list) 
{
    if (list->tail != NULL)
    {
        list->current = list->tail;
        return list->tail->data;
    }
    return NULL;
}

void* prevList(List* list) 
{
    if(list->current!=NULL && list->current->prev != NULL)
    {
        list->current = list->current->prev;
        return list->current->data;
    }
    return NULL;
}

void pushFront(List* list, void* data) 
{
    Node* tmp = createNode(data);
    if (tmp != NULL)
    {
        tmp->next = list->head;
        if(list->head)
        {
            list->head->prev = tmp;
        }
        list->head = tmp;
        tmp->prev = NULL;
    }
}

void pushBack(List* list, void* data) 
{
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) 
{
    Node* tmp = createNode(data);
    tmp->next = list->current->next;
    tmp->prev = list->current;
    list->head = tmp;
    tmp->data = data;
}

void * popFront(List * list) 
{
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) 
{
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) 
{
    void* dato = list->current->data;
    if (list->current->prev == NULL)
    {
        list->head = list->current->next;
        list->current->next->prev = NULL;
    }
    else if (list->current->next == NULL)
    {
        list->tail = list->current->prev;
        list->current->prev->next = NULL;
    }
    else if(list->current->prev != NULL && list->current->next != NULL)
    {
      list->current->prev->next = list->current->next;
      list->current->next->prev = list->current->prev;
    }
    free(list->current);
    return dato;
}

void cleanList(List * list) 
{
    while (list->head != NULL) 
    {
        popFront(list);
    }
}