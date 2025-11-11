
#define _CRT_SECURE_NO_WARNINGS
#include "Utils.h"
#include <ctime>
#include <cstdlib>
#include <cctype>
#include <sstream>
#ifdef _WIN32
#include <Windows.h>
#else
// 非 Windows 环境需用其他库（如 iconv），此处仅展示 Windows 实现
#endif



// 生成唯一取件码(实际实现:用时间确保唯一性)
std::string Utils::generateUniquePickCode() {
    std::string code = GlobalConst::PICK_CODE_PREFIX;
    for (int i = 0; i < GlobalConst::PICK_CODE_RANDOM_LEN; ++i) {
        code += '0' + generateRandomInt(0, 9);
    }
    return code;
}

// 验证取件码格式
bool Utils::isValidPickCode(const std::string& pickCode) {
    if (pickCode.substr(0, GlobalConst::PICK_CODE_PREFIX.length()) != GlobalConst::PICK_CODE_PREFIX) {
        return false;
    }
    std::string randomPart = pickCode.substr(GlobalConst::PICK_CODE_PREFIX.length());
    if (randomPart.length() != GlobalConst::PICK_CODE_RANDOM_LEN) {
        return false;
    }
    for (char c : randomPart) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

// 获取当前时间戳(YYYY-MM-DD HH:MM:SS)
std::string Utils::getCurrentTimeStamp() {
    time_t now = time(nullptr);
    tm* t = localtime(&now);
    char buf[20];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", t);
    return buf;
}

// 获取当前日期(YYYY-MM-DD)
std::string Utils::getCurrentDate() {
    time_t now = time(nullptr);
    tm* t = localtime(&now);
    char buf[11];
    strftime(buf, sizeof(buf), "%Y-%m-%d", t);
    return buf;
}

// 计算日期差(实际实现:只支持YYYY-MM-DD格式)
int Utils::calculateDateDiff(const std::string& date1, const std::string& date2) {
    tm t1 = {}, t2 = {};
    sscanf(date1.c_str(), "%d-%d-%d", &t1.tm_year, &t1.tm_mon, &t1.tm_mday);
    sscanf(date2.c_str(), "%d-%d-%d", &t2.tm_year, &t2.tm_mon, &t2.tm_mday);
    t1.tm_year -= 1900;
    t1.tm_mon -= 1;
    t2.tm_year -= 1900;
    t2.tm_mon -= 1;
    return difftime(mktime(&t1), mktime(&t2)) / (60 * 60 * 24);
}

// 判断快递是否过期
bool Utils::isExpressOverdue(const std::string& inStockDate) {
    std::string inDate = inStockDate.substr(0, 10); // 提取日期部分
    std::string today = getCurrentDate();
    return calculateDateDiff(today, inDate) > GlobalConst::EXPRESS_OVERDUE_DAYS;
}

// 手机号脱敏
std::string Utils::desensitizePhone(const std::string& phone) {
    if (phone.length() != 11) return phone;
    return phone.substr(0, 3) + "****" + phone.substr(7, 4);
}

// 验证手机号格式
bool Utils::isValidPhone(const std::string& phone) {
    if (phone.length() != 11) return false;
    for (char c : phone) {
        if (!isdigit(c)) return false;
    }
    return true;
}

// 获取手机号后4位
std::string Utils::getPhoneSuffix(const std::string& phone) {
    if (phone.length() >= 4) {
        return phone.substr(phone.length() - 4);
    }
    return phone;
}

// 字符串分割
std::vector<std::string> Utils::splitString(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string item;
    while (getline(ss, item, delimiter)) {
        result.push_back(trimString(item));
    }
    return result;
}

// 去除字符串前后空格(仅处理ASCII空格)
std::string Utils::trimString(const std::string& str) {
    if (str.empty()) return str;

    size_t start = 0;
    // 只处理ASCII空格、制表符、换行符等
    while (start < str.size() && (str[start] == ' ' || str[start] == '\t' || str[start] == '\n' || str[start] == '\r')) {
        start++;
    }

    size_t end = str.size();
    do {
        end--;
    } while (end >= start && (str[end] == ' ' || str[end] == '\t' || str[end] == '\n' || str[end] == '\r'));

    return str.substr(start, end - start + 1);
}

// 判断字符串是否为空
bool Utils::isEmptyString(const std::string& str) {
    std::string trimmed = trimString(str);
    return trimmed.empty();
}

// 生成指定范围的随机数
int Utils::generateRandomInt(int min, int max) {
    static bool initialized = false;
    if (!initialized) {
        srand(static_cast<unsigned int>(time(nullptr)));
        initialized = true;
    }
    return min + rand() % (max - min + 1);
}

std::string Utils::utf8ToGbk(const std::string &utf8Str) {
    // 步骤1：UTF-8 → Unicode（宽字符）
    int wideCharLen = MultiByteToWideChar(
        CP_UTF8,        // 源编码为 UTF-8
        0,              // 无额外标志
        utf8Str.c_str(),// 源字符串
        -1,             // 自动处理字符串结尾'\0'
        nullptr,        // 先获取所需缓冲区长度
        0
    );
    if (wideCharLen == 0) {
        return ""; // 转换失败
    }

    std::vector<wchar_t> wideCharBuf(wideCharLen);
    MultiByteToWideChar(
        CP_UTF8,
        0,
        utf8Str.c_str(),
        -1,
        wideCharBuf.data(),
        wideCharLen
    );

    // 步骤2：Unicode → GBK
    int gbkLen = WideCharToMultiByte(
        CP_ACP,         // 目标编码为系统ANSI编码（中文Windows下为GBK/GB2312）
        0,
        wideCharBuf.data(),
        -1,
        nullptr,
        0,
        nullptr,
        nullptr
    );
    if (gbkLen == 0) {
        return "";
    }

    std::vector<char> gbkBuf(gbkLen);
    WideCharToMultiByte(
        CP_ACP,
        0,
        wideCharBuf.data(),
        -1,
        gbkBuf.data(),
        gbkLen,
        nullptr,
        nullptr
    );

    // 去掉结尾的'\0'，返回有效字符串
    return std::string(gbkBuf.data(), gbkLen - 1);
}

// 辅助函数：将 GBK 编码的字符串转换为 UTF-8 编码
u8string Utils::gbkToUtf8(const std::string& gbkStr) {
    if (gbkStr.empty()) {
        return "";
    }

    // 第一步：将 GBK 转换为宽字符（UTF-16，内部临时使用，不暴露给外部）
    int wideSize = MultiByteToWideChar(
        CP_ACP,       // 源编码：系统默认 ANSI 编码（GBK/CP936）
        0,            // 转换标志：默认
        gbkStr.c_str(),  // 源 GBK 字符串（char*）
        -1,           // 长度：自动计算（包含终止符）
        nullptr,      // 临时缓冲区：先计算大小
        0             // 缓冲区大小：0
    );
    if (wideSize == 0) {
        return ""; // 转换失败
    }

    // 分配宽字符缓冲区
    std::wstring wideStr(wideSize, L'\0');
    MultiByteToWideChar(
        CP_ACP,
        0,
        gbkStr.c_str(),
        -1,
        &wideStr[0],
        wideSize
    );

    // 第二步：将宽字符（UTF-16）转换为 UTF-8
    int utf8Size = WideCharToMultiByte(
        CP_UTF8,      // 目标编码：UTF-8
        0,            // 转换标志：默认
        wideStr.c_str(),  // 源宽字符串
        -1,           // 长度：自动计算
        nullptr,      // 临时缓冲区：先计算大小
        0,            // 缓冲区大小：0
        nullptr, nullptr
    );
    if (utf8Size == 0) {
        return ""; // 转换失败
    }

    // 分配 UTF-8 缓冲区并转换
    u8string utf8Str(utf8Size, '\0');
    WideCharToMultiByte(
        CP_UTF8,
        0,
        wideStr.c_str(),
        -1,
        &utf8Str[0],
        utf8Size,
        nullptr, nullptr
    );

    // 移除自动添加的终止符
    utf8Str.pop_back();
    return utf8Str;
}