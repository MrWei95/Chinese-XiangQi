#ifndef __PIECE_H
#define __PIECE_H

#include <SFML/Graphics.hpp>
#include "gamesource.h"

// ==============================
// 棋子基本参数
// ==============================

// 中国象棋棋盘 10行 9列
const int ROWS = 10;
const int COLS = 9;
const float gridSpacing = 90;					// 格点间隔，棋盘每行/列的格子像素距离

// 棋盘左上角第一个点的像素坐标
const sf::Vector2f boardOrigin(88 - PIECE_PIXELOFFSET, 70 - PIECE_PIXELOFFSET);     

sf::Vector2f boardToPixel(int row, int col);            // 逻辑格子坐标 → 像素坐标
sf::Vector2i pixelToBoard(int x, int y);                // 像素坐标 → 棋盘格子

extern sf::Vector2f boardPixels[ROWS][COLS];            // 棋盘坐标
void initBoardPixels();

// 棋子颜色枚举
enum class PieceColor
{
    NONE,
    RED,
    BLACK
};

// 棋子 类
class XiangQiPiece
{
public:
    enum class Type
    {
        NONE,
        Wang,           // 将帅
        Shi,            // 士
        Xiang,          // 相
        Ma,             // 马
        Ju,             // 车
        Pao,            // 炮
        Bing            // 兵
    };

    XiangQiPiece();
    XiangQiPiece(Type type, PieceColor color);

    Type getType() const;
    PieceColor getColor() const;
    bool isEmpty() const;

    void setPosition(int row, int col);
    sf::Vector2i getPosition() const;

    const sf::Sprite& getSprite() const;
    void setSprite(const sf::Texture& texture, float x, float y);

private:
    Type type;
    PieceColor color;
    sf::Vector2i position;
    sf::Sprite sprite;
};

// 棋子布局记录
struct PieceInitInfo {
    XiangQiPiece::Type type;
    PieceColor color;
    int row;
    int col;
};

extern std::vector<XiangQiPiece> pieces;
extern std::map<std::string, sf::Texture> pieceTextures;
extern std::vector<PieceInitInfo> initialLayout;

void loadPieceTextures();       // 加载棋子贴图
void initPieces();              // 初始化棋子


// ==============================
// 选中效果
// ==============================

class SelectionMarker
{
public:
    // 初始化（加载图片）
    bool load(const std::string& filepath);

    // 设置位置到指定棋子坐标（棋子左上角坐标）
    void setPosition(const sf::Vector2f& pieceTopLeft);

    // 设置是否显示
    void setVisible(bool visible);

    // 渲染
    void draw(sf::RenderWindow& window) const;

private:
    sf::Texture texture;
    sf::Sprite sprite;
    bool isVisible = false;
};

#endif
