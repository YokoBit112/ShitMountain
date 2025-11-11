#include "Ctrl.h"


/************************ 异常记录操作 ************************/



//添加异常记录
//传入Abnormal异常记录信息
//传出状态位             success:true
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

//更新异常处理结果
//传入str记录ID、str处理结果
//传出状态位             success:true
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

//获取所有异常记录
//传入无
//传出list<Abnormal>异常记录表
std::list<Abnormal> DataManager::getAllAbnormalRecords() {
    return abnormalList;
}

//通过类型获取异常记录
//传入AbnormalType异常类型
//传出list<Abnormal>异常记录表
std::list<Abnormal> DataManager::getAbnormalRecordsByType(AbnormalType type) {
    std::list<Abnormal> result;
    for (const auto& abn : abnormalList) {
        if (abn.getAbnormalType() == type) {
            result.push_back(abn);
        }
    }
    return result;
}

//删除已处理的异常记录
//传入无
//传出状态位             success:true
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
