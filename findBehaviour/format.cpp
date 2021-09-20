#include "format.h"

namespace myFind {
    std::string format::boolToString(bool b) {
        return b ? "true" : "false";
    }
}