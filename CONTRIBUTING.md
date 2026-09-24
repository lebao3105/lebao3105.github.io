## Contributing to this website

This project is...weird.

Got rewritten 3 times, and this time the site gets rewritten with C++ and WASM.

Raylib is very good, light and simple, but we need a bit more than that. That's why this exists.

Many custom widgets have been implemented/being implemented at the moment. And the API is a bit weird and very, very unfinished. C++ is not C, after all - and we're using a C library inside C++ stuff.

### Free and non-free

We can:

* Freely use (almost?) everything the browser offers (e.g `document.getElementById`)
* Freely modify HTML elements, if any
* Freely draw anything we want
* Freely download using Emscripten API (if on Web) or anything else usable

We can't/don't:

* Render the content using HTML
* Explicitly call WASM functions as none (in C++) is made for that (intentional)
* What else?

### Idea

#### Single-page site

Since the aim of this project is to fully use WASM, you will see that index.html is the only HTML file here.

Do you wonder why sometimes website to navigate so fast: only needed things are changed?
It's because of single-page technique - you stay in one position, try to navigate to /target (without modifying the address bar yourself), and the site may do this:

```js
history.pushState("/target", "", "/target");
```

The address bar will change to use `/target` without pulling anything else, saving time.

This project does pretty much the same. Check [navigation.cxx](js/navigation.cxx).

#### Main loop

Raylib draws stuff every frame, until the window is closed. Setting up the main loop is easy enough.

In Emscripten, it's:

```cpp
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
```

In other platforms:

```cpp
raylib::Window window = ...;

while (! window.ShouldClose())
    UpdateDrawFrame();
```

UpdateDrawFrame does the following:

* Receive mouse changes (scrolls, clicks etc)
    - And handle that if needed
* Draw
    - Set the background
    - Draw the pivot
    - Draw the page content

#### Page content

It's done via parsing files in [content/](content), using a "language" inspired by Markdown.

The "parser" is implemented in [siteContent.cxx](js/siteContent.cxx). It reads the input file *line-by-line*, but can remember unclosed markers like *italic*.

HTML stuff are not affected. Reserved identifiers are case-sensitive.

| Line starts with...                    | HTML equivalent       | Description                  | Notes                                          |
|----------------------------------------|-------------------|------------------------------|------------------------------------------------|
| # (literal hastag)                     | \<h3\>            | Header level 3, NOT level 1! |                                                |
| #1, #2 ... (literal hastag + number)   | \<h1\> ... \<h6\> | Header level \<number\>      | Between # and number must not contain anything |
| \*empty or contains only whitespaces\* | \<br/\>           | Line break                   |                                                |
| SWITCH\<header, setting\>              | A switch button    | A single switch with name    | header = the switch's name, setting is the site's cookie key |
| LU:                                    | Updated \<h6\> element with "title" class      |  Last updated text                  | After LU: must be a whitespace |
| TI:                                    | Updated \<h6\> element with "last-updated" ID     |  Title of the page                  | After TI: must be a whitespace |
