   #include <Wire.h> 
#include <LiquidCrystal_I2C.h> 
#define pot A0 
#define button1 A1 
#define button2 A2 
#define button3 A3 
#define button4 2 
#define pwm1 9 
#define pwm2 10 
LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD I2C address to 0x27 for a 16 chars and 2 line display 
void setup() { 
pinMode(button1, INPUT_PULLUP); 
pinMode(button2, INPUT_PULLUP); 
pinMode(button3, INPUT_PULLUP); 
pinMode(button4, INPUT_PULLUP); 
pinMode(pot, INPUT); 
pinMode(pwm1, OUTPUT); 
pinMode(pwm2, OUTPUT); 
lcd.init(); // initialize the lcd 
lcd.backlight(); // turn on the backlight 
Serial.begin(9600); 
resetDisplay(); 
} 
void loop() { 
inclothes(); 
if (digitalRead(button1) == HIGH) { 
readyToWash(); 
} 
int potVal = analogRead(pot); 
int pwmVal = map(potVal, 0, 1023, 0, 255); 

analogWrite(pwm1, pwmVal); 
analogWrite(pwm2, 0); 
buffer(100);  
analogWrite(pwm1, 0); 
analogWrite(pwm2, pwmVal); 
buffer(100); 
Serial.println(pwmVal); 

} 
void buffer(unsigned long time) { 
digitalWrite(pwm1, LOW); 
digitalWrite(pwm2, LOW); 
delay(time); 
} 
void resetDisplay() { 
lcd.clear(); 
lcd.print("Press Button 1"); 
lcd.setCursor(0, 1); 
lcd.print("to Start"); 
while(digitalRead(button1) == LOW){} 
delay(200); // Debounce delay 
readyToWash(); 
} 
void readyToWash() { 
lcd.clear(); 
lcd.print("Ready to wash."); 
lcd.setCursor(0, 1); 

lcd.print("Fill Detergent!"); 
delay(3000); 
while (digitalRead(button2) == LOW) {} // Wait for button 2 press 
delay(200); // Debounce delay 
showCompleteMessage(); 
closeDoor(); 
} 
void closeDoor() { 
lcd.clear(); 
lcd.print("Close the Door!"); 
while (digitalRead(button2) == LOW) {} // Wait for button 2 press 
delay(200); // Debounce delay 
showCompleteMessage(); 
fillWater(); 
} 
void fillWater() { 
lcd.clear(); 
lcd.print("Fill the water!"); 
while (digitalRead(button2) == LOW) {} // Wait for button 2 press 
delay(200); // Debounce delay 
showCompleteMessage(); 
selectWashType(); 
} 

void selectWashType() { 
lcd.clear(); 
lcd.print("Quick Wash or"); 
lcd.setCursor(0, 1); 
lcd.print("Regular Wash?"); 
while (true) { 
if (digitalRead(button3) == HIGH) { 
delay(2000); // Debounce delay 
quickWash(); 
break; 
} 
if (digitalRead(button4) == HIGH) { 
delay(2000); // Debounce delay 
deepWash(); 
break; 
} 
} 
} 
void quickWash() { 
lcd.clear(); 
lcd.print("Quick Wash"); 
analogWrite(pwm1, 255); 
analogWrite(pwm2, 0); // Maximum speed 
delay(5000); // 5 seconds 
analogWrite(pwm1, 255); 

delay(5000); // 5 seconds 
analogWrite(pwm1, 255); 
delay(5000); // 5 seconds 
analogWrite(pwm1, 0); // Stop the motor 
analogWrite(pwm2, 255); // Maximum speed 
delay(5000); // 5 seconds 
analogWrite(pwm2, 255); // Maximum speed 
delay(5000); // 5 seconds 
analogWrite(pwm2, 255); // Maximum speed 
delay(5000); // 5 seconds 
analogWrite(pwm2, 0); 
finishWashing(); 
} 
void deepWash() { 
lcd.clear(); 
lcd.print("Regular Wash"); 
analogWrite(pwm1, 255); 
analogWrite(pwm2, 0); 
delay(5000); // 5 seconds 
analogWrite(pwm1, 200); 
delay(5000); // 5 seconds 
analogWrite(pwm1, 180); 
delay(5000); // 5 seconds 
analogWrite(pwm1, 0); // Stop the motor 
analogWrite(pwm2, 255); 
delay(5000); // 5 seconds 
analogWrite(pwm2, 200); 
delay(5000); // 5 seconds 
analogWrite(pwm2, 180); 
delay(5000); // 5 seconds 
analogWrite(pwm2, 0);
analogWrite(pwm1, 255);   
delay(5000); // 5 seconds 
analogWrite(pwm1,200); 
delay(5000); // 5 seconds 
analogWrite(pwm1, 128); 
delay(5000); // 5 seconds 
analogWrite(pwm1, 0); // Stop the motor 
analogWrite(pwm2, 255); // Maximum speed 
delay(5000); // 5 seconds 
analogWrite(pwm2, 200); // Maximum speed 
delay(5000); // 5 seconds 
analogWrite(pwm2, 128); // Maximum speed 
delay(5000); // 5 seconds 
analogWrite(pwm2, 0); 
finishWashing(); 
} 
void finishWashing() { 
lcd.clear(); 
lcd.print("Washing is"); 
lcd.setCursor(0, 1); 
lcd.print("Finished!"); 
delay(2000); 
outclothes(); 
} 
void inclothes() { 
lcd.clear(); 
lcd.print("Put in the"); 
lcd.setCursor(0, 1); 
lcd.print("clothes, please!"); 
delay(2000); // Show message for 2 seconds 
while (digitalRead(button2) == LOW) { 
delay(200); // Debounce delay 
showCompleteMessage(); 
resetDisplay(); 
} // Wait for button 2 press 
} 
void outclothes() { 
lcd.clear(); 
lcd.print("Take out the"); 
lcd.setCursor(0, 1); 
lcd.print("clothes, please!"); 
delay(2000); // Show message for 2 seconds 
while (digitalRead(button2) == LOW) {} // Wait for button 2 press 
delay(200); // Debounce delay 
resetDisplay(); 
} 

void showCompleteMessage() { 
lcd.clear(); 
lcd.print("Complete."); 
delay(2000); // Show message for 2 seconds 
}