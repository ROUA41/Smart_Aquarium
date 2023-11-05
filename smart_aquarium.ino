#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Adafruit_Sensor.h>
#include "DHT.h"
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define DHT11PIN 15
#define LIGHT_SENSOR_PIN 36  // ESP32 pin GIOP36 (ADC0) connected to light sensor
#define LED_PIN 18  // ESP32 pin GIOP22 connected to LED
#define ANALOG_THRESHOLD  500

DHT dht(DHT11PIN, DHT11);
int lcdColumns = 16;
int lcdRows = 2;

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows); 
char auth[] = "xF_CEvzCcd9l7S--E5o2wqBIkUtk26qg";  // Insérez votre jeton d'authentification Blynk
char ssid[] = "Redmi 9T";         // Insérez votre nom de réseau WiFi
char pass[] = "rouuuua1234";    // Insérez votre mot de passe WiFi
float hsensor = A3; // Broche analogique utilisée pour la lecture du capteur
float sensorValue = 0; // Variable qui stockera la valeur lue sur le capteur
int moisture;
float humidity;
const int pinCapteur = 34;
const int oneWireBus = 4;     
OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);
void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  dht.begin(); //Start the DHT11 Sensor
  pinMode(LED_PIN, OUTPUT);
  sensors.begin();
  lcd.init();                    
  lcd.backlight();  
}
void loop()
{Blynk.run();
//dht11
  float humi = dht.readHumidity();
  float temp = dht.readTemperature();
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print("ºC ");
  Serial.print("Humidity: ");
  Serial.println(humi);
  if (isnan(temp) || isnan(humi)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V0, temp);
  Blynk.virtualWrite(V1, humi);
  delay(2000);
  lcd.setCursor(0, 0);
  lcd.print("Temp ext:");
  lcd.print(temp);
  lcd.print("°C");
  lcd.setCursor(0, 1);
  lcd.print("hum ext:");
  lcd.print(humi);
  lcd.print("%");
  delay(2000);
  lcd.clear();

  //cap de sol
  sensorValue = analogRead(hsensor);
  moisture = ( 100 - ( (sensorValue/4095.00) * 100 ) );
  Serial.print("hum sol =");
  Serial.print(moisture);  /* Print Temperature on the serial window */
  Serial.println("%");
  //sensorValue = analogRead(hsensor);// lire la valeur aux bornes de capteur
  //Serial.print("moisture=");
  //Serial.print(sensorValue);
  Blynk.virtualWrite(V2, moisture);
  lcd.setCursor(0,0);
  lcd.print("hum sol= ");
  lcd.print(moisture);
  lcd.print("%");
  delay(2000);
  lcd.clear();

  // cap de niveau
  int valeurCapteur = analogRead(pinCapteur);
  float pourcentageNiveau = map(valeurCapteur, 0, 4095, 0, 100);
  Blynk.virtualWrite(V3, pourcentageNiveau);
  Serial.print("Niveau d'eau : ");
  Serial.print(pourcentageNiveau);
  Serial.println("%");
  lcd.setCursor(3, 0);
  lcd.print("niveau eau:");
  lcd.setCursor(4,1);
  lcd.print(pourcentageNiveau);
  lcd.print(" %");
  delay(2000);
  lcd.clear();

  // cap temp de l'eau
  sensors.requestTemperatures(); 
  float temperatureC = sensors.getTempCByIndex(0);
  Serial.print("Temperature eau: ");
  Serial.print(temperatureC);
  Serial.println("ºC");
  Blynk.virtualWrite(V4, temperatureC);
  lcd.setCursor(3, 0);
  lcd.print("la temp eau:");
  lcd.setCursor(4,1);
  lcd.print(temperatureC);
  lcd.print("°C");
  delay(2000);
  lcd.clear();

  //lumiere
  int analogValue = analogRead(LIGHT_SENSOR_PIN); // read the value on analog pin
  if (analogValue < ANALOG_THRESHOLD)
    digitalWrite(LED_PIN, HIGH); // turn on LED
  else
    digitalWrite(LED_PIN, LOW);  // turn off LED
}