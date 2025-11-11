#ifndef MENUUI_H
#define MENUUI_H

#include "DataManager.h"

class MenuUI {
public:
    MenuUI(DataManager& dm) : dataManager(dm) {}

    // 显示主菜单（角色选择）
    void showMainMenu();

private:
    DataManager& dataManager;  // 关联数据管理器
    const std::string EXPRESS_FILE = GlobalConst::DEFAULT_EXPRESS_PATH;
    const std::string USER_FILE = GlobalConst::DEFAULT_USER_PATH;
    const std::string STORAGE_FILE = GlobalConst::DEFAULT_STORAGE_PATH;
    const std::string ABNORMAL_FILE = GlobalConst::DEFAULT_ABNORMAL_PATH;
    const std::string LOG_FILE = GlobalConst::DEFAULT_LOG_PATH;

    /************************ 管理员菜单 ************************/
    bool adminLogin();                  // 管理员登录
    void showAdminMainMenu();           // 管理员主菜单
    void showExpressManageMenu();       // 快递管理子菜单
    void showAbnormalManageMenu();      // 异常处理子菜单
    void showDataStatMenu();            // 数据统计子菜单
    void showSystemConfigMenu();        // 系统配置子菜单
    void showOperationLogs();           // 查看操作日志

    /************************ 用户菜单 ************************/
    void showUserMainMenu();            // 用户主菜单
    std::string userPhoneVerify();      // 用户手机号验证

    /************************ 快递业务处理 ************************/
    void handleExpressStockIn();        // 快递入库
    void handleExpressStockOut();       // 快递出库
    void handleExpressQuery();          // 快递查询
    void handleBulkExpressImport();     // 批量导入快递

    /************************ 异常业务处理 ************************/
    void markAbnormalExpress();         // 标记异常快递
    void handleAbnormalExpress();       // 处理异常快递
    void queryAbnormalRecords();        // 查询异常记录
    void clearHandledAbnormal();        // 清理已处理异常

    /************************ 统计与报表 ************************/
    void showRealTimeStats();           // 实时统计
    void showDateStats();               // 按日期统计
    void showCompanyStats();            // 按公司统计
    void showAbnormalStats();           // 异常统计
    void exportReport();                // 导出报表

    /************************ 系统配置 ************************/
    void manageStorageAreas();          // 管理存储区域
    void modifyPickCodeRule();          // 修改取件码规则
    void setOverdueDays();              // 设置逾期天数
    void changeAdminPassword();         // 修改管理员密码

    /************************ 用户业务处理 ************************/
    void queryUserInStockExpress(const std::string& phone); // 查询用户在库快递
    void queryUserPickHistory(const std::string& phone);    // 查询用户取件记录
    void submitAbnormalFeedback(const std::string& phone);  // 提交异常反馈

    /************************ 通用工具 ************************/
    int inputIntWithCheck(const std::string& prompt, int minVal, int maxVal); // 整数输入校验
    std::string inputStrWithTrim(const std::string& prompt);                  // 字符串输入去空格
    void showResultTip(bool isSuccess, const std::string& successMsg, const std::string& failMsg); // 结果提示
    void waitForKeyPress();                                                   // 等待按键
    void clearScreen();                                                       // 清空屏幕
};

#endif // MENUUI_H