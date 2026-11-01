# Contributing

## Scope

StyleMiiU RPX is a devkitPro Wii U Aroma plugin. Contributions must preserve
the upstream theme functionality while keeping the experimental `men.rpx`
launcher isolated and clearly documented.

All contributions, including source code, comments, documentation, variables,
and commit messages, must be written in English.

## Development Setup

1. Install devkitPro with devkitPPC, WUT, WUMS, and the Wii U development
   libraries required by WUPS.
2. Clone the repository and its pinned dependencies:

   ```sh
   git clone --recurse-submodules https://github.com/Wiirizon/StyleMiiU-Plugin-RPX.git
   cd StyleMiiU-Plugin-RPX
   git submodule update --init --recursive
   ```

3. On Windows, run the commands from the devkitPro MSYS2 shell.

## Build and Validation

Build the plugin with:

```sh
make -j4
```

For a clean release build:

```sh
make clean
make -j4
```

The build must produce `stylemiiu.wps` and `stylemiiu.elf`. Before
committing, run:

```sh
git diff --check
git status --short
```

Hardware testing requires a Wii U running Aroma and the matching
RPXLoadingModule. Record the exact tested path and distinguish user-reported
results from complete compatibility coverage. Do not claim console validation
when only a local build has been performed.

## Code and Documentation

- Keep changes surgical and follow the existing C/C++ style.
- Preserve case-insensitive recursive `men.rpx` discovery.
- Keep RPX launching separate from asset redirection and mashup behavior.
- Update `README.md` whenever user-visible behavior, build requirements, or
  safety limitations change.
- Do not commit generated binaries, private paths, credentials, Nintendo data,
  or untrusted theme assets.

## Commits and Releases

Use concise English commit messages. AI-assisted commits must include the
standard `Co-authored-by` trailer for the assisting agent, using that agent's
official contributor name and routing email.

Version changes belong in `src/globals.h`. Release assets must be rebuilt from
the tagged source, checked for the expected filename, and accompanied by the
relevant license notices.
