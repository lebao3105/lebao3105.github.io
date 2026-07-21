#include "siteContent.hxx"
#include "utils.hxx"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace emscripten;
using namespace std::literals::string_literals;

val createSwitch(const std::string &name, const bool value)
{
    val divCnt = createElement("div");
    val text = createTextNode(name);
    appendChild(divCnt, text);

    val switchBtn = createElement("button");
    switchBtn.set("type", "button");
    switchBtn.set("aria-pressed", value ? "true" : "false");

    switchBtn.set("innerHTML", R"(
        <span class="stateLabel stateLabel-on">On</span>
        <span class="stateLabel stateLabel-off">Off</span>
    )");
    appendChild(divCnt, switchBtn);

    return divCnt;
}

bool isInParagraph = false;

val lineParser(const std::string &line)
{
    val result;

    if (line[0] == '#') {
        constexpr int ONE = static_cast<int>('1');
        constexpr int SIX = static_cast<int>('6');
        const int num = static_cast<int>(line[1]);
        if ((num >= ONE) && (num <= SIX))
        {
            result = createElement("h"s + line[1]);
            result.set("innerHTML", line.substr(2));
        } else {
            result = createElement("h3");
            result.set("innerHTML", line.substr(1));
        }
        isInParagraph = false;
    }
    else if (!isInParagraph) {
        result = createElement("p");
    }
    else {
        result = createTextNode(line + " ");
    }

    return result;
}

void addPageContent()
{
    val contentDiv =
        document.call<val>("getElementsByClassName", "top"s)
                .call<val>("item", 0);
    contentDiv.set("innerHTML", ""s);

    std::string contentPath = "/content";
    contentPath += window["location"]["pathname"].as<std::string>();
    if (contentPath == "/content/")
        contentPath += "index.md";
    else
        contentPath.replace(contentPath.size() - 4, 4, "md");
    std::cout << "[Page Content] Going to load " << contentPath << std::endl;

    std::ifstream f{contentPath, std::ios::in};
    if (!f.is_open())
        throw new std::runtime_error("Unable to read content file!");

    std::stringstream ss;
    ss << f.rdbuf();
    val elm;
    for (std::string line; std::getline(ss, line); /* nothing */)
    {
        trimString(line);
        if (line.empty() && elm != val::undefined()) {
            appendChild(elm, createElement("br"));
            continue;
        }
        else if (line.starts_with("TI: ")) {
            val title = document.call<val>("getElementsByClassName", "title"s)
                                .call<val>("item", 0);
            auto t = line.substr(3);
            appendChild(title, createTextNode(t));
            document.set("title", t);
            continue;
        }
        else if (line.starts_with("LU: ")) {
            val lu = document.call<val>("getElementById", "last-updated"s);
            appendChild(lu, createTextNode(line.substr(3)));
            continue;
        }

        val newElm = lineParser(line);
        if (!isInParagraph) {
            appendChild(contentDiv, newElm);

            // Avoid adding paragraphs to headers
            if (line[0] != '#') {
                elm = newElm;
                isInParagraph = true;
            }
        }
        else {
            appendChild(elm, newElm);
        }
    }
}
