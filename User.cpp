#include "User.h"
#include "Utils.h"

// 构造函数实现

//取件人用户端构造函数
User::User() {}
User::User(const std::string& p) : phone(Utils::desensitizePhone(p)) {}
User::User(const std::string& p, const std::string& n) : phone(Utils::desensitizePhone(p)), name(n) {}

// Getter实现
std::string User::getPhone() const { return phone; }													//获取取件人手机号
std::string User::getName() const { return name; }														//获取取件人姓名
std::list<std::string> User::getExpressHistory() const { return historyExpressIds; }					//获取取件人历史快递ID列表

// Setter实现
void User::setName(const std::string& n) { name = n; }														//设置取件人姓名
void User::addExpressHistory(const std::string& expressId) { historyExpressIds.push_back(expressId); }		//添加取件人历史快递ID
void User::clearExpressHistory() { historyExpressIds.clear(); }												//清空取件人历史快递ID列表		
