#include <iostream>
#include "DataManager.h"
#include "MenuUI.h"
#include "GlobalDefine.h"
//#define NOMINMAX
//#ifdef _WIN32
//#include <Windows.h>
//void setConsoleUTF8() {
//    // 1. 设置控制台输入/输出编码为 UTF-8（65001）
//    if (!SetConsoleOutputCP(65001)) {
//        std::cerr << "设置输出编码失败！" << std::endl;
//    }
//    if (!SetConsoleCP(65001)) {
//        std::cerr << "设置输入编码失败！" << std::endl;
//    }
//
//    // 2. 设置控制台字体为支持中文的 UTF-8 字体（如“Consolas”或“微软雅黑”）
//    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//    if (hConsole == INVALID_HANDLE_VALUE) {
//        std::cerr << "获取控制台句柄失败！" << std::endl;
//        return;
//    }
//
//    CONSOLE_FONT_INFOEX fontInfo = { 0 };
//    fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX); // 必须初始化此成员
//    if (!GetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo)) {
//        std::cerr << "获取当前字体失败！" << std::endl;
//        return;
//    }
//
//    // 切换为支持中文的字体（确保系统中存在该字体）
//    wcscpy_s(fontInfo.FaceName, L"Consolas"); // 或 L"Microsoft YaHei"
//    if (!SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo)) {
//        std::cerr << "设置字体失败！" << std::endl;
//    }
//}
//#else
//void setConsoleUTF8() {}  // 非 Windows 系统无需处理
//#endif

int main() {
    //setConsoleUTF8();
    //// 初始化数据管理器
    DataManager dataManager;

    // 加载数据
    bool loadSuccess = dataManager.loadAllData(
        GlobalConst::DEFAULT_EXPRESS_PATH,
        GlobalConst::DEFAULT_USER_PATH,
        GlobalConst::DEFAULT_STORAGE_PATH,
        GlobalConst::DEFAULT_ABNORMAL_PATH
    );

    if (!loadSuccess) {
        std::cout << "警告：数据加载失败，将使用空数据启动系统" << std::endl;
        system("pause");
    }

    // 初始化菜单UI并显示主菜单
    MenuUI menu(dataManager);
    menu.showMainMenu();

    // 程序退出前保存数据
    dataManager.saveAllData(
        GlobalConst::DEFAULT_EXPRESS_PATH,
        GlobalConst::DEFAULT_USER_PATH,
        GlobalConst::DEFAULT_STORAGE_PATH,
        GlobalConst::DEFAULT_ABNORMAL_PATH
    );

    return 0;
}