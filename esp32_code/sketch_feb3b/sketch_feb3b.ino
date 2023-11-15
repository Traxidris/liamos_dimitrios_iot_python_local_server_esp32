#include <WiFi.h>
#include <Arduino.h>
#include <ThingSpeak.h>
#include <WiFiClient.h>
#include <HTTPClient.h>

String serverNamelocal="http://192.168.117.77:4000";
String Login="http://192.168.117.77:4000/login?username=liamos&password=dimitris&";
const int ledPin = 22;
int i;
const char* ssid = "LIAMOS";
const char* password = "11111111";
const int potPin = 36;
int potValue = 0;
WiFiClient client;
unsigned long myChannelNumber = 1996838;
const char * myWriteAPIKey = "2IJHXIP8IB12UJAJ";

void setup() {
pinMode(ledPin, OUTPUT);
Serial.begin(115200);
WiFi.begin(ssid, password);

while (WiFi.status() != WL_CONNECTED) {
Serial.print("Connecting to WiFi");
delay(500);
ThingSpeak.begin(client);
}

Serial.println("\nConnected to the WiFi network");
Serial.print("IP address: ");
Serial.println(WiFi.localIP());

HTTPClient http;
http.begin(Login.c_str());
int httpResponseCode = http.GET();

if (httpResponseCode>0) {
Serial.print("HTTP Response code: ");
Serial.println(httpResponseCode);
String payload = http.getString();
Serial.println(payload);
}
else {
Serial.print("Error code: ");
Serial.println(httpResponseCode);
}
http.end();
delay(1);
}

void loop() {
i=potValue;
ThingSpeak.writeField(myChannelNumber, 1, i, myWriteAPIKey);
potValue = analogRead(potPin);
Serial.println(potValue);
HTTPClient http;
String serverLocalPath= serverNamelocal +"/dashboard?f1="+String(potValue)+"&";
Serial.println(serverLocalPath);
http.begin(serverLocalPath.c_str());
int httpResponseCode = http.GET();

if (httpResponseCode>0) {
Serial.print("HTTP Response code: ");
Serial.println(httpResponseCode);
String payload = http.getString();
Serial.println(payload);
}
else {
Serial.print("Error code: ");
Serial.println(httpResponseCode);
}
http.end();
delay(1);

WiFiClient client;
const char *host = "192.168.117.77";
const int httpPort = 4000;
if (!client.connect(host, httpPort)) {
Serial.println("connection failed");
return;
}
client.print(String("GET /light HTTP/1.1\r\n") +
              "Host: " + host + "\r\n" +
"Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 10) {
      Serial.println("Client Timeout !");
      client.stop();
      return;
    }
  }

  while (client.available()) {
    String line = client.readStringUntil('\r');
    int value = line.toInt();
    if (value == 1) {
        digitalWrite(ledPin, HIGH);
} else {
digitalWrite(ledPin, LOW);
}
}
}
