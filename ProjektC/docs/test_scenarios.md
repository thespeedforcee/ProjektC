# Test Scenarios

| Test ID | Test Goal | User Action | Expected Result | Status |
| :--- | :--- | :--- | :--- | :--- |
| **T01** | Missing config file | Deleting the `config.txt` file from the folder before running the game. | The game doesn't crash. The program detects the missing file and loads the default snake speed (6.0). | PASSED |
| **T02** | Invalid stats data | Typing letters (e.g., "test") instead of numbers into the `highscore.txt` file. | The program ignores the letters. It doesn't break the game; the variable just takes a safe value of 0. | PASSED |
| **T03** | Random key presses | Quickly pressing unbound keys (like Space, Enter, or letters) during the game. | The game completely ignores it. The snake keeps moving smoothly, and the program only reacts to the arrow keys. | PASSED |
| **T04** | Impossible move | Trying to turn around instantly (e.g., pressing the down arrow while the snake is moving up). | The conditions in the code block this move so the snake doesn't eat itself. The snake continues moving up. | PASSED |
| **T05** | Freeing memory | Growing the snake to a large size, then closing the game with the ESC key. | The cleanup function properly frees the memory of each segment one by one using the `free` command. | PASSED |
