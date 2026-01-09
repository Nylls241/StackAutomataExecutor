/* Author: Nylls Boutoto, 2025 */
/* LR Parser Stack - Abstract Data Type */

#ifndef STACK_LR_H
#define STACK_LR_H

#include <stddef.h>  /* size_t */

/* ========================================
   ABSTRACT TYPES
   ======================================== */

/**
 * Symbol: terminal (>0) or non-terminal (<0)
 * Terminals are normal ASCII characters
 * Non-terminals have their high-order bit set to 1 (negative values)
 */
typedef signed char Symbol;

/**
 * State: automaton state number
 * States are numbered from 0 to nblines-1 in the LR table
 */
typedef int State;

/* ========================================
   DATA STRUCTURES
   ======================================== */

/**
 * Stack element: pair (state, symbol)
 * The LR parser stack alternates between states and symbols
 */
typedef struct {
    State state;      /* Automaton state */
    Symbol symbol;    /* Pushed symbol (terminal or non-terminal) */
} StackElem;

/**
 * LR parser stack
 * Dynamically-sized stack with doubling strategy
 */
typedef struct {
    StackElem* data;  /* Dynamic array of elements */
    size_t size;      /* Number of elements in the stack */
    size_t capacity;  /* Allocated capacity */
} StackLR;

/* ========================================
   CREATION AND DESTRUCTION
   ======================================== */

/**
 * Initializes a new stack with the given capacity
 * @param capacity: initial capacity (use 0 for default)
 * @return initialized stack
 */
StackLR stack_init(size_t capacity);

/**
 * Frees the memory allocated for the stack
 * @param stack: pointer to the stack to destroy
 */
void stack_destroy(StackLR* stack);

/* ========================================
   BASIC OPERATIONS
   ======================================== */

/**
 * Pushes a new element (state, symbol) onto the stack
 * @param p: pointer to the stack
 * @param s: symbol to push
 * @param e: state to push
 */
void stack_push(StackLR* p, Symbol s, State e);

/**
 * Removes the top element from the stack
 * @param p: pointer to the stack
 */
void stack_pop(StackLR* p);

/**
 * Pops N elements from the stack (useful for reductions)
 * @param p: pointer to the stack
 * @param n: number of elements to pop
 */
void stack_pop_n(StackLR* p, size_t n);

/**
 * Clears the stack (resets to empty)
 * @param p: pointer to the stack
 */
void stack_clear(StackLR* p);

/* ========================================
   ACCESS FUNCTIONS
   ======================================== */

/**
 * Returns the top element without removing it
 * @param p: pointer to the stack
 * @return top element
 */
StackElem stack_top(StackLR* p);

/**
 * Returns only the state at the top of the stack
 * @param p: pointer to the stack
 * @return top state
 */
State stack_top_state(StackLR* p);

/**
 * Returns only the symbol at the top of the stack
 * @param p: pointer to the stack
 * @return top symbol
 */
Symbol stack_top_symbol(StackLR* p);

/**
 * Returns the element at index i from the bottom
 * @param p: pointer to the stack
 * @param i: index from bottom (0 = bottom)
 * @return element at index i
 */
StackElem stack_get(StackLR* p, size_t i);

/* ========================================
   QUERY FUNCTIONS
   ======================================== */

/**
 * Checks if the stack is empty
 * @param p: pointer to the stack
 * @return 1 if empty, 0 otherwise
 */
int stack_is_empty(StackLR* p);

/**
 * Returns the current size of the stack
 * @param p: pointer to the stack
 * @return number of elements
 */
size_t stack_size(StackLR* p);

/* ========================================
   DISPLAY FUNCTIONS
   ======================================== */

/**
 * Prints the stack in the required format: 0a2a2S3
 * @param p: pointer to the stack
 */
void stack_print(StackLR* p);

/**
 * Prints the stack in debug format (detailed, one line per element)
 * @param p: pointer to the stack
 */
void stack_print_debug(StackLR* p);

#endif /* STACK_LR_H */