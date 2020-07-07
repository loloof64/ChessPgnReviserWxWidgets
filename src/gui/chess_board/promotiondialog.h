#ifndef _PROMOTION_DIALOG_H
#define _PROMOTION_DIALOG_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/bitmap.h>
#include <wx/bmpbuttn.h>
#include <wx/dialog.h>
#include <wx/event.h>
#include <wx/sizer.h>
#include <wx/string.h>
#endif

namespace loloof64
{
    class PromotionDialog : public wxDialog
    {
    public:
        PromotionDialog(
            wxWindow *parent, const wxString &title,
            wxBitmap knightBitmap, wxBitmap bishopBitmap,
            wxBitmap rookBitmap, wxBitmap queenBitmap
        );

    private:
        wxBitmap _knightBitmap;
        wxBitmap _bishopBitmap;
        wxBitmap _rookBitmap;
        wxBitmap _queenBitmap;

        void handleQueenSelection(wxCommandEvent &event);
        void handleRookSelection(wxCommandEvent &event);
        void handleBishopSelection(wxCommandEvent &event);
        void handleKnightSelection(wxCommandEvent &event);

        wxDECLARE_EVENT_TABLE();
    };
}; // namespace loloof64

#endif