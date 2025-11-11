#ifndef FILEIO_H
#define FILEIO_H

#include <string>
#include <list>
#include "Express.h"
#include "User.h"
#include "Storage.h"
#include "Abnormal.h"

class FileIO {
public:
    // 快递数据读写
    static bool loadExpressFromFile(const std::string& filePath, std::list<Express>& expressList);
    static bool saveExpressToFile(const std::string& filePath, const std::list<Express>& expressList);
    static bool appendExpressToFile(const std::string& filePath, const Express& exp);

    // 用户数据读写
    static bool loadUserFromFile(const std::string& filePath, std::list<User>& userList);
    static bool saveUserToFile(const std::string& filePath, const std::list<User>& userList);

    // 存储区域数据读写
    static bool loadStorageFromFile(const std::string& filePath, std::list<Storage>& storageList);
    static bool saveStorageToFile(const std::string& filePath, const std::list<Storage>& storageList);

    // 异常记录数据读写
    static bool loadAbnormalFromFile(const std::string& filePath, std::list<Abnormal>& abnormalList);
    static bool saveAbnormalToFile(const std::string& filePath, const std::list<Abnormal>& abnormalList);

    // 操作日志读写
    static bool appendLogToFile(const std::string& logPath, const std::string& logContent);
    static bool loadLogFromFile(const std::string& logPath, std::list<std::string>& logList);

private:
    // 检查文件路径是否合法
    static bool checkFilePathValid(const std::string& filePath);
};

#endif // FILEIO_H