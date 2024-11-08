#ifndef _LIST_FUNC_H
#define _LIST_FUNC_H

#include <stdlib.h>

const int LIST_DEFAULT_SIZE = 8;
const int LIST_POISON = -1; 
const int LIST_NEXT_POISON = -666;  

const int DUMMY_ELEM_POS = 0;

enum ListFuncStatus 
{
    STAT_FAIL,
    STAT_OK
};

struct DoublyLinkedList 
{
    int free;

    int* data;
    int* next;
    int* prev;
};

#define CALLOC( array_name ) array_name = ( int* )calloc( LIST_DEFAULT_SIZE, sizeof( int ) );\
                            if ( !array_name )\
                                return STAT_FAIL;

ListFuncStatus list_ctor( DoublyLinkedList* list );
ListFuncStatus list_dtor( DoublyLinkedList* list );
ListFuncStatus fill_with_poison ( DoublyLinkedList* list );
ListFuncStatus insert_at_position_in_list( DoublyLinkedList* list, int new_elem );
ListFuncStatus delete_at_position( DoublyLinkedList* list, int anchor );
ListFuncStatus list_connect_elems( DoublyLinkedList* list, int anchor );

#endif