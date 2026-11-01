# AI Agent Instructions

## Project Context

StyleMiiU RPX is a Wii U Aroma plugin forked from StyleMiiU. It preserves the
original theme-management behavior and adds experimental support for launching
trusted homebrew `men.rpx` files through Aroma's RPXLoadingModule. The plugin
also includes the upstream theme shuffle, mashup, and audio-stream changes
present in the pinned history.

The project is written in C and C++ for devkitPro's devkitPPC toolchain. The
main plugin entry point is `src/main.cpp`; theme content redirection is in
`src/themeSelector.cpp`; project-wide state and the plugin version are defined
in `src/globals.*`. External WUPS, content-redirection, notifications, and
RPX-loader libraries are pinned as submodules under `external/`.

Do not copy chat transcripts, private paths, credentials, Nintendo data, or
unverified historical claims into the repository. Use conversation history only
as context and verify technical details against the source and build files.

## Required Rules

### AI Co-Author Rule

Any time an AI agent modifies, creates, or refactors code, it MUST append itself
as a co-author in the git commit message using the standard GitHub co-author
format. If the AI agent does not know its official GitHub contributor routing
email, it must check the repository's commit history to find previous examples
of its own attribution, or search the web to find its correct official
co-author tag.

For Copilot, use:

`Co-authored-by: Copilot <223556219+Copilot@users.noreply.github.com>`

### Documentation Sync Rule

Any time an AI agent changes, adds, or removes code, it MUST simultaneously
update the relevant documentation (README, comments, or wikis) to reflect
those changes.

### Language Rule

All contributions to this repository, including code comments, variables,
commit messages, and documentation, MUST be written in English.

## Coding Standards

- Follow the existing C++23 style and keep changes focused.
- Preserve the original GPLv3 and dependency license notices.
- Keep `men.rpx` discovery case-insensitive and recursive.
- Launch RPX files through `RPXLoader_LaunchHomebrew`; do not replace or patch
  Nintendo system files.
- Keep RPX launching separate from asset-based mashup replacement.
- Report launch and content-redirection failures through the existing logger
  and notification mechanisms.
- Do not add Nintendo firmware, keys, dumped executables, themes, or private
  build artifacts to the repository.

## Workflow Guidelines

1. Work from a clone created with `--recurse-submodules`.
2. Verify submodule status before editing and preserve the pinned revisions.
3. Use the devkitPro MSYS2 shell on Windows.
4. Build with `make -j4`; use `make clean` before a release rebuild.
5. Confirm `stylemiiu.wps` and `stylemiiu.elf` are generated successfully.
6. Review `git diff --check`, `git status`, and the final release contents.
7. Keep generated binaries and local debug files ignored.
8. Push completed changes only after validation, using a normal push unless the
   user explicitly authorizes a history rewrite.

## Release and Safety Notes

- The plugin requires Aroma and the RPXLoadingModule for `men.rpx` launching.
- RPX files execute as homebrew code; use only files from trusted sources.
- Console behavior remains experimental and must not be described as validated
  without actual hardware testing.
- Release packages must include the plugin and applicable license notices only.
