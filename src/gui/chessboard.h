#ifndef _CHESS_BOARD_H
#define _CHESS_BOARD_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/colour.h>
    #include <wx/dc.h>
    #include <wx/dcclient.h>
    #include <wx/event.h>
    #include <wx/gdicmn.h>
    #include <wx/font.h>
    #include <wx/panel.h>
    #include <wx/pen.h>
    #include <wx/string.h>
    #include <wx/window.h>
#endif

namespace loloof64 {
    class ChessBoard : public wxPanel {
    public:
        ChessBoard(wxWindow *parent, int size);
        virtual ~ChessBoard();    
        void paintEvent(wxPaintEvent & evt);
        void refresh();
    private:
        int _size;
        void render(wxDC& dc);

        void drawBackground(wxDC& dc);
        void drawCells(wxDC &dc);
        void drawCoordinates(wxDC &dc);

        wxDECLARE_EVENT_TABLE();
    };
};
#endif