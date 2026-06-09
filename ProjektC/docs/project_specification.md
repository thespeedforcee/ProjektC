# Project Specification: Interactive Snake

## 1. General Description
The project is an interactive "Snake" game written in C. It utilizes the Allegro 5 library to handle the graphical user interface (GUI) and respond to keyboard events.

## 2. Architecture
The project strictly follows a modular architecture and is divided into independent components:
* `main.c` - Program entry point, event handling, and the main game loop.
* `snake_logic.c` - Encapsulated application core; handles movement logic, collision detection, and dynamic singly linked list management.
* `gui.c` - Graphical user interface module; responsible for drawing the game state, menus, and text using Allegro 5 primitives.
* `file_operations.c` - Data persistence module; handles saving/loading high scores, logging events, and writing game history to text files.

## 3. Technical Requirements
* **Memory Management:** The snake grows dynamically during the game. Each new segment is added to a singly linked list using the `malloc` function. Memory is safely freed using `free` to prevent memory leaks.
* **File Operations:** The game saves event logs (`log.txt`), game history (`historia.txt`), and the high score (`highscore.txt`), ensuring persistent application state storage safely managed by the I/O module.
* **Error Handling:** The program features strict pointer protection (verifying `!= NULL`) for both file streams and dynamic memory allocation.
