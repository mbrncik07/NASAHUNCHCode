#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

int offset = 20;
int sensorPin = A1;
LiquidCrystal_I2C lcd(0x27,20,4);  

int motor1pin1 = A2;

int motor1pin2 = A3;

int Booster1OUT1 = A4;

int Booster1OUT2 = A5;

int static_variable = 9;


unsigned long previousMillis = 0;
unsigned long previousMillis1 = 0;
unsigned long previousMillis3 = 0;  //will store last time LED was blinked
const long period = 1000;
const long MotorPeriod = 20000;     
int time = 0;

double AverageVoltageList[] = {};
int N = 0; 




void setup()
{
  
  lcd.init();
  lcd.backlight();
  
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(Booster1OUT1, OUTPUT);
  pinMode(Booster1OUT2, OUTPUT);
  Serial.begin(9600);

   
                    // initialize the lcd 
  // Print a message to the LCD.
} 
  



void loop()
{ 
  unsigned long currentMillis = millis();
  unsigned long currentMillis1 = millis(); // store the current time
  

  int volt = analogRead(A1);
  double Voltage = map(volt, 0, 1023, 0, 2500) + offset;
  Voltage /= 100; 

  Serial.print("Variable_1:");
  Serial.print(Voltage);
  Serial.print(",");
  Serial.print("Variable_2:");
  Serial.println(static_variable);
  

  if (currentMillis - previousMillis >= period){
  previousMillis = currentMillis;
  lcd.setCursor(0,0);
  lcd.print("TIME:");
  lcd.setCursor(6,0);
  lcd.print(time);
  lcd.setCursor(6,3);
  lcd.print("VOLTAGE:");
  lcd.print(Voltage);

  time++;
  
  }
  
  //in progress to try to solve the issue of differentiating between steady or all of a sudden events
  /*if (currentMillis - previousMillis3 >= 1000){
    previousMillis3 = currentMillis;

    AverageVoltageList[N] = Voltage;

    N += 1;

    if (N == 59){
       for(i = 0; i < 60; i++){
         sum += AverageVoltageList[i];
                  
       }
       AverageVoltageList[] = {};
    }


    */
      

  if (Voltage < 9){
    
    
    
    previousMillis1 = currentMillis1;
    digitalWrite(motor1pin1, HIGH);
    digitalWrite(motor1pin2, LOW);

    digitalWrite(Booster1OUT1, LOW);
    digitalWrite(Booster1OUT2, HIGH);
    
    
  }



  if (currentMillis1 - previousMillis1 >= MotorPeriod){
    
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, LOW);

    digitalWrite(Booster1OUT1, LOW);
    digitalWrite(Booster1OUT2, LOW);
    
    }
  
  
  
}

// end trigger code