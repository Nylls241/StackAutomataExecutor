/* Author: Nylls Boutoto, 2025 */
/* Parse Tree - Abstract Data Type */

#ifndef TREE_H
#define TREE_H

#include <stddef.h>  /* size_t */

/* ========================================
   ABSTRACT TYPES
   ======================================== */

/**
 * Symbol: terminal (>0) or non-terminal (<0)
 * Same encoding as in the stack
 */
typedef signed char Symbol;

/* ========================================
   DATA STRUCTURES
   ======================================== */

/**
 * Parse tree node
 * - Leaves represent terminals (nb_children = 0)
 * - Internal nodes represent non-terminals (nb_children > 0)
 */
typedef struct tree_node {
    Symbol label;                /* Node label (terminal or non-terminal) */
    struct tree_node **children; /* Array of pointers to children */
    size_t nb_children;          /* Number of children */
} tree_node;

/* ========================================
   CREATION AND DESTRUCTION
   ======================================== */

/**
 * Creates a leaf node (terminal)
 * @param terminal: terminal symbol (positive value)
 * @return pointer to the new leaf, or NULL on error
 */
tree_node* tree_create_leaf(Symbol terminal);

/**
 * Creates an internal node (non-terminal) with its children
 * @param nonterminal: non-terminal symbol (negative value)
 * @param children: array of pointers to child nodes
 * @param nb_children: number of children
 * @return pointer to the new node, or NULL on error
 * 
 * Note: This function takes ownership of the children array
 */
tree_node* tree_create_node(Symbol nonterminal, 
                            tree_node **children, 
                            size_t nb_children);

/**
 * Recursively frees the memory of a tree
 * @param node: root of the tree to destroy
 */
void tree_destroy(tree_node *node);

/* ========================================
   DISPLAY FUNCTIONS
   ======================================== */

/**
 * Prints the tree in prefix format: Label(child1()child2()...)
 * Example: S(a()S(a()S()b())b())
 * 
 * @param node: root of the tree to print
 * 
 * Display conventions:
 * - Terminals are printed as is
 * - Non-terminals are printed without the high-order bit (positive)
 * - Empty parentheses () represent leaves
 */
void tree_print(tree_node *node);

/**
 * Prints the tree in indented format (for debugging)
 * @param node: root of the tree to print
 * @param depth: current depth (use 0 for initial call)
 */
void tree_print_debug(tree_node *node, int depth);

/* ========================================
   UTILITY FUNCTIONS (optional)
   ======================================== */

/**
 * Returns the height of the tree
 * @param node: root of the tree
 * @return height (0 for a leaf)
 */
size_t tree_height(tree_node *node);

/**
 * Returns the number of nodes in the tree
 * @param node: root of the tree
 * @return total number of nodes
 */
size_t tree_size(tree_node *node);

#endif /* TREE_H */