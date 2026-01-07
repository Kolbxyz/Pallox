/*
** ===========================================
** __________        .__  .__
** \______   \_____  |  | |  |   _______  ___
**  |     ___/\__  \ |  | |  |  /  _ \  \/  /
**  |    |     / __ \|  |_|  |_(  <_> >    <
**  |____|    (____  /____/____/\____/__/\_ \.
**                 \/                      \/
**
**         MODULE: pallox - Managed Arena
** ===========================================
** - Description: Pallox is a Region-based memory manager
** - You can create a region called a "registry"
**
**   @method register a new ptr to that region with register_ptr()
**   @method free a single ptr w free_ptr()
**   @method free all pointers from the registry with pdestroy()
**   @method alloc a new ppointer with palloc()
**
** - Pallox handles null pointers to avoid errors in all functions
** - Potential banned functions:
**  • calloc()
**  • fprintf()
*/

#include <stdio.h>
#include <stdlib.h>
#include "memory_manager.h"

// ============== [ PRIVATE HELPERS ] ============== //
static void free_2d_arr(void **arr)
{
    if (!arr) {
        return;
    }
    for (int i = 0; arr[i]; ++i) {
        if (arr[i]) {
            free(arr[i]);
        }
    }
    free(arr);
}

static void init_registry(registry_t *registry, size_t size)
{
    *(registry->ptrs) = NULL;
}

// ============== [ REGISTRY METHODS ] ============== //
/*
** Free a registered pointer
** @param id to identify the pointer to free
** @param registry where the pointer should be freed from
*/
void free_ptr(char *id, registry_t *registry)
{
    ptr_track_t *ptr = my_find_node(*registry->ptrs, id);

    if (ptr != NULL) {
        fprintf(stderr, "Freeing: %s\n", ptr->id);
        if (ptr->addr)
            my_delete_node(registry->ptrs, id);
        if (ptr->type == PTR_CHAR)
            free(ptr->addr);
        if (ptr->type == PTR_CHAR_ARR)
            free_2d_arr(ptr->addr);
        free(ptr);
    } else
        fprintf(stderr, "Trying to free invalid ptr.\n");
}

/*
** Free all pointers from the registry
** @param registry from which to free all pointers
*/
void pdestroy(registry_t *registry)
{
    ptr_track_t *curr = *registry->ptrs;
    ptr_track_t *next = NULL;

    while (curr) {
        next = curr->next;
        free_ptr(curr->id, registry);
        curr = next;
    }
}

/*
** Register a new pointer
** @param ptr the pointer to register
** @param id the identifier for that pointer
** @param type the type of pointer
** @param registry where the pointer should be freed from
*/
int register_ptr(void *ptr, char *id, int type, registry_t *registry)
{
    if (registry) {
        if (my_find_node(*registry->ptrs, id) || !id) {
            fprintf(stderr, "%s", "Attempt to create using an invalid id.\n");
            return INVALID_PTR_ID;
        }
        if (!add_ptr(ptr, type, id, registry->ptrs) && ptr) {
            fprintf(stderr, "%s", "Error when registering new ptr.\n");
            return NEW_PTR_ERROR;
        }
    }
    return SUCCESS_CODE;
}

/*
** Alloc a new pointer with the given data
** @param size the size of the data in bytes
** @param type the type of the pointer
** @param id the id of the new pointer
** @param registry where the pointer should be freed from
*/
void *palloc(size_t size, int type, char *id, registry_t *registry)
{
    void *ptr = calloc(1, size);

    if (ptr && register_ptr(ptr, id, type, registry) == SUCCESS_CODE) {
        return ptr;
    }
    return NULL;
}

int main(void)
{
    registry_t registry = {.ptrs = malloc(sizeof(ptr_track_t *))};

    char *ptr = palloc(sizeof(char *) * 5, PTR_CHAR_ARR, "test", &registry);
    char *ptr2 = palloc(sizeof(char *) * 5, PTR_CHAR_ARR, "test2", &registry);
    for (ptr_track_t *ptr = *registry.ptrs; ptr != NULL; ptr = ptr->next)
        fprintf(stderr, "PTR %p\n", ptr->addr);
    free_ptr("test2", &registry);
    free_ptr("test", &registry);
    for (ptr_track_t *ptr = *registry.ptrs; ptr != NULL; ptr = ptr->next)
        fprintf(stderr, "FREE %s\n", ptr->id);
    pdestroy(&registry);
    return 0;
}
