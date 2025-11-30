#include "MenuUI.h"
#include "Utils.h"
#include "GlobalDefine.h"
#include <iostream>
#include <limits>
#include <iomanip>
using namespace std;
// 显示主菜单
void MenuUI::showMainMenu() {
    while (true) {
        clearScreen();
        std::cout << "==================== 菜鸟驿站物流管理系统 ====================" << std::endl;
        std::cout << "                      欢迎使用本系统                          " << std::endl;
        std::cout << "==============================================================" << std::endl;
        std::cout << "1. 管理员登录" << std::endl;
        std::cout << "2. 用户取件查询" << std::endl;
        std::cout << "3. 退出系统" << std::endl;
        std::cout << "==============================================================" << std::endl;

        int choice = inputIntWithCheck("请选择操作（1-3）：", 1, 3);
        switch (choice) {
        case 1:
            if (adminLogin()) {
                showAdminMainMenu();
            }
            else {
                showResultTip(false, "", "密码错误，登录失败！");
                waitForKeyPress();
            }
            break;
        case 2:
            showUserMainMenu();
            break;
        case 3:
            std::cout << "感谢使用，系统即将退出..." << std::endl;
            return;
        }
    }
}

// 管理员登录
bool MenuUI::adminLogin() {
    clearScreen();
    std::cout << "==================== 管理员登录 ====================" << std::endl;
    std::string password = inputStrWithTrim("请输入管理员密码：");
    // 实际项目中应使用加密验证
    return (password == GlobalConst::ADMIN_DEFAULT_PWD);
}

// 显示管理员主菜单
void MenuUI::showAdminMainMenu() {
    while (true) {
        clearScreen();
        std::cout << "==================== 管理员主菜单 ====================" << std::endl;
        std::cout << "1. 快递管理" << std::endl;
        std::cout << "2. 异常处理" << std::endl;
        std::cout << "3. 数据统计与报表" << std::endl;
        std::cout << "4. 系统配置" << std::endl;
        std::cout << "5. 操作日志" << std::endl;
        std::cout << "6. 返回上一级" << std::endl;
        std::cout << "======================================================" << std::endl;

        int choice = inputIntWithCheck("请选择操作（1-6）：", 1, 6);
        switch (choice) {
        case 1:
            showExpressManageMenu();
            break;
        case 2:
            showAbnormalManageMenu();
            break;
        case 3:
            showDataStatMenu();
            break;
        case 4:
            showSystemConfigMenu();
            break;
        case 5:
            showOperationLogs();
            break;
        case 6:
            return;
        }
    }
}

// 快递管理子菜单
void MenuUI::showExpressManageMenu() {
    while (true) {
        clearScreen();
        std::cout << "==================== 快递管理 ====================" << std::endl;
        std::cout << "1. 快递入库" << std::endl;
        std::cout << "2. 快递出库" << std::endl;
        std::cout << "3. 快递查询" << std::endl;
        std::cout << "4. 返回上一级" << std::endl;
        std::cout << "==================================================" << std::endl;

        int choice = inputIntWithCheck("请选择操作（1-4）：", 1, 5);
        switch (choice) {
        case 1:
            handleExpressStockIn();
            break;
        case 2:
            handleExpressStockOut();
            break;
        case 3:
            handleExpressQuery();
            break;
        case 4:
            return;
        }
    }
}

// 异常处理子菜单
void MenuUI::showAbnormalManageMenu() {
    while (true) {
        clearScreen();
        std::cout << "==================== 异常处理 ====================" << std::endl;
        std::cout << "1. 标记异常快递" << std::endl;
        std::cout << "2. 处理异常快递" << std::endl;
        std::cout << "3. 查询异常记录" << std::endl;
        std::cout << "4. 清理已处理异常" << std::endl;
        std::cout << "5. 返回上一级" << std::endl;
        std::cout << "==================================================" << std::endl;

        int choice = inputIntWithCheck("请选择操作（1-5）：", 1, 5);
        switch (choice) {
        case 1:
            markAbnormalExpress();
            break;
        case 2:
            handleAbnormalExpress();
            break;
        case 3:
            queryAbnormalRecords();
            break;
        case 4:
            clearHandledAbnormal();
            break;
        case 5:
            return;
        }
    }
}

// 数据统计与报表子菜单
void MenuUI::showDataStatMenu() {
    while (true) {
        clearScreen();
        std::cout << "==================== 数据统计与报表 ====================" << std::endl;
        std::cout << "1. 实时统计信息" << std::endl;
        std::cout << "2. 按日期统计" << std::endl;
        std::cout << "3. 按快递公司统计" << std::endl;
        std::cout << "4. 异常件统计" << std::endl;
        std::cout << "5. 返回上一级" << std::endl;
        std::cout << "========================================================" << std::endl;

        int choice = inputIntWithCheck("请选择操作（1-5）：", 1, 6);
        switch (choice) {
        case 1:
            showRealTimeStats();
            break;
        case 2:
            showDateStats();
            break;
        case 3:
            showCompanyStats();
            break;
        case 4:
            showAbnormalStats();
            break;
        case 5:
            return;
        }
    }
}

// 系统配置子菜单
void MenuUI::showSystemConfigMenu() {
    while (true) {
        clearScreen();
        std::cout << "==================== 系统配置 ====================" << std::endl;
        std::cout << "1. 管理存储区域" << std::endl;
        std::cout << "2. 修改取件码规则" << std::endl;
        std::cout << "3. 设置逾期天数" << std::endl;
        std::cout << "4. 修改管理员密码" << std::endl;
        std::cout << "5. 返回上一级" << std::endl;
        std::cout << "==================================================" << std::endl;

        int choice = inputIntWithCheck("请选择操作（1-5）：", 1, 5);
        switch (choice) {
        case 1:
            manageStorageAreas();
            break;
        case 2:
            modifyPickCodeRule();
            break;
        case 3:
            setOverdueDays();
            break;
        case 4:
            changeAdminPassword();
            break;
        case 5:
            return;
        }
    }
}

// 显示用户主菜单
void MenuUI::showUserMainMenu() {
    while (true) {
        clearScreen();
        std::cout << "==================== 用户取件服务 ====================" << std::endl;
        std::string phone = userPhoneVerify();
        if (phone.empty()) {
            waitForKeyPress();
            return;
        }

        std::cout << "登录成功！欢迎使用取件服务" << std::endl;
        std::cout << "1. 查询我的在库快递" << std::endl;
        std::cout << "2. 查询我的取件记录" << std::endl;
        std::cout << "3. 异常反馈" << std::endl;
        std::cout << "4. 退出" << std::endl;
        std::cout << "======================================================" << std::endl;

        int choice = inputIntWithCheck("请选择操作（1-4）：", 1, 4);
        switch (choice) {
        case 1:
            queryUserInStockExpress(phone);
            break;
        case 2:
            queryUserPickHistory(phone);
            break;
        case 3:
            submitAbnormalFeedback(phone);
            break;
        case 4:
            return;
        }
    }
}

// 用户手机号验证
std::string MenuUI::userPhoneVerify() {
    std::string phone = inputStrWithTrim("请输入您的手机号（用于查询快递）：");
    if (Utils::isValidPhone(phone)) {
        return phone;
    }

    showResultTip(false, "", "手机号格式不正确，请重新输入！");
    return "";
}

// 输入整数并校验
int MenuUI::inputIntWithCheck(const std::string& prompt, int minVal, int maxVal) {
    int input;
    while (true) {
        std::cout << prompt;
        if (std::cin >> input && input >= minVal && input <= maxVal) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return input;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "输入无效！请输入" << minVal << "-" << maxVal << "之间的整数。" << std::endl;
    }
}


 




// 输入字符串并去空格
std::string MenuUI::inputStrWithTrim(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return Utils::gbkToUtf8(Utils::trimString(input));
}

// 显示操作结果提示
void MenuUI::showResultTip(bool isSuccess, const std::string& successMsg, const std::string& failMsg) {
    if (isSuccess) {
        std::cout << "[成功] " << successMsg << std::endl;
    }
    else {
        std::cout << "[失败] " << failMsg << std::endl;
    }
}

// 等待用户按回车继续
void MenuUI::waitForKeyPress() {
    std::cout << "按回车键继续..." << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// 清空控制台屏幕
void MenuUI::clearScreen() {
    // 跨平台清屏实现
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void MenuUI::handleExpressStockIn() {
    clearScreen();
    std::cout << "==================== 快递入库 ====================" << std::endl;

    std::string expressId = inputStrWithTrim("请输入快递单号：");
    if (Utils::isEmptyString(expressId)) {
        showResultTip(false, "", "快递单号不能为空！");
        waitForKeyPress();
        return;
    }

    // 检查快递是否已存在
    Express existing = dataManager.getExpressByExpressId(expressId);
    if (!existing.getExpressId().empty()) {
        showResultTip(false, "", "该快递单号已存在！");
        waitForKeyPress();
        return;
    }

    std::string phone = inputStrWithTrim("请输入收件人手机号：");
    if (!Utils::isValidPhone(phone)) {
        showResultTip(false, "", "手机号格式不正确！");
        waitForKeyPress();
        return;
    }

    std::string company = inputStrWithTrim("请输入快递公司：");
    if (Utils::isEmptyString(company)) {
        showResultTip(false, "", "快递公司不能为空！");
        waitForKeyPress();
        return;
    }

    // 自动生成取件码
    std::string pickCode = Utils::generateUniquePickCode();
    std::cout << "自动生成取件码：" << pickCode << std::endl;

    // 选择存储区域
    std::string areaId = inputStrWithTrim("请输入存储区域（如A-1）：");
    Storage storage = dataManager.getStorageAreaByAreaId(areaId);
    if (storage.getAreaId().empty()) {
        showResultTip(false, "", "存储区域不存在！");
        waitForKeyPress();
        return;
    }

    if (storage.isFull()) {
        showResultTip(false, "", "该存储区域已满！");
        waitForKeyPress();
        return;
    }

    // 创建快递对象
    Express exp(expressId, pickCode, phone, company, Utils::getCurrentTimeStamp(), areaId, ExpressStatus::IN_STOCK);

    // 添加快递
    if (dataManager.addExpress(exp)) {
        // 分配到存储区域
        dataManager.assignExpressToStorage(areaId, expressId);

        // 关联用户
        dataManager.addOrUpdateUser(User(phone));

        showResultTip(true, "快递入库成功！取件码：" + pickCode, "");
    }
    else {
        showResultTip(false, "", "快递入库失败！");
    }

    waitForKeyPress();
}

void MenuUI::handleExpressStockOut() {
    clearScreen();
    std::cout << "==================== 快递出库 ====================" << std::endl;

    std::string pickCode = inputStrWithTrim("请输入取件码：");
    if (!Utils::isValidPickCode(pickCode)) {
        showResultTip(false, "", "取件码格式不正确！");
        waitForKeyPress();
        return;
    }

    // 查询快递
    Express exp = dataManager.getExpressByPickCode(pickCode);
    if (exp.getExpressId().empty()) {
        showResultTip(false, "", "未找到该取件码对应的快递！");
        waitForKeyPress();
        return;
    }

    if (exp.getStatus() != ExpressStatus::IN_STOCK) {
        showResultTip(false, "", "该快递状态异常，当前状态：" + Utils::utf8ToGbk(exp.getStatusString()));
        waitForKeyPress();
        return;
    }

    // 显示快递信息
    std::cout << "快递信息：" << std::endl;
    std::cout << "单号：" << exp.getExpressId() << std::endl;
    std::cout << "收件人：" << exp.getUserPhone() << std::endl;
    std::cout << "快递公司：" << Utils::utf8ToGbk(exp.getCompany()) << std::endl;
    std::cout << "存储位置：" << exp.getLocation() << std::endl;

    // 验证手机号
    std::string phoneSuffix = Utils::getPhoneSuffix(exp.getUserPhone());
    std::string inputSuffix = inputStrWithTrim("请输入收件人手机号后4位进行验证：");

    if (inputSuffix != phoneSuffix) {
        showResultTip(false, "", "手机号后4位验证失败！");
        waitForKeyPress();
        return;
    }

    // 执行出库操作
    if (dataManager.updateExpressStatus(exp.getExpressId(), ExpressStatus::PICKED)) {
        // 从存储区域移除
        dataManager.removeExpressFromStorage(exp.getLocation(), exp.getExpressId());

        // 添加用户取件记录
        dataManager.addUserExpressHistory(exp.getUserPhone(), exp.getExpressId());

        showResultTip(true, "快递出库成功！", "");
    }
    else {
        showResultTip(false, "", "快递出库失败！");
    }

    waitForKeyPress();
}

void MenuUI::handleExpressQuery() {
    clearScreen();
    std::cout << "==================== 快递查询 ====================" << std::endl;
    std::cout << "1. 按快递单号查询" << std::endl;
    std::cout << "2. 按取件码查询" << std::endl;
    std::cout << "3. 按手机号后4位查询" << std::endl;
    std::cout << "4. 按日期范围查询" << std::endl;

    int choice = inputIntWithCheck("请选择查询方式（1-4）：", 1, 4);
    std::list<Express> results;

    switch (choice) {
    case 1: {
        std::string expressId = inputStrWithTrim("请输入快递单号：");
        Express exp = dataManager.getExpressByExpressId(expressId);
        if (!exp.getExpressId().empty()) {
            results.push_back(exp);
        }
        break;
    }
    case 2: {
        std::string pickCode = inputStrWithTrim("请输入取件码：");
        Express exp = dataManager.getExpressByPickCode(pickCode);
        if (!exp.getExpressId().empty()) {
            results.push_back(exp);
        }
        break;
    }
    case 3: {
        std::string suffix = inputStrWithTrim("请输入手机号后4位：");
        results = dataManager.getExpressListByPhoneSuffix(suffix);
        break;
    }
    case 4: {
        std::string startDate = inputStrWithTrim("请输入开始日期（YYYY-MM-DD）：");
        std::string endDate = inputStrWithTrim("请输入结束日期（YYYY-MM-DD）：");
        results = dataManager.getExpressListByInTimeRange(startDate, endDate);
        break;
    }
    }

    // 显示查询结果
    std::cout << "查询结果：共 " << results.size() << " 条记录" << std::endl;
    if (!results.empty()) {
        std::cout << std::left << std::setw(20) << "单号"
            << std::setw(10) << "取件码"
            << std::setw(15) << "收件人"
            << std::setw(10) << "公司"
            << std::setw(20) << "入库时间"
            << std::setw(10) << "位置"
            << std::setw(5) << "状态" << std::endl;
        std::cout << std::string(90, '-') << std::endl;

        for (const auto& exp : results) {
            std::cout << std::left << std::setw(20) << exp.getExpressId()
                << std::setw(10) << exp.getPickCode()
                << std::setw(15) << exp.getUserPhone()
                << std::setw(10) << Utils::utf8ToGbk(exp.getCompany())
                << std::setw(20) << exp.getInTime()
                << std::setw(10) << exp.getLocation()
                << std::setw(10) << Utils::utf8ToGbk(exp.getStatusString()) << std::endl;
        }
    }

    waitForKeyPress();
}


void MenuUI::markAbnormalExpress() {
    clearScreen();
    std::cout << "==================== 标记异常快递 ====================" << std::endl;

    std::string expressId = inputStrWithTrim("请输入快递单号：");
    Express exp = dataManager.getExpressByExpressId(expressId);
    if (exp.getExpressId().empty()) {
        showResultTip(false, "", "未找到该快递单号！");
        waitForKeyPress();
        return;
    }
    std::list<Abnormal> abnormals = dataManager.getAllAbnormalRecords();

    auto it = std::find_if(abnormals.begin(), abnormals.end(),
        [&](const Abnormal& a) { return a.getExpressId() == expressId; });

    if (it == abnormals.end()) {
        std::cout << "1. 丢失" << std::endl;
        std::cout << "2. 错发" << std::endl;
        std::cout << "3. 逾期未取" << std::endl;
        int typeChoice = inputIntWithCheck("请选择异常类型（1-3）：", 1, 3);

        AbnormalType type;
        switch (typeChoice) {
        case 1: type = AbnormalType::LOST; break;
        case 2: type = AbnormalType::WRONG_DELIVER; break;
        case 3: type = AbnormalType::OVERDUE; break;
        default: type = AbnormalType::LOST;
        }

        // 生成异常记录ID
        std::string recordId = "AR" + Utils::getCurrentDate() + std::to_string(Utils::generateRandomInt(100, 999));

        // 创建异常记录
        Abnormal abnormal(recordId, expressId, type, Utils::getCurrentTimeStamp());

        if (dataManager.addAbnormalRecord(abnormal)) {
            showResultTip(true, "异常快递标记成功！记录ID：" + recordId, "");
        }
        else {
            showResultTip(false, "", "异常快递标记失败！");
        }
    }
    else cout << "已标记，请返回" << endl;
    waitForKeyPress();
}

void MenuUI::handleAbnormalExpress() {
    clearScreen();
    std::cout << "==================== 处理异常快递 ====================" << std::endl;

    std::string recordId = inputStrWithTrim("请输入异常记录ID：");
    std::list<Abnormal> abnormals = dataManager.getAllAbnormalRecords();

    auto it = std::find_if(abnormals.begin(), abnormals.end(),
        [&](const Abnormal& a) { return a.getRecordId() == recordId; });

    if (it == abnormals.end()) {
        showResultTip(false, "", "未找到该异常记录ID！");
        waitForKeyPress();
        return;
    }

    Abnormal abnormal = *it;
    if (abnormal.isHandled()) {
        showResultTip(false, "", "该异常记录已处理完成！");
        waitForKeyPress();
        return;
    }

    // 显示异常信息
    std::cout << "异常信息：" << std::endl;
    std::cout << "记录ID：" << abnormal.getRecordId() << std::endl;
    std::cout << "快递单号：" << abnormal.getExpressId() << std::endl;
    std::cout << "异常类型：" << Utils::utf8ToGbk(abnormal.getAbnormalTypeString()) << std::endl;
    std::cout << "创建时间：" << abnormal.getCreateTime() << std::endl;
    std::cout << "当前状态：" << Utils::utf8ToGbk(abnormal.getHandleStatusString()) << std::endl;

    std::string result = inputStrWithTrim("输入1为已处理，回车键返回\n请输入处理结果:");
    if (Utils::isEmptyString(result)) {
        showResultTip(false, "", "返回上一级");
        waitForKeyPress();
        return;
    }
    result = "已处理";
    if (dataManager.updateAbnormalHandleResult(recordId, result)) {
        showResultTip(true, "异常记录处理完成！", "");
    }
    else {
        showResultTip(false, "", "异常记录处理失败！");
    }

    waitForKeyPress();
}

void MenuUI::queryAbnormalRecords() {
    clearScreen();
    std::cout << "==================== 查询异常记录 ====================" << std::endl;
    std::cout << "1. 查看所有异常记录" << std::endl;
    std::cout << "2. 按类型查询" << std::endl;

    int choice = inputIntWithCheck("请选择查询方式（1-2）：", 1, 2);
    std::list<Abnormal> results;

    if (choice == 1) {
        results = dataManager.getAllAbnormalRecords();
    }
    else {
        std::cout << "1. 丢失" << std::endl;
        std::cout << "2. 错发" << std::endl;
        std::cout << "3. 逾期未取" << std::endl;
        int typeChoice = inputIntWithCheck("请选择异常类型（1-3）：", 1, 3);

        AbnormalType type;
        switch (typeChoice) {
        case 1: type = AbnormalType::LOST; break;
        case 2: type = AbnormalType::WRONG_DELIVER; break;
        case 3: type = AbnormalType::OVERDUE; break;
        default: type = AbnormalType::LOST;
        }

        results = dataManager.getAbnormalRecordsByType(type);
    }

    // 显示查询结果
    std::cout << "查询结果：共 " << results.size() << " 条记录" << std::endl;
    if (!results.empty()) {
        std::cout << std::left << std::setw(15) << "记录ID"
            << std::setw(20) << "快递单号"
            << std::setw(10) << "异常类型"
            << std::setw(20) << "创建时间"
            << std::setw(10) << "状态"
            << std::setw(20) << "处理结果" << std::endl;
        std::cout << std::string(95, '-') << std::endl;

        for (const auto& abn : results) {
            std::cout << std::left << std::setw(15) << abn.getRecordId()
                << std::setw(20) << abn.getExpressId()
                << std::setw(10) << Utils::utf8ToGbk( abn.getAbnormalTypeString())
                << std::setw(20) << abn.getCreateTime()
                << std::setw(10) << Utils::utf8ToGbk(abn.getHandleStatusString())
                << std::setw(20) << (abn.getHandleResult().length() > 18 ?
                    abn.getHandleResult().substr(0, 18) + "..." : abn.getHandleResult())
                << std::endl;
        }
    }

    waitForKeyPress();
}

void MenuUI::clearHandledAbnormal() {
    clearScreen();
    std::cout << "==================== 清理已处理异常 ====================" << std::endl;

    int choice = inputIntWithCheck("确定要删除所有已处理的异常记录吗？(1-是，2-否)：", 1, 2);
    if (choice == 1) {
        if (dataManager.deleteHandledAbnormalRecords()) {
            showResultTip(true, "已处理异常记录清理完成！", "");
        }
        else {
            showResultTip(false, "", "没有可清理的已处理异常记录！");
        }
    }
    else {
        showResultTip(false, "", "已取消清理操作！");
    }

    waitForKeyPress();
}

void MenuUI::showRealTimeStats() {
    clearScreen();
    std::cout << "==================== 实时统计信息 ====================" << std::endl;

    int inStockCount = dataManager.getInStockExpressCount();
    std::cout << "当前在库快递数量：" << inStockCount << std::endl;

    std::string today = Utils::getCurrentDate();
    auto dailyCount = dataManager.getDailyExpressCount(today);
    std::cout << "今日入库数量：" << dailyCount["in"] << std::endl;
    std::cout << "今日出库数量：" << dailyCount["out"] << std::endl;

    auto abnormalCount = dataManager.getAbnormalCountByType();
    std::cout << "异常件总数：";
    int totalAbnormal = 0;
    for (const auto& pair : abnormalCount) {
        totalAbnormal += pair.second;
    }
    std::cout << totalAbnormal << std::endl;

    std::cout << "各存储区域占用率：" << std::endl;
    auto occupancy = dataManager.getStorageOccupancyRate();
    for (const auto& pair : occupancy) {
        std::cout << "  " << pair.first << ": " << (pair.second * 100) << "%"
            << (pair.second >= GlobalConst::STORAGE_WARN_THRESHOLD ? " [预警]" : "") << std::endl;
    }

    waitForKeyPress();
}

void MenuUI::showDateStats() {
    clearScreen();
    std::cout << "==================== 按日期统计 ====================" << std::endl;

    std::string date = inputStrWithTrim("请输入要统计的日期（YYYY-MM-DD，留空则统计今天）：");
    if (date.empty()) {
        date = Utils::getCurrentDate();
    }

    auto dailyCount = dataManager.getDailyExpressCount(date);
    std::cout << date << " 统计信息：" << std::endl;
    std::cout << "  入库数量：" << dailyCount["in"] << std::endl;
    std::cout << "  出库数量：" << dailyCount["out"] << std::endl;
    std::cout << "  库存变化：" << (dailyCount["in"] - dailyCount["out"]) << std::endl;

    waitForKeyPress();
}

void MenuUI::showCompanyStats() {
    clearScreen();
    std::cout << "==================== 按快递公司统计 ====================" << std::endl;

    auto companyCount = dataManager.getExpressCountByCompany();
    std::cout << "各快递公司快递数量：" << std::endl;

    int total = 0;
    for (const auto& pair : companyCount) {
        total += pair.second;
    }

    for (const auto& pair : companyCount) {
        float percentage = total > 0 ? (static_cast<float>(pair.second) / total) * 100 : 0;
        std::cout << "  " << std::left << std::setw(10) << pair.first
            << "数量：" << std::setw(5) << pair.second
            << "占比：" << std::fixed << std::setprecision(1) << percentage << "%" << std::endl;
    }

    std::cout << "  " << std::string(25, '-') << std::endl;
    std::cout << "  总计：" << total << std::endl;

    waitForKeyPress();
}

void MenuUI::showAbnormalStats() {
    clearScreen();
    std::cout << "==================== 异常件统计 ====================" << std::endl;

    auto abnormalCount = dataManager.getAbnormalCountByType();
    std::cout << "各类型异常件数量：" << std::endl;

    int total = 0;
    for (const auto& pair : abnormalCount) {
        total += pair.second;
    }

    for (const auto& pair : abnormalCount) {
        float percentage = total > 0 ? (static_cast<float>(pair.second) / total) * 100 : 0;
        std::cout << "  " << std::left << std::setw(10) << pair.first
            << "数量：" << std::setw(5) << pair.second
            << "占比：" << std::fixed << std::setprecision(1) << percentage << "%" << std::endl;
    }

    std::cout << "  " << std::string(25, '-') << std::endl;
    std::cout << "  总计：" << total << std::endl;

    waitForKeyPress();
}

void MenuUI::exportReport() {
    clearScreen();
    std::cout << "==================== 导出报表 ====================" << std::endl;
    std::cout << "1. 导出快递明细报表" << std::endl;
    std::cout << "2. 导出异常件报表" << std::endl;
    std::cout << "3. 导出统计汇总报表" << std::endl;

    int choice = inputIntWithCheck("请选择报表类型（1-3）：", 1, 3);
    std::string filePath = inputStrWithTrim("请输入导出文件路径：");

    // 实际项目中应实现报表导出逻辑
    showResultTip(true, "报表导出成功！文件路径：" + filePath, "");

    waitForKeyPress();
}

void MenuUI::manageStorageAreas() {
    clearScreen();
    std::cout << "==================== 管理存储区域 ====================" << std::endl;
    std::cout << "1. 添加存储区域" << std::endl;
    std::cout << "2. 修改存储区域容量" << std::endl;
    std::cout << "3. 查看所有存储区域" << std::endl;

    int choice = inputIntWithCheck("请选择操作（1-3）：", 1, 3);

    if (choice == 1) {
        std::string areaId = inputStrWithTrim("请输入存储区域ID（如A-1）：");
        int capacity = inputIntWithCheck("请输入最大容量：", 1, 1000);

        Storage storage(areaId, capacity);
        if (dataManager.addStorageArea(storage)) {
            showResultTip(true, "存储区域添加成功！", "");
        }
        else {
            showResultTip(false, "", "存储区域添加失败，可能已存在！");
        }
    }
    else if (choice == 2) {
        std::string areaId = inputStrWithTrim("请输入要修改的存储区域ID：");
        int newCapacity = inputIntWithCheck("请输入新的最大容量：", 1, 1000);

        if (dataManager.updateStorageCapacity(areaId, newCapacity)) {
            showResultTip(true, "存储区域容量修改成功！", "");
        }
        else {
            showResultTip(false, "", "存储区域修改失败，可能不存在！");
        }
    }
    else if (choice == 3) {
        auto occupancy = dataManager.getStorageOccupancyRate();
        std::cout << "所有存储区域信息：" << std::endl;
        std::cout << std::left << std::setw(10) << "区域ID"
            << std::setw(10) << "最大容量"
            << std::setw(10) << "当前占用"
            << std::setw(10) << "占用率" << std::endl;
        std::cout << std::string(40, '-') << std::endl;

        for (const auto& pair : occupancy) {
            Storage storage = dataManager.getStorageAreaByAreaId(pair.first);
            std::cout << std::left << std::setw(10) << pair.first
                << std::setw(10) << storage.getMaxCapacity()
                << std::setw(10) << storage.getCurrentCount()
                << std::setw(10) << std::fixed << std::setprecision(1)
                << (pair.second * 100) << "%" << std::endl;
        }
    }

    waitForKeyPress();
}

#include "GlobalDefine.h"

void MenuUI::modifyPickCodeRule() {
    clearScreen();
    std::cout << "==================== 修改取件码规则 ====================" << std::endl;
    std::cout << "当前取件码规则：" << GlobalConst::PICK_CODE_PREFIX
        << " + " << GlobalConst::PICK_CODE_RANDOM_LEN << "位随机数" << std::endl;

    std::string newPrefix = inputStrWithTrim("请输入新的前缀（如YZ-）：");
    if (Utils::isEmptyString(newPrefix)) {
        showResultTip(false, "", "前缀不能为空！");
        waitForKeyPress();
        return;
    }

    int newLen = inputIntWithCheck("请输入随机数位数（3-6）：", 3, 6);

    GlobalConst::PICK_CODE_PREFIX = newPrefix;
    GlobalConst::PICK_CODE_RANDOM_LEN = newLen;
    showResultTip(true, "取件码规则修改成功！新规则：" + newPrefix + " + " + std::to_string(newLen) + "位随机数", "");

    waitForKeyPress();
}

void MenuUI::setOverdueDays() {
    clearScreen();
    std::cout << "==================== 设置逾期天数 ====================" << std::endl;
    std::cout << "当前逾期天数：" << GlobalConst::EXPRESS_OVERDUE_DAYS << "天" << std::endl;

    int days = inputIntWithCheck("请输入新的逾期天数（3-30）：", 3, 30);

    GlobalConst::EXPRESS_OVERDUE_DAYS = days;
    showResultTip(true, "逾期天数设置成功！新的逾期天数：" + std::to_string(days) + "天", "");

    waitForKeyPress();
}

void MenuUI::changeAdminPassword() {
    clearScreen();
    std::cout << "==================== 修改管理员密码 ====================" << std::endl;

    std::string oldPwd = inputStrWithTrim("请输入旧密码：");
    if (oldPwd != GlobalConst::ADMIN_DEFAULT_PWD) {
        showResultTip(false, "", "旧密码不正确！");
        waitForKeyPress();
        return;
    }

    std::string newPwd = inputStrWithTrim("请输入新密码：");
    if (Utils::isEmptyString(newPwd) || newPwd.length() < 6) {
        showResultTip(false, "", "新密码不能为空且长度不能少于6位！");
        waitForKeyPress();
        return;
    }

    std::string confirmPwd = inputStrWithTrim("请确认新密码：");
    if (newPwd != confirmPwd) {
        showResultTip(false, "", "两次输入的密码不一致！");
        waitForKeyPress();
        return;
    }

    GlobalConst::ADMIN_DEFAULT_PWD = newPwd;
    showResultTip(true, "管理员密码修改成功！请牢记新密码。", "");

    waitForKeyPress();
}

void MenuUI::showOperationLogs() {
    clearScreen();
    std::cout << "==================== 操作日志 ====================" << std::endl;

    std::list<std::string> logs = dataManager.getOperationLogs();
    std::cout << "最近" << logs.size() << "条操作记录：" << std::endl;

    int count = 0;
    for (const auto& log : logs) {
        count++;
        std::cout << count << ". " << log << std::endl;
    }

    std::cout << std::endl;
    int choice = inputIntWithCheck("是否需要回滚上一步操作？(1-是，2-否)：", 1, 2);
    if (choice == 1) {
        if (dataManager.rollbackLastOperation()) {
            showResultTip(true, "上一步操作已回滚！", "");
        }
        else {
            showResultTip(false, "", "没有可回滚的操作！");
        }
    }

    waitForKeyPress();
}

void MenuUI::queryUserInStockExpress(const std::string& phone) {
    clearScreen();
    std::cout << "==================== 我的在库快递 ====================" << std::endl;

    std::list<Express> expressList = dataManager.getExpressListByPhoneSuffix(Utils::getPhoneSuffix(phone));
    std::list<Express> inStockList;

    for (const auto& exp : expressList) {
        if (exp.getStatus() == ExpressStatus::IN_STOCK) {
            inStockList.push_back(exp);
        }
    }

    std::cout << "您当前有 " << inStockList.size() << " 个在库快递" << std::endl;
    if (!inStockList.empty()) {
        std::cout << std::left << std::setw(10) << "取件码"
            << std::setw(10) << "公司"
            << std::setw(20) << "入库时间"
            << std::setw(10) << "位置" << std::endl;
        std::cout << std::string(50, '-') << std::endl;

        for (const auto& exp : inStockList) {
            std::cout << std::left << std::setw(10) << exp.getPickCode()
                << std::setw(10) << Utils::utf8ToGbk(exp.getCompany())
                << std::setw(20) << exp.getInTime()
                << std::setw(10) << exp.getLocation() << std::endl;
        }

        std::cout << std::endl << "请凭取件码到对应位置取件，并向管理员出示手机号后4位进行验证。" << std::endl;
    }

    waitForKeyPress();
}

void MenuUI::queryUserPickHistory(const std::string& phone) {
    clearScreen();
    std::cout << "==================== 我的取件记录 ====================" << std::endl;

    User user = dataManager.getUserByPhone(phone);
    std::list<std::string> historyIds = user.getExpressHistory();

    std::cout << "您共有 " << historyIds.size() << " 条取件记录" << std::endl;
    if (!historyIds.empty()) {
        std::cout << std::left << std::setw(10) << "取件码"
            << std::setw(10) << "公司"
            << std::setw(20) << "取件时间" << std::endl;
        std::cout << std::string(40, '-') << std::endl;

        for (const auto& id : historyIds) {
            Express exp = dataManager.getExpressByExpressId(id);
            if (!exp.getExpressId().empty() && exp.getStatus() == ExpressStatus::PICKED) {
                std::cout << std::left << std::setw(10) << exp.getPickCode()
                    << std::setw(10) << Utils::utf8ToGbk(exp.getCompany())
                    << std::setw(20) << exp.getInTime() << std::endl; // 简化实现，实际应记录取件时间
            }
        }
    }

    waitForKeyPress();
}

void MenuUI::submitAbnormalFeedback(const std::string& phone) {
    clearScreen();
    std::cout << "==================== 异常反馈 ====================" << std::endl;

    std::string expressId = inputStrWithTrim("请输入快递单号：");
    Express exp = dataManager.getExpressByExpressId(expressId);
    if (exp.getExpressId().empty()) {
        showResultTip(false, "", "未找到该快递单号！");
        waitForKeyPress();
        return;
    }
    std::list<Abnormal> abnormals = dataManager.getAllAbnormalRecords();

    auto it = std::find_if(abnormals.begin(), abnormals.end(),
        [&](const Abnormal& a) { return a.getExpressId() == expressId; });

    if (it == abnormals.end()) {
        std::cout << "1. 丢失" << std::endl;
        std::cout << "2. 错发" << std::endl;
        std::cout << "3. 逾期未取" << std::endl;
        int typeChoice = inputIntWithCheck("请选择异常类型（1-3）：", 1, 3);

        AbnormalType type;
        switch (typeChoice) {
        case 1: type = AbnormalType::LOST; break;
        case 2: type = AbnormalType::WRONG_DELIVER; break;
        case 3: type = AbnormalType::OVERDUE; break;
        default: type = AbnormalType::LOST;
        }

        // 生成异常记录ID
        std::string recordId = "AR" + Utils::getCurrentDate() + std::to_string(Utils::generateRandomInt(100, 999));

        // 创建异常记录
        Abnormal abnormal(recordId, expressId, type, Utils::getCurrentTimeStamp());

        if (dataManager.addAbnormalRecord(abnormal)) {
            showResultTip(true, "异常快递标记成功！记录ID：" + recordId, "");
        }
        else {
            showResultTip(false, "", "异常快递标记失败！");
        }
    }
    else {
        cout << "异常已汇报，请勿重复上报" << endl;
    }

    waitForKeyPress();
}

