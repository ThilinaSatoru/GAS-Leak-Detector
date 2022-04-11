const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <link href="http://fonts.cdnfonts.com/css/aotani" rel="stylesheet" />

    <script
      src="https://kit.fontawesome.com/d7a828bb45.js"
      crossorigin="anonymous"
    ></script>
    <style>
      html {
        font-family: "Aotani", sans-serif;
        background-color: #00add6;
        font-family: Arial;
        display: inline-block;
        margin: 0px auto;
      }
      h2 {
        font-size: 3rem;
        text-align: center;
        text-transform: uppercase;
      }
      h4 {
        text-align: center;
      }
      p {
        padding: 2rem;
        margin-left: 5%;
        margin-right: 5%;
        max-width: 700px;
        background-color: #222;
        color: #fff;
        font-size: 1.5rem;
      }
      .dataON {
        color: #00add6;
        font-weight: 100;
        font-size: 3rem;
        padding-left: 13%;
      }
      .dataOFF {
        color: #222;
        font-size: 3rem;      
        padding-left: 13%;
      }
      .on-off {
        color: #cccccc;
        position: absolute;
        margin-top: 5em;
        margin-left: 20px;
        font-size: 15px;
      }
      .switch {
        position: relative;
        display: inline-block;
        left: 1em;
        margin-top: 5%;
        width: 100px;
        height: 48px;
      }
      .switch input {
        display: none;
      }
      .slider {
        position: absolute;
        top: 0;
        left: 0;
        right: 0;
        bottom: 0;
        background-color: #ccc;
        border-radius: 6px;
      }
      .slider:before {
        position: absolute;
        content: "";
        height: 32px;
        width: 32px;
        left: 8px;
        bottom: 8px;
        background-color: #fff;
        -webkit-transition: 0.4s;
        transition: 0.4s;
        border-radius: 3px;
      }
      input:checked + .slider {
        background-color: #b30000;
      }
      input:checked + .slider:before {
        -webkit-transform: translateX(52px);
        -ms-transform: translateX(52px);
        transform: translateX(52px);
      }
      .units {
        color: rgb(153, 153, 153);
        font-size: 1.2rem;
        font-style: italic;
      }
      i {
        color: #a54006;
        padding-left: 3%;
        font-size: 50px;
      }
      .dht-labels {
        font-size: 1.5rem;
        vertical-align: middle;
        padding-left: 2%;
        padding-bottom: 15px;
      }
      .footer {
        text-align: center;
        color: #222;
      }
    </style>
    <title>Gas Monitor</title>
  </head>

  <body>
    <h2>Gas Leakage Live Monitor</h2>
    <p>
      <i class="fa-solid fa-warehouse" style="font-size: 50px;"></i>
      <span class="dht-labels">STORE ROOM</span><br />
      <span id="OUTstore" class="dataOFF" disabled="true"></span>
      <sup class="units">value</sup>
      <br />
      <span class="on-off">Enable/Disable</span>
      <label class="switch">
        <input
          type="checkbox"
          onchange="handleToggle_store(event,'OUTstore')"
          id="1"
        />
        <span class="slider"></span>
      </label>
    </p>

    <p>
      <i class="fa-solid fa-utensils" style="font-size: 50px;"></i>
      <span class="dht-labels">KITCHEN</span><br />
      <span id="OUTkitchen" class="dataOFF" disabled="true"></span>
      <sup class="units">value</sup>
      <br />
      <span class="on-off">Enable/Disable</span>
      <label class="switch">
        <input
          type="checkbox"
          onchange="handleToggle_store(event,'OUTkitchen')"
          id="2"
        />
        <span class="slider"></span>
      </label>
    </p>

    <div class="footer">
      <h4>NIBM | ESP8266 Server |</h4>
    </div>

    <script>
      const interval = 5000;
      setInterval(function () {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("OUTstore").innerHTML = this.responseText;
          }
        };
        xhttp.open("GET", "/Vstore", true);
        xhttp.send();
      }, interval);

      setInterval(function () {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("OUTkitchen").innerHTML = this.responseText;
          }
        };
        xhttp.open("GET", "/Vkitchen", true);
        xhttp.send();
      }, interval);

      function handleToggle_store(event, dID) {
        var xhttp = new XMLHttpRequest();
        const data = document.getElementById(dID);
        const bool = data.getAttribute("disabled");

        if (bool === "false") {
          // if enabled set disabled - (OFF)
          data.setAttribute("disabled", "true");
          data.classList.replace("dataON", "dataOFF");
          data.style.display = "none";
          if (dID === "OUTstore") {
            xhttp.open("GET", "/update?state=1", true);
          } else if (dID === "OUTkitchen") {
            xhttp.open("GET", "/update?state=2", true);
          }
        } else {
          // if disabled set enabled - (ON)
          data.setAttribute("disabled", "false");
          data.classList.replace("dataOFF", "dataON");
          data.style.display = "inline-block";
          if (dID === "OUTstore") {
            xhttp.open("GET", "/update?state=3", true);
          } else if (dID === "OUTkitchen") {
            xhttp.open("GET", "/update?state=4", true);
          }
        }
        xhttp.send();
      }
    </script>
  </body>
</html>

)rawliteral";
