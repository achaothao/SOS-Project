// Name: A Chao Thao
// Assignment: CS449 Sprint 2 
// Date: 10/13/2024

#include "SOSGameLogic.h"
#include <cstring>
using namespace std;

// Constructor: Initializes the board with the given size
SOSGameLogic::SOSGameLogic(int size)
{
    boardSize = size;
    board = new char* [size];
    for (int i = 0; i < size; ++i)
        board[i] = new char[size];
    ClearBoard();
}

// Resets the board to a new size and clears its contents
void SOSGameLogic::ResetBoard(int size)
{
    for (int i = 0; i < boardSize; ++i)
        delete[] board[i];
    delete[] board;

    boardSize = size;
    board = new char* [size];
    for (int i = 0; i < size; ++i)
        board[i] = new char[size];
    ClearBoard();
}

// Places a move on the board 
// @param row Row index where the move will be placed
// @param col Column index where the move will be placed
// @param move The character ('S' or 'O') to place on the board
// @return True if the move was placed successfully, false if the cell is occupied or invalid
bool SOSGameLogic::PlaceMove(int row, int col, char move)
{
    if (row < 0 || row >= boardSize || col < 0 || col >= boardSize || board[row][col] != ' ')
        return false;

    board[row][col] = move;
    return true;
}

// Checks if the specified cell is already occupied
// @param row Row index of the cell to check
// @param col Column index of the cell to check
// @return True if the cell is occupied, false otherwise
bool SOSGameLogic::IsCellOccupied(int row, int col) const
{
    return board[row][col] != ' ';
}

// Clear the board game
void SOSGameLogic::ClearBoard()
{
    for (int i = 0; i < boardSize; ++i)
        memset(board[i], ' ', boardSize);
}

int SOSGameLogic::GetBoardSize() const
{
    return boardSize;
}