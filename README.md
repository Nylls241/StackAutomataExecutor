# StackAutomataExecutor

A C implementation of a stack automaton with execution capabilities for a given input word. This project provides a foundation for understanding and experimenting with stack automata, including file-based automaton definitions and input word processing.

---

## **Features**
- **Stack Implementation**: Provides a simple and efficient stack data structure with basic operations like push, pop, and empty checks.
- **Automaton Execution**: Executes a stack automaton defined in a text file against an input word.
- **File-Based Configuration**: Automata are defined in a structured text file for easy customization.
- **Modular Design**: Organized into separate modules for stack operations, automaton logic, and main execution.

---

## **Directory Structure**

```plaintext
StackAutomataExecutor/
├── README.md         # Project documentation
├── LICENSE           # Licensing information
├── automaton.c       # Automaton execution logic
├── automaton.h       # Automaton function declarations
├── automaton.txt     # Example automaton definition file
├── main.c            # Entry point for the program
├── stack.c           # Stack implementation logic
└── stack.h           # Stack function declarations
```

## Installation  
1. Clone the repository:   
```sh
git clone https://github.com/Nylls241/StackAutomataExecutor.git
cd StackAutomataExecutor
```
2. Build the project using `make`:
```sh
make
```

3. Run the executable:
```sh
./AP automaton.txt input_word
```


