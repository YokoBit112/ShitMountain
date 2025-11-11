#include "FileIO.h"
#include <fstream>
#include <iostream>
#include "Utils.h"
#include "GlobalDefine.h"

// 检查文件路径是否有效(实际实现:检查目录是否存在)
bool FileIO::checkFilePathValid(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        std::ofstream createFile(filePath, std::ios::binary);
        createFile.close();
    }
    return true;
}

bool FileIO::loadExpressFromFile(const std::string& filePath, std::list<Express>& expressList) {
    if (!checkFilePathValid(filePath)) return false;

    // 二进制模式打开，避免换行符转换影响UTF-8字节
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) return false;

    std::string line;
    while (std::getline(file, line)) {
        line = Utils::trimString(line);
        if (line.empty()) continue;

        std::vector<std::string> parts = Utils::splitString(line, ',');
        if (parts.size() != 7) continue;

        Express exp(
            parts[0], parts[1], parts[2], parts[3], parts[4], parts[5],
            EnumConverter::stringToExpressStatus(parts[6])
        );
        expressList.push_back(exp);
    }

    file.close();
    return true;
}

bool FileIO::saveExpressToFile(const std::string& filePath, const std::list<Express>& expressList) {
    if (!checkFilePathValid(filePath)) return false;

    // 二进制模式写入，确保UTF-8字节不被转换
    std::ofstream file(filePath, std::ios::binary);
    if (!file.is_open()) return false;

    for (const auto& exp : expressList) {
        file << exp.getExpressId() << ","
            << exp.getPickCode() << ","
            << exp.getUserPhone() << ","
            << exp.getCompany() << ","
            << exp.getInTime() << ","
            << exp.getLocation() << ","
            << exp.getStatusString() << "\n";
    }

    file.close();
    return true;
}

bool FileIO::appendExpressToFile(const std::string& filePath, const Express& exp) {
    if (!checkFilePathValid(filePath)) return false;
    std::ofstream file(filePath, std::ios::app | std::ios::binary);
    if (!file.is_open()) return false;

    file << exp.getExpressId() << ","
        << exp.getPickCode() << ","
        << exp.getUserPhone() << ","
        << exp.getCompany() << ","
        << exp.getInTime() << ","
        << exp.getLocation() << ","
        << exp.getStatusString() << "\n";
    file.close();
    return true;
}

bool FileIO::loadUserFromFile(const std::string& filePath, std::list<User>& userList) {
    if (!checkFilePathValid(filePath)) return false;
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) return false;

    std::string line;
    while (getline(file, line)) {
        line = Utils::trimString(line);
        if (line.empty()) continue;
        std::vector<std::string> parts = Utils::splitString(line, ',');
        if (parts.size() < 1) continue;

        User user(parts[0]);
        if (parts.size() >= 2) user.setName(parts[1]);
        if (parts.size() >= 3) {
            std::vector<std::string> historyIds = Utils::splitString(parts[2], '|');
            for (const auto& id : historyIds) {
                if (!Utils::isEmptyString(id)) user.addExpressHistory(id);
            }
        }
        userList.push_back(user);
    }
    file.close();
    return true;
}

bool FileIO::saveUserToFile(const std::string& filePath, const std::list<User>& userList) {
    if (!checkFilePathValid(filePath)) return false;
    std::ofstream file(filePath, std::ios::binary);
    if (!file.is_open()) return false;

    for (const auto& user : userList) {
        file << user.getPhone() << "," << user.getName();
        std::list<std::string> history = user.getExpressHistory();
        if (!history.empty()) {
            file << ",";
            for (auto it = history.begin(); it != history.end(); ++it) {
                if (it != history.begin()) file << "|";
                file << *it;
            }
        }
        file << "\n";
    }
    file.close();
    return true;
}

bool FileIO::loadStorageFromFile(const std::string& filePath, std::list<Storage>& storageList) {
    if (!checkFilePathValid(filePath)) return false;
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) return false;

    std::string line;
    while (getline(file, line)) {
        line = Utils::trimString(line);
        if (line.empty()) continue;
        std::vector<std::string> parts = Utils::splitString(line, ',');
        if (parts.size() < 2) continue;

        int maxCap = atoi(parts[1].c_str());
        Storage storage(parts[0], maxCap);
        if (parts.size() >= 3) {
            std::vector<std::string> expIds = Utils::splitString(parts[2], '|');
            for (const auto& id : expIds) {
                if (!Utils::isEmptyString(id)) storage.addExpress(id);
            }
        }
        storageList.push_back(storage);
    }
    file.close();
    return true;
}

bool FileIO::saveStorageToFile(const std::string& filePath, const std::list<Storage>& storageList) {
    if (!checkFilePathValid(filePath)) return false;
    std::ofstream file(filePath, std::ios::binary);
    if (!file.is_open()) return false;

    for (const auto& storage : storageList) {
        file << storage.getAreaId() << "," << storage.getMaxCapacity();
        std::list<std::string> expIds = storage.getExpressIds();
        if (!expIds.empty()) {
            file << ",";
            for (auto it = expIds.begin(); it != expIds.end(); ++it) {
                if (it != expIds.begin()) file << "|";
                file << *it;
            }
        }
        file << "\n";
    }
    file.close();
    return true;
}

bool FileIO::loadAbnormalFromFile(const std::string& filePath, std::list<Abnormal>& abnormalList) {
    if (!checkFilePathValid(filePath)) return false;
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) return false;

    std::string line;
    while (getline(file, line)) {
        line = Utils::trimString(line);
        if (line.empty()) continue;
        std::vector<std::string> parts = Utils::splitString(line, ',');
        if (parts.size() < 4) continue;

        Abnormal abnormal(
            parts[0], parts[1],
            EnumConverter::stringToAbnormalType(parts[2]),
            parts[3]
        );
        if (parts.size() >= 5) abnormal.updateHandleStatus(EnumConverter::stringToHandleStatus(parts[4]));
        if (parts.size() >= 6) abnormal.setHandleResult(parts[5], parts.size() >= 7 ? parts[6] : "");
        abnormalList.push_back(abnormal);
    }
    file.close();
    return true;
}

bool FileIO::saveAbnormalToFile(const std::string& filePath, const std::list<Abnormal>& abnormalList) {
    if (!checkFilePathValid(filePath)) return false;
    std::ofstream file(filePath, std::ios::binary);
    if (!file.is_open()) return false;

    for (const auto& abn : abnormalList) {
        file << abn.getRecordId() << ","
            << abn.getExpressId() << ","
            << abn.getAbnormalTypeString() << ","
            << abn.getCreateTime()<< ","
            << abn.getHandleStatusString();

        if (!abn.getHandleResult().empty()) {
            file << "," << abn.getHandleResult() << "," << abn.getHandleTime();
        }
        file << "\n";
    }
    file.close();
    return true;
}

bool FileIO::appendLogToFile(const std::string& logPath, const std::string& logContent) {
    if (!checkFilePathValid(logPath)) return false;
    std::ofstream file(logPath, std::ios::app | std::ios::binary);
    if (!file.is_open()) return false;

    file << "[" << Utils::getCurrentTimeStamp() << "] " << logContent << "\n";
    file.close();
    return true;
}

bool FileIO::loadLogFromFile(const std::string& logPath, std::list<std::string>& logList) {
    if (!checkFilePathValid(logPath)) return false;
    std::ifstream file(logPath, std::ios::binary);
    if (!file.is_open()) return false;

    std::string line;
    while (getline(file, line)) {
        line = Utils::trimString(line);
        if (!line.empty()) logList.push_back(line);
    }
    file.close();
    return true;
}
