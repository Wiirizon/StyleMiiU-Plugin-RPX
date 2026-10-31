#pragma once

/**
 * ConfigItemBooleanVar: config item for a bool variable.
 *
 * This differs from WUPSConfigItemBoolean:
 * - State is stored in a user-provided boolean variable.
 * - Said state is updated immediately after input.
 * - The changed callback is invoked immediately after the value changes.
 * - The default true/false labels are "yes/no".
 * - We don't bother making it C-friendly.
 */

#include <expected>
#include <functional>
#include <optional>
#include <string>

#include <wups/config.h>
#include <wups/config/WUPSConfigItem.h>

#include "Error.h"

namespace wupsext {

    struct ConfigItemBooleanVarContext;

    using ConfigItemBooleanVarChangedSignature = void (ConfigItemBooleanVarContext &);
    using ConfigItemBooleanVarChangedFunc = std::function<ConfigItemBooleanVarChangedSignature>;

    struct ConfigItemBooleanVarContext {
        WUPSConfigItemHandle handle;
        const std::string identifier;
        bool &variable;
        ConfigItemBooleanVarChangedFunc changedCallback;
        const std::string trueLabel;
        const std::string falseLabel;

        ConfigItemBooleanVarContext(const std::string &identifier_,
                                    bool &variable_,
                                    ConfigItemBooleanVarChangedFunc changedCallback_,
                                    const std::optional<std::string> &trueLabel_,
                                    const std::optional<std::string> &falseLabel_);

        void
        toggleValue();

    };

    WUPSConfigAPIStatus
    ConfigItemBooleanVar_Create(const std::string &identifier,
                                const std::string &displayName,
                                bool &variable,
                                ConfigItemBooleanVarChangedFunc changedCallback,
                                const std::optional<std::string> &trueLabel,
                                const std::optional<std::string> &falseLabel,
                                WUPSConfigItemHandle &outHandle)
        noexcept;

    class ConfigItemBooleanVar : public WUPSConfigItem {

        explicit
        ConfigItemBooleanVar(WUPSConfigItemHandle itemHandle)
            noexcept;

    public:

        static
        std::expected<ConfigItemBooleanVar, Error>
        CreateSafe(const std::string &identifier,
                   const std::string &displayName,
                   bool &variable,
                   ConfigItemBooleanVarChangedFunc callback = {},
                   const std::optional<std::string> &trueLabel = {},
                   const std::optional<std::string> &falseLabel = {})
            noexcept;

        static
        ConfigItemBooleanVar
        Create(const std::string &identifier,
               const std::string &displayName,
               bool &variable,
               ConfigItemBooleanVarChangedFunc callback = {},
               const std::optional<std::string> &trueLabel = {},
               const std::optional<std::string> &falseLabel = {});

    };

} // namespace wupsext
