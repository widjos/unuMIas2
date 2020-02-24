#ifndef LINKEDLIST_H
#define LINKEDLIST_H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


class LinkedList
{



public:
    struct partition{
      char part_status;
      char part_type;
      char part_fit;
      int  part_start;
      int  part_size;
      char part_name[16];

    };

    LinkedList();
    void insertFirst(char* name, struct partition data);

private:



    struct nodo{
        struct partition particion;
        char name[16];
        struct nodo* next;

    };


    struct nodo *head = nullptr;
    struct nodo *current = nullptr;


};

#endif // LINKEDLIST_H
