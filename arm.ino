/*********
  Rui Santos
  Complete project details at http://randomnerdtutorials.com
*********/

#include <WiFi.h>
#include <Servo.h>
int pos = 0;
Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;// create servo object to control a servo
// twelve servo objects can be created on most boards

// GPIO the servo is attached to
static const int servoPin1 = 13;
static const int servoPin2 = 12;
static const int servoPin3 = 14;
static const int servoPin4 = 27;

// Replace with your network credentials
const char* ssid     = "AndroidAP73B9";
const char* password = "hello123456";

// Set web server port number to 80
WiFiServer server(80);


// Variable to store the HTTP request
String header;

// Decode HTTP GET value
String valueString1 = String(90);
String valueString2 = String(0);
String valueString3 = String(5);
String valueString4 = String(0);
String valueStringse = String(0);
int pos1 = 0;
int pos2 = 0;
int pos3 = 0;


// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0;
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 1000;
void setup() {
  Serial.begin(115200);

  myservo1.attach(servoPin1); // attaches the servo on the servoPin to the servo object
  myservo2.attach(servoPin2);
  myservo3.attach(servoPin3);
  myservo4.attach(servoPin4);
  

 
  myservo1.write(90);
  myservo2.write(10);
  myservo3.write(5);

  for(int i = 0; i <= 180; i +=1){
    myservo1.write(i);
    delay(20);
  }
  for(int i = 0; i <= 75; i +=1){
    myservo3.write(i);
    delay(5);
  }
  for(int i = 180; i >= 90; i -=1){
    myservo1.write(i);
    delay(20);
    
  }
  for(int i = 0; i <= 90; i +=1){
    myservo2.write(i);
    delay(20);
    
  }
  for(int i = 90; i >= 10; i -=1){
    myservo2.write(i);
    myservo3.write(i);
    delay(20);
  }

  // Connect to Wi-Fi network w ith SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();   // Listen for incoming clients
  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>body { text-align: center; font-family: \"Trebuchet MS\", Arial; margin-left:auto; margin-right:auto; background-image: url(\"https://e1.pxfuel.com/desktop-wallpaper/68/228/desktop-wallpaper-neon-light-ring-huawei-mediapad-stock-sci-neon-iphone-12-pro-max-thumbnail.jpg\"); background-repeat: no-repeat; background-position: center; background-size: cover;}");
            client.println(".slider1 { width: 500px; }");
            client.println(".slider2 { width: 500px; }");
            client.println(".slider3 { width: 500px; }");
            client.println(".slider4 { width: 500px; }</style>");
            client.println("<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js\"></script>");

            // Web Page
            client.println("</head><body><h1>Arm Mechanism control by prathamesh</h1>");
            client.println("<p>Left Right Position: <span id=\"servoPos1\"></span></p>");
            client.println("<input type=\"range\" min=\"0\" max=\"180\" class=\"slider1\" id=\"servoSlider1\" onchange=\"servo1(this.value)\" value=\"" + valueString1 + "\"/>");

            client.println("<p>Extend Position: <span id=\"servoPos2\"></span></p>");
            client.println("<input type=\"range\" min=\"0\" max=\"100\" class=\"slider2\" id=\"servoSlider2\" onchange=\"servo2(this.value)\" value=\"" + valueString2 + "\"/>");

            client.println("<p>Left Right Position: <span id=\"servoPos3\"></span></p>");
            client.println("<input type=\"range\" min=\"0\" max=\"180\" class=\"slider3\" id=\"servoSlider3\" onchange=\"servo3(this.value)\" value=\"" + valueString3 + "\"/>");

            client.println("<p>Claw Position: <span id=\"servoPos4\"></span></p>");
            client.println("<input type=\"range\" min=\"0\" max=\"45\" class=\"slider4\" id=\"servoSlider4\" onchange=\"servo4(this.value)\" value=\"" + valueString4 + "\"/>");

            client.println("<p><button type=\"button\" onclick=\"resbu('0')\" id=\"resetbut\" />RESET</p>");

            client.println("<script>var slider1 = document.getElementById(\"servoSlider1\");");
            client.println("var servoP1 = document.getElementById(\"servoPos1\"); servoP1.innerHTML = slider1.value;");
            client.println("slider1.oninput = function() { slider1.value = this.value; servoP1.innerHTML = this.value; }");
            client.println("$.ajaxSetup({timeout:500}); function servo1(pos) { ");
            client.println("$.get(\"/?value=s1$\" + pos + \"&\"); {Connection: close};}");


            client.println("var slider2 = document.getElementById(\"servoSlider2\");");
            client.println("var servoP2 = document.getElementById(\"servoPos2\"); servoP2.innerHTML = slider2.value;");
            client.println("slider2.oninput = function() { slider2.value = this.value; servoP2.innerHTML = this.value; }");
            client.println("$.ajaxSetup({timeout:500}); function servo2(pos) { ");
            client.println("$.get(\"/?value=s2$\" + pos + \"&\"); {Connection: close};}");

            client.println("var slider3 = document.getElementById(\"servoSlider3\");");
            client.println("var servoP3 = document.getElementById(\"servoPos3\"); servoP3.innerHTML = slider3.value;");
            client.println("slider3.oninput = function() { slider3.value = this.value; servoP3.innerHTML = this.value; }");
            client.println("$.ajaxSetup({timeout:500}); function servo3(pos) { ");
            client.println("$.get(\"/?value=s3$\" + pos + \"&\"); {Connection: close};}");

            client.println("var slider4 = document.getElementById(\"servoSlider4\");");
            client.println("var servoP4 = document.getElementById(\"servoPos4\"); servoP4.innerHTML = slider4.value;");
            client.println("slider4.oninput = function() { slider4.value = this.value; servoP4.innerHTML = this.value; }");
            client.println("$.ajaxSetup({timeout:500}); function servo4(pos) { ");
            client.println("$.get(\"/?value=s4$\" + pos + \"&\"); {Connection: close};}");

            client.println("$.ajaxSetup({ timeout: 500 }); function resbu(pos) {");
            client.println("$.get(\"/?value=s5$\" + pos + \"&\"); slider3.value = 0; slider1.value = 90; slider2.value = 9; slider4.value = 0; servoP1.innerHTML = 90; servoP2.innerHTML = 10; servoP3.innerHTML = 0; servoP4.innerHTML = 0; {Connection: close};}</script>");
            client.println("</body></html>");

            //GET /?value=180& HTTP/1.1
            if (header.indexOf("GET /?value=") >= 0) {
              pos1 = header.indexOf('=');
              pos2 = header.indexOf('$');
              pos3 = header.indexOf('&');
              valueStringse = header.substring(pos1 + 1, pos2);


              if (valueStringse == "s1") {
                valueString1 = header.substring(pos2 + 1, pos3);


                int current = myservo1.read();

                if (valueString1.toInt() > current) {
                  for (int i = current ; i <= valueString1.toInt(); i += 1) {
                    delay(30);
                    myservo1.write(i);
                  }
                } else {
                  for (int i = current; i >= valueString1.toInt(); i -= 1) {
                    delay(30);
                    myservo1.write(i);
                  }
                }

              }
              //Rotate the servo
              if (valueStringse == "s2") {
                valueString2 = header.substring(pos2 + 1, pos3);


                int current = myservo2.read();

                if (valueString2.toInt() > current) {
                  for (int i = current ; i <= valueString2.toInt(); i += 1) {
                    delay(40);
                    myservo2.write(i);
                  }
                } else {
                  for (int i = current; i >= valueString2.toInt(); i -= 1) {
                    delay(40);
                    myservo2.write(i);
                  }
                }
              }
              if (valueStringse == "s3") {
                valueString3 = header.substring(pos2 + 1, pos3);


                int current = myservo3.read();

                if (valueString3.toInt() > current) {
                  for (int i = current ; i <= valueString3.toInt(); i += 1) {
                    delay(40);
                    myservo3.write(i);
                  }
                } else {
                  for (int i = current; i >= valueString3.toInt(); i -= 1) {
                    delay(40);
                    myservo3.write(i);
                  }
                }
              }
              if (valueStringse == "s4") {
                valueString4 = header.substring(pos2 + 1, pos3);
                myservo4.write(valueString4.toInt());
              }
              
              if (valueStringse == "s5") {
                myservo1.write(90);
                myservo2.write(10);
                myservo3.write(10);
                myservo4.write(pos);
                valueString4 = pos;
                valueString3 = 10;
                valueString2 = 10;
                valueString1 = 90;

              }
              Serial.println(valueStringse);
            }
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
