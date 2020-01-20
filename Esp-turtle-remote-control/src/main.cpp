#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "LcdKeypadShield.h"
#include "WemosD1R1Pins.h"

//Create oobject by board type
LcdKeypadShield lcd = LcdKeypadShield::createByBoaard(WemosD1R1);

const char* ssid = "";

const char* password = "";

ESP8266WebServer server(80);


void handleRoot() 
{
  server.send(200, "text/plain", "Hello World!");
}

void handleNotFound()
{
  String message = "File Not Found\n\n";

  message += "URI: ";

  message += server.uri();

  message += "\nMethod: ";

  message += (server.method() == HTTP_GET)?"GET":"POST";

  message += "\nArguments: ";

  message += server.args();

  message += "\n";

  for (uint8_t i=0; i<server.args(); i++)
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);
}



void setup(void)
{
  //set lcd size
  lcd.begin(16,2);

  WiFi.begin(ssid, password);

  //wait for connection
  lcd.printNew("Connecting");
  int i = 0;
  while (WiFi.status() != WL_CONNECTED) 
  {
    if(!(i % 3))
    {
      lcd.printNew("Connecting");
    }
    lcd.print(".");
    i++;
    delay(500);
  }
  
  lcd.printNew("IP addr:");
  
  lcd.setCursor(0,1);

  IPAddress ip = WiFi.localIP();

  lcd.print(ip.toString().c_str());

  server.on("/", handleRoot);

  server.on("/inline", []()
  {
    server.send(200, "text/plain", "Inline method");
  });

  server.onNotFound(handleNotFound);

  server.begin();
}

void loop(void)
{
  server.handleClient();
}