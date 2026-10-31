#include "globals.h"

bool gThemeManagerEnabled = DEFAULT_THEME_MANAGER_ENABLED;
bool gShuffleThemes       = DEFAULT_SHUFFLE_THEMES;
bool gMashupThemes        = DEFAULT_MASHUP_THEMES;
bool gShowNotification    = DEFAULT_SHOW_NOTIFICATION;

std::unordered_set<std::filesystem::path> gEnabledThemes;

const std::filesystem::path theme_directory_path = "fs:/vol/external01/wiiu/themes";

CRLayerHandle gContentLayerHandle = 0;

std::string gLoadedTheme;
std::string gLoadedMenTheme;
std::string gLoadedMen2Theme;
std::string gLoadedCafeBaristaTheme;
