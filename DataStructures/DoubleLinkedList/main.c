#include "../include/list.h"

/* ============================ Test Functions ============================ */
void print_int(void *value) {
    printf("%d", *(int*)value);
}

void free_int(void *value) {
    printf("Freeing int: %d\n", *(int*)value);
    free(value);
}

int main(void) {
    printf("=== Testing Integer Linked List ===\n\n");
    
    // Create sentinel node
    node_s *h = node_sentinel();
    if(!h) error("Failed to create sentinel");
    
    printf("1. Initial empty list:\n");
    print_list_int(h);
    printf("\n");
    
    // Add elements 10, 20, 30, 40, 50
    printf("2. Adding elements 10, 20, 30, 40, 50:\n");
    for(int i = 1; i <= 5; i++) {
        int *val = malloc(sizeof(int));
        if(!val) {
            list_free_int(h);
            error("Malloc failed");
        } 
        *val = i * 10;
        node_enqueue(h, node_new(val));
        print_list_int(h);
    }
    printf("\n");
    
    // Remove first 3 elements
    printf("3. Removing first 3 elements:\n");
    for(int i = 0; i < 3; i++) {
        node_s *dequeued = node_dequeue(h);
        if(!dequeued->sentinel) {
            printf("Removed: %d\n", *(int*)dequeued->value);
            free(dequeued->value);
            free(dequeued);
            print_list_int(h);
        } else {
            printf("Empty List!\n");
            break;
        }
    }
    printf("\n");
    
    // Add more elements
    printf("4. Adding elements 100 and 200:\n");
    int *val100 = malloc(sizeof(int));
    int *val200 = malloc(sizeof(int));
    if(!val100 || !val200) {
        list_free_int(h);
        error("Malloc failed");   
    }
    *val100 = 100;
    *val200 = 200;
    
    node_enqueue(h, node_new(val100));
    node_enqueue(h, node_new(val200));
    print_list_int(h);
    printf("\n");
    
    // Remove all elements
    printf("5. Removing all remaining elements:\n");
    node_s *dequeued;
    while(!(dequeued = node_dequeue(h))->sentinel) {
        printf("Removed: %d\n", *(int*)dequeued->value);
        free(dequeued->value);
        free(dequeued);
        print_list_int(h);
    }
    printf("\n");
    
    // Add one final element
    printf("6. Adding final element 999:\n");
    int *val999 = malloc(sizeof(int));
    if(!val999) {
        list_free_int(h);
        error("Malloc failed");
    }
    *val999 = 999;
    node_enqueue(h, node_new(val999));
    print_list_int(h);
    printf("\n");
    
    // Test generic functions
    printf("7. Testing generic print function:\n");
    print_list_generic(h, print_int);
    printf("\n");
    
    // Clean up
    printf("8. Cleaning up using generic free function:\n");
    list_free_generic(h, free_int);
    free(h);
    
    printf("\n=== All tests completed successfully ===\n");
    return 0;
}
