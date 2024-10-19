function getCardCSS()
{
    for (let i = 0; i < document.styleSheets.length; i++)
    {
        const sheet = document.styleSheets[i];

        try {
            const rules = sheet.cssRules || sheet.rules; // for cross browser compability
            for (let j = 0 ; j < rules.length; j++)
            {
                const rule = rules[j];
                if (rule.selectorText === '.card' && rule instanceof CSSStyleRule)
                {
                    return rule.style;
                }
            }
        }
        catch (e)
        {
            // do something
        }
    }
}

function loadPosts(path)
{
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200)
        {
            parseAndReturnPosts(this, path);
        }
    }
    xmlHttp.open('GET', '/content/' + path, false);
    xmlHttp.send(null);
}

function getHTMLTitle(path)
{
    var xmlHttp = new XMLHttpRequest();
    var result = '';

    xmlHttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200)
        {
            var htmlDoc = new DOMParser().parseFromString(this.responseText, 'text/html')
            result = htmlDoc.getElementsByTagName('title')[0].innerText;
        }
    }
    xmlHttp.open('GET', '/content/' + path, false);
    xmlHttp.send(null);

    return result;
}

function parseAndReturnPosts(xmlRequest, path)
{
    var parser = new DOMParser();
    var htmlDoc = parser.parseFromString(xmlRequest.responseText, 'text/html');
    var aList = htmlDoc.getElementsByTagName('a');
    var targetList = document.getElementsByClassName("grid")[0];

    for (i = 1; i < aList.length; i++) {
        try {
            var spanList = aList[i].getElementsByTagName("span");
            if (spanList[0].innerText.endsWith('.html'))
            {
                var newElement = document.createElement('div');
                newElement.innerHTML =
                    getHTMLTitle(path + '/' + spanList[0].innerText) +
                    "<br><br>" + spanList[2].innerText;

                newElement.style.backgroundColor = "lightgray"
                newElement.style.paddingLeft = "10px"
                newElement.style.cursor = "pointer"
                
                targetList.appendChild(newElement);
            }
        }
        catch (error) {
            
        }
    }
}