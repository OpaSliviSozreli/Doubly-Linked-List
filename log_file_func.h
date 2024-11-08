#ifndef _LOG_FILE_FUNC_H
#define _LOG_FILE_FUNC_H

#include <stdio.h>

#include "list_func.h"

enum ListErrors 
{ 
    LIST_SUCCESS            =     0     ,
    LIST_TAIL_IS_NEGATIVE   = ( 1 << 1 ),
    INVALID_LIST_POINTER    = ( 1 << 2 ),
    LIST_OVERFLOW           = ( 1 << 3 ),
    LIST_FREE_IS_NOT_FREE   = ( 1 << 4 ),
    INVALID_LIST_ELEM_NEXT  = ( 1 << 5 ),
    DAMAGED_LIST_CONNECTION = ( 1 << 6 ),
    LIST_IS_EMPTY           = ( 1 << 7 ),
    LIST_HEAD_IS_NEGATIVE   = ( 1 << 8 ),
};

#define LIST_VERIFY( list ) if ( list_verify( list ) != LIST_SUCCESS )\
                            {                                         \
                                list_dump( list );                    \
                                return STAT_FAIL;                     \
                            }

int list_verify( const DoublyLinkedList* list );
ListFuncStatus list_dump( DoublyLinkedList* list );
void close_log_file( void );
FILE* create_log_file( const char* log_file_name );

#endif