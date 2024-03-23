#include "MeMCore.h"
#include <math.h>



#define RGBWait 150  //in milliseconds
#define LDRWait 10  //in milliseconds
#define IR A2
#define LDR A3
#define pinA A0
#define pinB A1
#define TIMEOUT 1500  // Max microseconds to wait
#define SPEED_OF_SOUND 340
#define ULTRASONIC 12
#define IR_MIN 30
#define IR_MAX 400
//Constants for Music
#define NOTE_C3 131
#define NOTE_D3 147
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_G3 196
#define NOTE_A3 220
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_D4 294
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_G4 392
#define NOTE_A4 440
#define NOTE_B4 494

MeUltrasonicSensor ultraSensor(PORT_1);
MeDCMotor leftMotor(M1);   // assigning leftMotor to port M1
MeDCMotor rightMotor(M2);  // assigning RightMotor to port M2

uint8_t motorSpeed = 180;
int turnTime_left = 310;
int turnTime_right = 300;
int Uturn_time = 570;
int TURNDELAY = 200;

//Line Sensor Ports
MeLineFollower lineFinder(PORT_2);

//Buzzer
MeBuzzer buzzer;

//Music note array (for Melody) - Mortal Kombat Theme
int melody[] = {
  NOTE_A3,
  NOTE_A3,
  NOTE_C4,
  NOTE_A3,
  NOTE_D4,
  NOTE_A3,
  NOTE_E4,
  NOTE_D4,
  NOTE_C4,
  NOTE_C4,
  NOTE_E4,
  NOTE_C4,
  NOTE_G4,
  NOTE_C4,
  NOTE_E4,
  NOTE_C4,
  NOTE_G3,
  NOTE_G3,
  NOTE_B3,
  NOTE_G3,
  NOTE_C4,
  NOTE_G3,
  NOTE_D4,
  NOTE_C4,
  NOTE_F3,
  NOTE_F3,
  NOTE_A3,
  NOTE_F3,
  NOTE_C4,
  NOTE_F3,
  NOTE_C4,
  NOTE_B3,
  NOTE_A3,
  NOTE_A3,
  NOTE_C4,
  NOTE_A3,
  NOTE_D4,
  NOTE_A3,
  NOTE_E4,
  NOTE_D4,
  NOTE_C4,
  NOTE_C4,
  NOTE_E4,
  NOTE_C4,
  NOTE_G4,
  NOTE_C4,
  NOTE_E4,
  NOTE_C4,
  NOTE_G3,
  NOTE_G3,
  NOTE_B3,
  NOTE_G3,
  NOTE_C4,
  NOTE_G3,
  NOTE_D4,
  NOTE_C4,
  NOTE_F3,
  NOTE_F3,
  NOTE_A3,
  NOTE_F3,
  NOTE_C4,
  NOTE_F3,
  NOTE_C4,
  NOTE_B3,
  NOTE_A3,
  NOTE_A3,
  NOTE_A3,
  NOTE_A3,
  NOTE_G3,
  NOTE_C4,
  NOTE_A3,
  NOTE_A3,
  NOTE_A3,
  NOTE_A3,
  NOTE_G3,
  NOTE_E3,
  NOTE_A3,
  NOTE_A3,
  NOTE_A3,
  NOTE_A3,
  NOTE_G3,
  NOTE_C4,
  NOTE_A3,
  NOTE_A3,
  NOTE_A3,
  NOTE_A3,
  NOTE_G3,
  NOTE_E3,
  NOTE_A3,
  NOTE_A3,
  NOTE_A3,
  NOTE_A3,
  NOTE_A3
};

//Duration of each note in melody
int noteDurations[] = {
  8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  6, 6, 6, 6, 6, 6, 6, 6,
  6, 6, 6, 6, 6, 6, 6, 6,
  6, 6, 6, 6, 6, 6, 4, 8,
  4, 6, 6, 6, 6
};

//Contains the RGB values
int RGB[] = { 0, 0, 0 };
//Contains the raw data collected
int colourArray[] = { 0, 0, 0 };
//Predetermined values
float blackArray[] = { 660, 976, 875 };
float greyDiff[] = { 150, 25, 108 };

void setup() {
  delay(5000);  // Do nothing for 5000 ms = 5 seconds
   //setup the inputs/outputs for the colour sensor and IR sensor
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(LDR, INPUT);
  pinMode(IR, INPUT);
  Serial.begin(9600);
}

void loop() {
  leftMotor.run(-motorSpeed);  // Bot starts off going straight
  rightMotor.run(motorSpeed);
  blacklinedetector();
  runstraight();
}

//Movement Functions


// This function is used to stop motors
void stopMotor() {
  leftMotor.stop();
  rightMotor.stop();
}


//  This function is used to turn the bot 90 degrees to the left
void turn_left() {
  delay(TURNDELAY);
  leftMotor.run(270);
  rightMotor.run(270);
  delay(turnTime_left);
  stopMotor();
}


//  This function is used to turn the bot 90 degrees to the right
void turn_right() {
  delay(TURNDELAY);
  leftMotor.run(-270);
  rightMotor.run(-270);
  delay(turnTime_right);
  stopMotor();
}


// / This function is used to turn the bot 180 degrees on the spot (towards the right)
void u_turn_right() {
  delay(TURNDELAY);
  leftMotor.run(-270);
  rightMotor.run(-270);
  delay(Uturn_time);
  stopMotor();
}



//This function is used to stop the bot
void stop() {
  leftMotor.run(0);
  rightMotor.run(0);
}

//  This function is used to perform to consecutive 90 degree left turns on the bot
//The bot turns left, moves forward one tile and turns left again
void two_left_turns() {
  delay(TURNDELAY);
  leftMotor.run(270); // Turns left
  rightMotor.run(270);
  delay(turnTime_left);
  stop();
  delay(50);
  leftMotor.run(-270); // Goes straight
  rightMotor.run(270);
  delay(550);
  stop();
  delay(50);
  leftMotor.run(270); // Turns left again
  rightMotor.run(270);
  delay(turnTime_left + 20);
  stop();
}


// This function is used to perform to consecutive 90 degree right turns on the bot
// The bot turns right, moves forward one tile and turns right again
void two_right_turns() {
  delay(TURNDELAY);
  leftMotor.run(-270); //Turns right
  rightMotor.run(-270);
  delay(turnTime_right + 10);
  stop();
  delay(50);
  leftMotor.run(-270); //Goes straight
  rightMotor.run(270);
  delay(650);
  stop();
  delay(50);
  leftMotor.run(-270); // Turns right again
  rightMotor.run(-270);
  delay(turnTime_right + 20);
  stop();
}

//End of Movement functions

//Sensor Functions

//Detects if the linefollower is on a blackline
void blacklinedetector() {
  int sensorState = lineFinder.readSensors();

  if (sensorState == S1_IN_S2_OUT) {  // situation 1
    leftMotor.run(0);                 // Left wheel stops
    rightMotor.run(150);              // Right wheel go forward
  }
  if (sensorState == S1_OUT_S2_IN) {  // situation 2
    leftMotor.run(-150);              // Left wheel go forward
    rightMotor.run(0);                // Right wheel stops
  }
  if (sensorState == S1_IN_S2_IN) {  // situation 3
    leftMotor.run(0);                // Both wheels stop
    rightMotor.run(0);
    delay(200);


    digitalWrite(pinA, HIGH);  //Turn on red LED
    digitalWrite(pinB, LOW);
    delay(RGBWait);
    //get the average of 5 consecutive readings for the current colour and return an average
    colourArray[0] = getAvgReading(5);
    //the average reading returned minus the lowest value divided by the maximum possible range, multiplied by 255 will give a value between 0-255
    RGB[0] = (colourArray[0] - blackArray[0]) / (greyDiff[0]) * 255;
    delay(RGBWait);


    digitalWrite(pinA, LOW);  //Turn on blue LED
    digitalWrite(pinB, LOW);
    delay(RGBWait);
    colourArray[1] = getAvgReading(5);
    RGB[1] = (colourArray[1] - blackArray[1]) / (greyDiff[1]) * 255;
    delay(RGBWait);


    digitalWrite(pinA, LOW);  //Turn on green LED
    digitalWrite(pinB, HIGH);
    delay(RGBWait);
    colourArray[2] = getAvgReading(5);
    RGB[2] = (colourArray[2] - blackArray[2]) / (greyDiff[2]) * 255;
    delay(RGBWait);

    long color = detectColor(RGB);
    lightWaypoint(color);
  }
}

int getAvgReading(int times) {
  //find the average reading for the requested number of times of scanning LDR
  int reading;
  int total = 0;
  //take the reading as many times as requested and add them up
  for (int i = 0; i < times; i++) {
    reading = analogRead(LDR);
    total = reading + total;
    delay(LDRWait);
  }
  //calculate the average and return it
  return total / times;
}


//This function takes in the RGB values and returns the colour that is detected
char detectColor(int RGB[3]) {
  int res;
  if ((RGB[0] >= 220) && (RGB[1] >= 220) && (RGB[2] >= 220)) {
    //White
    res = 'W';
  } 
  else if ((RGB[0] >= 300) && (RGB[1] >= 120) && (RGB[1] <= 200) && (RGB[2] <= 150)) {
    //Orange
    res = 'O';
  } 
  else if ((RGB[0] >= 300) && (RGB[1] < 100) && (RGB[2] <= 120)) {
    //Red
    res = 'R';
  } 
  else if ((RGB[0] >= 280) && (RGB[1] >= 100) && (RGB[1] <= 200) && (RGB[2] >= 100) && (RGB[2] <= 210)) {
    //Purple
    res = 'P';
  } 
   if ((RGB[0] < 280) && (RGB[1] >= 100) && (RGB[1] <= 200) && (RGB[2] >= 100) && (RGB[2] <= 210)) {
    //Green
    res = 'G';
  }
   else {
    //Blue
    res = 'B';
  }
  return res;
}

// Takes in the colour that was detetced and instructs the mbot to perform a specific action
void lightWaypoint(char color) {
  if (color == 'R') {
    turn_left();
  } 
  else if (color == 'G') {
    turn_right();
  } 
  else if (color == 'O') {
    u_turn_right();
  } 
  else if (color == 'P') {
    two_left_turns();
  } 
  else if (color == 'B') {
    two_right_turns();
  } 
  else {
    play();
  }
}

//Function for the buzzer sound
void play() {
  for (int thisNote = 0; thisNote < 93; thisNote++) {
    int noteDuration = 625 / noteDurations[thisNote];
    buzzer.tone(8, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.20;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    buzzer.noTone(8);
  }
}

// Function that helps the mbot to run straight
void runstraight() {
  pinMode(ULTRASONIC, OUTPUT); //Turn on ultrasonic sensor
  digitalWrite(ULTRASONIC, LOW);
  delayMicroseconds(2);
  digitalWrite(ULTRASONIC, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRASONIC, LOW);

  float amb_IR = (analogRead(IR) / 1023) * 5; // Ambient IR reading
  digitalWrite(pinA, HIGH);  //Turns on the IR
  digitalWrite(pinB, HIGH);
  delay(5);
  float actual_IR = (analogRead(IR) / 1023) * 5; // Actual IR reading
  delay(1);
  int final_IR = amb_IR - actual_IR;
  digitalWrite(pinA, LOW);  //Turns on the green LED in order to turn off the IR sensor
  digitalWrite(pinB, HIGH);
   
  pinMode(ULTRASONIC, INPUT);
  long duration = pulseIn(ULTRASONIC, HIGH, TIMEOUT);
  int distance = 0;
  if (duration > 0) { // Checks to see if the left wall is nearby
    distance = duration / 2.0 / 1000000 * SPEED_OF_SOUND * 100;
    if (distance <= 7) { // Threshold value determined from testing
      leftMotor.run(-motorSpeed);  // If bot is too close to left wall right wheel slows down left wheel stays at same speed
      rightMotor.run(motorSpeed / 2);
      delay(100);
    }
  }

  if (final_IR >= 4) { // Threshold value determined from testing
    leftMotor.run(-motorSpeed / 2);  // If bot is too close to right wall left wheel slows down right wheel stays at same speed
    rightMotor.run(motorSpeed);
    delay(100);
  } 
  delay(100);
}
