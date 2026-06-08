# 🐍 Semester Project – C Programming: Interactive Snake Game

## 🧩 Project Topic
**Category:** 🎮 Games  
**Project Title:** Interactive Snake in C

## 📌 General Information

| Field | Details |
| :--- | :--- |
| **Course** | Low-Level Programming in C |
| **Instructor** | Dr hab. inż. A. Rybarczyk |
| **Academic Year** | 2025/2026 |
| **Format** | Pair project |

## 📖 Project Description
An interactive, low-level programming project implemented entirely in C, featuring modular architecture, dynamic memory management, robust error handling, and a graphical user interface (GUI) powered by the **Allegro 5** library. 

This project explicitly complies with the academic requirements for a grade of 5.0. The core mechanic (the snake) is built using a singly linked list with dynamic memory allocation (`malloc`/`free`). The project includes structured coding practices, effective use of pointers, custom data structures, and binary/text file-based operations for game state and score tracking.

## 🏗️ Functional Requirements
* Provide user interaction via a graphical user interface (Allegro 5 keyboard events).
* Validate input data (preventing the snake from reversing into itself).
* Handle errors robustly (safe memory allocation, checking file stream pointers).
* Detect collisions with grid boundaries and the snake's own tail.
* Support saving and loading data from files (High Scores and Game State).

## 💾 File Operations
* Saving application/game state to allow players to pause and resume later.
* Logging errors and configuration settings.
* Reading and updating player statistics (High Score system).

## 🧠 Project Architecture
The code is strictly modular and organized into independent components to ensure maintainability:

* `main.c` – Program entry point, game loop, and event handling.
* `snake_logic.c` – Core logic, collision detection, and linked list manipulation.
* `file_operations.c` – Saving/loading states and logging mechanisms.
* `gui.c` – Rendering logic using the Allegro 5 primitives addon.

**Required elements implemented:**
* Structures (`struct`) for game state and segments.
* Pointers for linked list traversal.
* Dynamic memory allocation for continuous snake growth.
* Well-structured, readable functions without code duplication.

## 🚩 Milestones

### Milestone 1: Initial Project Setup & Modular Structure (Due: April 07, 2026)
* Define detailed project specification and functional requirements (#1).
* Set up repository structure and initial modular framework in C (#2).
* Configure compilation settings and package manager (#3).
* Design and implement initial data structures including structs and pointers (#4).

### Milestone 2: Core Game Logic & File Handling (Due: May 05, 2026)
* Implement the main game logic, movement, and collision enforcement (#5).
* Integrate dynamic memory management (linked lists) for game state handling (#6).
* Develop file operations for game states, logs, and player statistics (#7).
* Perform rigorous debugging, memory-leak checking, and preliminary testing (#8).

### Milestone 3: GUI Development & Enhanced User Interaction (Due: June 11, 2026)
* Implement graphical user interface using the Allegro 5 library (#9).
* Introduce cursor/keyboard interaction and grid-based graphical constraints (#10).
* Ensure comprehensive error handling for input validation and memory safety (#11).
* Conduct integration, functional, and usability testing of GUI and core mechanics (#12).

### Final Submission (Due: June 15, 2026)
* Refactor and finalize codebase for readability, maintainability, and efficiency (#13).
* Finalize documentation, inline commenting, and README updates (#14).
* Project submission via the university platform (#15).

## 📁 Repository Structure

```text
your_project/
├── assets/
│   └── images/
├── docs/
│   ├── project_specification.md
│   └── user_manual.md
├── include/
│   ├── snake_logic.h
│   ├── gui.h
│   └── file_operations.h
├── src/
│   ├── snake_logic.c
│   ├── gui.c
│   ├── file_operations.c
│   └── main.c
├── logs/
├── saves/
├── tests/
│   ├── test_logic.c
│   └── test_gui.c
├── .gitignore
└── README.md
```
## ⚙️ Technical and Academic Compliance (Grade 5.0 Checklist)
* Logical modularity: Separated logic, GUI, and file I/O for ease of maintenance.
* Advanced dynamic structures: Use of pointers and a singly linked list to manage memory explicitly and efficiently as the snake grows.
* Robust file operations: Functionality to store binary game states and text-based logs.
* Graphical Interface: Comprehensive GUI ensuring intuitive, interactive gameplay using external libraries.
* Resilience: Detailed error handling to prevent memory leaks and produce secure software.

## 🤝 Development and Contribution Guidelines
* Clear and descriptive variable/function naming (English).
* Modular implementation: each .c file represents a specific module with a corresponding .h header.
* Regular commits and pull requests referencing specific GitHub issues.
* Thorough documentation and inline comments explaining complex pointer operations.
