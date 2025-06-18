#include "main.h"
#include "gamesource.h"
#include <filesystem>
#include <map>

// 设置窗口图标
void SetWindowIcon(sf::RenderWindow& window_name, const std::string& iconPath)
{
    sf::Image icon;
    if (icon.loadFromFile(iconPath))
    {
        window_name.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }
    else
    {
        std::cerr << "加载窗口图标失败：" << iconPath << std::endl;
    }
}

// 创建实体
sf::Sprite CreateEntity(const std::string& entityname,
                        const std::string& texturePath,
                        const sf::Vector2f& position)
{
    static std::map<std::string, sf::Texture> textureCache;

    if (textureCache.find(entityname) == textureCache.end())
    {
        sf::Texture texture;
        if (!texture.loadFromFile(texturePath))
        {
            std::cerr << "加载图像失败: " << texturePath << std::endl;
            exit(-1);
        }
        textureCache[entityname] = std::move(texture);
    }

    sf::Sprite sprite;
    sprite.setTexture(textureCache[entityname]);
    sprite.setPosition(position);
    return sprite;
}
