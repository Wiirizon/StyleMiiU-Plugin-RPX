# StyleMiiU RPX

StyleMiiU RPX is a small fork of [StyleMiiU](https://github.com/ThemeCafe/StyleMiiU-Plugin) that adds support for homebrew `men.rpx` themes, such as WiiUNX2.

It keeps the original theme options and adds a way to launch a custom menu from your SD card.

Modified on October 28, 2026 to add RPX theme launching and update the plugin title. The plugin remains licensed under GPLv3; see [LICENSE](LICENSE). This is an unofficial project and is not affiliated with or endorsed by Nintendo.

**No system file is modified by this plugin.**

This plugin's codebase is heavily based on SDCafiine.

## Installation

(`[ENVIRONMENT]` is a placeholder for the actual environment name.)

Copy the file `stylemiiu.wps` into `SD:/wiiu/environments/[ENVIRONMENT]/plugins`.

## Usage

This plugin can detect Men.pack, Men2.pack and cafe_barista_men.bfsar automatically to make the theme have any folder structure you desire. SDCaffine's file structure is still compatible with this plugin. *Additional files like AllMessage.szs do still need to be on their corresponding folder structure, like this: `SD:/wiiu/themes/[ThemeName]/content/[TheLanguageToPatch]/Message/AllMessage.szs`*

Themes will only load from the `SD:/wiiu/themes` directory, it is recommended that you move all your themes from SDCafiine into the themes directory to avoid problems of both plugins trying to patch the Wii U Menu.

A step to step guide on how to use it:
1. Open the WUPS menu (**L + ↓ + SELECT**) and enter the **StyleMiiU RPX** menu. Make sure StyleMiiU RPX is enabled, otherwise it won't do anything.
2. Enter the **Available Themes** option and you should see the folders that are in `SD:/wiiu/themes/`, showing up empty if no theme is present. Once there, set whatever theme you want to Current Theme. If no theme it's set, the Wii U's default home menu will be loaded.
3. Once you exit the WUPS menu, the Home Menu should restart and once it gets restarted, your Home Menu will now have the theme you chose applied to it.

Additional options:
- Shuffle themes: This option tries to mimic the 3DS' option of shuffling themes, you can use it by simply activating the option and then in **Available Themes**, select the themes you want to shuffle through. The themes will change **every time you restart the console or exiting back to the menu**. If you disable this option, then the last theme you selected will become the default theme for it to fallback on.
- Mashup themes: This option makes the themes get mixed with each other every time you restart the console or enter and exit to the menu, providing mixes of music, themes and even miscellaneous stuff like the Wii cursor. *Shuffle themes must also be enabled for this to work.*

## men.rpx themes

Put the executable inside its own theme folder, for example:

```text
SD:/wiiu/themes/WiiUNX2/men.rpx
```

Select it under **StyleMiiU RPX > Available Themes**, with **Mashup themes** turned off. The plugin also finds `men.rpx` in subfolders, including `code/men.rpx`. If the selected theme contains an executable, it takes priority over the theme's asset files. Shuffle can select RPX themes; mashup continues to use asset files only.

Only use RPX files from sources you trust: they run as homebrew code and can access your console and SD card.

This needs Aroma's RPXLoadingModule. The executable is launched as homebrew through Aroma's wrapper application, rather than replacing the system menu in memory. Use a homebrew menu built to run this way; a dumped or patched Nintendo menu is not supported. WiiUNX2 still needs testing on a console with this launch method.

To switch back, open the plugin menu from the custom menu and choose a regular theme, clear the current theme, or disable StyleMiiU RPX. Closing the plugin menu returns to the Wii U Menu. If an executable prevents you from reaching the plugin menu, power off and remove its `men.rpx` from the SD card.

Install this fork in place of the original StyleMiiU plugin. It still builds as `stylemiiu.wps` and uses the same saved settings. No file in your Aroma environment is replaced apart from the plugin you install.

## Troubleshooting

The plugin will sometimes not work properly when certain race conditions are triggered. The most commons ones being described further in this file.

### Bootlooping on Wii U Menu splash

The first reason might be you have both SDCafiine and StyleMiiU trying to patch a theme to the Wii U menu, which can cause issues. Moving themes from SDCafiine's directory to the theme's directory or disabling SDCafiine will usually solve this issue.

This problem might also show up due to the fact that you're using a theme that hasn't been tested or properly made to support an European/PAL console. European/PAL consoles have more language packs built onto the menu menaning the file size on themes needs to be smaller to work properly. This is more likely to happen with animated themes or unoptimized themes.

### My theme isn't loading

The most common issue would be having bad or corrupted Men.pack, Men2.pack or cafe_barista_men.bfsar files which makes the plugin unable to patch them on the Wii U Menu. This is highly unlikely to happen and the reason might also be the same as the bootlooping problem on EU consoles.


## Building

Make sure to clone/pull the submodules (use the `--recurse-submodules` option).

Should be as easy as running `make` and let it do its thing.
