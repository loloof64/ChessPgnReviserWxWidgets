#include "main_window.h"
#include "chess_board/chessboard.h"

MainWindow::MainWindow()
    : wxFrame(NULL, wxID_ANY, "Chess Pgn Reviser", wxDefaultPosition, wxSize(CHESS_BOARD_SIZE, CHESS_BOARD_SIZE + 50))
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
                     "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
    SetMenuBar( menuBar );
    CreateStatusBar();
    SetStatusText("Welcome to Chess Pgn Reviser !");
    Bind(wxEVT_MENU, &MainWindow::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &MainWindow::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MainWindow::OnExit, this, wxID_EXIT);

    using namespace loloof64;
    new ChessBoard(this, CHESS_BOARD_SIZE);
}
void MainWindow::OnExit(wxCommandEvent& event)
{
    Close(true);
}
void MainWindow::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("Chess Pgn Reviser is a simple application in order to help you train yourself with chess pgn files.",
                 "About Chess Pgn Reviser", wxOK | wxICON_INFORMATION);
}
void MainWindow::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world Chess Pgn Reviser !");
}