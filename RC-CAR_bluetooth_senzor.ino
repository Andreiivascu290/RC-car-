
#include<SoftwareSerial.h>
#include<Servo.h>
Servo motor;


SoftwareSerial BlueTooth(0,1);  
char BT_input;                  
int motorPin1=10;                
int motorPin2=11; 
int trigPin = 3;
int echoPin = 5; 
int led = 4;


void setup()
{
  BlueTooth.begin(9600);
  Serial.begin(9600);
  pinMode(motorPin1,OUTPUT);
  pinMode(motorPin2,OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);  
  pinMode(led, OUTPUT);
  motor.attach(6);
  motor.write(100);
  
}
void loop()
 {
  long duration, distance, verf=0; //Calculul distantei cu senzorul ultrasonic
  digitalWrite(trigPin, LOW);
  delayMicroseconds(20);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(100);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration/29.387/2;   //calculul distantei in cm 
  if(BlueTooth.available()>0) //Testarea existentei conexiunii bluetooth
  {
    while(distance){                    //Folosim while pentru ca recalcularea distantei sa fie facuta astfel incat
      BT_input=BlueTooth.read();        //Daca nu este respectata conditia de distanta data de if-ul de mai jos tot procesul functiei 
      digitalWrite(trigPin, LOW);        //void loop sa fie reluat
      delayMicroseconds(20);
      digitalWrite(trigPin,HIGH);
      delayMicroseconds(100);
      digitalWrite(trigPin, LOW);
      duration = pulseIn(echoPin, HIGH);
      distance = duration/29.387/2;   
      if(distance <= 50 && verf==1)               //daca distanta inregistrata de senzor este mai mica de 50 cm
      {                                //masina franeaza
      digitalWrite(motorPin1,LOW);
      digitalWrite(motorPin2,HIGH);
      analogWrite(9, 255);
      delay(200);
      verf=0;  
      digitalWrite(motorPin1,LOW);
      digitalWrite(motorPin2,LOW);
      analogWrite(9, 255); 
             
      }   
      else if(BT_input=='f') //Comanda deplasare inainte
      {
      digitalWrite(motorPin1,HIGH);
      digitalWrite(motorPin2,LOW);
      analogWrite(9, 255);
      verf=1;
      }
      else if(BT_input=='b') //Comanda deplasare inapoi
      {
      digitalWrite(motorPin1,LOW);
      digitalWrite(motorPin2,HIGH);
      analogWrite(9, 255);
      verf=0;
    
      }
      else if(BT_input=='s') //Comanda franare
      {
      digitalWrite(motorPin1,LOW);
      digitalWrite(motorPin2,HIGH);
      analogWrite(9, 255);
      delay(200);
      verf=0;  
      digitalWrite(motorPin1,LOW);
      digitalWrite(motorPin2,LOW);
      analogWrite(9, 255); 
      }
      else if(BT_input=='i') //Comanda directiei centru
      {
      motor.write(100);
      }
      else if(BT_input=='l') //Comanda directiei stanga
      {
      motor.write(145);
      }
      else if(BT_input=='r') //Comanda directiei dreapta
      {
      motor.write(55);
      }
      else if(BT_input=='n')
      {
        digitalWrite(led, HIGH); //aprinde faruri
      }
      else if(BT_input=='o')
      {
        digitalWrite(led, LOW); //stinge faruri
      }
  }
}
    
          
   
  
}
