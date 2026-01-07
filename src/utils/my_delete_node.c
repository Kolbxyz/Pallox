#include "memory_manager.h"
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#include <stdio.h>
void my_delete_node(ptr_track_t **ptrs, char *data_ref)
{
    ptr_track_t *prev = NULL;
    ptr_track_t *next = NULL;

    for (ptr_track_t *temp = *ptrs; temp; temp = next) {
        next = temp->next;
        if (strcmp(temp->id, data_ref)) {
            prev = temp;
            temp = next;
            continue;
        }
        if (prev)
            prev->next = next;
        else
            *ptrs = next;
    }
}
