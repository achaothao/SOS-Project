// Name: A Chao Thao
// Assignment: CS449 Sprint 2 
// Date: 10/13/2024

#include "pch.h"
#include <gtest/gtest.h>
#include "SOSGameLogic.h"
#include "SOSGameLogic.cpp"

// Test User Story 1: Choose a board size
TEST(SOSGameLogicTest, ChooseBoardSize) {
    SOSGameLogic gameLogic(5);
    EXPECT_EQ(gameLogic.GetBoardSize(), 5);

    gameLogic.ResetBoard(7);
    EXPECT_EQ(gameLogic.GetBoardSize(), 7);
}

// Test User Story 2: Choose the game mode of a chosen board (Placeholder)
TEST(SOSGameLogicTest, GameModeSelection) {
    SOSGameLogic simpleGame(3);  // Initialize a simple game
    EXPECT_EQ(simpleGame.GetBoardSize(), 3);  // Check size after initialization

    // Placeholder logic: Extend if specific game mode rules are added
    // Currently, no special mode behavior implemented.
}

// Test User Story 3: Start a new game of the chosen board size and game mode
TEST(SOSGameLogicTest, StartNewGame) {
    SOSGameLogic gameLogic(3);
    gameLogic.PlaceMove(0, 0, 'S');  // Place a move

    gameLogic.ResetBoard(3);  // Reset the board
    EXPECT_FALSE(gameLogic.IsCellOccupied(0, 0));  // Verify reset worked
}

// Test User Story 4: Make a move in a simple game
TEST(SOSGameLogicTest, SimpleGameMove) {
    SOSGameLogic gameLogic(3);
    EXPECT_TRUE(gameLogic.PlaceMove(0, 0, 'S'));  // Valid move
    EXPECT_TRUE(gameLogic.IsCellOccupied(0, 0));  // Verify cell is occupied

    EXPECT_FALSE(gameLogic.PlaceMove(0, 0, 'O'));  // Invalid: Cell already occupied
}

// Test User Story 6: Make a move in a general game (on a larger board)
TEST(SOSGameLogicTest, GeneralGameMove) {
    SOSGameLogic gameLogic(5);  // General game with a larger board
    EXPECT_TRUE(gameLogic.PlaceMove(2, 2, 'O'));  // Place move 'O'
    EXPECT_TRUE(gameLogic.IsCellOccupied(2, 2));  // Verify the move

    EXPECT_FALSE(gameLogic.PlaceMove(2, 2, 'S'));  // Invalid: Cell already occupied
}