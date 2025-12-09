#include <LiquidCrystal.h>
bool shot_ready;
// const int rs = 9, en = 8, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
const int trigger_pin = 11;
const int solenoid_pin = 12;
int press_time;
// LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() {
  // put your setup code here, to run once:
  shot_ready = false;
  Serial.begin(9600);
  pinMode(solenoid_pin, OUTPUT);
  pinMode(trigger_pin, INPUT);
  // set up the LCD's number of columns and rows:
  // lcd.begin(16, 1);
  // Print a message to the LCD.
  press_time = -1;

}

void loop() {
  // put your main code here, to run repeatedly:
  // analog_input = analogRead(A0);
  // Serial.println((analog_input/1024.0)*5);
  // delay(500);
  // Serial.println(digitalRead(trigger_pin), HEX);
  if(digitalRead(trigger_pin)){
    if(press_time != -1){
      if(millis() - press_time >= 10){
        shot_ready = true;
        digitalWrite(solenoid_pin, HIGH);
        delay(100);
        digitalWrite(solenoid_pin, LOW);
        press_time = -1;
      }
    }else{
      if(shot_ready)
        press_time = -1;
      else
        press_time = millis();
    }
  }else{
    shot_ready = false;
  }
}
