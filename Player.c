#include <stdio.h>
#include <stdlib.h>

// Définition d'un structure pour une ``ChainedList`` dynamique
typedef struct ChainedList ChainedList;

struct ChainedList
{
    int id;
    int value;
    ChainedList* previous;
    ChainedList* next;
};

// Création d'un pointeur
ChainedList* create(int id, int value)
{
    ChainedList* history=malloc(sizeof(history));
    history->id=id;
    history->value=value;
    history->previous=NULL;
    history->next=NULL;
    return history;
}

// Méthode qui ajoute une partie à l'historique
ChainedList* append(ChainedList* head, ChainedList* value)
{
    // head est la tête de liste, si head est vide alors history est inséré en tête de liste
    if (head==NULL){head=value; return head;}
    // head n'est pas vide donc history est inséré à la fin de la liste
    ChainedList* p;
    for (p=head;p->next!=NULL;p=p->next){}
        p->next=value;
        return head;
}


// Méthode qui supprime une partie de l'historique
ChainedList* removeHistory(ChainedList* head, ChainedList* value)
{
    // p est le pointeur qui va parcourir la liste
    ChainedList* p;
    // t est le pointeur qui va garder en mémoire l'emplacement de la dernière valeur
    ChainedList* t;
    while( (p = p->next) != NULL)
    {
         if(p->value == value)
         {
              t->next = p->next;
              free(p);
              break;
         } 
         t = p;
    }
}

int main()
{
    printf("Hello World");

    return 0;
}
