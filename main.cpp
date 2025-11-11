#include <iostream>
#include "DataManager.h"
#include "MenuUI.h"
#include "GlobalDefine.h"

int main() {
    DataManager dataManager;
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