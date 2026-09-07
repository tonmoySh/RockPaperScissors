#include <iostream>
#include <random>
#include <thread>
#include <chrono>
#include <string>
#include <string_view>
#include <optional>
#include <charconv>
#include <limits>

class RockPaperScissorsGame {
public:
    enum class Command {
        Rock,
        Paper,
        Scissors,
        Quit
    };

    enum class Result {
        Win,
        Lose,
        Tie
    };

    enum class LineStyle {
        SingleDash,
        DoubleDash
    };

private:
    static constexpr int possibleCommands {3}; //must be greater than 0
    std::size_t playerScore {0};
    std::size_t computerScore {0};
    std::size_t roundCount {1};
    std::size_t roundSize {1};
    std::uniform_int_distribution<int> dist{0, possibleCommands - 1}; //a <= b guaranteed
    std::mt19937 rng;
    
    static void displayHLine(LineStyle linestyle) noexcept {
        switch (linestyle) {
            case LineStyle::SingleDash : std::cout << "-----------------------------------------------------\n"; break;
            case LineStyle::DoubleDash : std::cout << "=====================================================\n"; break;
        }
    }

    static std::optional<std::size_t> parseRoundSize(std::string_view line) noexcept {
        std::size_t value{0};
        auto [nextPtr, ec] {std::from_chars(line.data(), line.data() + line.size(), value)};
        constexpr std::size_t maxPossibleRounds {std::numeric_limits<std::size_t>::max() - 1};
        if (ec == std::errc{} && nextPtr == line.data() + line.size() && value > 0 && value <= maxPossibleRounds) {
            return value;
        }

        return std::nullopt;
    }

    static std::optional<std::size_t> parseRoundSizeFromStdin() {
        std::string line;
        if (!std::getline(std::cin, line)) {
            return std::nullopt;
        }

        return parseRoundSize(line);
    }

    static std::optional<Command> parsePlayerCommand(std::string_view line) noexcept {//returns player's command (might be invalid or non-playable)
        if (line.size() != 1) {
            return std::nullopt;
        }

        const char c = static_cast<char>(std::tolower(static_cast<unsigned char>(line[0])));
        switch (c) {
            case 'r' : return Command::Rock;
            case 'p' : return Command::Paper;
            case 's' : return Command::Scissors;
            case 'q' : return Command::Quit;
            default : return std::nullopt; 
        }
    }

    std::optional<Command> parsePlayerCommandFromStdin() {
        std::string line;
        if (!std::getline(std::cin, line)) {
            return std::nullopt;
        }
        return parsePlayerCommand(line);
    }
    
    static constexpr std::string_view toString(Command command) noexcept { //converts command to string view
        switch (command) {
            case Command::Rock : return "Rock";
            case Command::Paper : return "Paper";
            case Command::Scissors : return "Scissors";
            default : return "";
        }
    }

    bool isPlayerCommandPlayable(std::optional<Command> answer) { //returns true if player entered valid Rock, Paper, Scissors command
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

    Command getComputerCommand() noexcept { //returns computer's command (always playable)
        return (static_cast<Command>(dist(rng)));
    }

    static constexpr Result evaluateResult(Command player, Command computer) noexcept{
        if (player == computer) {
            return Result::Tie;
        }
        else if ((player == Command::Paper && computer == Command::Rock) || (player == Command::Rock && computer == Command::Scissors) || (player == Command::Scissors && computer == Command::Paper)) {
            return Result::Win;
        }

        return Result::Lose;
    }

    constexpr void updateScore(Result result) noexcept { //Win and Lose refers to the player, for the computer it will be the opposite
        if (result == Result::Win) {
            ++playerScore;
        }
        else if (result == Result::Lose) {
            ++computerScore;
        }
    }

    bool displayGameWelcome() { //returns true when player enters valid roundSize
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

    void displayGameStart() const {
        std::cout << "\n\n";
        displayHLine(LineStyle::DoubleDash);
        std::cout << "ROUND: " << roundCount << " of " << roundSize << "\n";
        displayHLine(LineStyle::SingleDash);
        std::cout << "SCORE: You = " << playerScore << "    Computer = " << computerScore << '\n';
        std::cout << "Enter (r) for Rock, (p) for Paper, (s) for Scissors\nor (q) to quit: ";
    }
    
    static void displayGameResult(Command mvPlayer, Command mvComputer, Result result) { //can throw exception
        std::cout << "\nYour move: " << toString(mvPlayer) << '\n';
        std::cout << "Computer's move: " << toString(mvComputer) << '\n';
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

    void displayGameEnd() const {
        std::cout << '\n';
        displayHLine(LineStyle::DoubleDash);
        std::cout << "Match Ended!\n";
        std::cout << "Your score = " << playerScore << "    Computer's score = " << computerScore << '\n';
        std::cout << "Thank you for playing!\n";
        displayHLine(LineStyle::DoubleDash);
    }

    static void pause() {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

public:
    explicit RockPaperScissorsGame(std::mt19937::result_type seed_ = std::random_device{}()) : rng(seed_) {}

    void play() {
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
};

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