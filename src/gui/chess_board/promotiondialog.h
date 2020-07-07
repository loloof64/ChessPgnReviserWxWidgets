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

#include <functional>

namespace loloof64
{
    class PromotionDialog : public wxDialog
    {
    public:
    /* In callbacks, no need to worry about dialog closing : this will be handled. */
        PromotionDialog(
            wxWindow *parent, const wxString &title,
            wxBitmap knightBitmap, wxBitmap bishopBitmap,
            wxBitmap rookBitmap, wxBitmap queenBitmap,
            std::function<void ()> knightCallBack,
            std::function<void ()> bishopCallBack,
            std::function<void ()> rookCallBack,
            std::function<void ()> queenCallBack
        );

    private:
        wxBitmap _knightBitmap;
        wxBitmap _bishopBitmap;
        wxBitmap _rookBitmap;
        wxBitmap _queenBitmap;

        std::function<void ()> _queenCallback;
        std::function<void ()> _rookCallback;
        std::function<void ()> _knightCallback;
        std::function<void ()> _bishopCallback;

        void handleQueenSelection(wxCommandEvent &event);
        void handleRookSelection(wxCommandEvent &event);
        void handleBishopSelection(wxCommandEvent &event);
        void handleKnightSelection(wxCommandEvent &event);

        wxDECLARE_EVENT_TABLE();
    };
}; // namespace loloof64

#endif