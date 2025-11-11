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

/**************数据管理类***************/

class DataManager {
private:
    // 核心数据存储
    std::unordered_map<std::string, Express> expressMap;          // 单号|快递
    std::unordered_map<std::string, std::string> pickCodeMap;     // 取件码|单号
    std::unordered_map<std::string, User> userMap;                // 手机号|用户
    std::unordered_map<std::string, Storage> storageMap;          // 区域ID|存储区域
    std::list<Abnormal> abnormalList;                             // 异常记录列表
    std::list<std::string> operationLogStack;                     // 操作日志栈（用于回滚）人物
	
public:
    /************************ 快递操作 ************************/
	bool addExpress(const Express& exp);                                                                             // 添加快递
	Express getExpressByExpressId(const std::string& expressId);		                                             // 通过单号取快递
	Express getExpressByPickCode(const std::string& pickCode);													     // 通过取件码取快递
	bool updateExpressStatus(const std::string& expressId, ExpressStatus newStatus);								 // 更新快递状态
	bool updateExpressLocation(const std::string& expressId, const std::string& newLocation);   					 // 更新快递位置
	bool deleteExpress(const std::string& expressId);   													         // 删除快递
	std::list<Express> getExpressListByPhoneSuffix(const std::string& phoneSuffix); 								 // 通过手机号后缀获取快递列表
	std::list<Express> getExpressListByInTimeRange(const std::string& startDate, const std::string& endDate);		 // 获取指定时间段内入库的快递列表

    /************************ 用户操作 ************************/

	bool addOrUpdateUser(const User& user);                                                  // 添加或更新用户
	User getUserByPhone(const std::string& phone);  						                 // 通过手机号获取用户 
	bool addUserExpressHistory(const std::string& phone, const std::string& expressId);      // 添加用户快递历史记录
	std::list<std::string> getUserExpressHistory(const std::string& phone);					 // 获取用户快递历史记录

    /************************ 存储区域操作 ************************/

	bool addStorageArea(const Storage& storage);                                                // 添加存储区域
	Storage getStorageAreaByAreaId(const std::string& areaId);                                  // 通过区域ID获取存储区域
	bool updateStorageCapacity(const std::string& areaId, int newMaxCapacity);                  // 更新存储区域容量
	bool assignExpressToStorage(const std::string& areaId, const std::string& expressId);       // 分配快递到存储区域
	bool removeExpressFromStorage(const std::string& areaId, const std::string& expressId);     // 从存储区域移除快递
    std::unordered_map<std::string, float> getStorageOccupancyRate();

    /************************ 异常记录操作 ************************/

	bool addAbnormalRecord(const Abnormal& abnormal);                                             // 添加异常记录
	bool updateAbnormalHandleResult(const std::string& recordId, const std::string& result);	  // 更新异常处理结果
	std::list<Abnormal> getAllAbnormalRecords();											      // 获取所有异常记录
	std::list<Abnormal> getAbnormalRecordsByType(AbnormalType type);							  // 按类型获取异常记录
	bool deleteHandledAbnormalRecords();                                                          // 删除已处理的异常记录

    /************************ 操作日志与回滚 ************************/

	void addOperationLog(const std::string& logDesc);                                              // 添加操作日志
	bool rollbackLastOperation();												                   // 回滚最后一次操作
	std::list<std::string> getOperationLogs();													   // 获取操作日志列表

    /************************ 数据持久化 ************************/

	bool saveExpressDataToFile(const std::string& filePath);                                        // 保存快递数据到文件
	bool loadExpressDataFromFile(const std::string& filePath);									    // 从文件加载快递数据
	bool saveUserDataToFile(const std::string& filePath); 											// 保存用户数据到文件
	bool loadUserDataFromFile(const std::string& filePath);											// 从文件加载用户数据
	bool saveStorageDataToFile(const std::string& filePath); 										// 保存存储区域数据到文件
	bool loadStorageDataFromFile(const std::string& filePath); 										// 从文件加载存储区域数据
	bool saveAbnormalDataToFile(const std::string& filePath); 										// 保存异常记录数据到文件
	bool loadAbnormalDataFromFile(const std::string& filePath); 									// 从文件加载异常记录数据
    bool saveAllData(const std::string& expressPath, const std::string& userPath,
		const std::string& storagePath, const std::string& abnormalPath); 							// 保存所有数据
    bool loadAllData(const std::string& expressPath, const std::string& userPath,
		const std::string& storagePath, const std::string& abnormalPath); 							// 加载所有数据

    /************************ 统计操作 ************************/

	int getInStockExpressCount();															// 获取当前在库快递数量
	std::unordered_map<std::string, int> getDailyExpressCount(const std::string& date);		// 获取指定日期的快递入库数量
	std::unordered_map<std::string, int> getExpressCountByCompany();						// 获取各快递公司快递数量
	std::unordered_map<std::string, int> getAbnormalCountByType();							// 获取各异常类型数量		

};

#endif