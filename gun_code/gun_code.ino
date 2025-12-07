#include <LiquidCrystal.h>
bool trigger;
const int rs = 9, en = 8, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
const int trigger_pin = 11;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() {
  // put your setup code here, to run once:
  trigger = false;
  Serial.begin(9600);
  pinMode(12, OUTPUT);
  pinMode(trigger_pin, INPUT);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 1);
  // Print a message to the LCD.
  

}

void loop() {
  // put your main code here, to run repeatedly:
  // analog_input = analogRead(A0);
  // Serial.println((analog_input/1024.0)*5);
  // delay(500);
  Serial.println(digitalRead(trigger_pin), HEX);
  if((digitalRead(trigger_pin) == HIGH && trigger == false) || (digitalRead(trigger_pin) == LOW && trigger == true)){
    delay(100);
    if(digitalRead(trigger_pin) == HIGH){
      trigger = true;
    }else{
      trigger = false;
    }
  }else{
    return;
  }
  if(trigger){
    digitalWrite(12, HIGH);
    delay(100);
    digitalWrite(12, LOW);
    // digitalWrite(12, LOW);

    delay(100);
    //trigger = false;
  }
  lcd.setCursor(0, 0);
  lcd.print("hello");
}