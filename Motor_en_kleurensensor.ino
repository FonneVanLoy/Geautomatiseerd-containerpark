#define pwm1      3
#define pwm2      5

#include <SoftwareSerial.h>
SoftwareSerial BT(0,1); 
const int s0 = 8;  
const int s1 = 9;  
const int s2 = 12;  
const int s3 = 11;  
const int out = 10;  

int red = 0;  
int green = 0;  
int blue = 0; 
int inPin = 7;         // the number of the input pin
int outPin = 13;       // the number of the output pin

int state = HIGH;      // the current state of the output pin
int reading;           // the current reading from the input pin
int previous = LOW;    // the previous reading from the input pin

long time = 0;         
long debounce = 200; 

void setup() {
  // put your setup code here, to run once:
pinMode(pwm1, OUTPUT);
pinMode(pwm2, OUTPUT);

 Serial.begin(9600); 
  pinMode(s0, OUTPUT);  
  pinMode(s1, OUTPUT);  
  pinMode(s2, OUTPUT);  
  pinMode(s3, OUTPUT);  
  pinMode(out, INPUT);  
   
  digitalWrite(s0, HIGH);  
  digitalWrite(s1, HIGH);  
  pinMode(inPin, INPUT);
  pinMode(outPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
color(); 
  Serial.print("R Intensity:");  
  Serial.print(red, DEC);  
  Serial.print(" G Intensity: ");  
  Serial.print(green, DEC);  
  Serial.print(" B Intensity : ");  
  Serial.print(blue, DEC);  
  //Serial.println();  
  if (red > 100 && blue > 100 && green> 100)
  {
 digitalWrite(pwm1, 0);
   digitalWrite(pwm2, 0);
   delay(2000);
  }
  else if (red < blue && red < green && red < 20)
  {  
   Serial.println(" - (Red Color)");  
    digitalWrite(pwm1, 0);
    digitalWrite(pwm2, 0);
    delay(5000);
   
  }  

  else if (blue < red && blue < green)   
  {  
   Serial.println(" - (Blue Color)");  
   digitalWrite(pwm1, 0);
   digitalWrite(pwm2, 0); 
   delay(5000);
  }  

  else if (green < red && green < blue)  
  {  
   Serial.println(" - (Green Color)");  
    digitalWrite(pwm1, 0);
   digitalWrite(pwm2, 0);
   delay(5000);
  }  
  else{
  Serial.println();  
  }
   digitalWrite(pwm1, 0);
  digitalWrite(pwm2, 250); 
  delay(5000);

  reading = digitalRead(inPin);

  // if the input just went from LOW and HIGH and we've waited long enough
  // to ignore any noise on the circuit, toggle the output pin and remember
  // the time
  if (reading == HIGH && previous == LOW && millis() - time > debounce) {
    if (state == HIGH)
      state = LOW;
    else
      state = HIGH;

    time = millis();    
  }

  digitalWrite(outPin, state);

  previous = reading;
 } 
   
    
void color()  
{    
  digitalWrite(s2, LOW);  
  digitalWrite(s3, LOW);  
  //count OUT, pRed, RED  
  red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  digitalWrite(s3, HIGH);  
  //count OUT, pBLUE, BLUE  
  blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  digitalWrite(s2, HIGH);  
  //count OUT, pGreen, GREEN  
  green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
}

//}
