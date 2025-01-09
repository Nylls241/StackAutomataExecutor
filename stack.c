// stack.c: For stack management
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

static int stack[MAX_SIZE]; /**< Static array to store stack elements. */
static int top = -1;        /**< Index of the top of the stack (initially empty). */

/**
 * @brief Initializes the stack to an empty state.
 * 
 * Resets the `top` variable to indicate that the bottom of the stack is represented by the `#` character. 
 */
void initStack() {
    top = 0;              /**< Reset the top index to the first position. */
    stack[top] = '#';     /**< Set the bottom of the stack to the character `#`. */
}

/**
 * @brief Checks if the stack is empty.
 * 
 * @return `true` if the stack is empty, `false` otherwise.
 */
bool isEmpty() {
    return top == -1;
}

/**
 * @brief Checks if the stack is full.
 * 
 * @return `true` if the stack has reached its maximum capacity, `false` otherwise.
 */
bool isFull() {
    return top == MAX_SIZE - 1;
}

/**
 * @brief Pushes a value onto the stack.
 * 
 * Adds a new char value to the top of the stack.
 * 
 * @param value The char value to push onto the stack.
 * @note If the stack is full, an error message is displayed and the operation is aborted.
 */
void push(char value) {
    if (isFull()) {
        printf("Error: Stack is full.\n");
        return;
    }
    stack[++top] = value; /**< Increment `top` and store the value at the new top index. */
}

/**
 * @brief Pops the top value off the stack.
 * 
 * Removes and returns the value at the top of the stack.
 * 
 * @return The char value removed from the stack. If the stack is empty, an error message is displayed and `-1` is returned.
 * @note The bottom of the stack (character `#`) cannot be removed.
 */
int pop() {
    if (isEmpty()) {
        printf("Error: Stack is empty.\n");
        return -1; /**< Error: Attempting to pop from an empty stack. */
    }
    return stack[top--]; /**< Return the top value and decrement `top`. */
}

/**
 * @brief Reads the value at the top of the stack without removing it.
 * 
 * @return The char value at the top of the stack. If the stack is empty, an error message is displayed and `-1` is returned.
 */
int peek() {
    if (isEmpty()) {
        printf("Error: Stack is empty.\n");
        return -1; /**< Error: Attempting to read from an empty stack. */
    }
    return stack[top]; /**< Return the value at the current top index without modifying it. */
}
