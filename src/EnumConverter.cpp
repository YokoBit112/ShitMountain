#include "GlobalDefine.h"
#include <string>

// 枚举转换函数实现
namespace EnumConverter {
    std::string expressStatusToString(ExpressStatus status) {
        switch (status) {
        case ExpressStatus::IN_STOCK: return u8"在库";
        case ExpressStatus::PICKED: return u8"已取";
        case ExpressStatus::ABNORMAL: return u8"异常";
        default: return u8"未知";
        }
    }

    ExpressStatus stringToExpressStatus(const std::string& statusStr) {
        if (statusStr == u8"在库") return ExpressStatus::IN_STOCK;
        if (statusStr == u8"已取") return ExpressStatus::PICKED;
        if (statusStr == u8"异常") return ExpressStatus::ABNORMAL;
        return ExpressStatus::IN_STOCK;  // 注意：默认返回IN_STOCK是否合理？
    }

    std::string abnormalTypeToString(AbnormalType type) {
        switch (type) {
        case AbnormalType::LOST: return u8"丢失";
        case AbnormalType::WRONG_DELIVER: return u8"错发";
        case AbnormalType::OVERDUE: return u8"逾期未取";
        default: return u8"未知";
        }
    }

    AbnormalType stringToAbnormalType(const std::string& typeStr) {
        if (typeStr == u8"丢失") return AbnormalType::LOST;
        if (typeStr == u8"错发") return AbnormalType::WRONG_DELIVER;
        if (typeStr == u8"逾期未取") return AbnormalType::OVERDUE;
        return AbnormalType::LOST;  // 注意：默认返回LOST是否合理？
    }

    std::string handleStatusToString(HandleStatus status) {
        switch (status) {
        case HandleStatus::PENDING: return u8"待处理";
        case HandleStatus::HANDLING: return u8"处理中";
        case HandleStatus::RESOLVED: return u8"已解决";
        default: return u8"未知";
        }
    }

    HandleStatus stringToHandleStatus(const std::string& statusStr) {
        if (statusStr == u8"待处理") return HandleStatus::PENDING;
        if (statusStr == u8"处理中") return HandleStatus::HANDLING;
        if (statusStr == u8"已解决") return HandleStatus::RESOLVED;
        return HandleStatus::PENDING;  // 注意：默认返回PENDING是否合理？
    }
}