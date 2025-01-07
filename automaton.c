#include "automaton.h"
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
    }

    fclose(file);
    return automaton;
}

