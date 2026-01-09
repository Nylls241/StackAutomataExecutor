/* Author: Nylls Boutoto, 2025 */
/* Main program for LR Analyzer */

#include <stdio.h>
#include <stdlib.h>
#include "read_file.h"
#include "analyzer.h"

int main(int argc, char *argv[]) {
    /* Check arguments */
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <grammar_file> <input_string>\n", argv[0]);
        fprintf(stderr, "Example: %s test \"aaaabbbb\"\n", argv[0]);
        return 1;
    }
    
    const char *grammar_file = argv[1];
    const char *input_string = argv[2];
    
    /* Read grammar and table from file */
    file_read fr = read_file(grammar_file);
    grammar G = fr.G;
    table t = fr.t;
    
    /* Run the LR analyzer */
    int result = analyze_LR(G, t, input_string);
    
    /* Cleanup */
    for (size_t i = 0; i < G.size; i++) {
        free(G.rules[i].rhs);
    }
    free(G.rules);
    free(t.trans);
    
    /* Return exit code */
    return result ? 0 : 1;
}