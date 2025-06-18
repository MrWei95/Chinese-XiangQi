
#ifndef __MAIN_H
#define __MAIN_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string.h>
#include <iostream>
#include <windows.h>

//#include <dwmapi.h>						// 需要链接 dwmapi.lib
//#pragma comment(lib, "dwmapi.lib")
//#pragma comment(lib, "uxtheme.lib")

using namespace sf;

/**		窗口默认参数		**/
#define		WINDOW_FPS					60
#define		WINDOW_TIME_PER_FRAME		0.16F
#define		MAIN_WINDOW_WIDTH				896
#define		MAIN_WINDOW_HEIGHT				950


/**		常用路径		**/
#define		SFML_DLL_PATH				"./"

// 程序状态（0：退出；1：运行）
extern char ProgramRun_Flag;

#endif
