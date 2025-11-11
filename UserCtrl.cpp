#include "Ctrl.h"

/************************ 用户操作 ************************/



//添加或更新用户
//传入User用户信息
//传出状态位             success:true
bool DataManager::addOrUpdateUser(const User& user) {
    std::string phone = user.getPhone();
    userMap[phone] = user;

    // 记录操作日志
    std::string log = "添加/更新用户：" + phone;
    addOperationLog(log);
    FileIO::appendLogToFile(GlobalConst::DEFAULT_LOG_PATH, log);

    return true;
}

//通过手机号查询用户
//传入str手机号
//传出user用户信息
User DataManager::getUserByPhone(const std::string& phone) {
    auto it = userMap.find(Utils::desensitizePhone(phone));
    return it != userMap.end() ? it->second : User();
}

//添加用户取件记录
//传入str手机号、str快递单号
//传出状态位             success:true
bool DataManager::addUserExpressHistory(const std::string& phone, const std::string& expressId) {
    std::string desPhone = Utils::desensitizePhone(phone);
    auto it = userMap.find(desPhone);
    if (it == userMap.end()) return false;

    it->second.addExpressHistory(expressId);

    // 记录操作日志
    std::string log = "添加用户取件记录：" + desPhone + "→" + expressId;
    addOperationLog(log);
    FileIO::appendLogToFile(GlobalConst::DEFAULT_LOG_PATH, log);

    return true;
}

//获取用户取件记录
//传入str手机号
//传出list<str>取件记录表
std::list<std::string> DataManager::getUserExpressHistory(const std::string& phone) {
    User user = getUserByPhone(phone);
    return user.getExpressHistory();
}
