// 中国象棋 by MrWei95
#include "main.h"
#include <filesystem>
#include <map>
#include "gamesource.h"
#include "piece.h"

// 程序状态（0：退出；1：运行）
char ProgramRun_Flag = 1;

// 每一帧的时间
float deltaTime = WINDOW_TIME_PER_FRAME;

std::string pieceTypeToString(XiangQiPiece::Type type)
{
    switch (type)
    {
    case XiangQiPiece::Type::Wang:   return "Wang";
    case XiangQiPiece::Type::Shi:    return "Shi";
    case XiangQiPiece::Type::Xiang:  return "Xiang";
    case XiangQiPiece::Type::Ma:     return "Ma";
    case XiangQiPiece::Type::Ju:     return "Ju";
    case XiangQiPiece::Type::Pao:    return "Pao";
    case XiangQiPiece::Type::Bing:   return "Bing";
    default:                         return "NONE";
    }
}

int main()
{
    // 这里窗口标题"XiangQi"是占位的
    // SFML似乎不能设置中文标题
    sf::RenderWindow MainWindow(sf::VideoMode(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT), 
                                "XiangQi", 
                                sf::Style::Titlebar | sf::Style::Close);
    // 设置窗口标题为中文（使用 Windows API）
    SetWindowTextW(MainWindow.getSystemHandle(), L"中国象棋");

    MainWindow.setFramerateLimit(WINDOW_FPS);       // 窗口帧数限制
    MainWindow.setVerticalSyncEnabled(true);        // 窗口垂直同步

    // 设置窗口图标
    SetWindowIcon(MainWindow, WINDOW_ICON_PATH);
    // 创建棋盘背景实体
    sf::Sprite Background_Sprite = CreateEntity("Background", BOARD_TEXTURE_PATH, { 0.f, 0.f });

    initBoardPixels();          // 预先计算好棋盘的每个交点坐标
    loadPieceTextures();        // 加载棋子贴图
    initPieces();               // 初始化棋子

    // 创建选中框对象并加载贴图
    SelectionMarker selector;
    if (!selector.load("./Picture/select.png"))
        return -1;
    int selectedPieceIndex = -1;                 // 当前选中的棋子索引，-1 表示无

    // 程序主循环
    while (MainWindow.isOpen())
    {
        sf::Event event;
        while (MainWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                MainWindow.close();

            // 棋子选中
            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(MainWindow);

                for (int i = 0; i < pieces.size(); ++i)
                {
                    const sf::FloatRect bounds = pieces[i].getSprite().getGlobalBounds();
                    if (bounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                    {
                        // 如果点击的是已选中棋子，取消选中
                        if (selectedPieceIndex == i)
                        {
                            selectedPieceIndex = -1;
                            selector.setVisible(false);
                        }
                        else
                        {
                            selectedPieceIndex = i;
                            selector.setVisible(true);
                            selector.setPosition(pieces[i].getSprite().getPosition());
                        }
                        break; // 已处理点击，不需要再循环
                    }
                }
            }
        }

        MainWindow.clear();
        MainWindow.draw(Background_Sprite);      // 绘制棋盘背景

        selector.draw(MainWindow);
        // 绘制棋子
        for (const auto& piece : pieces)
        {
            MainWindow.draw(piece.getSprite());
        }

        MainWindow.display();
    }

    return 0;
}
