# Terminal-Based Rock-Paper-Scissors (C++17)

A lightweight C++17 Rock-Paper-Scissors game focused on clean architecture, safe input handling, and strict test coverage using GoogleTest.

## Technical Highlights and Design

* **Game Flexibility:** The player can configure the total number of rounds and can exit the game at any point during gameplay.
* **User-Friendly Interface:** Clear, readable terminal output shows current scores and round progress at each step.
* **Move Generation Algorithm:** Moves are generated using a Pseudo-Random Number Generator (PRNG) based on the Mersenne Twister algorithm (`std::mt19937` seeded via `std::random_device`) to ensure uniform move selection.
* **Decoupled Architecture:** Core game logic (`evaluateResult`, `parseRoundSize`, `parsePlayerCommand`) consists of pure, stateless functions completely isolated from standard terminal I/O, making unit testing straightforward.
* **Modern Error Handling:** Uses `std::optional` to handle invalid inputs cleanly without relying on exceptions for control flow.
* **Efficient Input Validation:** Uses `std::from_chars` for high-performance integer parsing without heap allocations or runtime exception overhead.
* **Strict Compiler Hygiene:** Compiled with `-Wall -Wextra -Wpedantic -Werror` (`/W4 /WX` on MSVC) to ensure the codebase remains completely warning-free.

## Directory Structure

```text
.
├── CMakeLists.txt
├── include/
│   └── rock_paper_scissors.hpp
├── src/
│   ├── main.cpp
│   └── rock_paper_scissors.cpp
└── test/
    └── test_main.cpp

```

## Prerequisites
* C++17 compatible compiler (Clang 10+, GCC 9+, or MSVC 2019+)
* CMake (version 3.14 or higher)

## How to use it

### Build Instruction
To configure and build both the main executable and the unit test suite:

```bash
#configure the build directory (automatically downloads GoogleTest)
cmake -B build

#compile all targets
cmake --build build

```

### Running the Unit Tests
The GoogleTest suite verifies various move outcomes, string case insensitivity, blank or whitespace inputs, invalid inputs, and numerical overflow boundaries up to std::size_t limits.

```bash
#run unit tests directly
./build/test_runner
```

### Executing the Game

```bash
#launch the terminal-based game
./build/rps_game
```

## Author

* **Author:** Tonmoy Sharma
* **Email:** [tonmoy2@icloud.com](mailto:tonmoy2@icloud.com)
* **GitHub:** [github.com/tonmoySh](https://github.com/tonmoySh)