#pragma once

#include <expected>
#include <functional>
#include <string>

#include <wups/config.h>
#include <wups/config/WUPSConfigItem.h>

#include "Error.h"

namespace wupsext {

    struct ConfigItemThemeContext;

    using ConfigItemThemeCallbackSignature = void (ConfigItemThemeContext &);
    using ConfigItemThemeCallbackFunc = std::function<ConfigItemThemeCallbackSignature>;


    struct ConfigItemThemeContext {
        WUPSConfigItemHandle handle;
        const std::string identifier;
        bool value;
        ConfigItemThemeCallbackFunc changedCallback;

        ConfigItemThemeContext(const std::string &identifier_,
                               bool value_,
                               ConfigItemThemeCallbackFunc changedCallback_);

        void
        toggleValue();
    };


    WUPSConfigAPIStatus
    ConfigItemTheme_Create(const std::string &identifier,
                           const std::string &displayName,
                           bool value,
                           ConfigItemThemeCallbackFunc changedCallback,
                           WUPSConfigItemHandle &outHandle)
        noexcept;

    void
    ConfigItemTheme_Clear();

    void
    ConfigItemTheme_ResetAll();

    void
    ConfigItemTheme_Select(ConfigItemThemeContext *item);

    void
    ConfigItemTheme_SelectByID(const std::string &identifier);

    void
    ConfigItemTheme_ForEach(ConfigItemThemeCallbackFunc callback);



    class ConfigItemTheme : public WUPSConfigItem {

        explicit
        ConfigItemTheme(WUPSConfigItemHandle itemHandle)
            noexcept;

    public:

        static
        std::expected<ConfigItemTheme, Error>
        CreateSafe(const std::string& identifier,
                   const std::string& displayName,
                   bool value,
                   ConfigItemThemeCallbackFunc changedCallback)
            noexcept;

        static
        ConfigItemTheme
        Create(const std::string& identifier,
               const std::string& displayName,
               bool value,
               ConfigItemThemeCallbackFunc changedCallback);

    };

} // namespace wupsext
