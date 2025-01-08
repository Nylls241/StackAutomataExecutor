#include <stdio.h>
#include <assert.h>
#include "stack.h"
#include "automaton.h"

void test_stack() {
    printf("Testing stack functionality...\n");

    // Initialize stack
    initStack();
    assert(isEmpty() == false); // Stack is initialized with `#`, so it's not empty.
    assert(read_top() == '#');

    // Push elements onto the stack
    push('a');
    push('b');
    push('c');
    assert(isEmpty() == false);
    assert(read_top() == 'c'); // Top should be 'c'

    // Pop elements from the stack
    assert(pop() == 'c');
    assert(read_top() == 'b');
    assert(pop() == 'b');
    assert(read_top() == 'a');

    // Pop to bottom
    assert(pop() == 'a');
    assert(read_top() == '#');

    // Attempt to pop beyond the bottom
    //assert(pop() == -1); // Error: Stack is empty
    printf("Stack tests passed.\n\n");
}

void test_automaton() {
    printf("Testing automaton functionality...\n");

    // Define a sample automaton
    Automaton automaton;
    automaton.num_states = 3;
    automaton.initial_state = 0;
    automaton.accepting_states[1] = true;
    automaton.accepting_states[2] = false;
    automaton.num_transitions = 3;

    // Define transitions
    automaton.transitions[0] = (Transition){0, 'a', '#', 1, 'P'}; // Push 'a'
    automaton.transitions[1] = (Transition){1, 'b', 'a', 2, 'P'}; // Push 'b'
    automaton.transitions[2] = (Transition){2, 'c', 'b', 1, 'p'}; // Pop 'b'

    // Test automaton properties
    assert(automaton.num_states == 3);
    assert(automaton.initial_state == 0);
    assert(automaton.accepting_states[1] == true);
    assert(automaton.accepting_states[2] == false);

    // Test transitions
    Transition t = automaton.transitions[0];
    assert(t.current_state == 0);
    assert(t.input_symbol == 'a');
    assert(t.stack_symbol == '#');
    assert(t.next_state == 1);
    assert(t.stack_action == 'P');

    printf("Automaton tests passed.\n\n");
}

int main() {
    printf("Running tests...\n\n");

    // Run individual tests
    test_stack();
    test_automaton();

    printf("All tests passed successfully!\n");
    return 0;
}
