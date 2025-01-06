#include "stack.h"
#include <stdio.h>

/**
 * @file main.c
 * @brief Test program for stack functions.
 * 
 * This program tests the stack implementation by performing various operations such as pushing, 
 * popping, and checking the stack's state. It also verifies edge cases like popping from an empty stack.
 */

/**
 * @brief Entry point for the stack testing program.
 * 
 * This function tests the following stack functionalities:
 * - Initializing the stack.
 * - Checking if the stack is empty.
 * - Pushing values onto the stack.
 * - Popping values from the stack.
 * - Handling edge cases like popping from an empty stack.
 * 
 * @return Returns 0 if the program executes successfully.
 */
int main() {
    // Initialize the stack
    printf("Initializing the stack...\n");
    initStack();

    // Test if the stack is empty
    if (isEmpty()) {
        printf("The stack is currently empty.\n");
    } else {
        printf("The stack is not empty.\n");
    }

    // Push some values onto the stack
    printf("Pushing values 'C', 20, and 'aaa' onto the stack...\n");
    push(10);
    push('20');
    push('aaa');

    // Check if the stack is empty
    if (isEmpty()) {
        printf("The stack is still empty after pushing values.\n");
    } else {
        printf("The stack is no longer empty after pushing values.\n");
    }

    // Pop values from the stack
    printf("Popping values from the stack...\n");
    int value = pop();
    printf("Popped value: %c\n", value);
    value = pop();
    printf("Popped value: %c\n", value);
    value = pop();
    printf("Popped value: %c\n", value);

    // Attempt to pop from an empty stack
    printf("Attempting to pop from an empty stack...\n");
    value = pop();
    if (value == -1) {
        printf("Error handled: Cannot pop from an empty stack.\n");
    }

    // Push more values and test stack behavior
    printf("Pushing more values onto the stack...\n");
    for (int i = 1; i <= 5; i++) {
        printf("Pushing %d onto the stack...\n", i * 10);
        push(i * 10);
    }

    // Pop all values to test stack behavior
    printf("Popping all values from the stack...\n");
    while (!isEmpty()) {
        value = pop();
        printf("Popped value: %d\n", value);
    }

    // Final empty check
    if (isEmpty()) {
        printf("The stack is empty after all operations.\n");
    } else {
        printf("The stack is not empty after all operations.\n");
    }

    return 0;
}
