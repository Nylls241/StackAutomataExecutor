# StackAutomataExecutor

A C implementation of a stack automaton with execution capabilities for a given input word. This project provides a foundation for understanding and experimenting with stack automata, including file-based automaton definitions and input word processing.

---

## **Features**
- **Stack Implementation**: Provides a simple and efficient stack data structure with basic operations like push, pop, and empty checks.
- **Automaton Execution**: Executes a stack automaton defined in a text file against an input word.
- **Unit Testing**: Includes a suite of unit tests to validate stack operations and automaton functionality.
- **Modular Design**: Organized into separate modules for stack operations, automaton logic, and testing.

---

## **Directory Structure**

```plaintext
Nylls241-StackAutomataExecutor/
├── README.md         # Project documentation
├── LICENSE           # Licensing information
├── Makefile          # Build configuration (In progress)
├── automaton.c       # Automaton execution logic
├── automaton.h       # Automaton function declarations
├── stack.c           # Stack implementation logic
├── stack.h           # Stack function declarations
└── unit_test.c       # Unit tests for the stack and automaton modules
```

---

## **Installation and Usage**

1. Clone the repository:
   ```sh
   git clone https://github.com/Nylls241/StackAutomataExecutor.git
   cd Nylls241-StackAutomataExecutor
   ```

2. Build the unit tests:
   ```sh
   gcc -o unit_test stack.c unit_test.c -Wall -Wextra
   ```

3. Run the unit tests:
   ```sh
   ./unit_test
   ```


