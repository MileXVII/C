#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

typedef struct node {
    struct node *next;
    struct node *prev;
    void *value;
    int sentinel;
} node_s;

void error(const char *err);

node_s* node_sentinel(void);
node_s* node_new(void *val);
void node_add_after(node_s *h, node_s *n);
void node_enqueue(node_s *h, node_s *n);
node_s *node_dequeue(node_s *h);

void print_list_int(node_s *h);
void list_free_int(node_s *h);

void print_list_generic(node_s *h, void (*print_func)(void*));
void list_free_generic(node_s *h, void (*free_func)(void*));

#endif /* LIST_H */
