#include <M5Unified.h>
#include <WiFiClientSecure.h>

// ref: https://sample.msr-r.net/m5stack-line-notify/

const char* ssid     = "ifdl";
const char* password = "XXXXXXXX"; // WiFi Password
const char* host     = "notify-api.line.me";
const char* token    = "XXXXXXXX"; // published LINE Notify token

unsigned long displayTime = 0;

boolean line_notify(String msg) {
  WiFiClientSecure client;
  client.setInsecure();
  if(!client.connect(host, 443)) {
    printf("connect error!\n");
    return false;
  }
  String query = String("message=") + msg;
  String request = String("")
              + "POST /api/notify HTTP/1.1\r\n"
              + "Host: " + host + "\r\n"
              + "Authorization: Bearer " + token + "\r\n"
              + "Content-Length: " + String(query.length()) +  "\r\n"
              + "Content-Type: application/x-www-form-urlencoded\r\n\r\n"
              + query + "\r\n";
  client.print(request);
  return true;
}

void setup() {
  M5.begin();
  M5.Display.setTextSize(2);
  M5.Display.clear();

  M5.Display.printf("WiFi connecting %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    M5.Display.print(".");
  }
  M5.Lcd.printf("ready\n");
}

void loop() {
  M5.update();
  if(M5.BtnA.wasPressed()) {
    String msg = "Button A Pressed";
    line_notify(msg);
  }
}
