#ifndef USER_H
#define USER_H

#include <string>
#include <list>

class User {
private:
    std::string phone;               // 手机号（唯一标识）
    std::string name;                // 姓名（可选）
    std::list<std::string> historyExpressIds; // 历史取件快递单号列表

public:
    // 构造函数
    User();
    User(const std::string& p);
    User(const std::string& p, const std::string& n);

    // Getter
    std::string getPhone() const;
    std::string getName() const;
    std::list<std::string> getExpressHistory() const;

    // Setter
    void setName(const std::string& n);
    // 添加取件记录
    void addExpressHistory(const std::string& expressId);
    // 清空取件记录
    void clearExpressHistory();
};

#endif // USER_H
