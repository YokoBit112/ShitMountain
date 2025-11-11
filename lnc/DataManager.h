#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <unordered_map>
#include <list>
#include "Express.h"
#include "User.h"
#include "Storage.h"
#include "Abnormal.h"
#include "FileIO.h"
#include "Utils.h"

class DataManager {
private:
    // 核心数据存储
    std::unordered_map<std::string, Express> expressMap;          // 单号→快递
    std::unordered_map<std::string, std::string> pickCodeMap;     // 取件码→单号
    std::unordered_map<std::string, User> userMap;                // 手机号→用户
    std::unordered_map<std::string, Storage> storageMap;          // 区域ID→存储区域
    std::list<Abnormal> abnormalList;                             // 异常记录列表
    std::list<std::string> operationLogStack;                     // 操作日志栈（用于回滚）

public:
    /************************ 快递操作 ************************/
    bool addExpress(const Express& exp);
    Express getExpressByExpressId(const std::string& expressId);
    Express getExpressByPickCode(const std::string& pickCode);
    bool updateExpressStatus(const std::string& expressId, ExpressStatus newStatus);
    bool updateExpressLocation(const std::string& expressId, const std::string& newLocation);
    bool deleteExpress(const std::string& expressId);
    std::list<Express> getExpressListByPhoneSuffix(const std::string& phoneSuffix);
    std::list<Express> getExpressListByInTimeRange(const std::string& startDate, const std::string& endDate);

    /************************ 用户操作 ************************/
    bool addOrUpdateUser(const User& user);
    User getUserByPhone(const std::string& phone);
    bool addUserExpressHistory(const std::string& phone, const std::string& expressId);
    std::list<std::string> getUserExpressHistory(const std::string& phone);

    /************************ 存储区域操作 ************************/
    bool addStorageArea(const Storage& storage);
    Storage getStorageAreaByAreaId(const std::string& areaId);
    bool updateStorageCapacity(const std::string& areaId, int newMaxCapacity);
    bool assignExpressToStorage(const std::string& areaId, const std::string& expressId);
    bool removeExpressFromStorage(const std::string& areaId, const std::string& expressId);
    std::unordered_map<std::string, float> getStorageOccupancyRate();

    /************************ 异常记录操作 ************************/
    bool addAbnormalRecord(const Abnormal& abnormal);
    bool updateAbnormalHandleResult(const std::string& recordId, const std::string& result);
    std::list<Abnormal> getAllAbnormalRecords();
    std::list<Abnormal> getAbnormalRecordsByType(AbnormalType type);
    bool deleteHandledAbnormalRecords();

    /************************ 操作日志与回滚 ************************/
    void addOperationLog(const std::string& logDesc);
    bool rollbackLastOperation();
    std::list<std::string> getOperationLogs();

    /************************ 数据持久化 ************************/
    bool saveExpressDataToFile(const std::string& filePath);
    bool loadExpressDataFromFile(const std::string& filePath);
    bool saveUserDataToFile(const std::string& filePath);
    bool loadUserDataFromFile(const std::string& filePath);
    bool saveStorageDataToFile(const std::string& filePath);
    bool loadStorageDataFromFile(const std::string& filePath);
    bool saveAbnormalDataToFile(const std::string& filePath);
    bool loadAbnormalDataFromFile(const std::string& filePath);
    bool saveAllData(const std::string& expressPath, const std::string& userPath,
        const std::string& storagePath, const std::string& abnormalPath);
    bool loadAllData(const std::string& expressPath, const std::string& userPath,
        const std::string& storagePath, const std::string& abnormalPath);

    /************************ 统计操作 ************************/
    int getInStockExpressCount();
    std::unordered_map<std::string, int> getDailyExpressCount(const std::string& date);
    std::unordered_map<std::string, int> getExpressCountByCompany();
    std::unordered_map<std::string, int> getAbnormalCountByType();
};

#endif // DATAMANAGER_H