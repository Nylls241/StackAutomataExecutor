#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <stdbool.h>

#define MAX_TRANSITIONS 128

// Transition structure
typedef struct {
    int current_state;
    char input_symbol;
    char stack_symbol;
    int next_state;
    char stack_action; // Push or Pop
} Transition;

// Automaton structure
typedef struct {
    int num_states;
    bool accepting_states[MAX_TRANSITIONS];
    Transition transitions[MAX_TRANSITIONS];
    int num_transitions;
} Automaton;

// Function to parse the automaton file
Automaton parse_automaton_file(const char* filename);

#endif // AUTOMATON_H
