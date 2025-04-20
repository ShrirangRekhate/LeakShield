#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>
#include <ZMPT101B.h>

// WiFi credentials
const char* ssid = "WifiSSID";
const char* password = "WIFI_Password";

// Voltage sensor setup
#define SENSITIVITY 500.0f
#define RELAY_PIN 2  // GPIO pin for relay control
#define VOLTAGE_THRESHOLD 15.0  // Threshold voltage in volts
ZMPT101B voltageSensor(32, 50.0);

// Web server on port 80
WebServer server(80);
// WebSocket server on port 81
WebSocketsServer webSocket = WebSocketsServer(81);

// Variables
float currentVoltage = 0.0;
bool relayState = false;
bool systemEnabled = true;

void setup() {
  Serial.begin(115200);
  
  // Initialize voltage sensor
  voltageSensor.setSensitivity(SENSITIVITY);
  
  // Initialize relay pin
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); 
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected to WiFi. IP address: ");
  Serial.println(WiFi.localIP());
  

  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
  server.on("/", handleRoot);
  server.on("/toggle", handleToggle);
  server.begin();
}

void loop() {
  server.handleClient();
  webSocket.loop();

  currentVoltage = voltageSensor.getRmsVoltage();
  
  if (systemEnabled) {
    if (currentVoltage > VOLTAGE_THRESHOLD) {
      digitalWrite(RELAY_PIN, LOW); 
      relayState = false;
    } else {
      digitalWrite(RELAY_PIN, HIGH); 
      relayState = true;
    }
  }
  
  // Send data to all connected WebSocket clients
  String json = "{\"voltage\":" + String(currentVoltage, 2) + 
                ",\"relay\":" + String(relayState ? "true" : "false") + 
                ",\"enabled\":" + String(systemEnabled ? "true" : "false") + "}";
  webSocket.broadcastTXT(json);
  
  // Serial output for debugging
  Serial.print("Voltage: ");
  Serial.print(currentVoltage);
  Serial.print("V, Relay: ");
  Serial.println(relayState ? "ON" : "OFF");
  
  delay(1000); // Update every second
}

void handleRoot() {
  String html = "<!DOCTYPE html><html><head><title>Voltage Monitor</title>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "<style>";
  html += "body { font-family: Arial, sans-serif; text-align: center; margin: 20px; }";
  html += ".voltage-display { font-size: 24px; margin: 20px; }";
  html += ".status { font-size: 18px; margin: 10px; }";
  html += ".relay { width: 100px; height: 100px; border-radius: 50%; margin: 20px auto; }";
  html += ".relay-on { background-color: #4CAF50; }";
  html += ".relay-off { background-color: #F44336; }";
  html += "button { padding: 10px 20px; font-size: 16px; margin: 10px; }";
  html += "</style>";
  html += "</head><body>";
  html += "<h1>Voltage Monitoring System</h1>";
  html += "<div class='voltage-display'>Voltage: <span id='voltage'>0.00</span> V</div>";
  html += "<div class='status'>System: <span id='systemStatus'>Active</span></div>";
  html += "<div id='relay' class='relay relay-off'></div>";
  html += "<div>Relay Status: <span id='relayStatus'>OFF</span></div>";
  html += "<button onclick='toggleSystem()'>Toggle System</button>";
  html += "<script>";
  html += "const ws = new WebSocket('ws://' + window.location.hostname + ':81/');";
  html += "ws.onmessage = function(event) {";
  html += "  const data = JSON.parse(event.data);";
  html += "  document.getElementById('voltage').textContent = data.voltage.toFixed(2);";
  html += "  const relay = document.getElementById('relay');";
  html += "  if(data.relay) {";
  html += "    relay.className = 'relay relay-on';";
  html += "    document.getElementById('relayStatus').textContent = 'ON';";
  html += "  } else {";
  html += "    relay.className = 'relay relay-off';";
  html += "    document.getElementById('relayStatus').textContent = 'OFF';";
  html += "  }";
  html += "  document.getElementById('systemStatus').textContent = ";
  html += "    data.enabled ? 'Active' : 'Disabled';";
  html += "};";
  html += "function toggleSystem() {";
  html += "  fetch('/toggle').then(response => response.text()).then(console.log);";
  html += "}";
  html += "</script>";
  html += "</body></html>";
  
  server.send(200, "text/html", html);
}

void handleToggle() {
  systemEnabled = !systemEnabled;
  server.send(200, "text/plain", systemEnabled ? "System Enabled" : "System Disabled");
}
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);
      break;
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[%u] Connected from %d.%d.%d.%d\n", num, ip[0], ip[1], ip[2], ip[3]);
      }
      break;
    case WStype_TEXT:
      break;
  }
}
