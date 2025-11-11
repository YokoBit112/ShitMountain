#ifndef EXPRESS_H
#define EXPRESS_H

#include <string>
#include "GlobalDefine.h"
#include "Utils.h"

/**********快递类***********/

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
    /**********构造函数***********/
	//无参构造函数
    Express();
	//有参构造函数
	//传入参数：string eId    ：  快递单号
	//          string pCode  ：  取件码
	//          string uPhone ：  收件人手机号
	//          string comp   ：  快递公司
	//          string iTime  ：  入库时间
	//          string loc    ：  存储位置
	//          ExpressStatus stat ： 快递状态
    Express(const std::string& eId, const std::string& pCode, const std::string& uPhone,
        const std::string& comp, const std::string& iTime, const std::string& loc,ExpressStatus stat);

    /***************GETTER声明*******************/

	std::string getExpressId() const;           // 获取快递单号
	std::string getPickCode() const;			// 获取取件码
	std::string getUserPhone() const;		    // 获取收件人手机号
	std::string getCompany() const;			    // 获取快递公司
	std::string getInTime() const;			    // 获取入库时间
	std::string getLocation() const;			// 获取存储位置
	ExpressStatus getStatus() const;			// 获取快递状态
	std::string getStatusString() const;		// 获取快递状态字符串表示

    /**********SETTER声明***********/

	void setStatus(ExpressStatus newStat);				// 设置快递状态
	void setLocation(const std::string& newLoc);		// 设置存储位置
	void setUserPhone(const std::string& phone);		// 设置收件人手机号
};

#endif
