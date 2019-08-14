#include <ESP8266WiFi.h>

const char* ssid = "CBR";
const char* password = "droker2412CBR";

const uint16_t port = 12345;
const char* host = "192.168.45.75";

WiFiServer ESPServer(port);
void setup() {
  Start();
  WiFiConnection();

  Serial.println("Otwieram serwer:");
  ESPServer.begin();
}



void loop()
{
  if (ESPServer.hasClient())
  {
    WiFiClient ESPClient = ESPServer.available();
    Serial.println("Mam klienta");

    while (1)
    {
      if (ESPClient.available())
      {
        //Serial.println("Mam sygnał");
        String Message = ESPClient.readString();
        Serial.println(Message);
        ESPClient.write("Tu serwer.");
      }
    }
  }
}

void Start()
{
  Serial.begin(9600);
  WiFi.disconnect();
  delay(3000);
  pinMode(2, OUTPUT);
  Serial.print("Start\n");
}

void WiFiConnection()
{
  Serial.print("Łączę z ");
  Serial.print(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nPołaczono z siecią WiFi, mój adres: ");
  IPAddress myAddress = WiFi.localIP();
  Serial.println(myAddress);
}
