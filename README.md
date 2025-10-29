# CSS Engine - Project Overview

This project is a simple C++ CSS Engine that handles selectors, attributes, and basic CSS-like structure. The program consists of three key files:

- `Classes.h`: Contains class definitions used for selectors and attributes.
- `Functions.h`: Contains function declarations that define the logic for processing the CSS-like structure.
- `main.cpp`: The main entry point where the CSS Engine is executed.

## Files Overview

### `Classes.h`

This header file contains the class definitions used for handling selectors and attributes. It includes structures to represent the main components of the CSS engine:

- **Selectors** - A class to define selectors that target HTML elements.
- **Attributes** - A class for storing attributes such as colors, font sizes, etc., associated with selectors.

### `Functions.h`

This header file defines various functions that implement the logic behind CSS-like processing. It includes:

- Functions for adding, removing, and counting selectors and attributes.
- Functions for parsing commands and interacting with the sections of the CSS engine.

### `main.cpp`

The main file where the program logic is implemented. It processes the input and switches between states to manage selectors, attributes, and commands. It also runs the interactive part of the engine that allows the user to:

- Add selectors and attributes.
- Execute commands to count or delete selectors and attributes.
- Transition between states (e.g., selector state, attribute state, and command state).
