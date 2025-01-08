#include "automaton.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Creates the automaton file automatically.
 */
void create_automaton_file() {
    FILE* file = fopen("automaton.txt", "w");
    if (!file) {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "2\n");
    fprintf(file, "1\n");
    fprintf(file, "0 ( # 1 \\\n");
    fprintf(file, "1 ) ( 1 \\\n");
    fprintf(file, "1 # # 1 \\\n");

    fclose(file);
}

/**
 * @brief Prints the automaton for verification.
 * 
 * @param automaton The automaton structure.
 */
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
        fprintf(stderr, "Usage: %s <input string>\n", argv[0]);
        return 1;
    }

    // Create the automaton file
    create_automaton_file();

    // Parse the automaton file
    Automaton automaton = parse_automaton_file("automaton.txt");

    // Print the parsed automaton for verification
    print_automaton(&automaton);

    // Execute the automaton on the input string
    if (execute_automaton(&automaton, argv[1])) {
        printf("Accepted\n");
    } else {
        printf("Rejected\n");
    }

    return 0;
}