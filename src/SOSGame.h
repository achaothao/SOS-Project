// Name: A Chao Thao
// Assignment: CS449 Sprint 2 
// Date: 10/13/2024

#ifndef SOSGAME_H
#define SOSGAME_H

#include <wx/wx.h> // Includes core wxWidgets functionality.
#include <wx/radiobut.h> // For radio button controls.
#include <wx/stattext.h> // For static text controls.
#include <vector>
#include "SOSGameLogic.h"
using namespace std;

class SOSGame : public wxFrame
{
public:
    SOSGame(const wxString& sosgame);

private:
    // GUI Components
    wxPanel* panel; // Panel to contain all other controls
    wxRadioButton* simpleGameRadio;
    wxRadioButton* generalGameRadio;
    wxRadioButton* bluePlayerS;
    wxRadioButton* bluePlayerO;
    wxRadioButton* redPlayerS;
    wxRadioButton* redPlayerO;
    wxChoice* boardSizeChoice;
    wxStaticText* currentTurnText;
    wxButton* newGameButton;

    vector<wxPanel*> cells; // Holds all board cells as panels
    SOSGameLogic* gameLogic; // Pointer to game logic object
    int currentPlayer;

    // Creates the game board dynamically
    void CreateBoard(int size);
    void OnCellClicked(wxMouseEvent& event); // Handles board cell clicks
    void OnNewGame(wxCommandEvent& event); // Resets the game
    void UpdateCurrentTurn(); // Updates the display for the current turn
    void ResetPlayerSelections();

    wxDECLARE_EVENT_TABLE(); // Declares the event table for event handling
};

#endif 