#include "list.h"

void error(const char *err) {
    if(errno != 0) {
        perror(err);
    } else {
        fprintf(stderr, "[ERROR]: %s!\n", err);
    }
    exit(EXIT_FAILURE);
}

/* ============================ Node Creation ============================ */
node_s* node_new(void *val) {
    node_s *n = calloc(1, sizeof(node_s));
    if(!n) return NULL;
    n->value = val;
    n->sentinel = 0;
    n->next = n->prev = n;
    return n;
}

node_s* node_sentinel(void) {
    node_s *n = node_new(NULL);
    if(!n) return NULL;
    n->sentinel = 1;
    return n;
}

/* ============================ Node Operations ============================ */
void node_add_after(node_s *h, node_s *n) {
    if(!h || !n) return;
    
    n->prev = h;
    n->next = h->next;
    h->next->prev = n;
    h->next = n;
}

void node_enqueue(node_s *h, node_s *n) {
    node_add_after(h, n);
}

node_s *node_dequeue(node_s *h) {
    if(!h || h->next == h) return h;
    
    node_s *p = h->prev;
    p->prev->next = h;
    h->prev = p->prev;
    p->next = p->prev = p;
    return p;
}

/* ============================ List Operations (Int specific) ============================ */
void print_list_int(node_s *h) {
    if(!h) return;
    
    node_s *c = h->next;
    while(c != h) {
        printf("[%d]-->", *(int*)c->value);
        c = c->next;
    }
    printf("NULL\n");
}

void list_free_int(node_s *h) {
    if(!h) return;
    
    node_s *it;
    while(!(it = node_dequeue(h))->sentinel) {
        printf("Freeing node with value: %d\n", *(int*)it->value);
        free(it->value);
        free(it);
    }
}

/* ============================ Generical List Operations ============================ */
void print_list_generic(node_s *h, void (*print_func)(void*)) {
    if(!h || !print_func) return;
    
    node_s *c = h->next;
    while(c != h) {
        printf("[");
        print_func(c->value);
        printf("]-->");
        c = c->next;
    }
    printf("NULL\n");
}

void list_free_generic(node_s *h, void (*free_func)(void*)) {
    if(!h) return;
    
    node_s *it;
    while(!(it = node_dequeue(h))->sentinel) {
        if(free_func) {
            free_func(it->value);
        }
        free(it);
    }
}
