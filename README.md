# LR Analyzer – Compilation Project 

## Description

LR (Left-to-right, Rightmost derivation) syntactic analyzer that takes as input:
- A context-free grammar
- An LR parsing table (SLR, LALR, or Canonical LR)
- An input string to parse

And produces:
- A step-by-step trace of the parsing process
- A verdict (accept or error)
- The syntax tree in prefix notation

## Project Structure

```
.
├── main.c              # Main program
├── analyzer.h          # Analyzer interface
├── analyzer.c          # Analyzer implementation
├── stack.h             # LR stack (interface)
├── stack.c             # LR stack (implementation)
├── tree.h              # Syntax tree (interface)
├── tree.c              # Syntax tree (implementation)
├── LRGrammar.h         # Grammar structures (provided by the prof)
├── LRGrammar.c         # Utility functions (provided by the prof)
├── read_file.h         # File reading (provided by the prof)
├── read_file.c         # File reading (provided by the prof)
├── test, test2, ...    # Test files (provided by the prof)
├── Makefile            # Build system
└── README.md           # This documentation
```

## Installation 

  Clone the repository:
   ```sh
   git clone https://github.com/Nylls241/StackAutomataExecutor.git
   cd StackAutomataExecutor
   ```

## Compilation

```bash
make
```

This produces the executable `LRanalyzer`.

## Usage

### Syntax

```bash
./LRanalyzer <grammar_file> <input_string>
```

### Examples

```bash
# Example 1: Grammar S -> aSb | ε
./LRanalyzer test "aaaabbbb"

# Example 2: Short string
./LRanalyzer test "ab"

# Example 3: Empty string (ε production)
./LRanalyzer test ""

# Example 4: Arithmetic expression grammar
./LRanalyzer test3 "a+a*a"

# Example 5: Grammar with parentheses
./LRanalyzer test2 "(())"
```

### Expected Output

For `./LRanalyzer test "aaaabbbb"`:

```
Flow | Stack
__________________________________
aaaabbbb | 0
d2 aaabbbb | 0a2
d2 aabbbb | 0a2a2
d2 abbbb | 0a2a2a2
d2 bbbb | 0a2a2a2a2
r2 bbbb | 0a2a2a2a2S3
d4 bbb | 0a2a2a2a2S3b4
r1 bbb | 0a2a2a2S3
d4 bb | 0a2a2a2S3b4
r1 bb | 0a2a2S3
d4 b | 0a2a2S3b4
r1 b | 0a2S3
d4  | 0a2S3b4
r1  | 0S1
accept
S(a()S(a()S(a()S(a()S()b())b())b())b())
```

## Test File Format

See files `test`, `test2`, `test3`, `test4` for examples.

### Structure

1. **Grammar** (one rule per line):
   ```
   S:a$Sb
   S:
   ```
   - Format: `NonTerminal:production`
   - Non-terminals in productions are prefixed with `$`
   - Empty production: nothing after `:`

2. **Parsing table** (tab-separated):
   - First row: symbols (terminals, `$`, non-terminals)
   - Following rows: state number, then actions
   - Actions:
     - `d<n>`: shift
     - `r<n>`: reduce
     - `a`: accept
     - empty: error


### Memory Checking

```bash
make valgrind
```

Checks for memory leaks using Valgrind.

## Implementation Choices

### LR Stack

**Structure:** Dynamic array with doubling strategy.

**Justification:**
- O(1) access to the top (most frequent operation)
- Amortized O(1) complexity for push
- Better spatial locality than linked lists
- Simple sequential display

### Syntax Tree

**Structure:** N-ary tree with fixed-size children array.

**Justification:**
- During reductions, all children are immediately known
- Direct construction avoids reallocations
- Order preserved for prefix printing
- More efficient than incremental approaches

### Main Algorithm

**Approach:** Classical stack-based automaton with two stacks (states/symbols and trees).

**Steps:**
1. Parse table lookup
2. Shift: push symbol and state, create a leaf
3. Reduce: pop stacks, create a node, apply GOTO transition
4. Accept: print the final syntax tree

## Data Structures

### StackLR (LR Stack)

```c
typedef struct {
    StackElem* data;  // Array of (state, symbol)
    size_t size;
    size_t capacity;
} StackLR;
```

### tree_node (Syntax Tree)

```c
typedef struct tree_node {
    signed char label;
    struct tree_node **children;
    size_t nb_children;
} tree_node;
```

### tree_stack (Tree Stack)

```c
typedef struct {
    tree_node **trees;
    size_t size;
    size_t capacity;
} tree_stack;
```

## Symbol Encoding

- **Terminals:** Positive values (standard ASCII codes)
  - Example: `'a'` = 97
- **Non-terminals:** Negative values (most significant bit set)
  - Example: `S` → `-'S'` = -83
- **End of input:** `$` represented by 0

## Complexity

| Operation | Complexity |
|----------|------------|
| Shift | O(1) |
| Reduce | O(k), where k is the rule length |
| Full parsing | O(n), where n is the input length |

## Limitations

- ASCII files only (no UTF-8)
- Maximum of 94 non-terminals (format limitation)
- No multi-line input (newline not supported)

## Cleanup

```bash
make clean
```

Removes all compiled files and executables.

## Author

Nylls Boutoto 

Project developed as part of the *Algorithms for Compilation* course.
