#include <gtest/gtest.h>
#include <optional>
#include "rock_paper_scissors.hpp"

TEST(GameLogicTest, EvaluatesAllMoveCombinations) {
    using Command = RockPaperScissorsGame::Command;
    using Result = RockPaperScissorsGame::Result;

    //ties
    EXPECT_EQ(RockPaperScissorsGame::evaluateResult(Command::Rock, Command::Rock), Result::Tie);
    EXPECT_EQ(RockPaperScissorsGame::evaluateResult(Command::Paper, Command::Paper), Result::Tie);
    EXPECT_EQ(RockPaperScissorsGame::evaluateResult(Command::Scissors, Command::Scissors), Result::Tie);

    //player wins
    EXPECT_EQ(RockPaperScissorsGame::evaluateResult(Command::Rock, Command::Scissors), Result::Win);
    EXPECT_EQ(RockPaperScissorsGame::evaluateResult(Command::Paper, Command::Rock), Result::Win);
    EXPECT_EQ(RockPaperScissorsGame::evaluateResult(Command::Scissors, Command::Paper), Result::Win);

    //player losses
    EXPECT_EQ(RockPaperScissorsGame::evaluateResult(Command::Scissors, Command::Rock), Result::Lose);
    EXPECT_EQ(RockPaperScissorsGame::evaluateResult(Command::Rock, Command::Paper), Result::Lose);
    EXPECT_EQ(RockPaperScissorsGame::evaluateResult(Command::Paper, Command::Scissors), Result::Lose);
}

TEST(InputParsingTest, ParsesValidPlayerCommands) {
    using Command = RockPaperScissorsGame::Command;

    EXPECT_EQ(RockPaperScissorsGame::parsePlayerCommand("r"), Command::Rock);
    EXPECT_EQ(RockPaperScissorsGame::parsePlayerCommand("R"), Command::Rock);
    EXPECT_EQ(RockPaperScissorsGame::parsePlayerCommand("p"), Command::Paper);
    EXPECT_EQ(RockPaperScissorsGame::parsePlayerCommand("P"), Command::Paper);
    EXPECT_EQ(RockPaperScissorsGame::parsePlayerCommand("s"), Command::Scissors);
    EXPECT_EQ(RockPaperScissorsGame::parsePlayerCommand("S"), Command::Scissors);
    EXPECT_EQ(RockPaperScissorsGame::parsePlayerCommand("q"), Command::Quit);
    EXPECT_EQ(RockPaperScissorsGame::parsePlayerCommand("Q"), Command::Quit);
}

TEST(InputParsingTest, RejectsInvalidPlayerCommands) {
    EXPECT_EQ(RockPaperScissorsGame::parsePlayerCommand("f"), std::nullopt);
    EXPECT_EQ(RockPaperScissorsGame::parsePlayerCommand("rock"), std::nullopt);
    EXPECT_EQ(RockPaperScissorsGame::parsePlayerCommand("absndfisefifae"), std::nullopt);
    EXPECT_EQ(RockPaperScissorsGame::parsePlayerCommand(""), std::nullopt);
    EXPECT_EQ(RockPaperScissorsGame::parsePlayerCommand(" "), std::nullopt);
    EXPECT_EQ(RockPaperScissorsGame::parsePlayerCommand("    "), std::nullopt);
    EXPECT_EQ(RockPaperScissorsGame::parsePlayerCommand("2"), std::nullopt);
    EXPECT_EQ(RockPaperScissorsGame::parsePlayerCommand("18446744073709551615"), std::nullopt);
}
TEST(InputParsingTest, ParsesValidRoundSizes) {
    EXPECT_EQ(RockPaperScissorsGame::parseRoundSize("1"), 1);
    EXPECT_EQ(RockPaperScissorsGame::parseRoundSize("5"), 5);
    EXPECT_EQ(RockPaperScissorsGame::parseRoundSize("100"), 100);
    EXPECT_EQ(RockPaperScissorsGame::parseRoundSize("4294967294"), 4294967294);
}

TEST(InputParsingTest, ParsesInvalidRoundSizes) {
    EXPECT_EQ(RockPaperScissorsGame::parseRoundSize("0"), std::nullopt);
    EXPECT_EQ(RockPaperScissorsGame::parseRoundSize("-1"), std::nullopt);
    EXPECT_EQ(RockPaperScissorsGame::parseRoundSize("fsdfsda"), std::nullopt);
    EXPECT_EQ(RockPaperScissorsGame::parseRoundSize(""), std::nullopt);
    EXPECT_EQ(RockPaperScissorsGame::parseRoundSize(" "), std::nullopt);
    EXPECT_EQ(RockPaperScissorsGame::parseRoundSize("    "), std::nullopt);
    EXPECT_EQ(RockPaperScissorsGame::parseRoundSize("18446744073709551615"), std::nullopt);
}



