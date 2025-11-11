#include "Ctrl.h"

/************************ 存储区域操作 ************************/



//添加存储区域
//传入Storage存储区域信息
//传出状态位             success:true
bool DataManager::addStorageArea(const Storage& storage) {
    if (storageMap.find(storage.getAreaId()) != storageMap.end()) return false;
    storageMap[storage.getAreaId()] = storage;

    // 记录操作日志
    std::string log = "添加存储区域：" + storage.getAreaId() + "（容量：" + std::to_string(storage.getMaxCapacity()) + "）";
    addOperationLog(log);
    FileIO::appendLogToFile(GlobalConst::DEFAULT_LOG_PATH, log);

    return true;
}

//通过区域ID查询存储区域
//传入str区域ID
//传出Storage存储区域信息
Storage DataManager::getStorageAreaByAreaId(const std::string& areaId) {
    auto it = storageMap.find(areaId);
    return it != storageMap.end() ? it->second : Storage();
}

//更新存储区域容量
//传入str区域ID、int新容量
//传出状态位             success:true
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

//分配快递到存储区域
//传入str区域ID、str快递单号
//传出状态位             success:true
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

//从存储区域移除快递
//传入str区域ID、str快递单号
//传出状态位             success:true
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

//获取所有存储区域的占用率
//传入无
//传出unordered_map<str,float>区域ID-占用率表
std::unordered_map<std::string, float> DataManager::getStorageOccupancyRate() {
    std::unordered_map<std::string, float> result;
    for (const auto& pair : storageMap) {
        result[pair.first] = pair.second.getOccupancyRate();
    }
    return result;
}
