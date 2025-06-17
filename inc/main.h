
#ifndef __MAIN_H
#define __MAIN_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string.h>
#include <iostream>
#include <windows.h>
#include <filesystem>

//#include <dwmapi.h>						// 需要链接 dwmapi.lib
//#pragma comment(lib, "dwmapi.lib")
//#pragma comment(lib, "uxtheme.lib")

using namespace sf;

/**		游戏默认参数		**/
#define		GAME_FPS					60
#define		GAME_TIME_PER_FRAME			0.16F

/**		常用路径		**/
#define		SFML_DLL_PATH				"./"
#define		GAME_ICON_PATH				"./icon/icon.bmp"


// 程序状态（0：退出；1：运行）
extern char ProgramRun_Flag;


#endif
