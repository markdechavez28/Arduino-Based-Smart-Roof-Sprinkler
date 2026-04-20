#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2
#define DHTTYPE DHT11
#define PUMP_PIN 8

#define HUMIDITY_THRESHOLD 60.0  // for testing only
#define TEMP_THRESHOLD 36.0      // for testing only

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(PUMP_PIN, OUTPUT);
  digitalWrite(PUMP_PIN, LOW);

  Serial.begin(9600);
  Wire.begin();                 
  dht.begin();
  delay(2000);                  

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Roof Sprinkler");
  delay(2000);                  
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Sensor error");
    lcd.setCursor(0, 1);
    lcd.print("Sensor Error  ");
    delay(2000);
  }
  //displays the temperature and humidity on the LCD screen
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature, 1);
  lcd.print("C   ");

  lcd.setCursor(0, 1);
  lcd.print("Hum: ");
  lcd.print(humidity, 1);
  lcd.print("%    ");
  //controls the pump based on the humidity and temperature readings
  if (temperature > TEMP_THRESHOLD && humidity <= HUMIDITY_THRESHOLD) {
    digitalWrite(PUMP_PIN, HIGH);
    Serial.println("Pump ON");
  } else {
    digitalWrite(PUMP_PIN, LOW);
    Serial.println("Pump OFF");
  }
  delay(2000);                 
}