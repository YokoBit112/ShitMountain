#include "Express.h"
#include "Utils.h"

// 构造函数实现
Express::Express() : status(ExpressStatus::IN_STOCK) {}

Express::Express(const std::string& eId, const std::string& pCode, const std::string& uPhone,
    const std::string& comp, const std::string& iTime, const std::string& loc,
    ExpressStatus stat)
    : expressId(eId), pickCode(pCode), userPhone(Utils::desensitizePhone(uPhone)),
    company(comp), inTime(iTime), location(loc), status(stat) {
}

// Getter实现
std::string Express::getExpressId() const { return (expressId); }
std::string Express::getPickCode() const { return (pickCode); }
std::string Express::getUserPhone() const { return (userPhone); }
std::string Express::getCompany() const { return company; }
std::string Express::getInTime() const { return inTime; }
std::string Express::getLocation() const { return (location); }
ExpressStatus Express::getStatus() const { return status; }
std::string Express::getStatusString() const { return  EnumConverter::expressStatusToString(status); }

// Setter实现
void Express::setStatus(ExpressStatus newStat) { status = newStat; }
void Express::setLocation(const std::string& newLoc) { location = newLoc; }
void Express::setUserPhone(const std::string& phone) { userPhone = Utils::desensitizePhone(phone); }

