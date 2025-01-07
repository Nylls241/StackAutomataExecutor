#include "automaton.h"
#include <stdio.h>

void print_automaton(const Automaton* automaton) {
    printf("Number of states: %d\n", automaton->num_states);

    printf("Accepting states: ");
    for (int i = 0; i < automaton->num_states; i++) {
        if (automaton->accepting_states[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");

    printf("Transitions:\n");
    for (int i = 0; i < automaton->num_transitions; i++) {
        Transition t = automaton->transitions[i];
        printf("%d %c %c %d %c\n", 
               t.current_state, 
               t.input_symbol, 
               t.stack_symbol, 
               t.next_state, 
               t.stack_action);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <automaton file>\n", argv[0]);
        return 1;
    }

    // Parse the automaton file
    Automaton automaton = parse_automaton_file(argv[1]);

    // Print the parsed automaton for verification
    print_automaton(&automaton);

    return 0;
}
