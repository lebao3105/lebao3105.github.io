Title: Texteditor (with Tkinter GUI) 2023 Update
Date: 2023-06-04 22:59
Modified: 2023-06-06 23:15
Category: Update
Tags: texteditor, textworker, tkinter
Summary: Update of texteditor project (Tkinter part)

# What happened?
```texteditor``` has started using wxPython GUI toolkit since the end of 2022.

[wxPython](https://wxpython.org) is the Python bindings of [wxWidgets](https://wxwidgets.org) - a GUI toolkit which brings us the native OS's look, plus some "advanced" widgets.

This marks my higher step in my programming skill, as this version of texteditor has a better organized, simplified code.

## How about Tkinter?
Tkinter UI is ugly in non-Windows/macOS OSes, due to the limitation of the Tcl kit Tkinter based on - but it's much easier to install than wxPython. We have customizable themes while we can't change the native UI in wxPython. Although it has fewer widgets/features than wxPython, but making portable builds with Tkinter is somewhat better, I think.

## What's next?
texteditor will stop using Tkinter after the ongoing 1.5 release.

The reason is simple: I really can't work on 2 different projects like that. Porting new changes together? We have ```libtextworker``` and Git ```data``` branch. Making builds? We have GitHub Actions and poetry. I don't think about "I'm tired". Not that.

Tkinter is the first thing people think about when they start making their first GUI Python apps. Because it's fast, easy to learn and use; and... most people use Windows - where Tcl doesn't have issues about.