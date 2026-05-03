function loadPath() {
  var pageloc = window.location.pathname.replace(".html", "");
  var breadcrumbOL = document.getElementById("path");

  function createNewLi(element, index, arr) {
    var newLI = document.createElement("li");

    if (element === "index") return;

    if (index === arr.length - 1) {
      newLI.className = "active";
      newLI.appendChild(document.createTextNode(element));
    } else {
      var newA = document.createElement("a");
      if (index === 0) {
        newA.setAttribute("href", "https://lebao3105.github.io");
        newA.appendChild(document.createTextNode("C:"));
      } else {
        newA.setAttribute("href", document.URL + "/../".repeat(index + 1));
        newA.appendChild(document.createTextNode(element));
      }
      newLI.appendChild(newA);
    }

    breadcrumbOL.appendChild(newLI);
  }
  pageloc.split("/").forEach(createNewLi);
}

function setupBackToTop() {
  var backToTop = document.createElement("a");
  backToTop.id = "back-to-top";
  backToTop.href = "#top";
  backToTop.className = "invisible";
  backToTop.onclick = () => {
    document.body.scrollTo(0, 0);
    this.className = "invisible";
    return false;
  };

  var glyph = document.createElement("i");
  glyph.classList.add("glyph");
  glyph.classList.add("glyph-up");
  backToTop.appendChild(glyph);
  document.body.appendChild(backToTop);

  function onViewportChange(_) {
    backToTop.className =
      document.body.scrollTop < 20 ? "invisible" : "visible";
  }

  window.onscroll = onViewportChange;
  window.onresize = onViewportChange;
}

function createTabItem(val) {
  var li = document.createElement("li");
  li.setAttribute("role", "presentation");

  var label = document.createElement("h1");
  label.classList.add("title-big");
  label.textContent = val.replace("\.html", "");

  if (
    document.location.pathname.endsWith(val) ||
    (document.location.pathname === "/" && val === "index.html")
  ) {
    li.classList.add("active");
    label.setAttribute("role", "tab");
    label.setAttribute("data-toggle", "tab");
    li.appendChild(label);
  } else {
    var lnk = document.createElement("a");
    lnk.href = "./" + val;
    lnk.setAttribute("role", "tab");
    lnk.setAttribute("data-toggle", "tab");
    lnk.appendChild(label);
    li.appendChild(lnk);
  }

  return li;
}

function setupPivot() {
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
