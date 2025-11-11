#ifndef ABNORMAL_H
#define ABNORMAL_H

#include <string>
#include "GlobalDefine.h"

class Abnormal {
private:
    std::string recordId;        // 异常记录ID（如"AR20241016001"）
    std::string expressId;       // 关联快递单号
    AbnormalType abnormalType;   // 异常类型
    std::string createTime;      // 创建时间（YYYY-MM-DD HH:MM:SS）
    HandleStatus handleStatus;   // 处理状态
    std::string handleResult;    // 处理结果
    std::string handleTime;      // 处理时间（未处理为空）

public:
    // 构造函数
    Abnormal();
    Abnormal(const std::string& id, const std::string& expId, AbnormalType type, const std::string& createTime);

    // Getter
    std::string getRecordId() const;
    std::string getExpressId() const;
    AbnormalType getAbnormalType() const;
    std::string getAbnormalTypeString() const;
    std::string getCreateTime() const;
    HandleStatus getHandleStatus() const;
    std::string getHandleStatusString() const;
    std::string getHandleResult() const;
    std::string getHandleTime() const;

    // Setter：更新处理状态
    bool updateHandleStatus(HandleStatus newStatus);
    // Setter：设置处理结果与时间
    bool setHandleResult(const std::string& result, const std::string& time);

    // 判断是否已处理
    bool isHandled() const;
};

#endif // ABNORMAL_H
