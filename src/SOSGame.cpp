// Name: A Chao Thao
// Assignment: CS449 Sprint 2 
// Date: 10/13/2024

#include "SOSGame.h"
#include <algorithm>

wxBEGIN_EVENT_TABLE(SOSGame, wxFrame)
EVT_LEFT_DOWN(SOSGame::OnCellClicked) // Registers the cell click event
wxEND_EVENT_TABLE()

// Constructor initializes the GUIand sets default values
SOSGame::SOSGame(const wxString& sosgame)
    : wxFrame(NULL, wxID_ANY, sosgame, wxDefaultPosition, wxSize(600, 400)), currentPlayer(0)
{
    panel = new wxPanel(this, wxID_ANY); // Main panel for the window
    panel->SetBackgroundColour(wxColour(255, 255, 255));

    // Game mode radio buttons
    new wxStaticText(panel, wxID_ANY, "SOS", wxPoint(155, 5), wxDefaultSize, wxALIGN_LEFT);

    simpleGameRadio = new wxRadioButton(panel, wxID_ANY, "Simple game", wxPoint(190, 5), wxDefaultSize, wxRB_GROUP);
    generalGameRadio = new wxRadioButton(panel, wxID_ANY, "General game", wxPoint(330, 5));

    // Board size selection dropdown
    new wxStaticText(panel, wxID_ANY, "Board Size:", wxPoint(470, 5), wxDefaultSize, wxALIGN_LEFT);
    wxArrayString sizes;
    for (int i = 3; i <= 10; ++i)
        sizes.Add(wxString::Format("%d", i));

    boardSizeChoice = new wxChoice(panel, wxID_ANY, wxPoint(540, 5), wxDefaultSize, sizes);
    boardSizeChoice->SetSelection(0);

    // Player move selection radio buttons
    new wxStaticText(panel, wxID_ANY, "Blue Player", wxPoint(10, 80), wxDefaultSize, wxALIGN_LEFT);
    bluePlayerS = new wxRadioButton(panel, wxID_ANY, "S", wxPoint(30, 120), wxDefaultSize, wxRB_GROUP);
    bluePlayerO = new wxRadioButton(panel, wxID_ANY, "O", wxPoint(30, 140));

    new wxStaticText(panel, wxID_ANY, "Red Player", wxPoint(470, 80), wxDefaultSize, wxALIGN_LEFT);
    redPlayerS = new wxRadioButton(panel, wxID_ANY, "S", wxPoint(490, 120), wxDefaultSize, wxRB_GROUP);
    redPlayerO = new wxRadioButton(panel, wxID_ANY, "O", wxPoint(490, 140));

    // Initialize game logic and board
    gameLogic = new SOSGameLogic(3);
    CreateBoard(3);

    // Current turn display and new game button
    currentTurnText = new wxStaticText(panel, wxID_ANY, "Current turn: Blue", wxPoint(250, 330), wxDefaultSize, wxALIGN_CENTER);

    newGameButton = new wxButton(panel, wxID_ANY, "New Game", wxPoint(500, 330));
    newGameButton->Bind(wxEVT_BUTTON, &SOSGame::OnNewGame, this);

    boardSizeChoice->Bind(wxEVT_CHOICE, &SOSGame::OnNewGame, this);
}

// Dynamically creates the board grid
void SOSGame::CreateBoard(int size)
{
    for (auto& cell : cells)
        cell->Destroy();
    cells.clear();

    int xPos = 160;
    int yPos = 50;
    int boxWidth = 35;
    int boxHeight = 30;
    int gap = 34;

    for (int row = 0; row < size; ++row)
    {
        for (int col = 0; col < size; ++col)
        {
            wxPanel* cell = new wxPanel(panel, wxID_ANY, wxPoint(xPos + (col * gap), yPos + (row * boxHeight)),
                wxSize(boxWidth, boxHeight), wxSIMPLE_BORDER);
            cells.push_back(cell);
            cell->Bind(wxEVT_LEFT_DOWN, &SOSGame::OnCellClicked, this);
        }
    }
    // Reset the logic for new board size
    gameLogic->ResetBoard(size);
    UpdateCurrentTurn();
}

// Handles a player's move
void SOSGame::OnCellClicked(wxMouseEvent& event)
{
    wxPanel* cell = dynamic_cast<wxPanel*>(event.GetEventObject());
    if (!cell) return;

    int index = std::find(cells.begin(), cells.end(), cell) - cells.begin();
    if (index < 0 || index >= cells.size()) return;

    int row = index / gameLogic->GetBoardSize();
    int col = index % gameLogic->GetBoardSize();

    if (gameLogic->IsCellOccupied(row, col))
    {
        wxMessageBox("This cell is already occupied! Please select a different cell.",
            "Invalid Move", wxOK | wxICON_ERROR);
        return;
    }

    char move = (currentPlayer == 0) ? (bluePlayerS->GetValue() ? 'S' : 'O') : (redPlayerS->GetValue() ? 'S' : 'O');

    if (gameLogic->PlaceMove(row, col, move))
    {
        new wxStaticText(cell, wxID_ANY, wxString::Format("%c", move), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
        currentPlayer = (currentPlayer + 1) % 2;
        UpdateCurrentTurn();
    }
}

// Resets the game
void SOSGame::OnNewGame(wxCommandEvent& event)
{
    int boardSize = boardSizeChoice->GetSelection() + 3;
    CreateBoard(boardSize);
    ResetPlayerSelections();
    currentPlayer = 0;
    UpdateCurrentTurn();
}

void SOSGame::ResetPlayerSelections()
{
    bluePlayerS->SetValue(true);
    redPlayerS->SetValue(true);
}

// Update player turn and tell which player turn it was
void SOSGame::UpdateCurrentTurn()
{
    if (!currentTurnText) {
        return;
    }
    wxString turnText = (currentPlayer == 0) ? "Current turn: Blue" : "Current turn: Red";
    currentTurnText->SetLabel(turnText);
}

class SOSApp : public wxApp
{
public:
    virtual bool OnInit();
};

IMPLEMENT_APP(SOSApp)

bool SOSApp::OnInit()
{
    SOSGame* game = new SOSGame("SOS Game");
    game->Show(true);
    return true;
}