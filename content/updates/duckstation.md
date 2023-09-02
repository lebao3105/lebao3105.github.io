Title: The first PlayStation 1 emulator for Windows 10 Mobile
Date: 2023-09-02 08:58
Category: Update
Tags: emulator, windows10mobile, uwp

# What happened?

Yesterday (in my country), Bashar Astifan - one of the Windows Universal Tool (WUT or W.U.T for short), has released the first build (also a small update today) of the PlayStation 1 emulator DuckStation for Windows 10 Mobile.

# What is DuckStation?

Above: a PlayStation 1 emulator, focusing on playability, performance, and long-term maintainable.

It is originally made by [Connor McLaughlin][orig], and the original version still lives & being developed until now.

DuckStation, like many other emulators, uses "BIOS" ROM images to start emulator and play games, which requires you to find from your console or somewhere else (legal reasons).

It has:

* CPU Recompiler/JIT (x86_64, armv7, AArch32 and 64)

* Skip BIOS splash/intro: "Fast boot"

* Windows - macOS - Linux support

* Namco GunCon, NeGCon support.

* Emulated CPU overclock.

And more on its [GitHub.][orig]

# What about the W10M port?

It's the unofficial port by [Bashar Astifan](https://github.com/basharst), who also made many things about emulators.

From Windows 10 Mobile Telegram group, or his GitHub, this is the updates from the original one:

* UWP Storage [solution](https://github.com/basharast/UWP2Win32) - Root access required to make the files load faster

* Custom data folder

* Improved touch screen functions

* Added On-Screen touch controller

* Improved files browser

* Fixed few issues with retroachivements

* Launch by file or URI

Universal Windows Platform of course. In fact, the original developer has made his first UWP support for this, but dropped.

This port is for Windows ARM32, min 15035. 14393 and DirectX 11 Feature Level 9.3 are nor ready yet (Level 10+ is supported).

The latest available version is 1.0.1 with small fixes.

# Where to get

This page: [https://github.com/basharast/DuckStation-UWP-ARM/releases](https://github.com/basharast/DuckStation-UWP-ARM/releases)

Note from Bashar: Reduce Overclocking value may help improve performance for weak GPUs - if you have enabled it - but don't reduce too much. Also disabling Scaled Dithering could help.

Enjoy!

[orig]: https://github.com/stenzek/duckstation