#ifndef _CHESS_BOARD_H
#define _CHESS_BOARD_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/bitmap.h>
    #include <wx/colour.h>
    #include <wx/dc.h>
    #include <wx/dcclient.h>
    #include <wx/event.h>
    #include <wx/gdicmn.h>
    #include <wx/font.h>
    #include <wx/panel.h>
    #include <wx/pen.h>
    #include <wx/rawbmp.h>
    #include <wx/string.h>
    #include <wx/window.h>
#endif

struct NSVGimage;

namespace loloof64 {
    class ChessBoard : public wxPanel {
    public:
        ChessBoard(wxWindow *parent, int size);
        virtual ~ChessBoard();    
        void paintEvent(wxPaintEvent & evt);
        void refresh();
    private:
        int _size;

        void loadImages();
        wxBitmap generateBitmapFromSvgData(NSVGimage *svgData, int bitmapSize);
        void render(wxDC& dc);

        void drawBackground(wxDC& dc);
        void drawCells(wxDC &dc);
        void drawCoordinates(wxDC &dc);
        void drawPieces(wxDC &dc);

        NSVGimage *_whitePawnSvg;
        wxBitmap _whitePawnBitmap;

        wxDECLARE_EVENT_TABLE();
    };
};
#endif