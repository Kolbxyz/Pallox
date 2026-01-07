#ifndef PALLOX_H_
    #define PALLOX_H_
    #include <stdio.h>

// ============== [ POINTER TYPES ] ============== //
enum ptr_type {
    PTR_CHAR,
    PTR_CHAR_ARR,
    PTR_INT_ARR
};

enum error_signals {
    SUCCESS_CODE,
    NEW_PTR_ERROR,
    INVALID_PTR_ID
};

// ============== [ POINTER TO BE TRACKED ] ============== //
typedef struct ptr_track_s {
    void *addr;
    int type;
    char *id;
    struct ptr_track_s *next;
} ptr_track_t;

// ============== [ REGISTRY DATA AND METADATA ] ============== //
typedef struct registry_s {
    ptr_track_t **ptrs;
} registry_t;

// ============== [ REGISTRY UTILITIES ] ============== //
ptr_track_t *add_ptr(void *ptr, int type, char *id, ptr_track_t **ptrs);
void *palloc(size_t size, int type, char *id, registry_t *registry);
int register_ptr(void *ptr, char *id, int type, registry_t *registry);
void pdestroy(registry_t *registry);
void free_ptr(char *id, registry_t *registry);


// ============== [ LINKED LISTS UTILITIES ] ============== //
void free_ptr(char *id, registry_t *registry);
void my_delete_node(ptr_track_t **ptrs, char *data_ref);
ptr_track_t *my_find_node(ptr_track_t *begin, void *data_ref);

#endif
