#include "DataManager.h"
#include <iostream>
#include <algorithm>

/************************ 快递操作 ************************/
bool DataManager::addExpress(const Express& exp) {
    if (expressMap.find(exp.getExpressId()) != expressMap.end()) return false;
    if (pickCodeMap.find(exp.getPickCode()) != pickCodeMap.end()) return false;

    expressMap[exp.getExpressId()] = exp;
    pickCodeMap[exp.getPickCode()] = exp.getExpressId();

    // 记录操作日志
    std::string log = "添加快递：" + exp.getExpressId() + "（取件码：" + exp.getPickCode() + "）";
    addOperationLog(log);
    FileIO::appendLogToFile(GlobalConst::DEFAULT_LOG_PATH, log);

    return true;
}

Express DataManager::getExpressByExpressId(const std::string& expressId) {
    auto it = expressMap.find(expressId);
    return it != expressMap.end() ? it->second : Express();
}

Express DataManager::getExpressByPickCode(const std::string& pickCode) {
    auto it = pickCodeMap.find(pickCode);
    if (it == pickCodeMap.end()) return Express();
    return getExpressByExpressId(it->second);
}

bool DataManager::updateExpressStatus(const std::string& expressId, ExpressStatus newStatus) {
    auto it = expressMap.find(expressId);
    if (it == expressMap.end()) return false;

    std::string oldStatus = it->second.getStatusString();
    it->second.setStatus(newStatus);

    // 记录操作日志
    std::string log = "更新快递状态：" + expressId + "（" + oldStatus + "→" + it->second.getStatusString() + "）";
    addOperationLog(log);
    FileIO::appendLogToFile(GlobalConst::DEFAULT_LOG_PATH, log);

    return true;
}

bool DataManager::updateExpressLocation(const std::string& expressId, const std::string& newLocation) {
    auto it = expressMap.find(expressId);
    if (it == expressMap.end()) return false;

    std::string oldLoc = it->second.getLocation();
    it->second.setLocation(newLocation);

    // 记录操作日志
    std::string log = "更新快递位置：" + expressId + "（" + oldLoc + "→" + newLocation + "）";
    addOperationLog(log);
    FileIO::appendLogToFile(GlobalConst::DEFAULT_LOG_PATH, log);

    return true;
}

bool DataManager::deleteExpress(const std::string& expressId) {
    auto it = expressMap.find(expressId);
    if (it == expressMap.end()) return false;

    std::string pickCode = it->second.getPickCode();
    pickCodeMap.erase(pickCode);
    expressMap.erase(it);

    // 记录操作日志
    std::string log = "删除快递：" + expressId + "（取件码：" + pickCode + "）";
    addOperationLog(log);
    FileIO::appendLogToFile(GlobalConst::DEFAULT_LOG_PATH, log);

    return true;
}

std::list<Express> DataManager::getExpressListByPhoneSuffix(const std::string& phoneSuffix) {
    std::list<Express> result;
    for (const auto& pair : expressMap) {
        const Express& exp = pair.second;
        if (Utils::getPhoneSuffix(exp.getUserPhone()) == phoneSuffix) {
            result.push_back(exp);
        }
    }
    return result;
}

std::list<Express> DataManager::getExpressListByInTimeRange(const std::string& startDate, const std::string& endDate) {
    std::list<Express> result;
    for (const auto& pair : expressMap) {
        const Express& exp = pair.second;
        std::string expDate = exp.getInTime().substr(0, 10);
        if (Utils::calculateDateDiff(expDate, startDate) >= 0 && Utils::calculateDateDiff(endDate, expDate) >= 0) {
            result.push_back(exp);
        }
    }
    return result;
}

/************************ 用户操作 ************************/
bool DataManager::addOrUpdateUser(const User& user) {
    std::string phone = user.getPhone();
    userMap[phone] = user;

    // 记录操作日志
    std::string log = "添加/更新用户：" + phone;
    addOperationLog(log);
    FileIO::appendLogToFile(GlobalConst::DEFAULT_LOG_PATH, log);

    return true;
}

User DataManager::getUserByPhone(const std::string& phone) {
    auto it = userMap.find(Utils::desensitizePhone(phone));
    return it != userMap.end() ? it->second : User();
}

bool DataManager::addUserExpressHistory(const std::string& phone, const std::string& expressId) {
    std::string desPhone = Utils::desensitizePhone(phone);
    auto it = userMap.find(desPhone);
    if (it == userMap.end()) return false;

    it->second.addExpressHistory(expressId);

    // 记录操作日志
    std::string log = "添加用户取件记录：" + desPhone + "→" + expressId;
    addOperationLog(log);
    FileIO::appendLogToFile(GlobalConst::DEFAULT_LOG_PATH, log);

    return true;
}

std::list<std::string> DataManager::getUserExpressHistory(const std::string& phone) {
    User user = getUserByPhone(phone);
    return user.getExpressHistory();
}

/************************ 存储区域操作 ************************/
bool DataManager::addStorageArea(const Storage& storage) {
    if (storageMap.find(storage.getAreaId()) != storageMap.end()) return false;
    storageMap[storage.getAreaId()] = storage;

    // 记录操作日志
    std::string log = "添加存储区域：" + storage.getAreaId() + "（容量：" + std::to_string(storage.getMaxCapacity()) + "）";
    addOperationLog(log);
    FileIO::appendLogToFile(GlobalConst::DEFAULT_LOG_PATH, log);

    return true;
}

Storage DataManager::getStorageAreaByAreaId(const std::string& areaId) {
    auto it = storageMap.find(areaId);
    return it != storageMap.end() ? it->second : Storage();
}

bool DataManager::updateStorageCapacity(const std::string& areaId, int newMaxCapacity) {
    auto it = storageMap.find(areaId);
    if (it == storageMap.end()) return false;

    int oldCap = it->second.getMaxCapacity();
    it->second.setMaxCapacity(newMaxCapacity);

    // 记录操作日志
    std::string log = "更新存储区域容量：" + areaId + "（" + std::to_string(oldCap) + "→" + std::to_string(newMaxCapacity) + "）";
    addOperationLog(log);
    FileIO::appendLogToFile(GlobalConst::DEFAULT_LOG_PATH, log);

    return true;
}

bool DataManager::assignExpressToStorage(const std::string& areaId, const std::string& expressId) {
    auto storageIt = storageMap.find(areaId);
    if (storageIt == storageMap.end()) return false;
    if (!expressMap.count(expressId)) return false;

    if (storageIt->second.addExpress(expressId)) {
        // 记录操作日志
        std::string log = "分配快递到存储区域：" + expressId + "→" + areaId;
        addOperationLog(log);
        FileIO::appendLogToFile(GlobalConst::DEFAULT_LOG_PATH, log);
        return true;
    }
    return false;
}

bool DataManager::removeExpressFromStorage(const std::string& areaId, const std::string& expressId) {
    auto storageIt = storageMap.find(areaId);
    if (storageIt == storageMap.end()) return false;

    if (storageIt->second.removeExpress(expressId)) {
        // 记录操作日志
        std::string log = "从存储区域移除快递：" + areaId + "→" + expressId;
        addOperationLog(log);
        FileIO::appendLogToFile(GlobalConst::DEFAULT_LOG_PATH, log);
        return true;
    }
    return false;
}

std::unordered_map<std::string, float> DataManager::getStorageOccupancyRate() {
    std::unordered_map<std::string, float> result;
    for (const auto& pair : storageMap) {
        result[pair.first] = pair.second.getOccupancyRate();
    }
    return result;
}

/************************ 异常记录操作 ************************/
bool DataManager::addAbnormalRecord(const Abnormal& abnormal) {
    for (const auto& abn : abnormalList) {
        if (abn.getRecordId() == abnormal.getRecordId()) return false;
    }
    abnormalList.push_back(abnormal);

    // 更新快递状态为异常
    updateExpressStatus(abnormal.getExpressId(), ExpressStatus::ABNORMAL);

    // 记录操作日志
    std::string log = "添加异常记录：" + abnormal.getRecordId() + "（" + abnormal.getAbnormalTypeString() + "）";
    addOperationLog(log);
    FileIO::appendLogToFile(GlobalConst::DEFAULT_LOG_PATH, log);

    return true;
}

bool DataManager::updateAbnormalHandleResult(const std::string& recordId, const std::string& result) {
    for (auto& abn : abnormalList) {
        if (abn.getRecordId() == recordId) {
            abn.setHandleResult(result, Utils::getCurrentTimeStamp());

            // 记录操作日志
            std::string log = "处理异常记录：" + recordId + "（结果：" + result + "）";
            addOperationLog(log);
            FileIO::appendLogToFile(GlobalConst::DEFAULT_LOG_PATH, log);
            return true;
        }
    }
    return false;
}

std::list<Abnormal> DataManager::getAllAbnormalRecords() {
    return abnormalList;
}

std::list<Abnormal> DataManager::getAbnormalRecordsByType(AbnormalType type) {
    std::list<Abnormal> result;
    for (const auto& abn : abnormalList) {
        if (abn.getAbnormalType() == type) {
            result.push_back(abn);
        }
    }
    return result;
}

bool DataManager::deleteHandledAbnormalRecords() {
    int count = 0;
    auto it = abnormalList.begin();
    while (it != abnormalList.end()) {
        if (it->isHandled()) {
            // 记录操作日志
            std::string log = "删除已处理异常记录：" + it->getRecordId();
            addOperationLog(log);
            FileIO::appendLogToFile(GlobalConst::DEFAULT_LOG_PATH, log);

            it = abnormalList.erase(it);
            count++;
        }
        else {
            ++it;
        }
    }
    return count > 0;
}

/************************ 操作日志与回滚 ************************/
void DataManager::addOperationLog(const std::string& logDesc) {
    operationLogStack.push_back(logDesc);
    // 限制日志栈大小（最多保留100条）
    if (operationLogStack.size() > 100) {
        operationLogStack.pop_front();
    }
}

bool DataManager::rollbackLastOperation() {
    if (operationLogStack.empty()) return false;
    // 简化回滚：仅删除最后一条日志（实际需根据操作类型执行反向逻辑）
    std::string lastLog = operationLogStack.back();
    operationLogStack.pop_back();

    // 记录回滚日志
    std::string log = "回滚操作：" + lastLog;
    addOperationLog(log);
    FileIO::appendLogToFile(GlobalConst::DEFAULT_LOG_PATH, log);

    return true;
}

std::list<std::string> DataManager::getOperationLogs() {
    return operationLogStack;
}

/************************ 数据持久化 ************************/
bool DataManager::saveExpressDataToFile(const std::string& filePath) {
    std::list<Express> expressList;
    for (const auto& pair : expressMap) {
        expressList.push_back(pair.second);
    }
    return FileIO::saveExpressToFile(filePath, expressList);
}

bool DataManager::loadExpressDataFromFile(const std::string& filePath) {
    std::list<Express> expressList;
    if (!FileIO::loadExpressFromFile(filePath, expressList)) return false;

    expressMap.clear();
    pickCodeMap.clear();
    for (const auto& exp : expressList) {
        expressMap[exp.getExpressId()] = exp;
        pickCodeMap[exp.getPickCode()] = exp.getExpressId();
    }
    return true;
}

bool DataManager::saveUserDataToFile(const std::string& filePath) {
    std::list<User> userList;
    for (const auto& pair : userMap) {
        userList.push_back(pair.second);
    }
    return FileIO::saveUserToFile(filePath, userList);
}

bool DataManager::loadUserDataFromFile(const std::string& filePath) {
    std::list<User> userList;
    if (!FileIO::loadUserFromFile(filePath, userList)) return false;

    userMap.clear();
    for (const auto& user : userList) {
        userMap[user.getPhone()] = user;
    }
    return true;
}

bool DataManager::saveStorageDataToFile(const std::string& filePath) {
    std::list<Storage> storageList;
    for (const auto& pair : storageMap) {
        storageList.push_back(pair.second);
    }
    return FileIO::saveStorageToFile(filePath, storageList);
}

bool DataManager::loadStorageDataFromFile(const std::string& filePath) {
    std::list<Storage> storageList;
    if (!FileIO::loadStorageFromFile(filePath, storageList)) return false;

    storageMap.clear();
    for (const auto& storage : storageList) {
        storageMap[storage.getAreaId()] = storage;
    }
    return true;
}

bool DataManager::saveAbnormalDataToFile(const std::string& filePath) {
    return FileIO::saveAbnormalToFile(filePath, abnormalList);
}

bool DataManager::loadAbnormalDataFromFile(const std::string& filePath) {
    std::list<Abnormal> abnormalListTmp;
    if (!FileIO::loadAbnormalFromFile(filePath, abnormalListTmp)) return false;

    abnormalList.clear();
    abnormalList = abnormalListTmp;
    return true;
}

bool DataManager::saveAllData(const std::string& expressPath, const std::string& userPath,
    const std::string& storagePath, const std::string& abnormalPath) {
    bool res1 = saveExpressDataToFile(expressPath);
    bool res2 = saveUserDataToFile(userPath);
    bool res3 = saveStorageDataToFile(storagePath);
    bool res4 = saveAbnormalDataToFile(abnormalPath);
    return res1 && res2 && res3 && res4;
}

bool DataManager::loadAllData(const std::string& expressPath, const std::string& userPath,
    const std::string& storagePath, const std::string& abnormalPath) {
    bool res1 = loadExpressDataFromFile(expressPath);
    bool res2 = loadUserDataFromFile(userPath);
    bool res3 = loadStorageDataFromFile(storagePath);
    bool res4 = loadAbnormalDataFromFile(abnormalPath);

    // 加载操作日志
    FileIO::loadLogFromFile(GlobalConst::DEFAULT_LOG_PATH, operationLogStack);
    return res1 && res2 && res3 && res4;
}

/************************ 统计操作 ************************/
int DataManager::getInStockExpressCount() {
    int count = 0;
    for (const auto& pair : expressMap) {
        if (pair.second.getStatus() == ExpressStatus::IN_STOCK) count++;
    }
    return count;
}

std::unordered_map<std::string, int> DataManager::getDailyExpressCount(const std::string& date) {
    std::unordered_map<std::string, int> result = { {"in", 0}, {"out", 0} };
    for (const auto& pair : expressMap) {
        const Express& exp = pair.second;
        std::string expDate = exp.getInTime().substr(0, 10);
        if (expDate == date) {
            if (exp.getStatus() == ExpressStatus::IN_STOCK) {
                result["in"]++;
            }
            else if (exp.getStatus() == ExpressStatus::PICKED) {
                result["out"]++;
            }
        }
    }
    return result;
}

std::unordered_map<std::string, int> DataManager::getExpressCountByCompany() {
    std::unordered_map<std::string, int> result;
    for (const auto& pair : expressMap) {
        std::string company = pair.second.getCompany();
        result[company]++;
    }
    return result;
}

std::unordered_map<std::string, int> DataManager::getAbnormalCountByType() {
    std::unordered_map<std::string, int> result;
    for (const auto& abn : abnormalList) {
        std::string type = abn.getAbnormalTypeString();
        result[type]++;
    }
    return result;
}