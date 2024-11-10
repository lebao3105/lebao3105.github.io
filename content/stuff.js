function loadPath(postType)
{
    var pageloc = window.location.pathname;
    pageloc = pageloc.replace(new RegExp("/", "g"), " / ").replace(".html", "");
    document.getElementById("path").innerText = pageloc;
    document.getElementById("path").setAttribute("href", document.URL + `/../../${postType}.html`);
}