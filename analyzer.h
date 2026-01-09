/* Author: Nylls Boutoto, 2025 */
/* LR Analyzer - Main Algorithm */

#ifndef ANALYZER_H
#define ANALYZER_H

#include "LRGrammar.h"
#include "stack.h"
#include "tree.h"

/* ========================================
   TREE STACK
   ======================================== */

/**
 * Stack for storing partial parse trees during analysis
 */
typedef struct {
    tree_node **trees;  /* Array of tree pointers */
    size_t size;        /* Number of trees in stack */
    size_t capacity;    /* Allocated capacity */
} tree_stack;

/* Tree stack operations */
tree_stack* tree_stack_init(size_t capacity);
void tree_stack_destroy(tree_stack *ts);
void tree_stack_push(tree_stack *ts, tree_node *tree);
tree_node* tree_stack_pop(tree_stack *ts);
tree_node* tree_stack_top(tree_stack *ts);
int tree_stack_is_empty(tree_stack *ts);
size_t tree_stack_size(tree_stack *ts);

/* ========================================
   MAIN ANALYZER
   ======================================== */

/**
 * Analyzes an input string using the LR parser
 * 
 * @param G: grammar
 * @param t: LR parse table
 * @param input: input string to analyze
 * @return 1 if accepted, 0 if rejected
 */
int analyze_LR(grammar G, table t, const char *input);

/* ========================================
   DISPLAY HELPERS
   ======================================== */

/**
 * Prints the remaining input (flow)
 * @param input: full input string
 * @param position: current position
 */
void print_flow(const char *input, size_t position);

#endif /* ANALYZER_H */