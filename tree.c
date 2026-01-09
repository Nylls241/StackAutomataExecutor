/* Author: Nylls Boutoto, 2025 */
/* Implementation of the Parse Tree */

#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

/* ========================================
   CREATION AND DESTRUCTION
   ======================================== */

/**
 * Creates a leaf node (terminal)
 * @param terminal: terminal symbol (positive value)
 * @return pointer to the new leaf, or NULL on error
 */
tree_node* tree_create_leaf(Symbol terminal) {
    tree_node *node = (tree_node*)malloc(sizeof(tree_node));
    if (!node) {
        fprintf(stderr, "Error: memory allocation failed for leaf node\n");
        return NULL;
    }
    
    node->label = terminal;
    node->children = NULL;
    node->nb_children = 0;
    
    return node;
}

/**
 * Creates an internal node (non-terminal) with its children
 * @param nonterminal: non-terminal symbol (negative value)
 * @param children: array of pointers to child nodes
 * @param nb_children: number of children
 * @return pointer to the new node, or NULL on error
 */
tree_node* tree_create_node(Symbol nonterminal, 
                            tree_node **children, 
                            size_t nb_children) {
    tree_node *node = (tree_node*)malloc(sizeof(tree_node));
    if (!node) {
        fprintf(stderr, "Error: memory allocation failed for internal node\n");
        return NULL;
    }
    
    node->label = nonterminal;
    node->children = children;
    node->nb_children = nb_children;
    
    return node;
}

/**
 * Recursively frees the memory of a tree
 * @param node: root of the tree to destroy
 */
void tree_destroy(tree_node *node) {
    if (!node) {
        return;
    }
    
    /* Recursively free all children */
    for (size_t i = 0; i < node->nb_children; i++) {
        tree_destroy(node->children[i]);
    }
    
    /* Free the children array */
    if (node->children) {
        free(node->children);
    }
    
    /* Free the node itself */
    free(node);
}

/* ========================================
   DISPLAY FUNCTIONS
   ======================================== */

/**
 * Prints the tree in prefix format: Label(child1()child2()...)
 * Example: S(a()S(a()S()b())b())
 * @param node: root of the tree to print
 */
void tree_print(tree_node *node) {
    if (!node) {
        return;
    }
    
    /* Print the label */
    if (node->label > 0) {
        /* Terminal: print as is */
        printf("%c", node->label);
    } else {
        /* Non-terminal: remove high-order bit (print positive) */
        printf("%c", -node->label);
    }
    
    /* Print children in parentheses */
    printf("(");
    for (size_t i = 0; i < node->nb_children; i++) {
        tree_print(node->children[i]);
    }
    printf(")");
}

/**
 * Prints the tree in indented format (for debugging)
 * @param node: root of the tree to print
 * @param depth: current depth (use 0 for initial call)
 */
void tree_print_debug(tree_node *node, int depth) {
    if (!node) {
        return;
    }
    
    /* Indentation based on depth */
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    
    /* Print the label with type information */
    if (node->label > 0) {
        printf("'%c' (terminal)\n", node->label);
    } else {
        printf("'%c' (non-terminal, code: %d)\n", -node->label, (int)node->label);
    }
    
    /* Recursively print all children */
    for (size_t i = 0; i < node->nb_children; i++) {
        tree_print_debug(node->children[i], depth + 1);
    }
}

/* ========================================
   UTILITY FUNCTIONS
   ======================================== */

/**
 * Returns the height of the tree
 * @param node: root of the tree
 * @return height (0 for a leaf)
 */
size_t tree_height(tree_node *node) {
    if (!node || node->nb_children == 0) {
        return 0;
    }
    
    size_t max_height = 0;
    for (size_t i = 0; i < node->nb_children; i++) {
        size_t child_height = tree_height(node->children[i]);
        if (child_height > max_height) {
            max_height = child_height;
        }
    }
    
    return max_height + 1;
}

/**
 * Returns the number of nodes in the tree
 * @param node: root of the tree
 * @return total number of nodes
 */
size_t tree_size(tree_node *node) {
    if (!node) {
        return 0;
    }
    
    size_t size = 1;  /* The current node */
    for (size_t i = 0; i < node->nb_children; i++) {
        size += tree_size(node->children[i]);
    }
    
    return size;
}