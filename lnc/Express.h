#ifndef EXPRESS_H
#define EXPRESS_H

#include <string>
#include "GlobalDefine.h"

class Express {
private:
    std::string expressId;   // 快递单号（唯一）
    std::string pickCode;    // 取件码
    std::string userPhone;   // 收件人手机号（脱敏）
    std::string company;     // 快递公司
    std::string inTime;      // 入库时间（YYYY-MM-DD HH:MM:SS）
    std::string location;    // 存储位置（如"A-1"）
    ExpressStatus status;    // 快递状态

public:
    // 构造函数
    Express();
    Express(const std::string& eId, const std::string& pCode, const std::string& uPhone,
        const std::string& comp, const std::string& iTime, const std::string& loc,
        ExpressStatus stat);

    // Getter
    std::string getExpressId() const;
    std::string getPickCode() const;
    std::string getUserPhone() const;
    std::string getCompany() const;
    std::string getInTime() const;
    std::string getLocation() const;
    ExpressStatus getStatus() const;
    std::string getStatusString() const;

    // Setter
    void setStatus(ExpressStatus newStat);
    void setLocation(const std::string& newLoc);
    void setUserPhone(const std::string& phone);
};

#endif // EXPRESS_H
