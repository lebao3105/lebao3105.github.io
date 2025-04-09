async function loadPosts(path)
{
    const targetList = document.getElementById("grid");
    targetList.innerHTML = `\
        <div class="progress-ring progress-large">
            <div class="progress-circle"></div>
            <div class="progress-circle"></div>
            <div class="progress-circle"></div>
            <div class="progress-circle"></div>
            <div class="progress-circle"></div>
        </div>
    `

    const response = await fetch(
        `https://api.github.com/repos/lebao3105/lebao3105.github.io/contents/${path}`)
    const data = await response.json()

    if (data.length === 1 && !data[0].name.endsWith(".html"))
    {
        targetList.innerHTML = `<h1 style="text-align: center;">No posts found;)</h1>`
        return
    }
    else
        targetList.innerHTML = ""

    for (let file of data)
    {
        if (file.name.endsWith(".html"))
        {
            var newElement = document.createElement('div')
            const titleAndTime = getHTMLTitleAndLastModified(path + '/' + file.name)
            newElement.innerHTML = titleAndTime[0] + "<br><br>" + titleAndTime[1]

            newElement.style.cursor = "pointer"
            newElement.className = "col-md-6 card"
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
    xmlHttp.open('GET', `/${path}`, false);
    xmlHttp.send(null);

    return result;
}