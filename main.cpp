#include "list_func.h"
#include "log_file_func.h"

int main()
{
    DoublyLinkedList list = {};
    list_ctor( &list );

    insert_at_position_in_list( &list, 8 );
    list_dump( &list );

    insert_at_position_in_list( &list, 88 );
    list_dump( &list );

    insert_at_position_in_list( &list, 18 );
    list_dump( &list );

    insert_at_position_in_list( &list, 28 );
    list_dump( &list );

    insert_at_position_in_list( &list, 888 );
    list_dump( &list );

    list_dtor( &list );

}