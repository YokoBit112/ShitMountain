#include "User.h"
#include "Utils.h"

// 构造函数实现
User::User() {}
User::User(const std::string& p) : phone(Utils::desensitizePhone(p)) {}
User::User(const std::string& p, const std::string& n) : phone(Utils::desensitizePhone(p)), name(n) {}

// Getter实现
std::string User::getPhone() const { return phone; }
std::string User::getName() const { return name; }
std::list<std::string> User::getExpressHistory() const { return historyExpressIds; }

// Setter实现
void User::setName(const std::string& n) { name = n; }
void User::addExpressHistory(const std::string& expressId) { historyExpressIds.push_back(expressId); }
void User::clearExpressHistory() { historyExpressIds.clear(); }
