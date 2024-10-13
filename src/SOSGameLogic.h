// Name: A Chao Thao
// Assignment: CS449 Sprint 2 
// Date: 10/13/2024

#ifndef SOSGAMELOGIC_H
#define SOSGAMELOGIC_H

class SOSGameLogic
{
public:
    // Constructor that initializes the board with a given siz
    SOSGameLogic(int size);
    // Places a move on the board
    bool PlaceMove(int row, int col, char move);
    // Resets the board to a new size and clears all cells
    void ResetBoard(int size);
    int GetBoardSize() const;
    // Checks if a specific cell is already occupied
    bool IsCellOccupied(int row, int col) const;

private:
    int boardSize;
    char** board;
    void ClearBoard();
};

#endif 