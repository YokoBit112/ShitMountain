#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <list>

class Storage {
private:
    std::string areaId;          // 区域ID（如"A-1"）
    int maxCapacity;             // 最大容量
    int currentCount;            // 当前占用数
    std::list<std::string> expressIds; // 存储的快递单号列表

public:
    // 构造函数
    Storage();
    Storage(const std::string& id, int cap);

    // Getter
    std::string getAreaId() const;
    int getMaxCapacity() const;
    int getCurrentCount() const;
    std::list<std::string> getExpressIds() const;
    // 计算占用率
    float getOccupancyRate() const;

    // Setter
    void setMaxCapacity(int newCap);
    // 添加快递（成功返回true，满仓返回false）
    bool addExpress(const std::string& expressId);
    // 移除快递（成功返回true，无该快递返回false）
    bool removeExpress(const std::string& expressId);
    // 判断是否满仓
    bool isFull() const;
    // 判断是否包含指定快递
    bool hasExpress(const std::string& expressId) const;
};

#endif // STORAGE_H
