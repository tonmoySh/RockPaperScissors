#pragma once

#include <random>
#include <string_view>
#include <optional>
#include <cstddef>

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

    explicit RockPaperScissorsGame(std::mt19937::result_type seed_ = std::random_device{}());

    void play();

    //made public for test execution
    //core helper member function
    static constexpr Result evaluateResult(Command player, Command computer) noexcept{
        if (player == computer) {
            return Result::Tie;
        }
        else if ((player == Command::Paper && computer == Command::Rock) || (player == Command::Rock && computer == Command::Scissors) || (player == Command::Scissors && computer == Command::Paper)) {
            return Result::Win;
        }

        return Result::Lose;
    }

    //input parsing member functions
    static std::optional<std::size_t> parseRoundSize(std::string_view line) noexcept;
    static std::optional<Command> parsePlayerCommand(std::string_view line) noexcept;

private:
    //member variables
    static constexpr int possibleCommands {3}; //must be greater than 0
    std::size_t playerScore {0};
    std::size_t computerScore {0};
    std::size_t roundCount {1};
    std::size_t roundSize {1};
    std::uniform_int_distribution<int> dist{0, possibleCommands - 1}; //a <= b guaranteed
    std::mt19937 rng;
    
    //input parsing member functions
    static std::optional<std::size_t> parseRoundSizeFromStdin();
    static std::optional<Command> parsePlayerCommandFromStdin();

    //helper member functions
    bool isPlayerCommandPlayable(std::optional<Command> answer);
    Command getComputerCommand() noexcept;
    void updateScore(Result result) noexcept;
    static constexpr std::string_view toString(Command command) noexcept {
        switch (command) {
            case Command::Rock : return "Rock";
            case Command::Paper : return "Paper";
            case Command::Scissors : return "Scissors";
            default : return "";
        }
    }
    
    //game output interface member functions
    static void displayHLine(LineStyle linestyle) noexcept;
    bool displayGameWelcome();
    void displayGameStart() const;
    static void displayGameResult(Command player, Command computer, Result result);
    void displayGameEnd() const;
    static void pause();
};