#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Replace with your network credentials
const char* ssid = "WiFi-4BB0";
const char* password = "72539842";

const String apiKey = "96b8b154c565fc30c7c6fedc15c2b885";
const String city = "Flagstaff Hill";
const String country = "AU";
const String units = "metric"; 
int menuIndex = 0;

void setup() {
  Wire.begin(12, 14); // SDA, SCL
  Serial.begin(115200);



  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  WiFi.begin(ssid, password);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("Connecting to Wi-Fi..."));
  display.display();

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }
}

void loop() {
  display.clearDisplay();
  Serial.println("attempting system display");
  
  if (menuIndex == 0) {
    displayWiFiInfo();
  } else if (menuIndex == 1) {
    displaySystemInfo();
  } else if (menuIndex == 2) {
    displaySensorData();
  }
  display.display();
  
  // Simple menu navigation simulation
  delay(5000); // Wait 5 seconds before moving to the next menu
  menuIndex = (menuIndex + 1) % 3; // Cycle through 3 screens
}

void displayWiFiInfo() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Wi-Fi Info:");
  display.print("SSID: ");
  display.println(WiFi.SSID());
  display.print("IP: ");
  display.println(WiFi.localIP());
  display.print("Signal: ");
  display.print(WiFi.RSSI());
  display.println(" dBm");
  display.display();
}

void displaySystemInfo() {
  display.setCursor(0, 0);
  display.println("System Info:");
  display.print("Chip ID: ");
  display.println(ESP.getChipId());
  display.print("Flash Size: ");
  display.println(ESP.getFlashChipRealSize() / 1024 / 1024);
  display.print("Free Heap: ");
  display.println(ESP.getFreeHeap());
}

void displaySensorData() {
  display.setCursor(0, 0);
  display.println("Sensor Data:");
  // Simulate some sensor data
  display.print("Temp: ");
  display.println("25.3 C");
  display.print("Humidity: ");
  display.println("60 %");
}
