#include "ThcPosition.h"

#include <vector>
#include <cctype>
#include <string>
#include <algorithm>

// https://stackoverflow.com/a/24315631/662618
// CC BY-SA 3.0
static inline void ReplaceAll(std::string &str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
}

namespace loloof64 {

    ThcPosition::ThcPosition(std::string fen) : IPosition()
    {
        _position = thc::ChessRules();
        _recordedPositions = std::map<std::string, int>();
        auto success = _position.Forsyth(fen.c_str());
        if (!success) throw IllegalPositionException();
    }

    std::string ThcPosition::getFen() const
    {
        auto copy = _position;
        return copy.ForsythPublish();
    }

    bool ThcPosition::isWhiteTurn() const
    {
        return _position.WhiteToPlay();
    }

    char ThcPosition::getPieceFenAt(int file, int rank) const
    {
        if (file < 0 || file > 7) throw IllegalCoordinate(file, rank);
        if (rank < 0 || rank > 7) throw IllegalCoordinate(file, rank);

        auto squareIndex = 8*(7-rank) + file;
        return _position.squares[squareIndex];
    }

    bool ThcPosition::isLegalMove(int startFile, int startRank, int endFile, int endRank) const
    {
        std::string moveStr;
        char startFileChar = 97 + startFile;
        char startRankChar = 49 + startRank;
        char endFileChar = 97 + endFile;
        char endRankChar = 49 + endRank;

        moveStr += startFileChar;
        moveStr += startRankChar;
        moveStr += endFileChar;
        moveStr += endRankChar;
        moveStr += 'q';

        thc::ChessRules copy = _position;
        thc::Move moveToTest;
        moveToTest.TerseIn(&copy, moveStr.c_str());

        return moveToTest.NaturalOut(&copy) != std::string("--");
    }

    bool ThcPosition::isPromotionMove(int startFile, int startRank, int endFile, int endRank) const
    {
        std::string moveStr;
        char startFileChar = 97 + startFile;
        char startRankChar = 49 + startRank;
        char endFileChar = 97 + endFile;
        char endRankChar = 49 + endRank;

        moveStr += startFileChar;
        moveStr += startRankChar;
        moveStr += endFileChar;
        moveStr += endRankChar;
        moveStr += 'q';

        thc::ChessRules copy = _position;
        thc::Move moveToTest;
        moveToTest.TerseIn(&copy, moveStr.c_str());

        const auto isLegal = moveToTest.NaturalOut(&copy) != std::string("--");

        if (! isLegal) return false;

        const auto promotionsSpecials = std::vector<thc::SPECIAL>{
            thc::SPECIAL::SPECIAL_PROMOTION_QUEEN,
            thc::SPECIAL::SPECIAL_PROMOTION_ROOK,
            thc::SPECIAL::SPECIAL_PROMOTION_BISHOP,
            thc::SPECIAL::SPECIAL_PROMOTION_KNIGHT
        };

        auto isPromotion = false;
        for (auto promotionToTest: promotionsSpecials)
        {
            if (moveToTest.special == promotionToTest) isPromotion = true;
        }

        return isPromotion;
    }

    std::string ThcPosition::makeMove(int startFile, int startRank, int endFile, int endRank, char promotionFen)
    {
        std::string moveStr;
        char startFileChar = 97 + startFile;
        char startRankChar = 49 + startRank;
        char endFileChar = 97 + endFile;
        char endRankChar = 49 + endRank;

        moveStr += startFileChar;
        moveStr += startRankChar;
        moveStr += endFileChar;
        moveStr += endRankChar;
        if (promotionFen) moveStr += tolower(promotionFen);

        thc::ChessRules copy =_position;
        thc::Move moveToTest;
        moveToTest.TerseIn(&copy, moveStr.c_str());

        const auto isLegal = moveToTest.NaturalOut(&copy) != std::string("--");

        if (! isLegal) throw IllegalMoveException();
        copy.PlayMove(moveToTest);

        _position = copy;
        auto positionToRecord = _position.ForsythPublish();
        // Strip both moves count from the position
        auto previous = positionToRecord.find(" ");
        auto current = previous;
        for (auto partIndex = 0; partIndex < 4; partIndex++)
        {
            previous = current+1;
            current = positionToRecord.find(" ", previous);
        }
        positionToRecord = positionToRecord.substr(0, current-2);
        _recordedPositions[positionToRecord]++;

        return copy.ForsythPublish();
    }
}

bool loloof64::ThcPosition::isCheckmate() const
{
    thc::TERMINAL terminalStatus;
    auto copy = _position;
    copy.Evaluate(terminalStatus);

    return (terminalStatus == thc::TERMINAL::TERMINAL_WCHECKMATE)
            || (terminalStatus == thc::TERMINAL_BCHECKMATE);
}

bool loloof64::ThcPosition::isStalemate() const
{
    thc::TERMINAL terminalStatus;
    auto copy = _position;
    copy.Evaluate(terminalStatus);

    return (terminalStatus == thc::TERMINAL::TERMINAL_WSTALEMATE)
            || (terminalStatus == thc::TERMINAL_BSTALEMATE);
}

bool loloof64::ThcPosition::isFiftyMovesRuleDraw() const
{
    // Not relying on the ChessRules class implementation
    // because not well suited
    const auto fen = getFen();

    auto halfMovesCount = -1;
    auto previous = fen.find(" ");
    auto current = previous;
    for (auto partIndex = 0; partIndex < 4; partIndex++)
    {
        previous = current+1;
        current = fen.find(" ", previous);
    }

    auto halfMovesPart = fen.substr(previous, current);
    halfMovesCount = std::stoi(std::string(halfMovesPart));

    return halfMovesCount >= 50;
}

bool loloof64::ThcPosition::isInsuficientMaterialDraw() const
{
    // Not relying on the ChessRules class implementation
    // because not well suited
    // Also, here not testing the case K+B / K+B where the bishops are
    // on the same color.

    const auto whitePiecesToKeep = std::vector<char>{'P', 'N', 'B', 'R', 'Q'};
    const auto blackPiecesToKeep = std::vector<char>{'p', 'n', 'b', 'r', 'q'};

    std::vector<char> whitePiecesExceptKing;
    std::vector<char> blackPiecesExceptKing;

    for (auto rank = 0; rank < 8; rank++)
    {
        for (auto file = 0; file < 8; file++)
        {
            auto piece = getPieceFenAt(file, rank);
            auto isAPieceToKeepForWhite = std::find(whitePiecesToKeep.begin(), whitePiecesToKeep.end(), piece) != whitePiecesToKeep.end();
            auto isAPieceToKeepForBlack = std::find(blackPiecesToKeep.begin(), blackPiecesToKeep.end(), piece) != blackPiecesToKeep.end();
            if (isAPieceToKeepForWhite) whitePiecesExceptKing.push_back(piece);
            else if (isAPieceToKeepForBlack) blackPiecesExceptKing.push_back(piece);
        }
    }

    const auto loneKings = whitePiecesExceptKing.size() == 0 && blackPiecesExceptKing.size() == 0;
    if (loneKings) return true;

    const auto loneKnightOrBishop =
            (blackPiecesExceptKing.size() == 0 && whitePiecesExceptKing.size() == 1 && whitePiecesExceptKing[0] == 'N') ||
            (blackPiecesExceptKing.size() == 0 && whitePiecesExceptKing.size() == 1 && whitePiecesExceptKing[0] == 'B') ||
            (whitePiecesExceptKing.size() == 0 && blackPiecesExceptKing.size() == 1 && blackPiecesExceptKing[0] == 'n') ||
            (whitePiecesExceptKing.size() == 0 && blackPiecesExceptKing.size() == 1 && blackPiecesExceptKing[0] == 'b');
    if (loneKnightOrBishop) return true;

    return false;
}

bool loloof64::ThcPosition::isThreeFoldRepetitionsDraw() const
{
    // Not relying on the ChessRules class implementation
    // because not well suited

    auto positionCopy = _position;

    auto positionWithStrippedMoveCounts = positionCopy.ForsythPublish();
    auto previous = positionWithStrippedMoveCounts.find(" ");
    unsigned long current = previous;
    for (auto partIndex = 0; partIndex < 4; partIndex++)
    {
        previous = current+1;
        current = positionWithStrippedMoveCounts.find(" ", previous);
    }
    positionWithStrippedMoveCounts = positionWithStrippedMoveCounts.substr(0, current-2);

    auto isThreeFold = _recordedPositions.at(positionWithStrippedMoveCounts) >= 3;
    return isThreeFold;
}

std::string loloof64::ThcPosition::getMoveSan(int startFile, int startRank, int endFile, int endRank, char promotionFen) const
{
    std::string moveStr;
    char startFileChar = 97 + startFile;
    char startRankChar = 49 + startRank;
    char endFileChar = 97 + endFile;
    char endRankChar = 49 + endRank;

    moveStr += startFileChar;
    moveStr += startRankChar;
    moveStr += endFileChar;
    moveStr += endRankChar;
    moveStr += tolower(promotionFen);

    thc::ChessRules copy = _position;
    thc::Move moveToTest;
    moveToTest.TerseIn(&copy, moveStr.c_str());

    const auto moveNotation = moveToTest.NaturalOut(&copy);
    const auto isLegal = moveNotation != std::string("--");

    if (! isLegal) throw IllegalMoveException();
    return std::string(moveNotation);
}

std::string loloof64::ThcPosition::getMoveFan(int startFile, int startRank, int endFile, int endRank, char promotionFen) const
{
    const auto whiteTurn = isWhiteTurn();
    const auto knightReplacement = whiteTurn ? std::string("\u2658") : std::string("\u265E");
    const auto bishopReplacement = whiteTurn ? std::string("\u2657") : std::string("\u265D");
    const auto rookReplacement = whiteTurn ? std::string("\u2656") : std::string("\u265C");
    const auto queenReplacement = whiteTurn ? std::string("\u2655") : std::string("\u265B");
    const auto kingReplacement = whiteTurn ? std::string("\u2654") : std::string("\u265A");

    auto moveFan = getMoveSan(startFile, startRank, endFile, endRank, promotionFen);
    ReplaceAll(moveFan, "N", knightReplacement);
    ReplaceAll(moveFan, "B", bishopReplacement);
    ReplaceAll(moveFan, "R", rookReplacement);
    ReplaceAll(moveFan, "Q", queenReplacement);
    ReplaceAll(moveFan, "K", kingReplacement);

    return moveFan;
}
