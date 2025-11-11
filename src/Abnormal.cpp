#include "Abnormal.h"
#include "GlobalDefine.h"
#include "Utils.h"
// 构造函数实现
Abnormal::Abnormal() : handleStatus(HandleStatus::PENDING) {}
Abnormal::Abnormal(const std::string& id, const std::string& expId, AbnormalType type, const std::string& createTime)
    : recordId(id), expressId(expId), abnormalType(type), createTime(createTime),
    handleStatus(HandleStatus::PENDING) {
}

// Getter实现
std::string Abnormal::getRecordId() const { return recordId; }
std::string Abnormal::getExpressId() const { return expressId; }
AbnormalType Abnormal::getAbnormalType() const { return abnormalType; }
std::string Abnormal::getAbnormalTypeString() const { return EnumConverter::abnormalTypeToString(abnormalType); }
std::string Abnormal::getCreateTime() const { return createTime; }
HandleStatus Abnormal::getHandleStatus() const { return handleStatus; }
std::string Abnormal::getHandleStatusString() const { return EnumConverter::handleStatusToString(handleStatus); }
std::string Abnormal::getHandleResult() const { return handleResult; }
std::string Abnormal::getHandleTime() const { return handleTime; }

// Setter实现
bool Abnormal::updateHandleStatus(HandleStatus newStatus) {
    handleStatus = newStatus;
    return true;
}

bool Abnormal::setHandleResult(const std::string& result, const std::string& time) {
    handleResult = result;
    handleTime = time;
    handleStatus = HandleStatus::RESOLVED;
    return true;
}

bool Abnormal::isHandled() const { return handleStatus == HandleStatus::RESOLVED; }
