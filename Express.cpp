#include "Express.h"


/**********快递类***********/

/***构造函数实现***/

//无参构造函数
Express::Express() : status(ExpressStatus::IN_STOCK) {}
//有参构造函数
//传入参数：string eId    ：  快递单号
//          string pCode  ：  取件码
//          string uPhone ：  收件人手机号
//          string comp   ：  快递公司
//          string iTime  ：  入库时间
//          string loc    ：  存储位置
//          ExpressStatus stat ： 快递状态
Express::Express(const std::string& eId, const std::string& pCode, const std::string& uPhone,
    const std::string& comp, const std::string& iTime, const std::string& loc,ExpressStatus stat)
    : expressId(eId), pickCode(pCode), userPhone(Utils::desensitizePhone(uPhone)),
    company(comp), inTime(iTime), location(loc), status(stat) {
}

/****GETTER实现*****/

std::string Express::getExpressId() const { return (expressId); }                                           // 获取快递单号
std::string Express::getPickCode() const { return (pickCode); }			                                    // 获取取件码
std::string Express::getUserPhone() const { return (userPhone); }		                                    // 获取收件人手机号
std::string Express::getCompany() const { return company; }			                                        // 获取快递公司
std::string Express::getInTime() const { return inTime; }			                                        // 获取入库时间
std::string Express::getLocation() const { return (location); }		                                    	// 获取存储位置
ExpressStatus Express::getStatus() const { return status; }			                                        // 获取快递状态
std::string Express::getStatusString() const { return  EnumConverter::expressStatusToString(status); }		// 获取快递状态字符串表示

/**********SETTER实现***********/

void Express::setStatus(ExpressStatus newStat) { status = newStat; }                                        // 设置快递状态
void Express::setLocation(const std::string& newLoc) { location = newLoc; }		                            // 设置存储位置
void Express::setUserPhone(const std::string& phone) { userPhone = Utils::desensitizePhone(phone); }		// 设置收件人手机号

