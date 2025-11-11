#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include "GlobalDefine.h"
using u8string = std::string;

class Utils {
public:
    // 生成唯一取件码
    static std::string generateUniquePickCode();
    // 验证取件码格式
    static bool isValidPickCode(const std::string& pickCode);

    // 获取当前时间戳（YYYY-MM-DD HH:MM:SS）
    static std::string getCurrentTimeStamp();
    // 获取当前日期（YYYY-MM-DD）
    static std::string getCurrentDate();
    // 计算日期差（date1 - date2，返回天数）
    static int calculateDateDiff(const std::string& date1, const std::string& date2);
    // 判断快递是否逾期
    static bool isExpressOverdue(const std::string& inStockDate);

    // 手机号脱敏（138****5678）
    static std::string desensitizePhone(const std::string& phone);
    // 验证手机号格式（11位数字）
    static bool isValidPhone(const std::string& phone);
    // 提取手机号后4位
    static std::string getPhoneSuffix(const std::string& phone);

    // 字符串分割
    static std::vector<std::string> splitString(const std::string& str, char delimiter);
    // 去除字符串前后空格
    static std::string trimString(const std::string& str);
    // 判断字符串是否为空（含全空格）
    static bool isEmptyString(const std::string& str);

    // 生成指定范围随机整数
    static int generateRandomInt(int min, int max);

    static std::string utf8ToGbk(const std::string& utf8Str);

    static u8string gbkToUtf8(const std::string& gbkStr);
};

#endif // UTILS_H