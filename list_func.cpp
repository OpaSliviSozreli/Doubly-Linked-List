#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "list_func.h"
#include "log_file_func.h"

ListFuncStatus list_ctor( DoublyLinkedList* list )
{
    assert( list );
    
    CALLOC( list->data );
    CALLOC( list->next );
    CALLOC( list->prev );

    list->free = 1;
//-------------------------------------------------------------------------------------------------
    //list->data = ( int* )calloc( LIST_DEFAULT_SIZE, sizeof( int ) );
    //list->next = ( int* )calloc( LIST_DEFAULT_SIZE, sizeof( int ) );
    //list->prev = ( int* )calloc( LIST_DEFAULT_SIZE, sizeof( int ) );
    //assert( list->data );
    //assert( list->next );
    //assert( list->prev );
//-------------------------------------------------------------------------------------------------
    fill_with_poison ( list );  

    list->prev[DUMMY_ELEM_POS] = 0;
    list->next[DUMMY_ELEM_POS] = 0;

    list->next[LIST_DEFAULT_SIZE - 1] = LIST_NEXT_POISON;

    return STAT_OK;
}

ListFuncStatus list_dtor( DoublyLinkedList* list )
{
    LIST_VERIFY( list );

    list->free = 0;

    fill_with_poison ( list );

    free( list->data );
    free( list->next );
    free( list->prev );

    return STAT_OK;
}

ListFuncStatus fill_with_poison ( DoublyLinkedList* list )
{
    if ( !list )
        return STAT_FAIL;
        
    for ( int i = 1; i < LIST_DEFAULT_SIZE - 1; i++ )
    {
        list->data[i] = LIST_POISON;
        list->next[i] = i + 1;
        list->prev[i] = LIST_POISON;
    }

    return STAT_OK;
}

ListFuncStatus insert_at_position_in_list( DoublyLinkedList* list, int new_elem )
{
    LIST_VERIFY( list );

    if  ( list->prev[list->free] != LIST_POISON ) 
    {   
        fprintf( stderr, "LIST IS FULL" );
        return STAT_FAIL;
    }

    list->data[list->free] = new_elem;

    int new_free = list->next[list->free];

    list->next[list->free] = list->next[list->prev[DUMMY_ELEM_POS]];
    list->prev[list->free] = list->prev[DUMMY_ELEM_POS];

    list->next[list->prev[DUMMY_ELEM_POS]] = list->free;
    list->prev[DUMMY_ELEM_POS] = list->free;

    list->free = new_free;

    return STAT_OK;
}

ListFuncStatus delete_at_position( DoublyLinkedList* list, int anchor )
{
    LIST_VERIFY( list );

    if ( list->next[DUMMY_ELEM_POS] == list->prev[DUMMY_ELEM_POS] ) 
    {   
        fprintf( stderr, "LIST IS EMPTY" );
        return STAT_FAIL;
    }

    list_connect_elems( list, anchor ); // TODO: need 2 pos not 1 // нихуя так не получается

    list->next[anchor] = list->free;
    list->prev[anchor] = LIST_POISON;

    list->free = anchor;

    return STAT_OK;
}

ListFuncStatus list_connect_elems( DoublyLinkedList* list, int anchor )
{
    LIST_VERIFY( list );

    list->next[list->prev[anchor]] = list->next[anchor];
    list->prev[list->next[anchor]] = list->prev[anchor];

    return STAT_OK;
}
