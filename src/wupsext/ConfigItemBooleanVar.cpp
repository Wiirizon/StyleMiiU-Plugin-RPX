#include <cassert>
#include <cstdint>
#include <cstdio>
#include <memory>
#include <new>
#include <utility>

#include <wups/config_api.h>

#include "ConfigItemBooleanVar.h"

namespace wupsext {

    ConfigItemBooleanVarContext::ConfigItemBooleanVarContext(
        const std::string &identifier_,
        bool &variable_,
        ConfigItemBooleanVarChangedFunc changedCallback_,
        const std::optional<std::string> &trueLabel_,
        const std::optional<std::string> &falseLabel_) :
        identifier{identifier_},
        variable(variable_),
        changedCallback{changedCallback_},
        trueLabel{trueLabel_.value_or("yes")},
        falseLabel{falseLabel_.value_or("no")}
    {}

    void
    ConfigItemBooleanVarContext::toggleValue()
    {
        variable = !variable;
        if (changedCallback)
                changedCallback(*this);
    }

    namespace {

        void
        handle_onInput(void *ctx,
                       WUPSConfigSimplePadData input)
        {
            auto item = reinterpret_cast<ConfigItemBooleanVarContext*>(ctx);
            assert(item);
            if ((input.buttons_d & WUPS_CONFIG_BUTTON_A) == WUPS_CONFIG_BUTTON_A)
                item->toggleValue();
            else if (input.buttons_d & WUPS_CONFIG_BUTTON_LEFT && !item->variable)
                item->toggleValue();
            else if ((input.buttons_d & WUPS_CONFIG_BUTTON_RIGHT) && item->variable)
                item->toggleValue();
        }

        std::int32_t
        handle_getCurrentValueDisplay(void *ctx,
                                      char *buffer,
                                      std::int32_t size)
        {
            auto item = reinterpret_cast<ConfigItemBooleanVarContext*>(ctx);
            assert(item);
            std::snprintf(buffer, size, "%s",
                          item->variable ? item->trueLabel.data() : item->falseLabel.data());
            return 0;
        }

        std::int32_t
        handle_getCurrentValueSelectedDisplay(void *ctx,
                                              char *buffer,
                                              std::int32_t size)
        {
            auto item = reinterpret_cast<ConfigItemBooleanVarContext*>(ctx);
            assert(item);
            if (item->variable)
                std::snprintf(buffer, size, "  %s >", item->trueLabel.data());
            else
                std::snprintf(buffer, size, "< %s  ", item->falseLabel.data());
            return 0;
        }

        void
        handle_onDelete(void *ctx)
        {
            auto item = reinterpret_cast<ConfigItemBooleanVarContext*>(ctx);
            assert(item);
            delete item;
        }

    } // namespace

    WUPSConfigAPIStatus
    ConfigItemBooleanVar_Create(const std::string &identifier,
                                const std::string &displayName,
                                bool &variable,
                                ConfigItemBooleanVarChangedFunc changedCallback,
                                const std::optional<std::string> &trueLabel,
                                const std::optional<std::string> &falseLabel,
                                WUPSConfigItemHandle &outHandle)
        noexcept
    {
        try {
            auto item = std::make_unique<ConfigItemBooleanVarContext>(
                identifier,
                variable,
                changedCallback,
                trueLabel,
                falseLabel);

            WUPSConfigAPIItemCallbacksV2 callbacks = {
                .getCurrentValueDisplay         = &handle_getCurrentValueDisplay,
                .getCurrentValueSelectedDisplay = &handle_getCurrentValueSelectedDisplay,
                .onSelected                     = nullptr,
                .restoreDefault                 = nullptr,
                .isMovementAllowed              = nullptr,
                .onCloseCallback                = nullptr,
                .onInput                        = &handle_onInput,
                .onInputEx                      = nullptr,
                .onDelete                       = &handle_onDelete};

            WUPSConfigAPIItemOptionsV2 options = {
                .displayName = displayName.data(),
                .context     = item.get(),
                .callbacks   = callbacks,
            };

            if (auto err = WUPSConfigAPI_Item_Create(options, &item->handle))
                return err;

            outHandle = item->handle;

            item.release();
            return WUPSCONFIG_API_RESULT_SUCCESS;
        }
        catch (std::bad_alloc &) {
            return WUPSCONFIG_API_RESULT_OUT_OF_MEMORY;
        }
        catch (std::exception &) {
            return WUPSCONFIG_API_RESULT_UNKNOWN_ERROR;
        }
    }

    ConfigItemBooleanVar::ConfigItemBooleanVar(WUPSConfigItemHandle itemHandle)
        noexcept :
        WUPSConfigItem{itemHandle}
    {}

    std::expected<ConfigItemBooleanVar, Error>
    ConfigItemBooleanVar::CreateSafe(const std::string &identifier,
                                     const std::string &displayName,
                                     bool &variable,
                                     ConfigItemBooleanVarChangedFunc callback,
                                     const std::optional<std::string> &trueLabel,
                                     const std::optional<std::string> &falseLabel)
        noexcept
    {
        WUPSConfigItemHandle itemHandle;
        if (auto e = ConfigItemBooleanVar_Create(identifier,
                                                 displayName,
                                                 variable,
                                                 callback,
                                                 trueLabel,
                                                 falseLabel,
                                                 itemHandle))
            return std::unexpected{Error{e, "ConfigItemBooleanVar_Create() failed"}};
        return ConfigItemBooleanVar{itemHandle};
    }

    ConfigItemBooleanVar
    ConfigItemBooleanVar::Create(const std::string &identifier,
                                 const std::string &displayName,
                                 bool &variable,
                                 ConfigItemBooleanVarChangedFunc callback,
                                 const std::optional<std::string> &trueLabel,
                                 const std::optional<std::string> &falseLabel)
    {
        auto result = CreateSafe(identifier,
                                 displayName,
                                 variable,
                                 callback,
                                 trueLabel,
                                 falseLabel);
        if (!result)
            throw result.error();
        return std::move(*result);
    }

} // namespace wupsext
