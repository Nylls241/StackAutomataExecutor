// stack.h: For declaring stack-related functions and structures
#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

#define MAX_SIZE 128 /**< Maximum size of the stack */

/**
 * @brief Initializes the stack to an empty state.
 * 
 * This function prepares the stack for use by resetting its internal state.
 */
void initStack();

/**
 * @brief Checks if the stack is empty.
 * 
 * @return `true` if the stack is empty, `false` otherwise.
 */
bool isEmpty();

/**
 * @brief Checks if the stack is full.
 * 
 * @return `true` if the stack has reached its maximum capacity, `false` otherwise.
 */
bool isFull();

/**
 * @brief Pushes a value onto the stack.
 * 
 * @param value The char value to be pushed onto the stack.
 * @note Ensure the stack is not full by using `isFull()` before calling this function.
 */
void push(char value);

/**
 * @brief Pops the top value off the stack.
 * 
 * @return The integer value that was removed from the stack.
 * @note Ensure the stack is not empty by using `isEmpty()` before calling this function.
 */
int pop();

/**
 * @brief Reads the top value of the stack without removing it.
 * 
 * @return The integer value currently at the top of the stack.
 * @note Ensure the stack is not empty by using `isEmpty()` before calling this function.
 */
int peek();

#endif // STACK_H
