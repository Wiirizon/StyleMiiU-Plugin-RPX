#include <wups/config_api.h>

#include "Error.h"

using namespace std::literals;

namespace wupsext {

    Error::Error(WUPSConfigAPIStatus code_,
                 const char *msg) :
        std::runtime_error{msg + ": "s + WUPSConfigAPI_GetStatusStr(code_)},
        code{code_}
    {}

    Error::Error(WUPSConfigAPIStatus code_,
                 const std::string &msg) :
        std::runtime_error{msg + ": "s + WUPSConfigAPI_GetStatusStr(code_)},
        code{code_}
    {}

} // namespace wupsext
