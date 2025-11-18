#include <Arduino_JSON.h>
#include <assert.h>
#include <LiquidCrystal.h>

#include <DHT.h>

#define DHTPIN 7  
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

String inputString = "";
bool stringComplete = false;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
JSONVar myObject;

void setup() 
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  inputString.reserve(200);

  dht.begin();
}

void loop() {
  float doAm = dht.readHumidity();
  float nhietDo = dht.readTemperature();

  lcd.setCursor(0,0);
  lcd.print("NHIET DO: "); lcd.print(nhietDo);
  lcd.setCursor(0,1);
  lcd.print("DO AM: "); lcd.print(doAm);


  myObject["NhietDo"] = (float) nhietDo;
  myObject["DoAm"] = (float) doAm;
  String jsonString = JSON.stringify(myObject);
  Serial.println(jsonString);
  delay(1000);
}
