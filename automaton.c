#include "automaton.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Parse the automaton definition from a file.
 * 
 * @param filename The file containing the automaton definition.
 * @return The parsed Automaton structure.
 */
Automaton parse_automaton_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    Automaton automaton = {0}; // Initialize the automaton structure

    // Read the number of states
    fscanf(file, "%d\n", &automaton.num_states);

    // Read the accepting states
    char line[256];
    fgets(line, sizeof(line), file);
    char* token = strtok(line, " ");
    while (token) {
        automaton.accepting_states[atoi(token)] = true;
        token = strtok(NULL, " ");
    }

    // Read transitions
    automaton.num_transitions = 0;
    while (fgets(line, sizeof(line), file)) {
        Transition* t = &automaton.transitions[automaton.num_transitions++];
        sscanf(line, "%d %c %c %d %c", 
               &t->current_state, 
               &t->input_symbol, 
               &t->stack_symbol, 
               &t->next_state, 
               &t->stack_action);
        if (t->stack_action == '\\') {
            t->stack_action = 'P'; // Replace '\' with 'P' for pop
        }
    }

    // Set the initial state
    automaton.initial_state = 0;

    fclose(file);
    return automaton;
}

/**
 * @brief Recursively executes the automaton on the input string.
 * 
 * @param automaton The automaton structure.
 * @param current_state The current state of the automaton.
 * @param input The input string.
 * @param input_index The current index in the input string.
 * @return `true` if the input is accepted, `false` otherwise.
 */
static bool execute_recursive(const Automaton* automaton, int current_state, const char* input, int input_index) {
    if (input[input_index] == '\0') {
        return automaton->accepting_states[current_state] && isEmpty();
    }

    for (int i = 0; i < automaton->num_transitions; i++) {
        Transition t = automaton->transitions[i];
        if (t.current_state == current_state && t.input_symbol == input[input_index] && t.stack_symbol == read_top()) {
            if (t.stack_action == 'P') {
                pop();
            } else if (t.stack_action == 'p') {
                push(t.stack_symbol);
            }
            if (execute_recursive(automaton, t.next_state, input, input_index + 1)) {
                return true;
            }
            if (t.stack_action == 'p') {
                pop();
            } else if (t.stack_action == 'P') {
                push(t.stack_symbol);
            }
        }
    }
    return false;
}

/**
 * @brief Executes the automaton on a given input string.
 * 
 * @param automaton The automaton structure.
 * @param input The input string.
 * @return `true` if the input is accepted, `false` otherwise.
 */
bool execute_automaton(const Automaton* automaton, const char* input) {
    initStack();
    return execute_recursive(automaton, automaton->initial_state, input, 0);
}