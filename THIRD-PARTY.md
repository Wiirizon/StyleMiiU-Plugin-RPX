# Credits and licenses

StyleMiiU RPX is based on [StyleMiiU by Juanen100 and its contributors](https://github.com/ThemeCafe/StyleMiiU-Plugin). The upstream credits and copyright notices are retained. The plugin is distributed under [GPLv3](LICENSE).

The following libraries are built from the source revisions pinned by this repository. Each is licensed under LGPLv3; the full license is included in its source directory.

| Library | Source revision | Source and license |
| --- | --- | --- |
| WiiUPluginSystem | `b0b109282cb2d343cd4ac35b5b7b4c3176d8e6c5` | [wiiu-env/WiiUPluginSystem](https://github.com/wiiu-env/WiiUPluginSystem/tree/b0b109282cb2d343cd4ac35b5b7b4c3176d8e6c5), `external/WiiUPluginSystem/LICENSE` |
| libcontentredirection | `502a4962acdf9acd48fc4aaa2d768de371f8348d` | [wiiu-env/libcontentredirection](https://github.com/wiiu-env/libcontentredirection/tree/502a4962acdf9acd48fc4aaa2d768de371f8348d), `external/libcontentredirection/LICENSE` |
| libnotifications | `c7fc69e2f7a265fee017c87fe066b587c9e5003d` | [wiiu-env/libnotifications](https://github.com/wiiu-env/libnotifications/tree/c7fc69e2f7a265fee017c87fe066b587c9e5003d), `external/libnotifications/LICENSE` |
| librpxloader | `7b055f15f2c0e31af5b0a4ceda44ecb1ec39cc34` | [wiiu-env/librpxloader](https://github.com/wiiu-env/librpxloader/tree/7b055f15f2c0e31af5b0a4ceda44ecb1ec39cc34), `external/librpxloader/LICENSE` |

The plugin also links against [wut by devkitPro and the wut authors](https://github.com/devkitPro/wut), under the zlib license. Its notice is reproduced in [licenses/wut-LICENSE](licenses/wut-LICENSE). The devkitPPC compiler and standard runtime are supplied separately by devkitPro; release build versions are recorded in the release package.

The source archive supplied with each release includes the plugin and all four pinned library sources, with their notices intact. It lets recipients rebuild and relink the plugin with modified versions of these libraries. The binary package includes copies of their license texts as well.

No Nintendo SDK, firmware, keys, menu executable, graphics, or audio are distributed with this plugin. Theme and RPX authors are responsible for the material they distribute. Nintendo, Wii U, and other product names identify compatibility; this project is not affiliated with or endorsed by Nintendo. These notices do not grant permission to use anyone else's copyrighted material or trademarks.
