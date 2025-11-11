#include "Ctrl.h"

/************************ 操作日志与回滚 ************************/



//添加操作日志
//传入str日志描述
//传出无
void DataManager::addOperationLog(const std::string& logDesc) {
    operationLogStack.push_back(logDesc);
    // 限制日志栈大小（最多保留100条）
    if (operationLogStack.size() > 100) {
        operationLogStack.pop_front();
    }
}

//回滚最后一次操作
//传入无
//传出状态位             success:true
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


//获取操作日志
//传入无
//传出list<str>操作日志表
std::list<std::string> DataManager::getOperationLogs() {
    return operationLogStack;
}

/************************ 数据持久化 ************************/
//保存快递数据到文件
//传入str文件路径
//传出状态位             success:true
bool DataManager::saveExpressDataToFile(const std::string& filePath) {
    std::list<Express> expressList;
    for (const auto& pair : expressMap) {
        expressList.push_back(pair.second);
    }
    return FileIO::saveExpressToFile(filePath, expressList);
}

//加载快递数据从文件
//传入str文件路径
//传出状态位             success:true
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

//保存用户数据到文件
//传入str文件路径
//传出状态位             success:true
bool DataManager::saveUserDataToFile(const std::string& filePath) {
    std::list<User> userList;
    for (const auto& pair : userMap) {
        userList.push_back(pair.second);
    }
    return FileIO::saveUserToFile(filePath, userList);
}

//加载用户数据从文件
//传入str文件路径
//传出状态位             success:true
bool DataManager::loadUserDataFromFile(const std::string& filePath) {
    std::list<User> userList;
    if (!FileIO::loadUserFromFile(filePath, userList)) return false;

    userMap.clear();
    for (const auto& user : userList) {
        userMap[user.getPhone()] = user;
    }
    return true;
}

//保存存储区域数据到文件
//传入str文件路径
//传出状态位             success:true
bool DataManager::saveStorageDataToFile(const std::string& filePath) {
    std::list<Storage> storageList;
    for (const auto& pair : storageMap) {
        storageList.push_back(pair.second);
    }
    return FileIO::saveStorageToFile(filePath, storageList);
}

//加载存储区域数据从文件
//传入str文件路径
//传出状态位             success:true
bool DataManager::loadStorageDataFromFile(const std::string& filePath) {
    std::list<Storage> storageList;
    if (!FileIO::loadStorageFromFile(filePath, storageList)) return false;

    storageMap.clear();
    for (const auto& storage : storageList) {
        storageMap[storage.getAreaId()] = storage;
    }
    return true;
}

//保存异常记录数据到文件
//传入str文件路径
//传出状态位             success:true
bool DataManager::saveAbnormalDataToFile(const std::string& filePath) {
    return FileIO::saveAbnormalToFile(filePath, abnormalList);
}

//加载异常记录数据从文件
//传入str文件路径
//传出状态位             success:true
bool DataManager::loadAbnormalDataFromFile(const std::string& filePath) {
    std::list<Abnormal> abnormalListTmp;
    if (!FileIO::loadAbnormalFromFile(filePath, abnormalListTmp)) return false;

    abnormalList.clear();
    abnormalList = abnormalListTmp;
    return true;
}

//保存所有数据
//传入str快递文件路径、str用户文件路径、str存储区域文件路径、str异常记录文件路径
//传出状态位             success:true
bool DataManager::saveAllData(const std::string& expressPath, const std::string& userPath,
    const std::string& storagePath, const std::string& abnormalPath) {
    bool res1 = saveExpressDataToFile(expressPath);
    bool res2 = saveUserDataToFile(userPath);
    bool res3 = saveStorageDataToFile(storagePath);
    bool res4 = saveAbnormalDataToFile(abnormalPath);
    return res1 && res2 && res3 && res4;
}



// 加载所有数据
//传入str快递文件路径、str用户文件路径、str存储区域文件路径、str异常记录文件路径
//传出状态位             success:true
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
//获取在库快递数量
//传入无
//传出int在库快递数量
int DataManager::getInStockExpressCount() {
    int count = 0;
    for (const auto& pair : expressMap) {
        if (pair.second.getStatus() == ExpressStatus::IN_STOCK) count++;
    }
    return count;
}

//获取出库快递数量
//传入无
//传出int出库快递数量
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

//获取各快递公司快递数量
//传入无
//传出unordered_map<str,int>快递公司-快递数量表
std::unordered_map<std::string, int> DataManager::getExpressCountByCompany() {
    std::unordered_map<std::string, int> result;
    for (const auto& pair : expressMap) {
        std::string company = pair.second.getCompany();
        result[company]++;
    }
    return result;
}

//获取各异常类型数量
//传入无
//传出unordered_map<str,int>异常类型-异常数量表
std::unordered_map<std::string, int> DataManager::getAbnormalCountByType() {
    std::unordered_map<std::string, int> result;
    for (const auto& abn : abnormalList) {
        std::string type = abn.getAbnormalTypeString();
        result[type]++;
    }
    return result;
}