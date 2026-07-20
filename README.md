My personal page lives again! And again!

Thanks to the dev of this [page](https://wp-store.neocities.org/xaps), now I know which style I should use:)

The production is live at https://lebao3105.github.io.

## Content writing syntax
(Not only for myself but for other readers too)

### Introducion
This website has gone through many big changes:
* From what I forgot to know how it looks like (sorry);
* To one with WinJS and a bit more JavaScript;
* To this one: still WinJS but with a C&C++ backend

This update uses WebAssembly for getting the right content for a website.
No, it does not make the page faster than static HTMLs, but it makes writing new pages much less painful. And to reach that, a new (sort of) language is (kinda) made, based on Markdown.

### Syntax

The "parser" is implemented in [js/siteContent.cxx](js/siteContent.cxx). It reads the input file *line-by-line*, but can remember unclosed markers like *italic*.

HTML stuff are not affected. Reserved identifiers are case-sensitive.

| Line starts with...                    | HTML output       | Description                  | Notes                                          |
|----------------------------------------|-------------------|------------------------------|------------------------------------------------|
| # (literal hastag)                     | \<h3\>            | Header level 3, NOT level 1! |                                                |
| #1, #2 ... (literal hastag + number)   | \<h1\> ... \<h6\> | Header level \<number\>      | Between # and number must not contain anything |
| \*empty or contains only whitespaces\* | \<br/\>           | Line break                   |                                                |
| SWITCH\<header, setting\>              | A WinJS Switch    | A single switch with name    | header = the switch's name, setting is the site's cookie key |
| LU:                                    | Updated <h6> element with "title" class      |  Last updated text                  | After LU: must be a whitespace |
| TI:                                    | Updated <h6> element with "last-updated" ID     |  Title of the page                  | After TI: must be a whitespace |
