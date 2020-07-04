#ifndef _CHESS_BOARD_H
#define _CHESS_BOARD_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/panel.h>
#endif

namespace loloof64 {
    class ChessBoard {
    public:
        ChessBoard();
        virtual ~ChessBoard();    
    };
};
#endif