// Includes the Servo library
#include <Servo.h>.
//Include the lcd library code:
#include <LiquidCrystal.h>

// Defines Tirg and Echo pins of the Ultrasonic Sensor
const int trigPin = 3;//orange
const int echoPin = 2;//red white - vcc grey -gnd

// Variables for the duration and the distance
long duration;
int distance;
Servo myServo; // Creates a servo object for controlling the servo motor
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  //set up the LCD's number of columns and rows:
  lcd.begin(16, 2);


  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  //Inicialización del buzzer
  pinMode(5, OUTPUT); //yellow
  pinMode(11, OUTPUT);
  Serial.begin(9600);
  myServo.attach(9); // Defines on which pin is the servo motor attached on 9 purple
}
void loop() {
  // rotates the servo motor from 15 to 165 degrees
  for (int i = 0; i <= 180; i++) {
    myServo.write(i);
    delay(30);
    distance = calculateDistance();// Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree

    Serial.print(i); // Sends the current degree into the Serial Port
    Serial.print(","); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
    Serial.print(distance); // Sends the distance value into the Serial Port
    Serial.print("."); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  }
  // Repeats the previous lines from 165 to 15 degrees
  for (int i = 180; i > 0; i--) {
    myServo.write(i);
    delay(30);
    distance = calculateDistance();
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
  }
}
// Function for calculating the distance measured by the Ultrasonic sensor
int calculateDistance() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance = duration * 0.034 / 2;
  if (distance < 40)
  {
    digitalWrite(5, HIGH);
    digitalWrite(11, HIGH);

  }
  else
  {
    digitalWrite(5, LOW);
    digitalWrite(11, LOW);

  }
  return distance;


}
