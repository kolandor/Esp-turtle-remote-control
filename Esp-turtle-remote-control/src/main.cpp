#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "LcdKeypadShield.h"
#include "WemosD1R1Pins.h"
#include "Commands.h"

//Create oobject by board type
LcdKeypadShield lcd = LcdKeypadShield::createByBoaard(WemosD1R1);

//Wi-Fi data
const char* ssid = "";
const char* password = "";
//Server object and port
ESP8266WebServer server(80);

void handleRoot() 
{
  String command = NONE;

  switch (lcd.getButton())
    {
    case Up:
      command = UP;
      break;

    case Down:
      command = DOWN;
      break;

    case Left:
      command = LEFT;
      break;
    
    case Right:
      command = RIGHT;
      break;
    }

  server.send(200, "text/plain", command);
}

void handleNotFound()
{
  server.send(404, "text/plain", NONE);
}

void setup(void)
{
  //set lcd size
  lcd.begin(16,2);

  lcd.userButtonsAutoCorrect();

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

  server.onNotFound(handleNotFound);

  server.begin();
}

void loop(void)
{
  server.handleClient();
}