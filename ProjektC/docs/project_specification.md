# Project Specification: Interactive Snake

## 1. General Description
The project is an interactive "Snake" game written in C, meeting the academic requirements for a 5.0 grade. It utilizes the Allegro 5 library to handle the graphical user interface (GUI) and respond to keyboard events.

## 2. Architecture
The project is divided into logical modules:
* `main.c` - The main game loop, event handling, and graphics rendering.
* `snake_logic.c` - The encapsulated application core; contains movement logic, collision detection, and singly linked list management.

## 3. Technical Requirements
* **Memory Management:** The snake grows dynamically during the game. Each new segment is added to a singly linked list using the `malloc` function, and upon game over, the memory is freed using the `free` function to prevent memory leaks.
* **File Operations:** The game saves event logs (`log.txt`), game history (`historia.txt`), and the high score (`highscore.txt`), ensuring persistent application state storage.
* **Error Handling:** The program verifies the successful opening of files (pointer protection by checking `!= NULL`).
