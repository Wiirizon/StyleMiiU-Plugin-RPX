#pragma once

#include <stdexcept>
#include <string>

namespace wupsext {

    struct Error : std::runtime_error {
        WUPSConfigAPIStatus code;

        Error(WUPSConfigAPIStatus code_,
              const char *msg);
        Error(WUPSConfigAPIStatus code_,
              const std::string &msg);
    };

} // namespace wupsext
