#include "linkedlist.h"

LinkedList::LinkedList()
{

}




void LinkedList::insertFirst(char* name, struct partition data)
{
    //create a link
    struct nodo *link = (struct nodo*) malloc(sizeof(struct nodo));

    strcpy(link->name,name);
    link->particion = data;

    //point it to old first node
    link->next = head;

    //point first to new first node
    head = link;
 }


