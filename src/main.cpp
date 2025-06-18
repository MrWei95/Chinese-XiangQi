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

    // 程序主循环
    while (MainWindow.isOpen())
    {
        sf::Event event;
        while (MainWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                MainWindow.close();
        }
        MainWindow.clear();
        MainWindow.draw(Background_Sprite);      // 绘制棋盘背景

        // 绘制棋子
        for (const auto& piece : pieces)
        {
            MainWindow.draw(piece.getSprite());
        }

        MainWindow.display();
    }

    return 0;
}
