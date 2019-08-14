#include <ESP8266WiFi.h>

unsigned long aktualnyCzas = 0;
unsigned long zapamietanyCzas = 0;
unsigned long roznicaCzasu = 0;

const char* ssid = "CBR";
const char* password = "droker2412CBR";

const uint16_t port = 12345;
const char* host = "192.168.45.75";
WiFiClient ESPClient;
int i = 0;
bool czujnik;

void setup()
{
  Start();
  WiFiConnection();
  firstConnection();
}
void loop()
{
  if (!ESPClient.connected())
  {
    Reconnection();
  }
  else
  {
    Communication();
  }
  delay(1000);
}

void Communication()
{
  if (digitalRead(4) == HIGH )
  {
    czujnik = true;
    if (czujnik)
    {
      aktualnyCzas = millis();
      zapamietanyCzas = aktualnyCzas;
      roznicaCzasu = 0;
      Serial.println("czujnik TRUE");
      ESPClient.print("Zapal");
      while (roznicaCzasu <= 10000UL)
      {
        if (digitalRead(4) == HIGH)
        {
          zapamietanyCzas = millis();
        }
        roznicaCzasu = millis() - zapamietanyCzas;
        Serial.println("TestA");
        delay(500);

      }

      Serial.println("Zgaś");
      ESPClient.println("Zgaś");
      czujnik = false;
    }
  }
  //String Message = ESPClient.readString();
  //Serial.println(Message);
  else
  {
    Serial.println("Brak ruchu");
    delay(500);
  }
}

void Reconnection()
{
  Serial.println("Nie połączono z serwerem!!!");
  ESPClient.connect(host, port);
  if (ESPClient.connected())
  {
    Serial.println("Połączono z serwerem!");
  }
  else
  {
    delay(1000);
    return;
  }
}
void firstConnection()
{
  while (!ESPClient.connected())
  {
    Serial.println("Próba połaczenia z serwerem!");
    ESPClient.connect(host, port);
    delay(1000);
    if (!ESPClient.connected())
    {
      Serial.println("Nie połączono z serwerem!!!");
    }
    else
    {
      Serial.println("Połączono z serwerem!");
    }
  }
}
void WiFiConnection()
{
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.print("Łączę z ");
  Serial.print(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nPołaczono z siecią WiFi.");
}
void Start()
{
  Serial.begin(9600);
  delay(3000);
  pinMode(4, INPUT);
  Serial.print("Start\n");
  digitalWrite(LED_BUILTIN, HIGH);
}
