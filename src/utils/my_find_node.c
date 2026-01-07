#include "memory_manager.h"
#include <stddef.h>
#include <string.h>

ptr_track_t *my_find_node(ptr_track_t *begin, void *data_ref)
{
    ptr_track_t *temp = begin;

    while (temp != NULL) {
        if (strcmp(temp->id, data_ref) == 0)
            return temp;
        temp = temp->next;
    }
    return NULL;
}
