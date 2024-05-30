#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char ssid[] = "----------";
char pass[] = "----------";

#define led 5
#define buzzer 4
#define light A0

#define BLYNK_AUTH_TOKEN "----------"
#define BLYNK_TEMPLATE_ID  "----------"
#define BLYNK_TEMPLATE_NAME  "----------"

#define BLYNK_PRINT Serial

BlynkTimer timer;

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

float temp=0;
float hum=0;
float luce=0;


BLYNK_WRITE(V0){
  if(param.asInt() == 1){
    digitalWrite(led, HIGH);  
  }else{
    digitalWrite(led, LOW);
  }
}

BLYNK_WRITE(V3){
  if(param.asInt() == 1){
    digitalWrite(buzzer, HIGH);  
  }else{
    digitalWrite(buzzer, LOW);
  }
}


void rwdata(){
  temp  = dht.readTemperature();
  hum = dht.readHumidity();
  luce = map(analogRead(light), 0, 1024, 0, 100);

  if(isnan(temp) || isnan(hum) || isnan(luce)){
    return;
  }

  Serial.print(temp);
  Serial.print("  ");
  Serial.print(hum);
  Serial.print("  ");
  Serial.println(luce);

  Blynk.virtualWrite(V1, temp);
  Blynk.virtualWrite(V2, hum); 
  Blynk.virtualWrite(V4, luce);
}

void setup(){
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  dht.begin();
  timer.setInterval(1000L, rwdata); 

  pinMode(light, INPUT);

  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);

  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);
}


void loop(){
  Blynk.run();
  timer.run();
}
