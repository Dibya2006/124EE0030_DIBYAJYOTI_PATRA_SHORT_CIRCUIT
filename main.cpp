// C++ code
//
// Pin definitions
const int redPin = 13;    //the red led is connected to pin 13
const int yellowPin = 12; //the yellow led is connected to pin 12
const int greenPin = 11;  //the green led is connected to pin 11
const int buttonPin = 2;  //the button is connected to pin 2

// Timing variables
unsigned long greenTime = 4000;  //there is a delay of 4 seconds after the glow of green led
unsigned long yellowTime = 4000; //there is a delay of 4 seconds after the glow of yellow led
unsigned long redTime = 4000;    //there is a delay of 4 seconds after the glow of red led
unsigned long pedestrianRedTime = 7000; //there is a delay of 7 seconds after the glow of red led after the pressing of push button
unsigned long previousMillis = 0;  //setting the lower limit 
unsigned long cycleDuration = 0;   //lower limit of cycle duration
enum TrafficState { YELLOW, GREEN, RED, PEDESTRIAN_RED };
TrafficState currentState = RED;

void setup() {
  pinMode(greenPin, OUTPUT); //setting the output pin for green led
  pinMode(yellowPin, OUTPUT); //setting the output pin for yellow led
  pinMode(redPin, OUTPUT); //setting the output pin for red led
  
 
  pinMode(buttonPin, INPUT_PULLUP);  
  
  Serial.begin(9600); //starts serial communication, so that the Arduino can send out commands through the USB connection
}

void loop() {
  
  int buttonState = digitalRead(buttonPin);

  
  if (buttonState == HIGH) {
    
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    digitalWrite(yellowPin, LOW);
    delay(pedestrianRedTime);  
    currentState = RED;  
  } else {
    
    unsigned long currentMillis = millis();
    
    
    if (currentMillis - previousMillis >= cycleDuration) {
      previousMillis = currentMillis;  
      
     
      switch (currentState) {
        case YELLOW://for the red case
          digitalWrite(greenPin, LOW);
          digitalWrite(yellowPin, LOW);
          digitalWrite(redPin, HIGH);
          currentState = RED;
          cycleDuration = redTime;  
          break;
        case GREEN://for the yellow case
          digitalWrite(greenPin, LOW);
          digitalWrite(yellowPin, HIGH);
          digitalWrite(redPin, LOW);
          currentState = YELLOW;
          cycleDuration = yellowTime;  
          break;
        case RED://for the green case
          digitalWrite(greenPin, HIGH);
          digitalWrite(yellowPin, LOW);
          digitalWrite(redPin, LOW);
          currentState = GREEN;
          cycleDuration = greenTime;  
          break;
        default:
          break;
      }
    }
  }
}
