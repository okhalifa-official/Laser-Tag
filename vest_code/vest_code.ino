#include <IRremote.h>
float health = 100.0;
bool isDead = false;
const int vibrator = 12;
const int life_leds[3] = {4,5,6};
const int revive_sensor = 7;
const int ir_receiver = 3;
const int danger_led = 10;
const int buzzer = 11;

void playReviveSound() {
  // Circular / swirling revive effect
  for (int i = 0; i < 3; i++) {        
    // Rising tone sweep
    for (int f = 600; f <= 1500; f += 100) {
      tone(buzzer, f, 40);
      delay(50);
    }
    // Falling tone sweep
    for (int f = 1500; f >= 600; f -= 100) {
      tone(buzzer, f, 40);
      delay(50);
    }
  }
  noTone(buzzer);
}

void playHitSound() {
  // Short sharp burst
  tone(buzzer, 1200); // initial high frequency
  delay(40);          // very short duration
  tone(buzzer, 800);  // quick drop
  delay(30);
  tone(buzzer, 600);  // final drop
  delay(20);

  noTone(buzzer);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(vibrator, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(danger_led, OUTPUT);
  
  digitalWrite(vibrator, LOW);
  digitalWrite(buzzer, LOW);
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
  playHitSound();
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
    // Revive mechanism
    if (digitalRead(revive_sensor) == HIGH)
    {
      delay(200);
      if (digitalRead(revive_sensor) == HIGH)
      {
        digitalWrite(vibrator,HIGH);
        playReviveSound();
        digitalWrite(vibrator,LOW);
        health = 100;
        isDead = false;
        for(int i=0; i<3; i++){
          digitalWrite(life_leds[i],HIGH);
          delay(100);
        }
        delay(100);
        IrReceiver.resume();
      }
    }
  }
}
