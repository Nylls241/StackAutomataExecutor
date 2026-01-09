/* Author: Nylls Boutoto, 2025 */
/* Implementation of the LR parser stack */

#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 16

/* ========================================
   CREATION AND DESTRUCTION
   ======================================== */

/**
 * Initializes a new stack with the given capacity
 * @param capacity: initial capacity (use 0 for default)
 * @return initialized stack
 */
StackLR stack_init(size_t capacity) {
    StackLR stack;
    
    if (capacity == 0) {
        capacity = INITIAL_CAPACITY;
    }
    
    stack.data = (StackElem*)malloc(capacity * sizeof(StackElem));
    if (!stack.data) {
        fprintf(stderr, "Error: memory allocation failed for stack\n");
        exit(1);
    }
    
    stack.size = 0;
    stack.capacity = capacity;
    
    return stack;
}

/**
 * Frees the memory allocated for the stack
 * @param stack: pointer to the stack to destroy
 */
void stack_destroy(StackLR* stack) {
    if (stack && stack->data) {
        free(stack->data);
        stack->data = NULL;
        stack->size = 0;
        stack->capacity = 0;
    }
}

/* ========================================
   BASIC OPERATIONS
   ======================================== */

/**
 * Pushes a new element (state, symbol) onto the stack
 * Automatically doubles capacity if needed
 * @param p: pointer to the stack
 * @param s: symbol to push
 * @param e: state to push
 */
void stack_push(StackLR* p, Symbol s, State e) {
    if (!p) {
        fprintf(stderr, "Error: null stack pointer in stack_push\n");
        return;
    }
    
    /* Check if we need to resize */
    if (p->size >= p->capacity) {
        p->capacity *= 2;
        p->data = (StackElem*)realloc(p->data, p->capacity * sizeof(StackElem));
        if (!p->data) {
            fprintf(stderr, "Error: memory reallocation failed in stack_push\n");
            exit(1);
        }
    }
    
    /* Push the new element */
    p->data[p->size].state = e;
    p->data[p->size].symbol = s;
    p->size++;
}

/**
 * Removes the top element from the stack
 * Does nothing if the stack is empty
 * @param p: pointer to the stack
 */
void stack_pop(StackLR* p) {
    if (!p) {
        fprintf(stderr, "Error: null stack pointer in stack_pop\n");
        return;
    }
    
    if (p->size > 0) {
        p->size--;
    }
}

/**
 * Pops N elements from the stack
 * Useful for reductions (pop |rhs| elements)
 * @param p: pointer to the stack
 * @param n: number of elements to pop
 */
void stack_pop_n(StackLR* p, size_t n) {
    if (!p) {
        fprintf(stderr, "Error: null stack pointer in stack_pop_n\n");
        return;
    }
    
    if (n > p->size) {
        fprintf(stderr, "Warning: trying to pop %zu elements from stack of size %zu\n", 
                n, p->size);
        p->size = 0;
    } else {
        p->size -= n;
    }
}

/* ========================================
   ACCESS FUNCTIONS
   ======================================== */

/**
 * Returns the top element without removing it
 * @param p: pointer to the stack
 * @return top element (undefined if stack is empty)
 */
StackElem stack_top(StackLR* p) {
    if (!p || p->size == 0) {
        fprintf(stderr, "Error: accessing top of empty stack\n");
        StackElem empty = {0, 0};
        return empty;
    }
    return p->data[p->size - 1];
}

/**
 * Returns only the state at the top of the stack
 * @param p: pointer to the stack
 * @return top state
 */
State stack_top_state(StackLR* p) {
    if (!p || p->size == 0) {
        fprintf(stderr, "Error: accessing top state of empty stack\n");
        return 0;
    }
    return p->data[p->size - 1].state;
}

/**
 * Returns only the symbol at the top of the stack
 * @param p: pointer to the stack
 * @return top symbol
 */
Symbol stack_top_symbol(StackLR* p) {
    if (!p || p->size == 0) {
        fprintf(stderr, "Error: accessing top symbol of empty stack\n");
        return 0;
    }
    return p->data[p->size - 1].symbol;
}

/**
 * Returns the element at index i from the bottom (0 = bottom)
 * @param p: pointer to the stack
 * @param i: index from bottom
 * @return element at index i
 */
StackElem stack_get(StackLR* p, size_t i) {
    if (!p || i >= p->size) {
        fprintf(stderr, "Error: invalid index %zu in stack of size %zu\n", i, p->size);
        StackElem empty = {0, 0};
        return empty;
    }
    return p->data[i];
}

/* ========================================
   QUERY FUNCTIONS
   ======================================== */

/**
 * Checks if the stack is empty
 * @param p: pointer to the stack
 * @return 1 if empty, 0 otherwise
 */
int stack_is_empty(StackLR* p) {
    return (p == NULL || p->size == 0);
}

/**
 * Returns the current size of the stack
 * @param p: pointer to the stack
 * @return number of elements in the stack
 */
size_t stack_size(StackLR* p) {
    if (!p) return 0;
    return p->size;
}

/* ========================================
   DISPLAY FUNCTIONS
   ======================================== */

/**
 * Prints the stack in the required format for the project
 * Format: 0s2s3S4 (alternating states and symbols)
 * Example: 0a2a2S3
 * @param p: pointer to the stack
 */
void stack_print(StackLR* p) {
    if (!p) {
        printf("(null stack)");
        return;
    }
    
    if (p->size == 0) {
        printf("0");  /* Initial state shown even if empty */
        return;
    }
    
    /* Print first state (always state 0 at bottom) */
    printf("%d", p->data[0].state);
    
    /* Print alternating symbols and states */
    for (size_t i = 1; i < p->size; i++) {
        Symbol sym = p->data[i].symbol;
        State state = p->data[i].state;
        
        /* Print symbol */
        if (sym > 0) {
            /* Terminal: print as is */
            printf("%c", sym);
        } else {
            /* Non-terminal: remove high-order bit */
            printf("%c", -sym);
        }
        
        /* Print state */
        printf("%d", state);
    }
}

/**
 * Prints the stack in debug format (one element per line)
 * @param p: pointer to the stack
 */
void stack_print_debug(StackLR* p) {
    if (!p) {
        printf("(null stack)\n");
        return;
    }
    
    printf("Stack (size=%zu, capacity=%zu):\n", p->size, p->capacity);
    
    if (p->size == 0) {
        printf("  (empty)\n");
        return;
    }
    
    for (size_t i = 0; i < p->size; i++) {
        Symbol sym = p->data[i].symbol;
        State state = p->data[i].state;
        
        printf("  [%zu] state=%d, symbol=", i, state);
        
        if (sym == 0) {
            printf("(none)");
        } else if (sym > 0) {
            printf("'%c' (terminal)", sym);
        } else {
            printf("'%c' (non-terminal, code=%d)", -sym, (int)sym);
        }
        
        if (i == p->size - 1) {
            printf(" <- TOP");
        }
        printf("\n");
    }
}

/**
 * Clears the stack (resets to empty without freeing memory)
 * @param p: pointer to the stack
 */
void stack_clear(StackLR* p) {
    if (p) {
        p->size = 0;
    }
}