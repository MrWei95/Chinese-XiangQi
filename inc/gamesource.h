﻿#ifndef __GAMESOURCE_H
#define __GAMESOURCE_H

/**		纹理路径		**/
// 窗口图标
#define		WINDOW_ICON_PATH				"./icon/icon.png"

// 棋盘纹理
#define     BOARD_TEXTURE_PATH              "./Picture/board.png"

// 贴图坐标偏移
#define     PIECE_PIXELOFFSET               40
#define     SELECT_PIXELOFFSET              50


// 加载窗口图标
void SetWindowIcon(sf::RenderWindow& window_name, const std::string& iconPath);
// 创建实体
sf::Sprite CreateEntity(const std::string& entityname,
    const std::string& texturePath,
    const sf::Vector2f& position);


#endif
