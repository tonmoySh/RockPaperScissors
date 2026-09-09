#include "rock_paper_scissors.hpp"

#include <iostream>
#include <exception>

int main() {
    try {
        RockPaperScissorsGame rpsGame{std::random_device{}()};
        rpsGame.play();
    }
    catch (const std::exception& e) {
        std::cerr << "Fatal Error: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}