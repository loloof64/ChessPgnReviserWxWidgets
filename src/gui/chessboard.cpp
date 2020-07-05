#include "chessboard.h"

namespace loloof64 {
    ChessBoard::ChessBoard(wxWindow *parent, int size): 
    wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(size, size)), _size(size) 
    {
    }

    ChessBoard::~ChessBoard() {
        
    }

    void ChessBoard::paintEvent(wxPaintEvent &evt) {
        wxPaintDC dc(this);
        render(dc);
    }

    void ChessBoard::refresh() {
        wxPaintDC dc(this);
        render(dc);
    }

    void ChessBoard::render(wxDC &dc) {
        drawBackground(dc);
        drawCells(dc);
    }

    void ChessBoard::drawBackground(wxDC &dc) {
        wxColour backgroundColor(30, 60, 250);
        dc.SetBrush(backgroundColor);
        dc.DrawRectangle(0,0,_size,_size);
    }

    void ChessBoard::drawCells(wxDC &dc) {
        wxColour whiteCellsColor(255, 206, 158);
        wxColour blackCellsColor(209, 139, 71);
        auto cellsSize = _size * 1.0 / 9.0;

        for (auto row = 0; row < 8; row++) {
            for (auto col = 0; col < 8; col++) {
                auto isWhiteCell = (row+col) %2 == 0;
                auto currentCellColor = isWhiteCell ? whiteCellsColor : blackCellsColor;

                auto x = (int) cellsSize * (col + 0.5);
                auto y = (int) cellsSize * (row + 0.5);

                dc.SetBrush(currentCellColor);
                dc.SetPen(wxNullPen);
                dc.DrawRectangle(x, y, cellsSize, cellsSize);
            }
        }
    }

    wxBEGIN_EVENT_TABLE(ChessBoard, wxPanel)
        EVT_PAINT(ChessBoard::paintEvent)
    wxEND_EVENT_TABLE()
}