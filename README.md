# Greek to Greeklish Translator GR->US

A simple C program that acts as a command-line filter to translate Greek text (ISO-8859-7) into Greeklish. It reads from `stdin`, writes the translation to `stdout`, and handles common letter combinations.

## Features

* Directly maps most Greek characters to their Latin counterparts (e.g., `Α` -> `A`, `φ` -> `f`).
* Uses a simple Finite State Machine (FSM) to handle special two-character combinations:
    * `ντ` / `ΝΤ` -> `d` / `D`
    * `μπ` / `ΜΠ` -> `b` / `B`
* Also handles accented characters and diacritics (`ί` -> `i'`, `ΐ` -> `i'"`).

## How to Use

1.  **Compile it:**
    ```bash
    gcc main.c -o translator
    ```

2.  **Run it:**
    It works as a standard Unix filter. You can pipe text to it or redirect a file.

    **Example with `echo`:**
    ```bash
    echo "Μια πρόταση με ντομάτα και μπάσκετ." | ./translator
    ```
    **Output:**
    ```
    Mia protash me domata kai basket.
    ```

    **Example with a file:**
    ```bash
    ./translator < my_greek_file.txt > my_greeklish_file.txt
    ```
