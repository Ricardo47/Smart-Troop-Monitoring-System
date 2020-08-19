//STATION CODE

#include <ESP8266WiFi.h>
#include <DallasTemperature.h>
#include <OneWire.h>

#define ONE_WIRE_BUS 4  //D2 pin of nodemcu

int Signal;
int S;
int PulseSensorPurplePin=A0;              //Pulse Sensor Analog Pin

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);      // Pass the oneWire reference to Dallas Temperature.
 
byte ledPin = 2;
char ssid[] = "Troop_AP";           // SSID of your AP
char pass[] = "Troop_comm";         // password of your AP

IPAddress server(192,168,4,15);     // IP address of the AP
WiFiClient client;

void setup()
{
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);           // connects to the WiFi AP
  Serial.println();
  Serial.println("Connection to the AP");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Connected to ");
  Serial.println("SQUAD LEADER");
  Serial.print("LocalIP:"); Serial.println(WiFi.localIP());
  Serial.println("MAC:" + WiFi.macAddress());
  Serial.print("Gateway:"); Serial.println(WiFi.gatewayIP());
  Serial.print("AP MAC:"); Serial.println(WiFi.BSSIDstr());
  sensors.begin();
 }

void loop() 
{
  sensors.requestTemperatures();                // Send the command to get temperatures  
  Signal = analogRead(PulseSensorPurplePin);    // Getting the analog data of pulse sensor
  S = (Signal/8);                                 // Calculating BPM
  
    client.connect(server, 80);
    Serial.println("********************************");
    Serial.print("Byte sent to the Squad Leader: ");
    Serial.println(client.print("Anyo\r"));
    String answer = client.readStringUntil('\r');
    Serial.println("From the Squad Leader: " + answer);
    String tempc = String(sensors.getTempCByIndex(0));
    Serial.print("Temperature of troop: " + tempc + "\r");         //Temperature on serial monitor of the client
    Serial.println(client.print(tempc));

    client.connect(server,80);
    String my = String(S);
    Serial.print("BPM of Troop: " + my + "\r" );
    Serial.println(client.print(my));
    //client.flush();
    
    if(client.available())
    { Serial.println("CLIENT NOT AVAILABLE"); }
}
