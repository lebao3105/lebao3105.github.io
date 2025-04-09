function loadPath()
{
    var pageloc = window.location.pathname;
    pageloc = pageloc.replace(new RegExp("/", "g"), " / ").replace(".html", "");

    var breadcrumbOL = document.getElementById("path");
    
    function createNewLi(element, index, arr) {
        var newLI = document.createElement("li");

        if (index === 0)
        {
            var newA = document.createElement("a");
            newA.setAttribute("href", "https://lebao3105.github.io");
            newA.appendChild(document.createTextNode("C:"));
            newLI.appendChild(newA);
        }
        else if (index === (arr.length - 1))
        {
            newLI.className = "active";
            newLI.appendChild(document.createTextNode(element));
        }
        else {
            var newA = document.createElement("a");
            newA.setAttribute("href", document.URL + "/../".repeat(index + 1));
            newA.appendChild(document.createTextNode(element));
            newLI.appendChild(newA);
        }

        breadcrumbOL.appendChild(newLI);
    }
    pageloc.split(" / ").forEach(createNewLi);
}