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

#include "ThcPosition.h"

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
        ThcPosition _boardLogic;

        void loadImages();
        wxBitmap generateBitmapFromSvgData(NSVGimage *svgData, int bitmapSize);
        wxBitmap getPieceBitmap(char pieceFen);
        void render(wxDC& dc);

        void drawBackground(wxDC& dc);
        void drawCells(wxDC &dc);
        void drawCoordinates(wxDC &dc);
        void drawPieces(wxDC &dc);
        void drawPlayerTurn(wxDC &dc);

        NSVGimage *_whitePawnSvg;
        NSVGimage *_whiteKnightSvg;
        NSVGimage *_whiteBishopSvg;
        NSVGimage *_whiteRookSvg;
        NSVGimage *_whiteQueenSvg;
        NSVGimage *_whiteKingSvg;
        NSVGimage *_blackPawnSvg;
        NSVGimage *_blackKnightSvg;
        NSVGimage *_blackBishopSvg;
        NSVGimage *_blackRookSvg;
        NSVGimage *_blackQueenSvg;
        NSVGimage *_blackKingSvg;

        wxBitmap _whitePawnBitmap;
        wxBitmap _whiteKnightBitmap;
        wxBitmap _whiteBishopBitmap;
        wxBitmap _whiteRookBitmap;
        wxBitmap _whiteQueenBitmap;
        wxBitmap _whiteKingBitmap;
        wxBitmap _blackPawnBitmap;
        wxBitmap _blackKnightBitmap;
        wxBitmap _blackBishopBitmap;
        wxBitmap _blackRookBitmap;
        wxBitmap _blackQueenBitmap;
        wxBitmap _blackKingBitmap;

        wxDECLARE_EVENT_TABLE();
    };
};
#endif