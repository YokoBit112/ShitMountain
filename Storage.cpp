#include "Storage.h"
#include "Utils.h"
// 仓库构造函数实现
Storage::Storage() : maxCapacity(0), currentCount(0) {}
Storage::Storage(const std::string& id, int cap) : areaId(id), maxCapacity(cap), currentCount(0) {}

// Getter实现
std::string Storage::getAreaId() const { return Utils::utf8ToGbk(areaId); }                         //获取仓库区域ID
int Storage::getMaxCapacity() const { return maxCapacity; }                                         //获取仓库最大容量
int Storage::getCurrentCount() const { return currentCount; }                                       //获取仓库当前包裹数量
std::list<std::string> Storage::getExpressIds() const { return expressIds; }                        //获取仓库内包裹ID列表
//获取仓库占用率
float Storage::getOccupancyRate() const {
    return maxCapacity == 0 ? 0.0f : static_cast<float>(currentCount) / maxCapacity;
}

// Setter实现
void Storage::setMaxCapacity(int newCap) { maxCapacity = newCap; }                                  //设置仓库最大容量

//添加包裹（入库
bool Storage::addExpress(const std::string& expressId) {
    if (currentCount >= maxCapacity) return false;
    expressIds.push_back(expressId);
    currentCount++;
    return true;
}

//删除包裹（出库
bool Storage::removeExpress(const std::string& expressId) {
    for (auto it = expressIds.begin(); it != expressIds.end(); ++it) {
        if (*it == expressId) {
            expressIds.erase(it);
            currentCount--;
            return true;
        }
    }
    return false;
}

//判断仓库满货
bool Storage::isFull() const { return currentCount >= maxCapacity; }

//查询包裹
bool Storage::hasExpress(const std::string& expressId) const {
    for (const auto& id : expressIds) {
        if (id == expressId) return true;
    }
    return false;
}
