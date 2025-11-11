#include "GlobalDefine.h"
#include <string>

// 全局常量定义实现
namespace GlobalConst {
    const std::string ADMIN_DEFAULT_PWD = "123";
    const int EXPRESS_OVERDUE_DAYS = 7;
    const std::string PICK_CODE_PREFIX = "YZ-";
    const int PICK_CODE_RANDOM_LEN = 4;
    const float STORAGE_WARN_THRESHOLD = 0.9f;
    const std::string DEFAULT_EXPRESS_PATH = "data/express.txt";
    const std::string DEFAULT_USER_PATH = "data/user.txt";
    const std::string DEFAULT_STORAGE_PATH = "data/storage.txt";
    const std::string DEFAULT_ABNORMAL_PATH = "data/abnormal.txt";
    const std::string DEFAULT_LOG_PATH = "data/operation.log";
}
