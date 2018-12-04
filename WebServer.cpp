#include "WebServer.hpp"

WifiScan Scan = WifiScan();
ESP8266WebServer server(80);

String ssid;
String password;
String ScanResult;

void (*switchFunction)(char*, char*);

void initializeAP() {
    WiFi.softAP("testAP");
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);
}

void handleRoot() {
    // server.send(200, "text/html", "<!DOCTYPE html><html><head></head><body> <form action='/connect'> <div> <div> <input type='text' value='ssid'> </div><div> <input type='password' value='password'> </div><div> <input type='submit' value='submit'> </div></div></form></body></html>");
    server.send(200, "text/html", "<html><head><title>ESP-8266 SSID Login</title><link rel='stylesheet' type='text/css' href='/style.css'></head><body><div id='container'><div class='login'><h1>Login</h1><div><div class='select'> <select id='ssid'></select></div> <input type='password' id='pass' placeholder='Password' required='required' /><button class='btn btn-primary btn-block btn-large' onclick='connect()'>Connect</button></div></div> <canvas id='canvas'>Canvas is not supported in your browser.</canvas> <canvas id='canvas2'>Canvas is not supported in your browser.</canvas></div> <script src='/script.js'></script> </body></html>");
}

void handleCSS() {
    server.send(200, "text/css", ".select,html{overflow:hidden}.btn-block,body,html{width:100%}#container,body,html{height:100%}.btn,.login h1{text-align:center}input,select{outline:0;color:#fff}.btn,select{cursor:pointer}body{margin:0;font-family:'Open Sans',sans-serif}canvas{display:block;position:absolute;top:0;left:0}#container{position:relative}#container canvas,.login{position:absolute}.btn{display:inline-block;padding:4px 10px;margin-bottom:0;font-size:13px;line-height:18px;color:#333;text-shadow:0 1px 1px rgba(255,255,255,.75);vertical-align:middle;background-color:#f5f5f5;background-image:-moz-linear-gradient(top,#fff,#e6e6e6);background-image:-ms-linear-gradient(top,#fff,#e6e6e6);background-image:-webkit-gradient(linear,0 0,0 100%,from(#fff),to(#e6e6e6));background-image:-webkit-linear-gradient(top,#fff,#e6e6e6);background-image:-o-linear-gradient(top,#fff,#e6e6e6);background-image:linear-gradient(top,#fff,#e6e6e6);background-repeat:repeat-x;filter:progid:dximagetransform.microsoft.gradient(startColorstr=#ffffff, endColorstr=#e6e6e6, GradientType=0);border:1px solid #e6e6e6;-webkit-border-radius:4px;-moz-border-radius:4px;border-radius:4px;-webkit-box-shadow:inset 0 1px 0 rgba(255,255,255,.2),0 1px 2px rgba(0,0,0,.05);-moz-box-shadow:inset 0 1px 0 rgba(255,255,255,.2),0 1px 2px rgba(0,0,0,.05);box-shadow:inset 0 1px 0 rgba(255,255,255,.2),0 1px 2px rgba(0,0,0,.05)}.btn.active,.btn.disabled,.btn:active,.btn:hover,.btn[disabled]{background-color:#e6e6e6}.btn-large{padding:9px 14px;font-size:15px;line-height:normal;-webkit-border-radius:5px;-moz-border-radius:5px;border-radius:5px}.btn:hover{color:#333;text-decoration:none;background-position:0 -15px;-webkit-transition:background-position .1s linear;-moz-transition:background-position .1s linear;-ms-transition:background-position .1s linear;-o-transition:background-position .1s linear;transition:background-position .1s linear}.btn-primary,.btn-primary:hover{text-shadow:0 -1px 0 rgba(0,0,0,.25);color:#fff}.btn-primary.active{color:rgba(255,255,255,.75)}.btn-primary{background-color:#4a77d4;background-image:-moz-linear-gradient(top,#6eb6de,#4a77d4);background-image:-ms-linear-gradient(top,#6eb6de,#4a77d4);background-image:-webkit-gradient(linear,0 0,0 100%,from(#6eb6de),to(#4a77d4));background-image:-webkit-linear-gradient(top,#6eb6de,#4a77d4);background-image:-o-linear-gradient(top,#6eb6de,#4a77d4);background-image:linear-gradient(top,#6eb6de,#4a77d4);background-repeat:repeat-x;filter:progid:dximagetransform.microsoft.gradient(startColorstr=#6eb6de, endColorstr=#4a77d4, GradientType=0);border:1px solid #3762bc;text-shadow:1px 1px 1px rgba(0,0,0,.4);box-shadow:inset 0 1px 0 rgba(255,255,255,.2),0 1px 2px rgba(0,0,0,.5)}.btn-primary.active,.btn-primary.disabled,.btn-primary:active,.btn-primary:hover,.btn-primary[disabled]{filter:none;background-color:#4a77d4}.btn-block{display:block}*{-webkit-box-sizing:border-box;-moz-box-sizing:border-box;-ms-box-sizing:border-box;-o-box-sizing:border-box;box-sizing:border-box}.login{-webkit-transform:translate(-50%,-50%);transform:translate(-50%,-50%);z-index:100;top:50%;left:50%;width:300px;height:300px}.login h1{color:#fff;text-shadow:0 0 10px rgba(0,0,0,.3);letter-spacing:1px}input{width:100%;margin-bottom:10px;background:rgba(0,0,0,.3);border:none;padding:10px;font-size:13px;text-shadow:1px 1px 1px rgba(0,0,0,.3);border:1px solid rgba(0,0,0,.3);border-radius:4px;box-shadow:inset 0 -5px 45px rgba(100,100,100,.2),0 1px 1px rgba(255,255,255,.2);-webkit-transition:box-shadow .5s ease;-moz-transition:box-shadow .5s ease;-o-transition:box-shadow .5s ease;-ms-transition:box-shadow .5s ease;transition:box-shadow .5s ease}.select,select{background:#2c3e50}input:focus{box-shadow:inset 0 -5px 45px rgba(100,100,100,.4),0 1px 1px rgba(255,255,255,.2)}select{-webkit-appearance:none;-moz-appearance:none;-ms-appearance:none;appearance:none;outline:0;box-shadow:none;border:0!important}.select{position:relative;display:block;width:300px;height:38px;line-height:3;border-radius:.25em;margin-bottom:5px}select{width:100%;height:100%;margin:0;padding:0 0 0 .5em}select::-ms-expand{display:none}.select::after{content:'\\25BC';position:absolute;top:0;right:0;bottom:0;padding:0 1em;background:#34495e;pointer-events:none;-webkit-transition:.25s all ease;-o-transition:.25s all ease;transition:.25s all ease}.select:hover::after{color:#f39c12}");
}

void handleJS() {
    // server.send(200, "text/javascript", "var canvas=document.getElementById('canvas'),ctx=canvas.getContext('2d'),canvas2=document.getElementById('canvas2'),ctx2=canvas2.getContext('2d'),cw=window.innerWidth,ch=window.innerHeight,charArr=['a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'],maxCharCount=100,fallingCharArr=[],fontSize=10,maxColums=cw/fontSize;function randomInt(b,c){return Math.floor(Math.random()*(c-b)+b)}function randomFloat(b,c){return Math.random()*(c-b)+b}function Point(b,c){this.x=b,this.y=c}canvas.width=canvas2.width=cw,canvas.height=canvas2.height=ch,Point.prototype.draw=function(b){this.value=charArr[randomInt(0,charArr.length-1)].toUpperCase(),this.speed=randomFloat(1,5),ctx2.fillStyle='rgba(255,255,255,0.8)',ctx2.font=fontSize+'px san-serif',ctx2.fillText(this.value,this.x,this.y),b.fillStyle='#0F0',b.font=fontSize+'px san-serif',b.fillText(this.value,this.x,this.y),this.y+=this.speed,this.y>ch&&(this.y=randomFloat(-100,0),this.speed=randomFloat(2,5))};for(var i=0;i<maxColums;i++)fallingCharArr.push(new Point(i*fontSize,randomFloat(-500,0)));var update=function(){ctx.fillStyle='rgba(0,0,0,0.05)',ctx.fillRect(0,0,cw,ch),ctx2.clearRect(0,0,cw,ch);for(var b=fallingCharArr.length;b--;)fallingCharArr[b].draw(ctx),fallingCharArr[b];requestAnimationFrame(update)};update();function connect(){var b=document.querySelector('#ssid').value,c=document.querySelector('#pass').value;fetch(`/connect?ssid=${b}&password=${c}`),console.log(b,c)}function addOption(b){var c=document.querySelector('#ssid'),d=document.createElement('option');d.text=b,c.add(d)}async function main(){var b=await getNetworks();for(let c=0;c<b.length;c++)addOption(b[c])}async function getNetworks(){var b=await fetch('/results').then(c=>c.text());return b.trim().split('\\n').map(c=>{return c=c.split(','),c[0]})}main();");
    server.send(200, "text/javascript", "var canvas=document.getElementById('canvas'),ctx=canvas.getContext('2d'),canvas2=document.getElementById('canvas2'),ctx2=canvas2.getContext('2d'),cw=window.innerWidth,ch=window.innerHeight,charArr=['a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'],maxCharCount=100,fallingCharArr=[],fontSize=10,maxColums=cw/fontSize;function randomInt(b,c){return Math.floor(Math.random()*(c-b)+b)}function randomFloat(b,c){return Math.random()*(c-b)+b}function Point(b,c){this.x=b,this.y=c}canvas.width=canvas2.width=cw,canvas.height=canvas2.height=ch,Point.prototype.draw=function(b){this.value=charArr[randomInt(0,charArr.length-1)].toUpperCase(),this.speed=randomFloat(1,5),ctx2.fillStyle='rgba(255,255,255,0.8)',ctx2.font=fontSize+'px san-serif',ctx2.fillText(this.value,this.x,this.y),b.fillStyle='#0F0',b.font=fontSize+'px san-serif',b.fillText(this.value,this.x,this.y),this.y+=this.speed,this.y>ch&&(this.y=randomFloat(-100,0),this.speed=randomFloat(2,5))};for(var i=0;i<maxColums;i++)fallingCharArr.push(new Point(i*fontSize,randomFloat(-500,0)));var update=function(){ctx.fillStyle='rgba(0,0,0,0.05)',ctx.fillRect(0,0,cw,ch),ctx2.clearRect(0,0,cw,ch);for(var b=fallingCharArr.length;b--;)fallingCharArr[b].draw(ctx),fallingCharArr[b];requestAnimationFrame(update)};update();function connect(){var b=document.querySelector('#ssid').value,c=document.querySelector('#pass').value;fetch(`/connect?ssid=${b}&password=${c}`).then(()=>{document.querySelector('button').style.display='none',document.querySelector('.select').style.display='none',document.querySelector('input').style.display='none',document.querySelector('h1').innerText='Connected!'})}function addOption(b){var c=document.querySelector('#ssid'),d=document.createElement('option');d.text=b,c.add(d)}async function main(){var b=await getNetworks();for(let c=0;c<b.length;c++)addOption(b[c])}async function getNetworks(){var b=await fetch('/results').then(c=>c.text());return b.trim().split('\\n').map(c=>{return c=c.split(','),c[0]})}main();");
}

void handleScan() {
    server.send(200, "text/plain", ScanResult);
    ScanResult = Scan.scan();
    initializeAP();
}

void handleResults() {
    server.send(200, "text/plain", ScanResult);
}

void handleConnect() {
    if (!server.hasArg("ssid") || !server.hasArg("password")) {
        return server.send(200, "application/json", "{'s':false}");
    }

    ssid = server.arg("ssid");
    password = server.arg("password");

    Serial.print("ssid: ");
    Serial.println(ssid);
    Serial.print("password: ");
    Serial.println(password);
    server.send(200, "application/json", "{'s':true}");
    WebServer_close();
    switchFunction(&ssid[0], &password[0]);
}

void WebServer_close() {
    server.close();
}

void WebServer_setup(void (*function)(char*, char*)) {
    switchFunction = function;
    ScanResult = Scan.scan();

    initializeAP();
    server.on("/", handleRoot);
    server.on("/scan", handleScan);
    server.on("/results", handleResults);
    server.on("/connect", handleConnect);
    server.on("/script.js", handleJS);
    server.on("/style.css", handleCSS);
    server.begin();
    Serial.println("HTTP server started");
}

void WebServer_loop() {
    server.handleClient();
}
