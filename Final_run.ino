#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Wire.h>
#include <Adafruit_VL53L0X.h>

// ====== WiFi Credentials ======
const char* ssid = "Izhanbhai Dandekar Sir";
const char* password = "11110000";

// ====== Create Web Server on Port 80 ======
ESP8266WebServer server(80);

// ====== Create VL53L0X Sensor Object ======
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

// ====== Variable to Store Last Measured Distance ======
uint16_t lastDistance = 0;

// ====== HTML Web Page ======
String htmlPage = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>Distance Measure</title>
  <style>
    body { font-family: Arial; text-align: center; margin-top: 40px; }
    table { margin: auto; border-collapse: collapse; }
    th, td { border: 1px solid #333; padding: 8px 12px; }
    button { padding: 10px 20px; font-size: 16px; margin-top: 20px; }
  </style>
</head>
<body>
  <h1>Distance Measure</h1>
  <button onclick="addReading()">Add Distance</button>
  <br><br>
  <table id="distanceTable">
    <tr>
      <th>Distance (mm)</th>
      <th>Label</th>
    </tr>
  </table>

  <script>
    function addReading() {
      fetch('/getDistance')
        .then(response => response.text())
        .then(data => {
          const label = prompt("Enter label for this reading:");
          const table = document.getElementById("distanceTable");
          const row = table.insertRow(-1);
          const cell1 = row.insertCell(0);
          const cell2 = row.insertCell(1);
          cell1.innerHTML = data;
          cell2.innerHTML = label || "No Label";
        });
    }
  </script>
</body>
</html>
)rawliteral";

void setup() {
  Serial.begin(115200);
  delay(1000); // Give time for Serial Monitor to initialize
  Serial.println("Booting...");

  // ====== Initialize I2C ======
  Wire.begin(D2, D1);  // D2 (GPIO4) = SDA, D1 (GPIO5) = SCL
  delay(100);

  // ====== Initialize VL53L0X Sensor ======
  if (!lox.begin()) {
    Serial.println("❌ Failed to initialize VL53L0X sensor!");
    while (true); // Halt here if sensor initialization fails
  }
  Serial.println("✅ VL53L0X sensor ready.");

  // ====== Connect to WiFi ======
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n✅ WiFi connected.");
  Serial.print("ESP8266 IP Address: ");
  Serial.println(WiFi.localIP());

  // ====== Web Routes ======

  // Serve the HTML page
  server.on("/", HTTP_GET, []() {
    server.send(200, "text/html", htmlPage);
  });

  // Handle distance measurement request
  server.on("/getDistance", HTTP_GET, []() {
    VL53L0X_RangingMeasurementData_t measure;
    lox.rangingTest(&measure, false); // Perform single ranging measurement

    if (measure.RangeStatus != 4) {
      lastDistance = measure.RangeMilliMeter;
      Serial.print("📏 Distance: ");
      Serial.print(lastDistance);
      Serial.println(" mm");
    } else {
      lastDistance = 0; // Invalid reading
      Serial.println("⚠️ Invalid distance reading.");
    }

    server.send(200, "text/plain", String(lastDistance));
  });

  // Start web server
  server.begin();
  Serial.println("🌐 HTTP server started.");
}

void loop() {
  server.handleClient(); // Continuously handle incoming requests
}
