async function loadPosts(path)
{
    const response = await fetch(
        'https://api.github.com/repos/lebao3105/lebao3105.github.io/contents/content/' + path)
    const data = await response.json()
    const targetList = document.getElementsByClassName("grid")[0];

    for (let file of data)
    {
        if (file.name.endsWith(".html"))
        {
            var newElement = document.createElement('div')
            const titleAndTime = getHTMLTitleAndLastModified(path + '/' + file.name)
            newElement.innerHTML = titleAndTime[0] + "<br><br>" + titleAndTime[1]

            newElement.style.backgroundColor = "lightgray"
            newElement.style.paddingLeft = "10px"
            newElement.style.cursor = "pointer"
            newElement.onclick = function () {
                location.href = path + '/' + file.name
            }

            targetList.appendChild(newElement)
        }
    }
}

function getHTMLTitleAndLastModified(path)
{
    var xmlHttp = new XMLHttpRequest();
    var result = [];

    xmlHttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200)
        {
            var htmlDoc = new DOMParser().parseFromString(this.responseText, 'text/html')
            result.push(htmlDoc.getElementsByTagName('title')[0].innerText);
            result.push(htmlDoc.getElementById('last-updated').innerText);
        }
    }
    xmlHttp.open('GET', '/content/' + path, false);
    xmlHttp.send(null);

    return result;
}