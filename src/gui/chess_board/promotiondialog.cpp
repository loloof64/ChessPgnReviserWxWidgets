#include "promotiondialog.h"

#define QUEEN_BUTTON 1
#define ROOK_BUTTON 2
#define BISHOP_BUTTON 4
#define KNIGHT_BUTTON 8

namespace loloof64
{
    PromotionDialog::PromotionDialog(
        wxWindow *parent, const wxString &title,
        wxBitmap knightBitmap, wxBitmap bishopBitmap,
        wxBitmap rookBitmap, wxBitmap queenBitmap,
        std::function<void()> knightCallBack,
        std::function<void()> bishopCallBack,
        std::function<void()> rookCallBack,
        std::function<void()> queenCallBack) : wxDialog(parent, wxID_ANY, title, wxDefaultPosition, wxDefaultSize, wxCAPTION),
                                               _knightBitmap(knightBitmap),
                                               _bishopBitmap(bishopBitmap),
                                               _rookBitmap(rookBitmap),
                                               _queenBitmap(queenBitmap),
                                               _knightCallback(knightCallBack),
                                               _bishopCallback(bishopCallBack),
                                               _rookCallback(rookCallBack),
                                               _queenCallback(queenCallBack)
    {
        wxSizer *mainSizer = new wxBoxSizer(wxHORIZONTAL);

        wxBitmapButton *queenButton = new wxBitmapButton(this, QUEEN_BUTTON, _queenBitmap);
        wxBitmapButton *rookButton = new wxBitmapButton(this, ROOK_BUTTON, _rookBitmap);
        wxBitmapButton *bishopButton = new wxBitmapButton(this, BISHOP_BUTTON, _bishopBitmap);
        wxBitmapButton *knightButton = new wxBitmapButton(this, KNIGHT_BUTTON, _knightBitmap);

        mainSizer->Add(queenButton, 1, wxALL, 5);
        mainSizer->Add(rookButton, 1, wxALL, 5);
        mainSizer->Add(bishopButton, 1, wxALL, 5);
        mainSizer->Add(knightButton, 1, wxALL, 5);

        SetSizerAndFit(mainSizer);
    }

    void PromotionDialog::handleQueenSelection(wxCommandEvent &event)
    {
        _queenCallback();
        Close();
    }

    void PromotionDialog::handleRookSelection(wxCommandEvent &event)
    {
        _rookCallback();
        Close();
    }

    void PromotionDialog::handleBishopSelection(wxCommandEvent &event)
    {
        _bishopCallback();
        Close();
    }

    void PromotionDialog::handleKnightSelection(wxCommandEvent &event)
    {
        _knightCallback();
        Close();
    }

    wxBEGIN_EVENT_TABLE(PromotionDialog, wxDialog)
        EVT_BUTTON(QUEEN_BUTTON, PromotionDialog::handleQueenSelection)
            EVT_BUTTON(ROOK_BUTTON, PromotionDialog::handleRookSelection)
                EVT_BUTTON(BISHOP_BUTTON, PromotionDialog::handleBishopSelection)
                    EVT_BUTTON(KNIGHT_BUTTON, PromotionDialog::handleKnightSelection)
                        wxEND_EVENT_TABLE()
}; // namespace loloof64