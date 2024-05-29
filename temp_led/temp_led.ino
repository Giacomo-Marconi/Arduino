#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

#define BLYNK_PRINT Serial
#define BLYNK_AUTH_TOKEN "------------"
#define BLYNK_TEMPLATE_ID "------------"
#define BLYNK_TEMPLATE_NAME "------------"

char auth[] = "------------";

char ssid[] = "------------";
char pass[] = "------------";

#define DHTPIN 2
#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE);

BlynkTimer timer; 

#define led = 5;

float temperature=0;
float humidity=0;



BLYNK_WRITE(V0){
  if(param.asInt() == 1){
    digitalWrite(led, HIGH);  
  }else{
    digitalWrite(led, LOW);
  }
}


void sendData() {
  temperature  = dht.readTemperature();
  humidity = dht.readHumidity();

  Serial.print("temp: ");
  Serial.print(temperature);
  Serial.print(" - hum: ");
  Serial.println(humidity);

  if(isnan(temperature) || isnan(humidity)){
    Serial.println("Valori non letti...");
    return;

  }

  Blynk.virtualWrite(V1, temperature);
  Blynk.virtualWrite(V2, humidity);  
}

void setup(){
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

  dht.begin();
  timer.setInterval(1000L, sendData); 

  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
}

void loop(){
  Blynk.run();
  timer.run();
}


