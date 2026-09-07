#include <iostream>
#include <random>
#include <thread>
#include <chrono>
#include <string>
#include <string_view>
#include <limits>

void clearTerminal() {
    std::cout << "\033[2J\033[1;1H";
}

std::string_view getWord(const char c) {
    switch (c) {
        case 'r' : return "Rock";
        case 'p' : return "Paper";
        case 's' : return "Scissors";
        default : return "";
    }
}

int main() {
    size_t n{0};
    std::cout << "ROCK-PAPER-SCISSORS\n";
    std::cout << "Welcome!\n";
    std::cout << "Enter the number of time you would like to play the game: ";
    std::cin >> n;
    std::cout << "Let's begin!";
    size_t scorePlayer {0};
    size_t scoreComputer {0};
    const int nPossibleInputs {3};
    std::array<char, nPossibleInputs> possibleInputs{'r', 'p', 's'};
    std::random_device seed; //seed from hardware
    std::mt19937 gen(seed()); //intialise the Mersenne Twister engine with seed
    std::uniform_int_distribution<int> distrib(0, nPossibleInputs - 1); //define the range

    for (size_t count {1}; count <= n; ++count) {
        clearTerminal();
        char inputPlayer {};
        int randIdx {distrib(gen)};
        char inputComputer {possibleInputs[randIdx]};
        std::cout << "\nROCK-PAPER-SCISSORS\n";
        std::cout << "SCORE:    You = " << scorePlayer << "  Computer = " << scoreComputer << '\n';
        std::cout << "Match: " << count << " / " << n << '\n';
        std::cout << "Enter (R) for Rock, (P) for Paper, (S) for Scissors:";
        std::cout << "DEBUG: 1\n";
        if (std::cin.peek() != EOF) {
            std::cout << "******* " << std::cin.peek() << '\n';
            std::cin.ignore();
        }
        std::cout << "DEBUG: 2\n";
        std::cin >> inputPlayer;
        auto it {std::find(possibleInputs.begin(), possibleInputs.end(), inputPlayer)};
        if (it == possibleInputs.end()) {
            std::cout << "Invalid Input.... Enter Again! \n";
            --count;
            std::this_thread::sleep_for(std::chrono::seconds(2));
            continue;
        } 
        std::cout << "Your move: " << getWord(inputPlayer) << '\n';
        std::cout << "Computer's move: " << getWord(inputComputer) << '\n';
        //compute result
        if (inputPlayer == inputComputer) {
            std::cout << "Tie!\n";
        }
        else if ((inputComputer == 'p' && inputPlayer == 'r') || (inputComputer == 'r' && inputPlayer == 's') || (inputComputer == 's' && inputPlayer == 'p')) {
            //computer wins
            std::cout << "YOU LOSE\n";
            ++scoreComputer;
        }
        else { //player wins
            std::cout << "YOU WON!\n";
            ++scorePlayer;
        }

        if (count < n) {
            std::cout << "Press Enter to play again!";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            continue;
        }
        else {
            std::cout << "Thank you for playing!\n";
        } 
    }
    return 0;
}