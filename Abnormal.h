#ifndef ABNORMAL_H
#define ABNORMAL_H

#include <string>
#include "GlobalDefine.h"
#include "Utils.h"

class Abnormal {
private:
    std::string     recordId;        // 异常记录ID（如"AR20241016001"）
    std::string     expressId;       // 关联快递单号
    AbnormalType    abnormalType;    // 异常类型
    std::string     createTime;      // 创建时间（YYYY-MM-DD HH:MM:SS）
    HandleStatus    handleStatus;    // 处理状态
    std::string     handleResult;    // 处理结果
    std::string     handleTime;      // 处理时间（未处理为空）

public:

    /*******************构造函数****************/

    //无参构造函数
    Abnormal();
	//有参构造函数
	//传入参数：string id：         ：  异常记录ID
	//          string expId        ：  关联快递单号
	//		    AbnormalType type   ：  异常类型
	//		    string createTime   ：  创建时间
    Abnormal(const std::string& id, const std::string& expId, AbnormalType type, const std::string& createTime);

    /*******************Getter************************/

	std::string getRecordId() const;                        //获取异常记录ID
	std::string getExpressId() const;                       //获取关联快递单号
	AbnormalType getAbnormalType() const;   		        //获取异常类型   
	std::string getAbnormalTypeString() const;              //获取异常类型字符串表示
	std::string getCreateTime() const;					    //获取创建时间
	HandleStatus getHandleStatus() const;				    //获取处理状态
	std::string getHandleStatusString() const;			    //获取处理状态字符串表示
	std::string getHandleResult() const;					//获取处理结果
	std::string getHandleTime() const;					    //获取处理时间

   /****************Setter*********************/

    //更新状态
	//传入参数：HandleStatus newStatus：新的处理状态
    bool updateHandleStatus(HandleStatus newStatus);

    //更新处理结果与时间
	//传入参数：string result   ：   处理结果
	//		    string time     ：   处理时间
    bool setHandleResult(const std::string& result, const std::string& time);

    //更新处理状态
    bool isHandled() const;
};

#endif 
