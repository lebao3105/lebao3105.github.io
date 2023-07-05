Title: How to build wxWidgets from source on Windows with cmake
Date: 2023-07-03 21:19
Modified: 2023-07-05 19:07
Category: Development

# Introducion
wxWidgets is a C++ library made for cross-platform GUI apps. It is made by the operating system's native controls (Win32, Gtk, Qt, Cocoa).

Because wxWidgets depends on GUI libraries which are not preinstalled (likely) in computers, you need to install it yourself if you want to use the library. There's an option to get pre-compiled library on wxWidgets [website](https://wxwidgets.org/download), but if you want to build your fresh builds yourself, this guide is for you.

# Preparion

You will need:

- C++ compiler (G++/Cl/...) (any environment: Visual Studio, MSYS2, MINGW, TDM-GCC... no WSL), cmake, ninja/make (you won't need this if you use VS) (Is ninja support 64bit builds? I've failed one time)

- GUI toolkit you want (normally just use the Windows SDK)

> If you have Visual Studio installed (with C++ workload of course), then you don't need anything else. If you use *NIX-like environment like MSYS2 or MINGW, install needed tools with its package manager. Else do an internet search:0

- Patient (first is for the installation of build tools)

For the rest of this tutorial, you need to know:

- ```%WXWIN%``` variable: your wxWidgets **install** folder, for me it's ```%USERPROFILE%\Desktop\wx33VS```

- ```%WXCFG%```: relative path to ```build.cfg``` file (start from ```%WXWIN%```), normally it's located in ```(build_type_and_arch)\mswud\``` (placed in ```lib\```).

- For wxWidgets cloned from GitHub: do update **all** submodules first and if you want, checkout to a specific release. The current on-going version is 3.3 and the latest stable version is 3.2.2.1.

# Make your cake!

## With Visual Studio

Open Developer Command Prompt from Start Menu.

## Else

Make sure needed tools are in your ```%PATH%```, then open Command Prompt.

## Run

1. Determine where's your installation folder and create it, if needed.

2. Run ```cd [path_to_the_source]``` in Command Prompt (CMD for short)

3. Now look:
- Create a blank directory and "cd" to that folder
- Run ```cmake -G [generator] [path_to_the_source] -DCMAKE_INSTALL_PREFIX=%WXWIN% [-DCMAKE_GENERATOR_PLATFORM=X64]```. For cmake generators, see [#generators](#generators); for cmake build platform see [#build-platforms](#build-platforms).
- Run ```cmake --build . --target install``` to install

That's all!

# Test

Get wx-config-windows [here](https://github.com/kowey/wx-config-win), get the .cpp file and compile it. Run the program with a random flag to test. If you don't see WXWIN/WXCFG-related errors, then you're done!

# Explains

## Generators

See here: https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#command-line-build-tool-generators or running ```cmake``` with no arg / --help flag.

## Build platforms

Supported platforms are:
* x86 (wxWidgets default?)
* x64
* arm64
* ia64??

Switch build platforms using ```-A``` or ```-DCMAKE_GENERATOR_PLATFORM``` flag, but seems only VS 2005+ support this.

For example with Ninja - the build failed:
```cmd
> cmake -G "Ninja" .. -DCMAKE_INSTALL_PREFIX=%USERPROFILE%\Desktop\wx33VS -DCMAKE_GENERATOR_PLATFORM=X64
CMake Error at CMakeLists.txt:98 (project):
  Generator

    Ninja

  does not support platform specification, but platform

    X64

  was specified.


-- Configuring incomplete, errors occurred!
```

## Issues

1. wx-config-win returns an error "build/msw/config.*" not found

Maybe you're installed wxWidgets with wrong platform?

2. How to verify if the install is 64bit?

- Check your command history - it's the fastest way
- or, check ```%WXWIN%\lib```. If there's a folder with "x64" on its name, you have a 64bit build of wxWidgets!

3. Can I build with other tools rather than cmake?

Definitively yes!

4. Can I use CMake GUI?

Yes, view https://docs.wxwidgets.org/3.2/overview_cmake.html for more details.

5. How about using ```./configure``` and ```make``` in MSYS2/MINGW/(...)?

Not tested yet, but it should work.

# References
- https://docs.wxwidgets.org/3.2/plat_msw_install.html#msw_build_make_params
- https://docs.wxwidgets.org/3.2/overview_cmake.html
- https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html
- https://stackoverflow.com/a/47983786 about CMAKE_GENERATOR_PLATFORM option