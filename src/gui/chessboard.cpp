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
        dc.SetBrush(*wxBLUE_BRUSH);
        dc.DrawRectangle(0,0,_size,_size);
    }

    wxBEGIN_EVENT_TABLE(ChessBoard, wxPanel)
        EVT_PAINT(ChessBoard::paintEvent)
    wxEND_EVENT_TABLE()
}