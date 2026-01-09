/* Author: Nylls Boutoto, 2025 */
/* Implementation of the LR Analyzer */

#include "analyzer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_TREE_STACK_CAPACITY 32

/* ========================================
   TREE STACK IMPLEMENTATION
   ======================================== */

tree_stack* tree_stack_init(size_t capacity) {
    tree_stack *ts = (tree_stack*)malloc(sizeof(tree_stack));
    if (!ts) {
        fprintf(stderr, "Error: memory allocation failed for tree stack\n");
        exit(1);
    }
    
    if (capacity == 0) {
        capacity = INITIAL_TREE_STACK_CAPACITY;
    }
    
    ts->trees = (tree_node**)malloc(capacity * sizeof(tree_node*));
    if (!ts->trees) {
        fprintf(stderr, "Error: memory allocation failed for tree stack data\n");
        exit(1);
    }
    
    ts->size = 0;
    ts->capacity = capacity;
    
    return ts;
}

void tree_stack_destroy(tree_stack *ts) {
    if (!ts) return;
    
    /* Free all remaining trees */
    for (size_t i = 0; i < ts->size; i++) {
        tree_destroy(ts->trees[i]);
    }
    
    free(ts->trees);
    free(ts);
}

void tree_stack_push(tree_stack *ts, tree_node *tree) {
    if (!ts) {
        fprintf(stderr, "Error: null tree stack in push\n");
        return;
    }
    
    /* Resize if needed */
    if (ts->size >= ts->capacity) {
        ts->capacity *= 2;
        ts->trees = (tree_node**)realloc(ts->trees, 
                                         ts->capacity * sizeof(tree_node*));
        if (!ts->trees) {
            fprintf(stderr, "Error: reallocation failed in tree stack push\n");
            exit(1);
        }
    }
    
    ts->trees[ts->size] = tree;
    ts->size++;
}

tree_node* tree_stack_pop(tree_stack *ts) {
    if (!ts || ts->size == 0) {
        fprintf(stderr, "Error: popping from empty tree stack\n");
        return NULL;
    }
    
    ts->size--;
    return ts->trees[ts->size];
}

tree_node* tree_stack_top(tree_stack *ts) {
    if (!ts || ts->size == 0) {
        fprintf(stderr, "Error: accessing top of empty tree stack\n");
        return NULL;
    }
    
    return ts->trees[ts->size - 1];
}

int tree_stack_is_empty(tree_stack *ts) {
    return (ts == NULL || ts->size == 0);
}

size_t tree_stack_size(tree_stack *ts) {
    return ts ? ts->size : 0;
}

/* ========================================
   DISPLAY HELPERS
   ======================================== */

void print_flow(const char *input, size_t position) {
    if (position >= strlen(input)) {
        /* End of input, print nothing */
        return;
    }
    
    /* Print remaining characters */
    printf("%s", &input[position]);
}

/* ========================================
   MAIN ANALYZER
   ======================================== */

int analyze_LR(grammar G, table t, const char *input) {
    /* Initialize stacks */
    StackLR stack = stack_init(0);
    tree_stack *tstack = tree_stack_init(0);
    
    /* Push initial state */
    stack_push(&stack, 0, 0);
    
    size_t position = 0;
    size_t input_len = strlen(input);
    
    /* Print header */
    printf("Flot | Pile\n");
    printf("__________________________________\n");
    
    /* Main loop */
    while (1) {
        /* FIRST: Print current state (flow | stack) */
        print_flow(input, position);
        printf(" | ");
        stack_print(&stack);
        printf("\n");
        
        /* Get current state */
        State current_state = stack_top_state(&stack);
        
        /* Get current input symbol */
        Symbol current_symbol;
        if (position < input_len) {
            current_symbol = input[position];
        } else {
            current_symbol = 0;  /* End of input ($) */
        }
        
        /* Look up action in table : We can see it in the subject of the project */
        signed char action = t.trans[256 * current_state + (unsigned char)current_symbol];
        
        /* Execute action */
        if (action > 0) {
            /* SHIFT */
            printf("d%d ", action);
            
            /* Push symbol and state onto stack */
            stack_push(&stack, current_symbol, action);
            
            /* Create leaf and push onto tree stack */
            tree_node *leaf = tree_create_leaf(current_symbol);
            tree_stack_push(tstack, leaf);
            
            /* Advance input */
            position++;
            
        } else if (action < 0 && action != -127) {
            /* REDUCE */
            int rule_num = -action;
            rule r = G.rules[rule_num - 1];  /* Rules are 1-indexed in table */
            
            printf("r%d ", rule_num);
            
            /* Calculate RHS length */
            size_t rhs_len = strlen((char*)r.rhs);
            
            tree_node **children = NULL;
            
            if (rhs_len > 0) {
                /* Pop rhs_len trees from tree stack */
                children = (tree_node**)malloc(rhs_len * sizeof(tree_node*));
                if (!children) {
                    fprintf(stderr, "Error: memory allocation failed for children\n");
                    exit(1);
                }
                
                /* Pop in reverse order to maintain left-to-right */
                for (int i = rhs_len - 1; i >= 0; i--) {
                    children[i] = tree_stack_pop(tstack);
                }
                
                /* Pop rhs_len elements from stack */
                stack_pop_n(&stack, rhs_len);
            }
            /* else: empty production, don't pop anything */
            
            /* Create new node */
            tree_node *new_node = tree_create_node(-r.lhs, children, rhs_len);
            tree_stack_push(tstack, new_node);
            
            /* GOTO: get previous state and look up next state */
            State prev_state = stack_top_state(&stack);
            
            /* Non-terminals are stored with high bit set (negative values) */
            /* In the table, they occupy indices 128-255 */
            unsigned char nt_index = (unsigned char)(-r.lhs);
            State next_state = t.trans[256 * prev_state + nt_index];
            
            /* Push non-terminal and new state */
            stack_push(&stack, -r.lhs, next_state);
            
        } else if (action == -127) {
            /* ACCEPT */
            printf("accept\n");
            
            /* Get final tree */
            tree_node *final_tree = tree_stack_top(tstack);
            
            /* Print tree */
            tree_print(final_tree);
            printf("\n");
            
            /* Cleanup */
            stack_destroy(&stack);
            tree_stack_destroy(tstack);
            
            return 1;  /* Success */
            
        } else {
            /* ERROR */
            printf("Syntax error at position %zu\n", position);
            
            /* Cleanup */
            stack_destroy(&stack);
            tree_stack_destroy(tstack);
            
            return 0;  /* Failure */
        }
    }
    
    return 0;  /* Should never reach here */
}