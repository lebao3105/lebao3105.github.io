import { smallPivot } from "./settings.js";

export function isTopLevelPage() { // TODO: Move to somewhere else
    return !location.pathname.includes('/', 1);
}

export function loadPath() {
    if (isTopLevelPage()) return;

    var breadcrumbOL = document.getElementById("path");
    var pageloc = window.location.pathname.replace(".html", "");
    pageloc.removeAttribute("hidden");

    var splits = pageloc.split('/');

    // On Win32 environments, the path has a leading /,
    // making splits start with an empty string. As a result,
    // the breadcrumb will contain two Windows drives.
    if (navigator.platform === "Win32") {
        splits.shift();
    }

    splits.forEach((element, index, arr) => {
        console.log("Path split: " + index + ". " + element);
        var newLI = document.createElement("li");

        if (index === arr.length - 1) {
            if (element === "index") return;
            newLI.className = "active";
            newLI.appendChild(document.createTextNode(element));
        } else {
            var newA = document.createElement("a");
            if (index === 0) {
                newA.setAttribute("href", "https://lebao3105.github.io");
                newA.appendChild(document.createTextNode("%SYSTEMROOT%"));
            } else {
                newA.setAttribute("href", document.URL + "/../".repeat(index + 1));
                newA.appendChild(document.createTextNode(element));
            }
            newLI.appendChild(newA);
        }

        breadcrumbOL.appendChild(newLI);
    });
}

export function setupBackToTop() {
    var backToTop = document.createElement("a");
    backToTop.id = "back-to-top";
    backToTop.href = "#top";
    backToTop.hidden = true;

    var glyph = document.createElement("i");
    glyph.classList.add("glyph");
    glyph.classList.add("glyph-up");
    backToTop.appendChild(glyph);
    document.body.appendChild(backToTop);

    function onViewportChange(_) {
        console.log("window.pageYOffset = ", window.pageYOffset);
        backToTop.hidden = window.pageYOffset < 150;
    }

    window.onscroll = onViewportChange;
    window.onresize = onViewportChange;
}

function createTabItem(val) {
    var li = document.createElement("li");
    li.setAttribute("role", "presentation");

    var label = document.createElement(smallPivot.get() ? "h3" : "h1");
    label.classList.add("title-big");
    label.textContent = val.replace("\.html", "");
    label.setAttribute("role", "tab");
    label.setAttribute("data-toggle", "tab");
    label.onclick = () => {
        history.pushState(val, "", val);
        let evt = new Event('popstate', { state: val });
        window.dispatchEvent(evt);
        document.getElementsByClassName("active")[0].classList.remove("active");
        label.classList.add("active");
    };

    if (document.location.pathname.endsWith(val) ||
        (document.location.pathname === "/" && val === "index.html"))
    {
        label.classList.add("active");
    }

    li.appendChild(label);

    return li;
}

export function setupPivot() {
    // Only do this on top-level pages
    if (!isTopLevelPage()) return;

    var tabList = document.getElementsByClassName("nav-tabs")[0];
    [
        "index.html",
        "projects.html",
        "tutorials.html",
        "updates.html",
        "blog.html",
    ].forEach((val, _, __) => {
        tabList.appendChild(createTabItem(val));
    });
}
