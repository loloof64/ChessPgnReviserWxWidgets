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
        drawCoordinates(dc);
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

    void ChessBoard::drawCoordinates(wxDC &dc) {
        auto cellsSize = _size * 1.0 / 9.0;
        auto fontSize = cellsSize * 0.25;

        wxColour coordinatesColor(255, 199, 0);
        wxFont coordinatesFont;
        coordinatesFont.SetPointSize(fontSize);
        coordinatesFont = coordinatesFont.Bold();
        
        dc.SetFont(coordinatesFont);
        dc.SetTextForeground(coordinatesColor);
        dc.SetTextBackground(wxNullColour);

        const char LETTER_A = 'a';
        for (auto col = 0; col < 8; col++) {
            auto x = cellsSize * (0.9 + col);
            auto y1 = cellsSize * 0.05;
            auto y2 = cellsSize * 8.45;

            auto value = LETTER_A + col;
            auto text = wxString::FromAscii(value);

            dc.DrawText(text, x, y1);
            dc.DrawText(text, x, y2);
        }

        const char DIGIT_1 = '1';
        for (auto row = 0; row < 8; row++) {
            auto y = cellsSize * (0.8 + row);
            auto x1 = cellsSize * 0.15;
            auto x2 = cellsSize * 8.6;

            auto value = DIGIT_1 + (7-row);
            auto text = wxString::FromAscii(value);

            dc.DrawText(text, x1, y);
            dc.DrawText(text, x2, y);
        }

    }

    wxBEGIN_EVENT_TABLE(ChessBoard, wxPanel)
        EVT_PAINT(ChessBoard::paintEvent)
    wxEND_EVENT_TABLE()
}