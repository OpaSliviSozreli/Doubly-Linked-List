#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "log_file_func.h"
#include "const.h"

FILE* log_file = create_log_file( "list_log.txt" );

FILE* create_log_file( const char* log_file_name ) 
{
    assert( log_file_name );

    FILE *log_file_ptr = fopen ( "list_log.txt", "w" );

    atexit( close_log_file );

    return log_file_ptr;
}

void close_log_file( void ) 
{
    if ( !log_file )
        fprintf( stderr, "log_file is nullptr" );

    fclose ( log_file );
}

ListFuncStatus list_dump( DoublyLinkedList* list )
{
    if ( log_file == nullptr )
        return STAT_FAIL;      

    for ( int i = 0; i < LIST_DEFAULT_SIZE - 1; i++ ) // TODO: in html
    {
        fprintf( log_file, "data content is <%d> %d\n", i, list->data[i] );
        fprintf( log_file, "next content is <%d> %d\n", i, list->next[i] );
        fprintf( log_file, "prev content is <%d> %d\n", i, list->prev[i] );
    }

    fprintf( log_file, "current free is %d\n", list->free );

// ------------------------------graph dump------------------------------------------------------------------

    FILE *graph_dump_file = fopen ( "graph_dump.dot", "w" );

    fprintf( graph_dump_file, "digraph G\n"
                              "{\n\trankdir=LR;\n\t"
                              "node [shape = Mrecord;"
                              "fillcolor = \"#F5CCDA\";];\n" ); //#2A612E

    for ( int i = 0; i < LIST_DEFAULT_SIZE; i++ )
    {
        if ( list->prev[list->next[i]] != LIST_POISON )
            fprintf( graph_dump_file, "\tnode%d [style = filled; label = \"node = %d  | data = %d | next = %d | prev = %d\"];\n",\
                                        i, i, list->data[i], list->next[i], list->prev[i]);
    }

    fprintf( graph_dump_file, "\tnode_free [fillcolor = \"#2A612E\"; label = \"free = %d\"];\n\n",\
                              list->free );

    for ( int i = 0; i < LIST_DEFAULT_SIZE - 1; i++ )
    {
        if ( list->prev[list->next[i]] != LIST_POISON )
            fprintf( graph_dump_file, "\tnode%d -> node%d [weight = 52; color = black;];\n",\
                                    i, i + 1 );
    }

    fprintf( graph_dump_file, "\tnode_free -> node%d [weight = 40; color = \"#2A612E\"; constraint = false;];\n\n}",\
                              list->free );

    fclose( graph_dump_file );

    return STAT_OK; 
}

int list_verify( const DoublyLinkedList* list )
{
    int list_errors = LIST_SUCCESS;

    if ( list == NULL ) 
    {
        list_errors |= INVALID_LIST_POINTER;

        fprintf( log_file, "INVALID_LIST_POINTER\n" );

        return list_errors;
    }

    if ( list->next[0] < 0 ) 
    {
        list_errors |= LIST_HEAD_IS_NEGATIVE;

        fprintf( log_file, "LIST_HEAD_IS_NEGATIVE\n" );
    }

    if ( list->next[0] > LIST_DEFAULT_SIZE - 1 ) 
    {
        list_errors |= LIST_OVERFLOW;

        fprintf( log_file, "LIST_OVERFLOW\n" );
    }

    if ( list->prev[0] < 0 )
    {
        list_errors |= LIST_TAIL_IS_NEGATIVE;

        fprintf( log_file, "LIST_TAIL_IS_NEGATIVE\n" );
    }

    if ( list->prev[0] > LIST_DEFAULT_SIZE - 1 )
    {
        list_errors |= LIST_OVERFLOW;

        fprintf( log_file, "LIST_OVERFLOW\n" );
    }

    if ( list->data[list->free] != LIST_POISON )
    {
        list_errors |= LIST_FREE_IS_NOT_FREE;

        fprintf( log_file, "LIST_FREE_IS_NOT_FREE\n" );
    }

    for ( int i = 0; i < LIST_DEFAULT_SIZE - 1; i++ ) 
    {
        int next_elem  = list->next[i];
        int prev_elem = list->prev[next_elem];

        if ( list->prev[i] == LIST_POISON )
            continue;
            
        if ( i != prev_elem ) 
        {
            list_errors |= DAMAGED_LIST_CONNECTION;

            fprintf( log_file, "DAMAGED_LIST_CONNECTION\n" );

            break;
        }
    }

    return list_errors;
}
//"C:\Users\elena\OneDrive\Документы\GitHub\Graphviz\bin\dot" -Tpng graph_dump.dot -o graph_dump.png