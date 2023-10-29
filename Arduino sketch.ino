#include <Servo.h>
#include <LiquidCrystal.h>
/* LCD pin configuration */
LiquidCrystal lcd(10,9,5,6,7,8); // LCD pins 

/* IR sensor  pin configuration */
int ir_pin = 4 ;  
/* Raindrop sensor  pin configuration */              
int digital_wetSensor_pin = 11;
/* Servo varaibles for the two servos used */
Servo servo,mini_servo;
/* Variable (pos1) = servo */
int pos1 = 90;
/* Variable (pos1) = mini_servo */
int pos2 = 75;
/* Time interval of IR sensor read INPUT signal */
const unsigned long eventInterval = 4000;
/* Time interval of Raindrop sensor read INPUT signal */
const unsigned long eventInterval_1 = 300;

unsigned long previousTime = 0 ;
unsigned long previousTime_1 = 0 ;
int ir_sense = 2;
int wet_sense = 2;



void setup() {
  pinMode (ir_pin, INPUT); // sensor pin INPUT
  pinMode(digital_wetSensor_pin, INPUT); // Raindrop sesnor pin INPUT

  Serial.begin(9600); // Serial monitor begin
  lcd.begin (16,2);  // LCD initialisation
  lcd.setCursor(0,0); // lCD set cursor to 0 column 0 row
  lcd.print("Getting ready"); // Print "Getting ready"
  servo.write(90);  // postion the servo to 90 degrees
  mini_servo.write(75);// postion mini_server to the postiion 75 degrees
  delay(1000); 
  lcd.clear(); // clear lcd
  lcd.setCursor(0,0);
  lcd.print("Ready to use now");// print ready to use 
  delay(3000); // dealy 3 seconds 


}

void loop() {
 
  unsigned long currentMillis = millis();
  
  int statusSensor = digitalRead (ir_pin);
  int wet_sensor = analogRead(A0);
  int d_wet_sensor = digitalRead(digital_wetSensor_pin);
  servo.attach(3, 500, 2500);
  mini_servo.attach(2, 500, 2500);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Scanning for ");
  lcd.setCursor(0,1);
  lcd.print("waste...");


/* TIMED event = IR sensor */
if(currentMillis - previousTime >= eventInterval){
  Serial.print("statusSensor: ");
  Serial.println(statusSensor);
  if (statusSensor == 0 ){
    ir_sense = 1;
  }else{
    ir_sense = 2;
  }
  previousTime = currentMillis;
}

/* TIMED event = Raindrop sensor */
if(currentMillis - previousTime >= eventInterval_1){
  Serial.print("\nWetSensor: ");
  Serial.println(d_wet_sensor);
  if (d_wet_sensor == LOW){
      Serial.print("Wet detected");
      wet_sense = 1;
      //ir_sense = 1;
  }else {
    //if (d_wet_sensor == HIGH){
      //Serial.print("DRY detected");
      wet_sense = 0;
      //ir_sense = 1; 
  }
  previousTime_1 = currentMillis;
}

/* Check for IR sensor and Raindrop sensor INPUT for Wet wate detection 
and perfom the action */
if (ir_sense == 1 && wet_sense == 1 ){
        Serial.print ("WET DETECTED");
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Detected:");
        lcd.setCursor(1,8);
        lcd.print("Wet waste:");
        servo.write(175);
        delay(1000);
        mini_servo.write(165);
        delay(1000);
        mini_servo.write(75);
        ir_sense = 2;
        wet_sense = 2;
        delay(1000);
}
/* Check for IR sensor and Raindrop sensor INPUT for Dry wate detection 
andperfom the action */
if (ir_sense == 1 && wet_sense == 0 ){
        Serial.print ("DRY DETECTED");
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Detected:");
        lcd.setCursor(1,8);
        lcd.print("Dry waste:");
        servo.write(90);
        delay(1000);
        mini_servo.write(165);
        delay(1000);
        mini_servo.write(75);
        ir_sense = 2;
        wet_sense = 2;
        delay(1000); 
}
}
