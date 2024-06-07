# Power Electronics Project 
# Open-Loop DC Motor Control System Using PWM Signal for Washing Machine Prototype

## Project Overview
This project involves creating a prototype of a washing machine using an Arduino to control a DC motor via PWM (Pulse Width Modulation). The project demonstrates how to build a DC drive system, control power electronics drive systems with microcontrollers, and implement various washing machine functions.

## Objectives
- Build a DC drive system.
- Learn how to control power electronics drive systems with microcontrollers.
- Build an H-bridge power converter with the required parts.
- Control motor speed using Arduino-generated PWM signals.
- Create a prototype of a washing machine and implement its functions.

## Hardware Required
- Arduino board (e.g., Arduino Uno)
- DC Motor
- H-bridge motor driver (e.g., L298N)
- Potentiometer
- Push buttons (4x)
- LCD display with I2C interface (16x2)
- Resistors, wires, and breadboard

## Circuit Diagram
![Circuit Diagram](/CircuitDiagram.jpg)

## Project Image
![Project Image](path/to/your/project_image.png)

## Code Explanation
The Arduino code controls the washing machine prototype using PWM signals to drive the DC motor. The control system includes several stages like adding clothes, filling detergent, closing the door, filling water, and selecting wash types.

### Key Functions
- **setup()**: Initializes pins, LCD, and serial communication.
- **loop()**: Main loop where PWM values are read from the potentiometer and applied to the motor.
- **buffer(time)**: Stops the motor for a specified duration.
- **resetDisplay()**: Resets the LCD display and waits for the start button.
- **readyToWash()**: Prepares the system for washing.
- **closeDoor()**: Ensures the door is closed before proceeding.
- **fillWater()**: Waits for water to be filled.
- **selectWashType()**: Allows the user to choose between quick wash and regular wash.
- **quickWash()**: Performs a quick wash cycle.
- **deepWash()**: Performs a deep wash cycle.
- **finishWashing()**: Signals that washing is complete.
- **inclothes()**: Prompts the user to add clothes.
- **outclothes()**: Prompts the user to take out clothes.
- **showCompleteMessage()**: Displays a completion message on the LCD.

## Usage
1. **Connect the Hardware**: Assemble your circuit based on the provided circuit diagram.
2. **Upload the Code**: Upload the Arduino code to your Arduino board using the Arduino IDE.
3. **Operate the Washing Machine**:
   - Add clothes and press the respective button.
   - Fill detergent and water when prompted.
   - Choose the wash type (quick wash or regular wash).
   - The motor will run according to the selected wash cycle, controlled by PWM signals.
   - Once the washing is complete, remove the clothes.

## Code
```cpp
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
```

## Challenges
- **Hardware Integration**: Ensuring all components work together smoothly was a significant challenge. Proper connections and reliable components were crucial for the project's success.
- **PWM Signal Stability**: Generating stable PWM signals to control the motor speed accurately required careful tuning and testing.
- **User Interface**: Designing an intuitive user interface using the LCD and buttons to simulate the washing machine's operation was challenging but essential for usability.

## Discussion
This project demonstrates the integration of various hardware components and software logic to create a functional prototype of a washing machine. The use of PWM signals to control the DC motor's speed showcases the practical application of microcontrollers in power electronics drive systems. The modular design of the code allows for easy modifications and enhancements, such as adding more wash cycles or improving the user interface.

## Conclusion
The Open-Loop DC Motor Control System for a Washing Machine Prototype successfully illustrates how to control a DC drive system using an Arduino. By following this project, others can learn about PWM signal generation, H-bridge motor drivers, and user interface design with an LCD and buttons. The challenges faced and overcome during the project provide valuable insights for future improvements and similar projects.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments
- Special thanks to the Arduino community for their support and resources.
- Inspiration from various online resources and tutorials.

## Contact
For any inquiries, please contact [S.M. Faizer] at [smfaizer000@gmail.com].
```

