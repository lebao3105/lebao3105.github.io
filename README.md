My personal page lives again! And again!

Thanks to the dev of this [page](https://wp-store.neocities.org/xaps), now I know which style I should use:)

The production is live at https://lebao3105.github.io.

This website has gone through many big changes:
* From what I forgot to know how it looks like (sorry);
* To one with WinJS and a bit more JavaScript;
* To this one: Raylib for the frontend, C++ for the backend

This update uses WebAssembly for getting the right content for a website.
No, it does not make the page faster than static HTMLs, but it makes writing new pages much less painful. And to reach that, a new (sort of) language is (kinda) made, based on Markdown.

## Requirements

* XMake (latest commit) or CMake or both
* A compiler that supports C++ 20
* Internet (to download dependencies).

### For PlayStation Vita

* VitaSDK
* gl4es4vita, pvr_psp2 in https://github.com/isage/vita-packages-extra/
* vitaGL, sdl2_vitagl, SceShaccCgExt from VitaSDK repos
* https://github.com/Rinnegatamante/raylib-5.5-vita for raylib

> Hint: For those who don't know how to build a Vita package, it's the same as making ones for Arch Linux. If you also don't know: go to the directory which contains VITABUILD, run `vita-makepkg -i`

> Hint for raylib: If you don't know how to build and install, run `make -C src clean all` then `make -C src install`

> Note for both hints above is that I assume you're already inside the corresponding directory.

### For Web

You only need Emscripten.

If you have it installed using XMake, run this first:

```
xmake env -b "python,emscripten"
```

To make sure required files can be found.

Otherwise, make sure that you have EMSDK variable set and needed tools (emcc, em++) available on PATH.

## Building

To ease compiling this project, partial non-web platforms support has been added.

With CMake, new presets have been added - use one with `--preset` flag. To see all available presets read [CMakePresets.json](CMakePresets.json). You can create ones that fit yourself using CMakeUserPresets.json (intentionally ignored in .gitignore).

With XMake, use `xmake f` to select target platform, toolset etc. Then `xmake b` to build and/or `xmake r` to build and run.
