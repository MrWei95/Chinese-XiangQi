// 中国象棋 by MrWei95
#include "main.h"

// 程序状态（0：退出；1：运行）
char ProgramRun_Flag = 1;

// 假设每一帧的时间为 16 毫秒（60FPS）
float deltaTime = GAME_TIME_PER_FRAME;

int main()
{
    sf::RenderWindow MainWindow(sf::VideoMode(896, 950), "XiangQi", sf::Style::Titlebar | sf::Style::Close);
    // 设置窗口标题为中文（使用 Windows API）
    SetWindowTextW(MainWindow.getSystemHandle(), L"中国象棋");

    MainWindow.setFramerateLimit(60);
    MainWindow.setVerticalSyncEnabled(true);
    
    // 绘制窗口图标
    sf::Image MainWindow_icon;
    if (MainWindow_icon.loadFromFile("./icon/icon.png"))
    {
        MainWindow.setIcon(MainWindow_icon.getSize().x, MainWindow_icon.getSize().y, MainWindow_icon.getPixelsPtr());
    }
    else
    {
        std::cerr << "加载图标失败：resource/icon" << std::endl;
    }

    // 绘制棋盘背景
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("Picture/board.png"))
    {
        std::cerr << "加载背景失败: resource/background.png\n";
        return -1;
    }
    // 创建背景精灵
    sf::Sprite backgroundSprite(backgroundTexture);
    // 设置背景大小为窗口尺寸（拉伸填满）
    sf::Vector2u textureSize = backgroundTexture.getSize();
    sf::Vector2u windowSize = MainWindow.getSize();
    backgroundSprite.setScale(
        float(windowSize.x) / textureSize.x,
        float(windowSize.y) / textureSize.y
    );

    while (MainWindow.isOpen())
    {
        sf::Event event;
        while (MainWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                MainWindow.close();
        }
        MainWindow.clear();

        MainWindow.draw(backgroundSprite); // 绘制背景
        MainWindow.display();
    }

    return 0;
}
