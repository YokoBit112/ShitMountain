#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <list>
/**************仓库容量类***************/

class Storage {
private:
    std::string areaId;                  // 区域ID（如"A-1"）
    int maxCapacity;                     // 最大容量
    int currentCount;                    // 当前占用数
    std::list<std::string> expressIds;   // 存储的快递单号列表

public:
    /******构造函数******/

	//无参构造函数
    Storage();
	//有参构造函数
	//传入参数：string  id    ：区域ID
    //          int     cap   ：最大容量
    Storage(const std::string& id, int cap);

    /*****GETTER声明******/

	std::string getAreaId() const;                  // 获取区域ID
	int getMaxCapacity() const;					    // 获取最大容量 
	int getCurrentCount() const;    	            // 获取当前占用数
	std::list<std::string> getExpressIds() const;   // 获取存储的快递单号列表
    float getOccupancyRate() const;                 // 计算占用率

	/*****SETTER声明******/

	void setMaxCapacity(int newCap);			        // 设置最大容量
    bool addExpress(const std::string& expressId);      // 添加快递（成功返回true，满仓返回false）
    bool removeExpress(const std::string& expressId);   // 移除快递（成功返回true，无该快递返回false）
    bool isFull() const;                                // 判断是否满仓
    bool hasExpress(const std::string& expressId) const;// 判断是否包含指定快递
};

#endif 
