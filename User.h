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
    std::string getPhone() const;                       //获取取件人手机号
    std::string getName() const;                        //获取取件人姓名
    std::list<std::string> getExpressHistory() const;   //获取取件历史

    // Setter
    void setName(const std::string& n);                 //设置取件人姓名
    // 添加取件记录
    void addExpressHistory(const std::string& expressId);
    // 清空取件记录
    void clearExpressHistory();
};

#endif // USER_H
