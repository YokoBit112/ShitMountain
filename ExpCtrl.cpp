#include "Ctrl.h"


/************************ 快递操作 ************************/


//添加快递
//传入参数：Express类
//传出状态位                     success:true/false
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

//通过快递单号取快递
//传入参数： str快递id
//传出Express类
Express DataManager::getExpressByExpressId(const std::string& expressId) {
    auto it = expressMap.find(expressId);
    return it != expressMap.end() ? it->second : Express();
}

//通过取件码取快递
//传入参数：str取件码
//传出参数：Express类
Express DataManager::getExpressByPickCode(const std::string& pickCode) {
    auto it = pickCodeMap.find(pickCode);
    if (it == pickCodeMap.end()) return Express();
    return getExpressByExpressId(it->second);
}

//更新快递状态                         状态：在库、出库、异常
//传入ExpId快递单号、ExpSta新状态
//传出bool                             success：true
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

//更新快递位置
//传入ExpID快递单号，str快递位置
//传出状态位                         success:true
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


//删除快递
//传入expID快递单号
//传出状态位
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


//查询快递（手机尾号）
//传入str尾号
//传出list<express> 快递表
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


//查找段时间内入库的快递
//传入str起始时间、str结束时间
//传出lis<exp>出库快递表
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