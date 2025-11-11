#include "Abnormal.h"


/*********异常处理*************/



/**初始化函数**/

//无参初始化
Abnormal::Abnormal() : handleStatus(HandleStatus::PENDING) {}
//有参初始化
//传入参数：string id：         ：  异常记录ID
//          string expId        ：  关联快递单号
//		    AbnormalType type   ：  异常类型
//		    string createTime   ：  创建时间
Abnormal::Abnormal(const std::string& id, const std::string& expId, AbnormalType type, const std::string& createTime)
    : recordId(id), expressId(expId), abnormalType(type), createTime(createTime),
    handleStatus(HandleStatus::PENDING) {
}

/****GETTER实现***/

std::string Abnormal::getRecordId() const { return recordId; }                                                      //获取异常记录ID
std::string Abnormal::getExpressId() const { return expressId; }    									            //获取关联快递单号 
AbnormalType Abnormal::getAbnormalType() const { return abnormalType; }   						                    //获取异常类型
std::string Abnormal::getAbnormalTypeString() const { return EnumConverter::abnormalTypeToString(abnormalType); }   //获取异常类型字符串表示
std::string Abnormal::getCreateTime() const { return createTime; }                                                  //获取创建时间
HandleStatus Abnormal::getHandleStatus() const { return handleStatus; }									            //获取处理状态
std::string Abnormal::getHandleStatusString() const { return EnumConverter::handleStatusToString(handleStatus); }   //获取处理状态字符串表示
std::string Abnormal::getHandleResult() const { return handleResult; }					                            //获取处理结果
std::string Abnormal::getHandleTime() const { return handleTime; }					                                //获取处理时间

/***SETTER实现***/

//更新状态
//传入参数：HandleStatus newStatus：新的处理状态
bool Abnormal::updateHandleStatus(HandleStatus newStatus) {
    handleStatus = newStatus;
    return true;
}

//更新处理结果与时间
//传入参数：string result   ：   处理结果
//		    string time     ：   处理时间
bool Abnormal::setHandleResult(const std::string& result, const std::string& time) {
    handleResult = result;
    handleTime = time;
    handleStatus = HandleStatus::RESOLVED;
    return true;
}

//更新处理状态
bool Abnormal::isHandled() const { return handleStatus == HandleStatus::RESOLVED; }
