#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2          
#define DHTTYPE DHT22     
#define PUMP_PIN 8        

#define HUMIDITY_THRESHOLD 80.0 // for testing only 
#define TEMP_THRESHOLD 20.0 // for testing only

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2); 

void setup() {
  pinMode(PUMP_PIN, OUTPUT);
  digitalWrite(PUMP_PIN, LOW);

  Serial.begin(9600);
  dht.begin();
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Roof Sprinkler");
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("No input");
    lcd.setCursor(0,1);
    lcd.print("Sensor Error  ");
    delay(2000);
    return;
  }

  lcd.setCursor(0,0);
  lcd.print("Temperature:");
  lcd.print(temperature, 1);
  lcd.print("C ");

  lcd.setCursor(0,1);
  lcd.print("Hum:");
  lcd.print(humidity, 1);
  lcd.print("%    "); 

  if (humidity < HUMIDITY_THRESHOLD || temperature > TEMP_THRESHOLD) {
    digitalWrite(PUMP_PIN, HIGH);
    Serial.println("Pump ON");
  } else {
    digitalWrite(PUMP_PIN, LOW);
    Serial.println("Pump OFF");
  }

  delay(1000); // for testing
}