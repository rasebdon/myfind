#include "formatHelper.h"

namespace myFind {
    std::string formatHelper::boolToString(bool b) {
        return b ? "true" : "false";
    }
}