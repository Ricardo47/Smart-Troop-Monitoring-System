//ACCESS POINT CODE

#include <ESP8266WiFi.h>
#include<DallasTemperature.h>
#include<OneWire.h>
#include<BlynkSimpleEsp8266.h>

int Signal1;
int S1;
int PulseSensorPurplePin1=A0;                          //Pulse Sensor Analog Pin

char auth[]="J3wcNUyb84MGXXfEYDdBb5o-lA8LTOX1";       //Blynk auth token
char ssid[]="a12asa";
char psd[]="a1ads11q";

WiFiServer server(80);
WiFiClient client;
IPAddress IP(192,168,4,15);
IPAddress mask = (255, 255, 255, 0);

#define ONE_WIRE_BUS 4                          //D2 pin of nodemcu
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire); 

int S;
String tempc1,itemp;                            //Variables for Temp
String BPMs,BPMt1;                               //Variables for BPM
void setup()  
{
  Serial.begin(9600);
  
  server.begin();
  Serial.println();
  
  sensors.begin();
}

void loop()
{
  //Creating server for the clients
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP("Troop_AP", "Troop_comm");
  WiFi.softAPConfig(IP, IP, mask);
  Serial.println("Squad Leader!!");
  Serial.println("Server started.");
  Serial.print("IP: ");     Serial.println(WiFi.softAPIP());
  Serial.print("MAC:");     Serial.println(WiFi.softAPmacAddress());

  // Connection between the client and server
    WiFiClient client = server.available(); 
    String request = client.readStringUntil('\r');
    Serial.println("********************************");
    Serial.println("From the Troop: " + request);
    Serial.print("Byte sent to the Troop: ");
    Serial.println(client.println(request + "ca" + "\r"));
    tempc1 = client.readStringUntil('\r');
    Serial.println("Temperature from Troop : " + tempc1);
    
    client = server.available();
    if(client.available()){Serial.println("YES");}
    String myBpm = String(client.readStringUntil('\r'));
    Serial.println("BPM from Troop: " + myBpm);
    
     //Data from this server unit
    sensors.requestTemperatures();   
    itemp = String(sensors.getTempCByIndex(0));
    Serial.println("Temperature from Leader : " + itemp);         //Temperature of Squad Leader
    Signal1 = analogRead(PulseSensorPurplePin1);
    S1 = (Signal1/8);
    BPMs = String(S1);
    Serial.println("BPM from Leader: " + BPMs);                   // BPM of Squad Leader
    
 
  // Connecting to a hotspot with Internet connection 
  WiFi.begin(ssid,psd);
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("Connected to " + String(ssid));
  Serial.println("********************************");
  Serial.print("Byte sent to the AP: ");
  Serial.println(client.print("Anyo\r"));
  String answer = client.readStringUntil('\r');
  Serial.println("From the AP: " + answer);
  String tempcs = String(sensors.getTempCByIndex(0));
  Serial.print("Temperature of SERVER: " + tempcs + "\r");         //Temperature on serial monitor of the client
  Serial.println(client.print(tempcs));
  Serial.println("Temperature of CLIENT:" + tempc1 +"\r");
  Serial.println(tempc1);
  Serial.println("BPM of CLIENT: " + myBpm + "\r");
  Serial.println(client.print(myBpm));
  Serial.println("BPM of SERVER: " + BPMs + "\r");
  Serial.println(BPMs);
  
  client.flush();
  client.stop();

  // Authenticating blynk app for analysis
  
  Blynk.begin(auth,ssid,psd);
  Blynk.run();
  Blynk.virtualWrite(V2,tempc1);
  Blynk.virtualWrite(V3,itemp);
  Blynk.virtualWrite(V4,myBpm);
  Blynk.virtualWrite(V5,BPMs);
}
