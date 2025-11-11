#include "Storage.h"
#include "Utils.h"
// 构造函数实现
Storage::Storage() : maxCapacity(0), currentCount(0) {}
Storage::Storage(const std::string& id, int cap) : areaId(id), maxCapacity(cap), currentCount(0) {}

// Getter实现
std::string Storage::getAreaId() const { return Utils::utf8ToGbk(areaId); }
int Storage::getMaxCapacity() const { return maxCapacity; }
int Storage::getCurrentCount() const { return currentCount; }
std::list<std::string> Storage::getExpressIds() const { return expressIds; }
float Storage::getOccupancyRate() const {
    return maxCapacity == 0 ? 0.0f : static_cast<float>(currentCount) / maxCapacity;
}

// Setter实现
void Storage::setMaxCapacity(int newCap) { maxCapacity = newCap; }

bool Storage::addExpress(const std::string& expressId) {
    if (currentCount >= maxCapacity) return false;
    expressIds.push_back(expressId);
    currentCount++;
    return true;
}

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

bool Storage::isFull() const { return currentCount >= maxCapacity; }

bool Storage::hasExpress(const std::string& expressId) const {
    for (const auto& id : expressIds) {
        if (id == expressId) return true;
    }
    return false;
}
