#include <IRremote.h>
float health = 100.0;
bool isDead = false;
const int vibrator = 12;
const int life_leds[3] = {4,5,6};
const int revive_sensor = 7;
const int ir_receiver = 3;
const int danger_led = 10;
void setup() {
  // put your setup code here, to run once:
  pinMode(vibrator, OUTPUT);
  pinMode(danger_led, OUTPUT);
  
  digitalWrite(vibrator, LOW);
  digitalWrite(danger_led, LOW);

  for(int i=0; i<3; i++){
    pinMode(life_leds[i], OUTPUT);
    digitalWrite(life_leds[i], HIGH);
  }

  pinMode(revive_sensor, INPUT);

  health = 100;
  isDead = false;

  Serial.begin(9600);
  IrReceiver.begin(ir_receiver, ENABLE_LED_FEEDBACK);
}

void damage(){
  health -= 10;
  digitalWrite(danger_led, HIGH);

  if(health <= 5){
    health = 0;
    isDead = true;
  }
  digitalWrite(vibrator, HIGH);
  float health_bar = int(4-((health+(100.0/3))/(100.0/3)));
  for(int i=0; i<health_bar; i++){
    digitalWrite(life_leds[i], LOW);
  }
}

void loop() {
  if(!isDead){
    if(IrReceiver.decode()){
      Serial.println("Hit: ");
      Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
      damage();
      Serial.println("Health: ");
      Serial.println(health, DEC);
      delay(200);
      if(!isDead)
        IrReceiver.resume();
    }else{
      digitalWrite(vibrator,LOW);
      digitalWrite(danger_led, LOW);
      delay(100);
    }
  }else{
    digitalWrite(vibrator, LOW);
    if (digitalRead(revive_sensor) == HIGH)
    {
      health = 100;
      isDead = false;
     for(int i=0; i<3; i++){
        digitalWrite(life_leds[i],HIGH);
      }
      delay(100);
      IrReceiver.resume();
    }
  }
}