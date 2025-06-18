#include "piece.h"
#include "main.h"

std::vector<XiangQiPiece> pieces;
std::map<std::string, sf::Texture> pieceTextures;

// 棋盘逻辑格子转化为窗口像素坐标
sf::Vector2f boardToPixel(int row, int col)
{
    return
    {
        boardOrigin.x + col * gridSpacing,
        boardOrigin.y + row * gridSpacing
    };
}

// 窗口像素坐标转化为棋盘逻辑格子
sf::Vector2i pixelToBoard(int x, int y)
{
    int col = static_cast<int>((x - boardOrigin.x + gridSpacing / 2) / gridSpacing);
    int row = static_cast<int>((y - boardOrigin.y + gridSpacing / 2) / gridSpacing);

    // 防止越界
    if (row < 0 || row >= ROWS || col < 0 || col >= COLS)
        return { -1, -1 };

    return { row, col };
}

// 棋盘坐标
sf::Vector2f boardPixels[ROWS][COLS];

// 初始化坐标，不用重复计算
void initBoardPixels()
{
    for (int row = 0; row < 10; ++row)
        for (int col = 0; col < 9; ++col)
            boardPixels[row][col] = boardToPixel(row, col);
}

XiangQiPiece::XiangQiPiece() : type(Type::NONE), color(PieceColor::NONE), position(-1, -1) {}
XiangQiPiece::XiangQiPiece(Type t, PieceColor c) : type(t), color(c), position(-1, -1) {}
XiangQiPiece::Type XiangQiPiece::getType() const { return type; }
PieceColor XiangQiPiece::getColor() const { return color; }
bool XiangQiPiece::isEmpty() const { return type == Type::NONE; }

void XiangQiPiece::setPosition(int row, int col)
{
    position = { col, row };
    sprite.setPosition(col * 60.f, row * 60.f);  // 每格60像素
}

sf::Vector2i XiangQiPiece::getPosition() const
{
    return position;
}

const sf::Sprite& XiangQiPiece::getSprite() const
{
    return sprite;
}

void XiangQiPiece::setSprite(const sf::Texture& texture, float x, float y)
{
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
}


// 加载棋子贴图
void loadPieceTextures()
{
    std::vector<std::string> names =
    {
        "Wang", "Shi", "Xiang", "Ma", "Ju", "Pao", "Bing"
    };
    for (const auto& name : names)
    {
        sf::Texture texRed, texBlack;
        texRed.loadFromFile("./Picture/RED_" + name + ".png");
        texBlack.loadFromFile("./Picture/BLACK_" + name + ".png");
        pieceTextures["RED_" + name] = texRed;
        pieceTextures["BLACK_" + name] = texBlack;
    }
}


// 初始化棋子
void initPieces()
{
    for (const auto& info : initialLayout)
    {
        XiangQiPiece piece(info.type, info.color);
        piece.setPosition(info.row, info.col);

        sf::Vector2f pixel = boardPixels[info.row][info.col];

        std::string prefix = (info.color == PieceColor::RED) ? "RED_" : "BLACK_";
        std::string name;
        switch (info.type)
        {
        case XiangQiPiece::Type::Wang:   name = "Wang"; break;
        case XiangQiPiece::Type::Shi:    name = "Shi"; break;
        case XiangQiPiece::Type::Xiang:  name = "Xiang"; break;
        case XiangQiPiece::Type::Ma:     name = "Ma"; break;
        case XiangQiPiece::Type::Ju:     name = "Ju"; break;
        case XiangQiPiece::Type::Pao:    name = "Pao"; break;
        case XiangQiPiece::Type::Bing:   name = "Bing"; break;
        default:                         name = "NONE"; break;
        }

        piece.setSprite(pieceTextures[prefix + name], pixel.x, pixel.y);
        pieces.push_back(piece);
    }
}


// 该数组定义棋子在棋盘的初始位置
std::vector<PieceInitInfo> initialLayout = {
    { XiangQiPiece::Type::Ju,    PieceColor::RED,   9, 0 },
    { XiangQiPiece::Type::Ma,    PieceColor::RED,   9, 1 },
    { XiangQiPiece::Type::Xiang, PieceColor::RED,   9, 2 },
    { XiangQiPiece::Type::Shi,   PieceColor::RED,   9, 3 },
    { XiangQiPiece::Type::Wang,  PieceColor::RED,   9, 4 },
    { XiangQiPiece::Type::Shi,   PieceColor::RED,   9, 5 },
    { XiangQiPiece::Type::Xiang, PieceColor::RED,   9, 6 },
    { XiangQiPiece::Type::Ma,    PieceColor::RED,   9, 7 },
    { XiangQiPiece::Type::Ju,    PieceColor::RED,   9, 8 },
    { XiangQiPiece::Type::Pao,   PieceColor::RED,   7, 1 },
    { XiangQiPiece::Type::Pao,   PieceColor::RED,   7, 7 },
    { XiangQiPiece::Type::Bing,  PieceColor::RED,   6, 0 },
    { XiangQiPiece::Type::Bing,  PieceColor::RED,   6, 2 },
    { XiangQiPiece::Type::Bing,  PieceColor::RED,   6, 4 },
    { XiangQiPiece::Type::Bing,  PieceColor::RED,   6, 6 },
    { XiangQiPiece::Type::Bing,  PieceColor::RED,   6, 8 },

    { XiangQiPiece::Type::Ju,    PieceColor::BLACK, 0, 0 },
    { XiangQiPiece::Type::Ma,    PieceColor::BLACK, 0, 1 },
    { XiangQiPiece::Type::Xiang, PieceColor::BLACK, 0, 2 },
    { XiangQiPiece::Type::Shi,   PieceColor::BLACK, 0, 3 },
    { XiangQiPiece::Type::Wang,  PieceColor::BLACK, 0, 4 },
    { XiangQiPiece::Type::Shi,   PieceColor::BLACK, 0, 5 },
    { XiangQiPiece::Type::Xiang, PieceColor::BLACK, 0, 6 },
    { XiangQiPiece::Type::Ma,    PieceColor::BLACK, 0, 7 },
    { XiangQiPiece::Type::Ju,    PieceColor::BLACK, 0, 8 },
    { XiangQiPiece::Type::Pao,   PieceColor::BLACK, 2, 1 },
    { XiangQiPiece::Type::Pao,   PieceColor::BLACK, 2, 7 },
    { XiangQiPiece::Type::Bing,  PieceColor::BLACK, 3, 0 },
    { XiangQiPiece::Type::Bing,  PieceColor::BLACK, 3, 2 },
    { XiangQiPiece::Type::Bing,  PieceColor::BLACK, 3, 4 },
    { XiangQiPiece::Type::Bing,  PieceColor::BLACK, 3, 6 },
    { XiangQiPiece::Type::Bing,  PieceColor::BLACK, 3, 8 },
};
