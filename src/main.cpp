#include <WiFi.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "spa";
const char* password = "12345678";

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);

  // Connect to WiFi (Station Mode)
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi!");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());

  // HTML Page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    String html = R"rawliteral(
      <!DOCTYPE html>
      <html>
      <head>
        <title>ESP32 OV7670 Stream</title>
      </head>
      <body>
        <h2>ESP32 Camera Stream</h2>
        <img src="/stream" />
      </body>
      </html>
    )rawliteral";
    request->send(200, "text/html", html);
  });

  // Placeholder stream
  server.on("/stream", HTTP_GET, [](AsyncWebServerRequest *request){
    // This will be replaced with image data later
    request->send(200, "image/jpeg", "", 0);
  });

  server.begin();
}

void loop() {
  // No code here for now
}
