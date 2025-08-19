async function loadPosts(path) {
  const targetList = document.getElementById("grid");
  targetList.innerHTML = `\
        <div class="progress-ring progress-large">
            <div class="progress-circle"></div>
            <div class="progress-circle"></div>
            <div class="progress-circle"></div>
            <div class="progress-circle"></div>
            <div class="progress-circle"></div>
        </div>
    `;

  const response = await fetch(
    `https://api.github.com/repos/lebao3105/lebao3105.github.io/contents/${path}`,
  );
  const data = await response.json();

  if (data.length === 1 && !data[0].name.endsWith(".html")) {
    targetList.innerHTML = `<h1 style="text-align: center;">No posts found;)</h1>`;
    return;
  } else targetList.innerHTML = "";

  for (let file of data) {
    if (file.name.endsWith(".html")) {
      var newElement = document.createElement("div");
      newElement.className = "entity-list-item active";
      const titleAndTime = getHTMLTitleAndLastModified(path + "/" + file.name);

      // Right content
      const timeDateElm = document.createElement("div");
      timeDateElm.className = "item-content-secondary";

      const timeElm = document.createElement("div");
      timeElm.className = "content-text-primary";
      timeElm.innerText = titleAndTime[1].split(" ")[3];
      timeDateElm.appendChild(timeElm);

      const dateElm = document.createElement("div");
      timeElm.className = "content-text-secondary";
      timeElm.innerText = titleAndTime[1].split(" ")[2];
      timeDateElm.appendChild(dateElm);

      newElement.appendChild(timeDateElm);

      // Main content
      const primaryDiv = document.createElement("div");
      primaryDiv.className = "item-content-primary";

      const titleElm = document.createElement("div");
      titleElm.className = "content-text-primary";
      titleElm.innerText = titleAndTime[0];
      primaryDiv.appendChild(titleElm);

      // don't know what else to put
      // const titleElm = document.createElement("div");
      // titleElm.className = "content-text-primary";
      // titleElm.innerText = titleAndTime[0];
      // primaryDiv.appendChild(titleElm);

      newElement.appendChild(primaryDiv);

      const expandedElm = document.createElement("div");
      expandedElm.className = "item-content-expanded";

      const shareButton = document.createElement("button");
      shareButton.className = "btn btn-secondary";
      shareButton.disabled = true;
      shareButton.innerText = "Share";
      expandedElm.appendChild(shareButton);

      const openButton = document.createElement("button");
      openButton.className = "btn btn-primary";
      openButton.innerText = "Open";
      openButton.onclick = function () {
        location.href = `${path}/${file.name}`;
      };
      expandedElm.appendChild(openButton);

      newElement.appendChild(expandedElm);
      targetList.appendChild(newElement);
    }
  }
}

function getHTMLTitleAndLastModified(path) {
  var xmlHttp = new XMLHttpRequest();
  var result = [];

  xmlHttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      var htmlDoc = new DOMParser().parseFromString(
        this.responseText,
        "text/html",
      );
      result.push(htmlDoc.getElementsByTagName("title")[0].innerText);
      result.push(htmlDoc.getElementById("last-updated").innerText);
    }
  };
  xmlHttp.open(
    "GET",
    `https://raw.githubusercontent.com/lebao3105/lebao3105.github.io/main//${path}`,
    false,
  );
  xmlHttp.send(null);

  return result;
}
