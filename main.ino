#include <LiquidCrystal_I2C.h>
#include <Servo.h>



Servo servo1;
LiquidCrystal_I2C lcd(0x27, 16, 2); //16 - columns , 2- rows

int joyX = A0;
int joyY = A1;
int switchPin = 2;

int trigPin = 10; 
int echoPin = 13;

float duration_us, distance_cm;
  
int servoVal;

int greenDiod = 4;
int yellowDiod = 5;
int redDiod = 6;
int clicks = 0;

void setup() 
{
  lcd.begin();
  lcd.backlight();
  
  lcd.setCursor(0,0);
  lcd.print("Distance [cm]: ");

  
  //servo
  servo1.attach(9);
  
  //ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  //Joystick Button
  pinMode(switchPin, INPUT);
  digitalWrite(switchPin, HIGH); 
  
  pinMode(greenDiod,OUTPUT); // green diod
  pinMode(yellowDiod,OUTPUT); // yellow diod
  pinMode(redDiod,OUTPUT); // red diod
    
   lcd.setCursor(0,0);
   lcd.print("Click to start");
  
  Serial.begin (9600);
  
}
void diod_controller(int distance){

    
    if(distance <100){
      digitalWrite(greenDiod,LOW);
      digitalWrite(yellowDiod,LOW);
      digitalWrite(redDiod,HIGH);
      }
      else if (distance >=100 && distance < 250) {
         digitalWrite(greenDiod,LOW);
         digitalWrite(yellowDiod,HIGH);
         digitalWrite(redDiod,LOW);
        }
        else if(distance >= 250){
          digitalWrite(greenDiod,HIGH);
          digitalWrite(yellowDiod,LOW);
          digitalWrite(redDiod,LOW);
          }
          
  }

  void clr_line_zero(){
 for(int i=0;i<16; i++){
           lcd.setCursor(i,0);
            lcd.print(" ");
          }
    }

    void clr_line_one(){
       for(int i=0;i<16; i++){
           lcd.setCursor(i,1);
            lcd.print(" ");
          }
      }

    void measureDistance(){
      if(clicks == 0){
        clr_line_zero();
        lcd.setCursor(0,0);
        lcd.print("Distance [cm]: ");
        }
        clicks++;
      // generate 10-microsecond pulse to TRIG pin
       digitalWrite(trigPin, HIGH);
       delayMicroseconds(10);
       digitalWrite(trigPin, LOW);

        duration_us = pulseIn(echoPin, HIGH);
        distance_cm = 0.017 * duration_us;

        //clearing function
        clr_line_one();
          
         lcd.setCursor(0,1);
         lcd.print(distance_cm);
        if(distance_cm > 420){
          lcd.setCursor(0,1);
          lcd.print("Out of range ");
          }
         diod_controller(distance_cm);
          delay(500);
          
      }

void loop()
{
  int buttonState = digitalRead(switchPin);
   
  servoVal = analogRead(joyX);
  servoVal = map(servoVal, 0, 1023, 60, 120);
  servo1.write(servoVal);

  if(buttonState == LOW){
    measureDistance();
    }
    
    
  delay(50);
}