#include "rock_paper_scissors.hpp"

#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <charconv>
#include <limits>
#include <cctype>

RockPaperScissorsGame::RockPaperScissorsGame(std::mt19937::result_type seed_) : rng(seed_) {}

void RockPaperScissorsGame::play() {
    if (!displayGameWelcome()) {
        return;
    }

    while (roundCount <= roundSize) {
        displayGameStart();
        std::optional<Command> playerCommand {parsePlayerCommandFromStdin()};
        Command computerCommand {getComputerCommand()};
        if (!isPlayerCommandPlayable(playerCommand)) {
            pause();
            continue;
        }
        Result result {evaluateResult(playerCommand.value(), computerCommand)}; //guaranteed that playerCommand will contain valid playable command
        updateScore(result);
        displayGameResult(playerCommand.value(), computerCommand, result);
        pause();
        ++roundCount;
    }

    displayGameEnd();
}

std::optional<std::size_t> RockPaperScissorsGame::parseRoundSize(std::string_view line) noexcept {
    std::size_t value{0};
    auto [nextPtr, ec] {std::from_chars(line.data(), line.data() + line.size(), value)};
    constexpr std::size_t maxPossibleRounds {std::numeric_limits<std::size_t>::max() - 1};
    if (ec == std::errc{} && nextPtr == line.data() + line.size() && value > 0 && value <= maxPossibleRounds) {
        return value;
    }

    return std::nullopt;
}

std::optional<RockPaperScissorsGame::Command> RockPaperScissorsGame::parsePlayerCommand(std::string_view line) noexcept {//returns player's command (might be invalid/non-playable)
    if (line.size() != 1) {
        return std::nullopt;
    }

    const char c {static_cast<char>(std::tolower(static_cast<unsigned char>(line[0])))};
    switch (c) {
        case 'r' : return Command::Rock;
        case 'p' : return Command::Paper;
        case 's' : return Command::Scissors;
        case 'q' : return Command::Quit;
        default : return std::nullopt; 
    }
}

std::optional<std::size_t> RockPaperScissorsGame::parseRoundSizeFromStdin() {
    std::string line;
    if (!std::getline(std::cin, line)) {
        return std::nullopt;
    }

    return parseRoundSize(line);
}

std::optional<RockPaperScissorsGame::Command> RockPaperScissorsGame::parsePlayerCommandFromStdin() {
    std::string line;
    if (!std::getline(std::cin, line)) {
        return std::nullopt;
    }
    
    return parsePlayerCommand(line);
}

bool RockPaperScissorsGame::isPlayerCommandPlayable(std::optional<Command> answer) { //returns true if player entered valid Rock, Paper, Scissors command
    if (answer.has_value()) {
        if (answer.value() == Command::Quit) {
            roundCount = roundSize + 1;
            return false;
        }
        else { //contains Rock, Paper or Scissors 
            return true;
        }
    }

    std::cout << "\nInvalid Input! Enter Again... \n";
    return false;
}

RockPaperScissorsGame::Command RockPaperScissorsGame::getComputerCommand() noexcept {
    return (static_cast<Command>(dist(rng)));
}

void RockPaperScissorsGame::updateScore(Result result) noexcept { //Win and Lose refers to the player, for computer it will be the opposite
    if (result == Result::Win) {
        ++playerScore;
    }
    else if (result == Result::Lose) {
        ++computerScore;
    }
}

void RockPaperScissorsGame::displayHLine(LineStyle linestyle) noexcept {
    switch (linestyle) {
        case LineStyle::SingleDash : std::cout << "-----------------------------------------------------\n"; break;
        case LineStyle::DoubleDash : std::cout << "=====================================================\n"; break;
    }
}

bool RockPaperScissorsGame::displayGameWelcome() { //returns true when player enters valid roundSize
    std::cout << '\n';
    displayHLine(LineStyle::DoubleDash);
    std::cout << "||               ROCK PAPER SCISSORS               ||\n";
    displayHLine(LineStyle::DoubleDash);
    std::cout << "Welcome!\n";
    constexpr int maxAttempt {10};
    int attempt {0};
    while (attempt < maxAttempt) {
        std::cout << "\nEnter the number of rounds you would like to play: ";
        if (auto answer {parseRoundSizeFromStdin()}; answer.has_value()) {
            roundSize = answer.value(); //valid value inserted!
            std::cout << "\nLET'S BEGIN!\n";
            return true;
        }
        std::cout << "Invalid Input!\n";
        ++attempt;
    }

    std::cout << "\nMaximum invalid attempts reached! Exiting game...\n";
    return false;
}

void RockPaperScissorsGame::displayGameStart() const {
    std::cout << "\n\n";
    displayHLine(LineStyle::DoubleDash);
    std::cout << "ROUND: " << roundCount << " of " << roundSize << '\n';
    displayHLine(LineStyle::SingleDash);
    std::cout << "SCORE: You = " << playerScore << "    Computer = " << computerScore << '\n';
    std::cout << "Enter (r) for Rock, (p) for Paper, (s) for Scissors\nor (q) to quit: ";
}

void RockPaperScissorsGame::displayGameResult(Command player, Command computer, Result result) {
    std::cout << "\nYour move: " << toString(player) << '\n';
    std::cout << "Computer's move: " << toString(computer) << '\n';
    displayHLine(LineStyle::SingleDash);
    if (result == Result::Tie) {
        std::cout << "TIE!\n";
    }
    else if (result == Result::Win) {
        std::cout << "YOU WIN!\n";
    }
    else {
        std::cout << "YOU LOSE!\n";
    }
    displayHLine(LineStyle::DoubleDash);
}

void RockPaperScissorsGame::displayGameEnd() const {
    std::cout << '\n';
    displayHLine(LineStyle::DoubleDash);
    std::cout << "Match Ended!\n";
    std::cout << "Your score = " << playerScore << "    Computer's score = " << computerScore << '\n';
    std::cout << "Thank you for playing!\n";
    displayHLine(LineStyle::DoubleDash);
}

void RockPaperScissorsGame::pause() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
}