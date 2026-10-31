#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <new>
#include <utility>
#include <vector>

#include "ConfigItemTheme.h"
#include <wups/config_api.h>

#include "globals.h"
#include "utils/logger.h"


namespace wupsext {

    // We use this to make the items behave like radio buttons when not shuffling.
    std::vector<ConfigItemThemeContext*> all_theme_items;


    ConfigItemThemeContext::ConfigItemThemeContext(const std::string &identifier_,
                                                   bool value_,
                                                   ConfigItemThemeCallbackFunc changedCallback_) :
        identifier{identifier_},
        value{value_},
        changedCallback{changedCallback_}
    {}

    void
    ConfigItemThemeContext::toggleValue()
    {
        value = !value;
        if (changedCallback)
            changedCallback(*this);
    }

    namespace {

        void
        handle_onInput(void *ctx, WUPSConfigSimplePadData input)
        {
            auto item = reinterpret_cast<ConfigItemThemeContext*>(ctx);
            assert(item);
            if ((input.buttons_d & WUPS_CONFIG_BUTTON_A) == WUPS_CONFIG_BUTTON_A) {
                item->toggleValue();
                if (!gShuffleThemes && item->value)
                    ConfigItemTheme_Select(item);
            }
        }

        std::int32_t
        handle_getCurrentValueDisplay(void *ctx,
                                      char *out_buf,
                                      std::int32_t out_size)
        {
            auto item = reinterpret_cast<ConfigItemThemeContext*>(ctx);
            assert(item);
            if (!item->value) {
                if (gShuffleThemes) {
                    std::snprintf(out_buf, out_size, "□");
                } else {
                    std::snprintf(out_buf, out_size, "○");
                }
            } else {
                if (gShuffleThemes) {
                    std::snprintf(out_buf, out_size, "■");
                } else {
                    std::snprintf(out_buf, out_size, "◉");
                }
            }
            return 0;
        }

        std::int32_t
        handle_getCurrentValueSelectedDisplay(void *ctx,
                                              char *out_buf,
                                              std::int32_t out_size)
        {
            auto item = reinterpret_cast<ConfigItemThemeContext*>(ctx);
            assert(item);
            if (!item->value) {
                std::snprintf(out_buf, out_size,
                              gShuffleThemes
                              ? "(Press \ue000 to enable) □"
                              : "(Press \ue000 to apply) ○");
            } else {
                if(gShuffleThemes) {
                    std::snprintf(out_buf, out_size, "(Press \ue000 to disable) ■");
                } else {
                    std::snprintf(out_buf, out_size, "(Press \ue000 to disable) ◉");
                }
            }
            return 0;
        }

        void
        handle_onDelete(void *ctx)
        {
            auto item = reinterpret_cast<ConfigItemThemeContext*>(ctx);
            assert(item);
            delete item;
        }

    } // namespace

    WUPSConfigAPIStatus
    ConfigItemTheme_Create(const std::string &identifier,
                           const std::string &displayName,
                           bool value,
                           ConfigItemThemeCallbackFunc changedCallback,
                           WUPSConfigItemHandle &outHandle)
        noexcept
    {
        try {
            auto item = std::make_unique<ConfigItemThemeContext>(identifier,
                                                                 value,
                                                                 changedCallback);

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
            all_theme_items.push_back(item.get());

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

    void
    ConfigItemTheme_Clear()
    {
        all_theme_items.clear();
    }

    void
    ConfigItemTheme_ResetAll()
    {
        DEBUG_FUNCTION_LINE_VERBOSE("Resetting all items!");
        for (auto it : all_theme_items)
            it->value = false;
    }

    void
    ConfigItemTheme_Select(ConfigItemThemeContext* item)
    {
        DEBUG_FUNCTION_LINE_VERBOSE("Selecting only %s", item->identifier.data());
        for (auto it : all_theme_items)
            it->value = it == item;
    }

    void
    ConfigItemTheme_SelectByID(const std::string &identifier)
    {
        for (auto it : all_theme_items)
            it->value = identifier == it->identifier;
    }

    void
    ConfigItemTheme_ForEach(ConfigItemThemeCallbackFunc callback)
    {
        for (auto it : all_theme_items)
            callback(*it);
    }

    ConfigItemTheme::ConfigItemTheme(WUPSConfigItemHandle itemHandle)
        noexcept :
        WUPSConfigItem{itemHandle}
    {}

    std::expected<ConfigItemTheme, Error>
    ConfigItemTheme::CreateSafe(const std::string& identifier,
                                const std::string& displayName,
                                bool value,
                                ConfigItemThemeCallbackFunc changedCallback)
        noexcept
    {
        WUPSConfigItemHandle itemHandle;
        if (auto e = ConfigItemTheme_Create(identifier,
                                            displayName,
                                            value,
                                            changedCallback,
                                            itemHandle))
            return std::unexpected{Error{e, "ConfigItemTheme_Create() failed"}};
        return ConfigItemTheme{itemHandle};
    }

    ConfigItemTheme
    ConfigItemTheme::Create(const std::string& identifier,
                            const std::string& displayName,
                            bool value,
                            ConfigItemThemeCallbackFunc callback)
    {
        auto result = CreateSafe(identifier,
                                 displayName,
                                 value,
                                 callback);
        if (!result)
            throw result.error();
        return std::move(*result);
    }

} // namespace wupsext
