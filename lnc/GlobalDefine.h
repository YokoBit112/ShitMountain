#ifndef GLOBALDEFINE_H
#define GLOBALDEFINE_H

#include <string>

// 快递状态枚举
enum class ExpressStatus {
    IN_STOCK,    // 在库
    PICKED,      // 已取
    ABNORMAL     // 异常
};

// 异常类型枚举
enum class AbnormalType {
    LOST,        // 丢失
    WRONG_DELIVER, // 错发
    OVERDUE      // 逾期未取
};

// 异常处理状态枚举
enum class HandleStatus {
    PENDING,     // 待处理
    HANDLING,    // 处理中
    RESOLVED     // 已解决
};

// 全局常量定义
namespace GlobalConst {
    extern const std::string ADMIN_DEFAULT_PWD;       // 管理员默认密码
    extern const int EXPRESS_OVERDUE_DAYS;            // 快递逾期天数
    extern const std::string PICK_CODE_PREFIX;        // 取件码前缀
    extern const int PICK_CODE_RANDOM_LEN;            // 取件码随机数位数
    extern const float STORAGE_WARN_THRESHOLD;        // 存储区域预警阈值（90%）
    extern const std::string DEFAULT_EXPRESS_PATH;
    extern const std::string DEFAULT_USER_PATH;
    extern const std::string DEFAULT_STORAGE_PATH;
    extern const std::string DEFAULT_ABNORMAL_PATH;
    extern const std::string DEFAULT_LOG_PATH;
}

// 枚举与字符串转换工具（仅声明）
namespace EnumConverter {
    std::string expressStatusToString(ExpressStatus status);
    ExpressStatus stringToExpressStatus(const std::string& statusStr);

    std::string abnormalTypeToString(AbnormalType type);
    AbnormalType stringToAbnormalType(const std::string& typeStr);

    std::string handleStatusToString(HandleStatus status);
    HandleStatus stringToHandleStatus(const std::string& statusStr);
}

#endif // GLOBALDEFINE_H
