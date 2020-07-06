#include "chessboard.h"
#include <string>

//////////////////////////
#include <iostream>
//////////////////////////

extern "C" char Chess_plt45_svg[];
extern "C" char Chess_nlt45_svg[];
extern "C" char Chess_blt45_svg[];
extern "C" char Chess_rlt45_svg[];
extern "C" char Chess_qlt45_svg[];
extern "C" char Chess_klt45_svg[];
extern "C" char Chess_pdt45_svg[];
extern "C" char Chess_ndt45_svg[];
extern "C" char Chess_bdt45_svg[];
extern "C" char Chess_rdt45_svg[];
extern "C" char Chess_qdt45_svg[];
extern "C" char Chess_kdt45_svg[];

#define NANOSVG_IMPLEMENTATION
#include "nanosvg.h"

#define NANOSVGRAST_IMPLEMENTATION
#include "nanosvgrast.h"

std::string DEFAULT_CHESS_POSITION = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

namespace loloof64
{
    ChessBoard::ChessBoard(wxWindow *parent, int size) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(size, size)),
                                                         _boardLogic(DEFAULT_CHESS_POSITION)
    {
        loadImages(size);
    }

    ChessBoard::~ChessBoard()
    {
    }

    void ChessBoard::paintEvent(wxPaintEvent &evt)
    {
        wxPaintDC dc(this);
        render(dc);
    }

    void ChessBoard::refresh()
    {
        wxPaintDC dc(this);
        render(dc);
    }

    void ChessBoard::setReversed(bool reversed)
    {
        _reversed = reversed;
        refresh();
    }

    void ChessBoard::render(wxDC &dc)
    {
        auto size = getShortestSize();
        if (_currentSize != size)
        {
            updateImagesSize(size);
            _currentSize = size;
        }

        drawBackground(dc);
        drawCells(dc);
        drawCoordinates(dc);
        drawPieces(dc);
        drawPlayerTurn(dc);
    }

    void ChessBoard::drawBackground(wxDC &dc)
    {
        auto size = getShortestSize();

        wxColour backgroundColor(30, 60, 250);
        dc.SetBrush(backgroundColor);
        dc.DrawRectangle(0, 0, size, size);
    }

    void ChessBoard::drawCells(wxDC &dc)
    {
        auto size = getShortestSize();

        wxColour whiteCellsColor(255, 206, 158);
        wxColour blackCellsColor(209, 139, 71);
        auto cellsSize = size * 1.0 / 9.0;

        for (auto row = 0; row < 8; row++)
        {
            for (auto col = 0; col < 8; col++)
            {
                auto isWhiteCell = (row + col) % 2 == 0;
                auto currentCellColor = isWhiteCell ? whiteCellsColor : blackCellsColor;

                auto x = (int)cellsSize * (col + 0.5);
                auto y = (int)cellsSize * (row + 0.5);

                dc.SetBrush(currentCellColor);
                dc.SetPen(wxNullPen);
                dc.DrawRectangle(x, y, cellsSize, cellsSize);
            }
        }
    }

    void ChessBoard::drawCoordinates(wxDC &dc)
    {
        auto size = getShortestSize();
        auto cellsSize = size * 1.0 / 9.0;
        auto fontSize = cellsSize * 0.25;

        wxColour coordinatesColor(255, 199, 0);
        wxFont coordinatesFont;
        coordinatesFont.SetPointSize(fontSize);
        coordinatesFont = coordinatesFont.Bold();

        dc.SetFont(coordinatesFont);
        dc.SetTextForeground(coordinatesColor);
        dc.SetTextBackground(wxNullColour);

        const char LETTER_A = 'a';
        for (auto col = 0; col < 8; col++)
        {
            auto x = cellsSize * (0.9 + col);
            auto y1 = cellsSize * 0.05;
            auto y2 = cellsSize * 8.45;

            auto file = _reversed ? 7 - col : col;
            auto value = LETTER_A + file;
            auto text = wxString::FromAscii(value);

            dc.DrawText(text, x, y1);
            dc.DrawText(text, x, y2);
        }

        const char DIGIT_1 = '1';
        for (auto row = 0; row < 8; row++)
        {
            auto y = cellsSize * (0.8 + row);
            auto x1 = cellsSize * 0.15;
            auto x2 = cellsSize * 8.6;

            auto rank = _reversed ? row : 7 - row;
            auto value = DIGIT_1 + rank;
            auto text = wxString::FromAscii(value);

            dc.DrawText(text, x1, y);
            dc.DrawText(text, x2, y);
        }
    }

    void ChessBoard::drawPieces(wxDC &dc)
    {
        auto size = getShortestSize();
        auto cellsSize = size * 1.0 / 9.0;

        for (auto row = 0; row < 8; row++)
        {
            for (auto col = 0; col < 8; col++)
            {
                auto file = _reversed ? 7 - col : col;
                auto rank = _reversed ? row : 7 - row;

                auto pieceFen = _boardLogic.getPieceFenAt(file, rank);
                auto isOccupiedCell = pieceFen != ' ';
                if (isOccupiedCell)
                {
                    auto x = (int)cellsSize * (col + 0.5);
                    auto y = (int)cellsSize * (row + 0.5);
                    auto bitmap = getPieceBitmap(pieceFen);

                    dc.DrawBitmap(bitmap, x, y, true);
                }
            }
        }
    }

    void ChessBoard::drawPlayerTurn(wxDC &dc)
    {
        auto size = getShortestSize();
        auto cellsSize = size * 1.0 / 9.0;
        auto whiteTurn = _boardLogic.isWhiteTurn();
        auto color = whiteTurn ? *wxWHITE : *wxBLACK;

        auto x = (int)(cellsSize * 8.70);
        auto y = (int)(cellsSize * 8.70);
        auto radius = (int)(cellsSize * 0.20);

        dc.SetBrush(wxBrush(color));
        dc.DrawCircle(x, y, radius);
    }

    void ChessBoard::loadImages(int size)
    {
        _whitePawnSvg = nsvgParse(Chess_plt45_svg, "px", 45.0f);
        _whiteKnightSvg = nsvgParse(Chess_nlt45_svg, "px", 45.0f);
        _whiteBishopSvg = nsvgParse(Chess_blt45_svg, "px", 45.0f);
        _whiteRookSvg = nsvgParse(Chess_rlt45_svg, "px", 45.0f);
        _whiteQueenSvg = nsvgParse(Chess_qlt45_svg, "px", 45.0f);
        _whiteKingSvg = nsvgParse(Chess_klt45_svg, "px", 45.0f);

        _blackPawnSvg = nsvgParse(Chess_pdt45_svg, "px", 45.0f);
        _blackKnightSvg = nsvgParse(Chess_ndt45_svg, "px", 45.0f);
        _blackBishopSvg = nsvgParse(Chess_bdt45_svg, "px", 45.0f);
        _blackRookSvg = nsvgParse(Chess_rdt45_svg, "px", 45.0f);
        _blackQueenSvg = nsvgParse(Chess_qdt45_svg, "px", 45.0f);
        _blackKingSvg = nsvgParse(Chess_kdt45_svg, "px", 45.0f);

        updateImagesSize(size);
    }

    void ChessBoard::updateImagesSize(int size)
    {
        auto cellsSize = (int)(size * 1.0 / 9.0);

        _whitePawnBitmap = generateBitmapFromSvgData(_whitePawnSvg, cellsSize);
        _whiteKnightBitmap = generateBitmapFromSvgData(_whiteKnightSvg, cellsSize);
        _whiteBishopBitmap = generateBitmapFromSvgData(_whiteBishopSvg, cellsSize);
        _whiteRookBitmap = generateBitmapFromSvgData(_whiteRookSvg, cellsSize);
        _whiteQueenBitmap = generateBitmapFromSvgData(_whiteQueenSvg, cellsSize);
        _whiteKingBitmap = generateBitmapFromSvgData(_whiteKingSvg, cellsSize);

        _blackPawnBitmap = generateBitmapFromSvgData(_blackPawnSvg, cellsSize);
        _blackKnightBitmap = generateBitmapFromSvgData(_blackKnightSvg, cellsSize);
        _blackBishopBitmap = generateBitmapFromSvgData(_blackBishopSvg, cellsSize);
        _blackRookBitmap = generateBitmapFromSvgData(_blackRookSvg, cellsSize);
        _blackQueenBitmap = generateBitmapFromSvgData(_blackQueenSvg, cellsSize);
        _blackKingBitmap = generateBitmapFromSvgData(_blackKingSvg, cellsSize);
    }

    // Inspired by https://forums.wxwidgets.org/viewtopic.php?t=44708 (wxWidgets forum)
    wxBitmap ChessBoard::generateBitmapFromSvgData(NSVGimage *svgData, int bitmapSize)
    {
        wxBitmap bitmap = wxNullBitmap;

        bitmap.Create(bitmapSize, bitmapSize, 32);

        NSVGrasterizer *rast = nsvgCreateRasterizer();
        unsigned char *image_buffer = (unsigned char *)malloc(bitmapSize * bitmapSize * 4);

        float scale = (float)bitmapSize / svgData->width;
        nsvgRasterize(rast, svgData, 0, 0, scale, image_buffer, bitmapSize, bitmapSize, bitmapSize * 4);

        wxAlphaPixelData bmdata(bitmap);
        wxAlphaPixelData::Iterator dst(bmdata);

        unsigned char *source_data = image_buffer;
        for (int y = 0; y < bitmap.GetHeight(); y++)
        {
            dst.MoveTo(bmdata, 0, y);
            for (int x = 0; x < bitmap.GetWidth(); x++)
            {
                const unsigned char alpha = source_data[3];
                dst.Blue() = source_data[2] * alpha / 255;
                dst.Green() = source_data[1] * alpha / 255;
                dst.Red() = source_data[0] * alpha / 255;
                dst.Alpha() = alpha;
                dst++;
                source_data += 4;
            }
        }
        nsvgDeleteRasterizer(rast);
        free(image_buffer);

        return bitmap;
    }

    int ChessBoard::getShortestSize() const
    {
        auto bothSides = GetSize();
        auto width = bothSides.GetWidth();
        auto height = bothSides.GetHeight();

        return width < height ? width : height;
    }

    wxBitmap ChessBoard::getPieceBitmap(char pieceFen)
    {
        switch (pieceFen)
        {
        case 'P':
            return _whitePawnBitmap;
        case 'N':
            return _whiteKnightBitmap;
        case 'B':
            return _whiteBishopBitmap;
        case 'R':
            return _whiteRookBitmap;
        case 'Q':
            return _whiteQueenBitmap;
        case 'K':
            return _whiteKingBitmap;
        case 'p':
            return _blackPawnBitmap;
        case 'n':
            return _blackKnightBitmap;
        case 'b':
            return _blackBishopBitmap;
        case 'r':
            return _blackRookBitmap;
        case 'q':
            return _blackQueenBitmap;
        case 'k':
            return _blackKingBitmap;

        default:
            std::string errorMessage = "Not a piece fen : ";
            errorMessage += pieceFen;
            errorMessage += " !";

            throw errorMessage;
            break;
        }
    }

    void ChessBoard::leftMouseButtonDownEvent(wxMouseEvent &evt) {
        _dndInProgress = true;
        std::cout << "Start drag" << std::endl;
    }

    void ChessBoard::leftMouseButtonUpEvent(wxMouseEvent &evt) {
        _dndInProgress = false;
        std::cout << "End drag" << std::endl;
    }

    void ChessBoard::mouseButtonMotionEvent(wxMouseEvent &evt) {
        if (_dndInProgress) {
            std::cout << "During drag" << std::endl;
        }
    }

    wxBEGIN_EVENT_TABLE(ChessBoard, wxPanel)
        EVT_PAINT(ChessBoard::paintEvent)
        EVT_LEFT_DOWN(ChessBoard::leftMouseButtonDownEvent)
        EVT_LEFT_UP(ChessBoard::leftMouseButtonUpEvent)
        EVT_MOTION(ChessBoard::mouseButtonMotionEvent)
    wxEND_EVENT_TABLE()
} // namespace loloof64