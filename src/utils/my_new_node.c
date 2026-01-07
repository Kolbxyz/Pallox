#include "memory_manager.h"
#include <stdlib.h>
#include <stdio.h>

ptr_track_t *add_ptr(void *ptr, int type, char *id, ptr_track_t **registry_ptrs)
{
    ptr_track_t *new_track = malloc(sizeof(ptr_track_t));

    if (!new_track)
        return NULL;
    new_track->addr = ptr;
    new_track->type = type;
    new_track->id = id;
    new_track->next = *registry_ptrs;
    *registry_ptrs = new_track;
    return *registry_ptrs;
}
