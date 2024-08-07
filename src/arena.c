#include "crossterm.h"

Region *new_region(size_t capacity) {
    size_t size = sizeof(Region) + sizeof(uintptr_t)*capacity;
    Region *r = malloc(size);
    r->next = NULL;
    r->count = 0;
    r->capacity = capacity;
    return r;
}

void *arena_alloc(Arena *a, size_t bytes) {
    // alignment
    size_t size = (bytes + sizeof(uintptr_t) - 1)/sizeof(uintptr_t);
    size_t capacity = size > REGION_DEFAULT_CAPACITY ? size : REGION_DEFAULT_CAPACITY;
    if (a->end == NULL || a->begin == NULL) {
        a->end = new_region(capacity);
        a->begin = a->end;
    }
    if (a->end->count + size > a->end->capacity && a->end->next == NULL) {
        a->end->next = new_region(capacity);
        a->end = a->end->next;
    }
    void *result = &a->end->data[a->end->count];
    a->end->count += size;
    return result;
}

void arena_free(Arena *a) {
    Region *r = a->begin, *tmp;
    while (r) {
        tmp = r; r = r->next;
        free(tmp);
    }
}

// int main() {
//     Arena a = {0};
//     char *str1, *str2, *str3;
//     str1 = arena_alloc(&a, 13);
//     strcpy(str1, "Hellokireditu");
//     str2 = arena_alloc(&a, 90);
//     strcpy(str2, "Worldint main() {Arena a = {0};char *str1, *str2;str1 = arena_alloc(&a, 13);strcpy");
//     str3 = arena_alloc(&a, 20);
//     strcpy(str3, "##kirediltu");
//     printf("%s, %s, %s\n", str1, str2, str3);
//     printf("%p, %p, %p\n", str1, str2, str3);
//     for (size_t i = 0; i < a.end->count; i++) {
//         printf("&data[%zu]=%p\n", i, &a.end->data[i]);
//     }
//     arena_free(&a);
// }
