/* Fill-in information from Blynk Device Info here */
// Device configuration with Blynk
#define BLYNK_TEMPLATE_ID "TMPL6GStd47OH"
#define BLYNK_TEMPLATE_NAME "Traffic Lights"
#define BLYNK_AUTH_TOKEN "EvMVM2MqF16-ZqpTHsNmNHndXGx5i2As"

// Pin definition for 12 LEDS

#define nr 12
#define ny 13
#define ng 14

#define er 33
#define ey 32
#define eg 25

#define wr 15
#define wy 5
#define wg 19

#define sr 21
#define sy 22
#define sg 23

#include <Arduino.h>
#include <Ultrasonic.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Innovative feature functions
void activatePedestrianSignal();
void beepBuzzer();


// Desired WiFi credentials
char ssid[] = "Ravindu Malinga";
char pass[] = "123456781";

bool loopRunning = false;

bool loopdef =false;

const unsigned long redDuration = 2000;
const unsigned long greenDuration = 6000;
const unsigned long yellowDuration = 2000;

// Configure Ultrasonic Sensor 

const int trigPin = 26;   // Ultrasonic sensor trigger pin
const int echoPin = 27;   // Ultrasonic sensor echo pin
const int buzzerPin = 34; // Buzzer pin

Ultrasonic ultrasonic(trigPin, echoPin);


BLYNK_WRITE(V0) { 

int btnState = param.asInt();
if (btnState == 1) {
    loopdef = 1; // Start the loop
  } else {
    loopdef = 0; // Exit the loop
  }
}

BLYNK_WRITE(V1) {
  int value2 = param.asInt();
  if (value2 == 1) {
    // 1st Junction
    digitalWrite(nr, HIGH);
    digitalWrite(ny, LOW);
    digitalWrite(ng, LOW);

    // 2nd Junction
    digitalWrite(er, LOW);
    digitalWrite(ey, LOW);
    digitalWrite(eg, HIGH);
    
    // 3rd Junction
    digitalWrite(sr, HIGH);
    digitalWrite(sy, LOW);
    digitalWrite(sg, LOW);
    
    
    // 4th Junction
    digitalWrite(wr, LOW);
    digitalWrite(wy, LOW);
    digitalWrite(wg, HIGH);

    delay(5000);

  } else {

    // Turn off all lights for the all junctions
     digitalWrite(nr, LOW);
    digitalWrite(ny, LOW);
    digitalWrite(ng, LOW);


    digitalWrite(er, LOW);
    digitalWrite(ey, LOW);
    digitalWrite(eg, LOW);
    
  
    digitalWrite(sr, LOW);
    digitalWrite(sy, LOW);
    digitalWrite(sg, LOW);
    
  
    digitalWrite(wr, LOW);
    digitalWrite(wy, LOW);
    digitalWrite(wg, LOW);
  }
}

BLYNK_WRITE(V3) {
  bool value4 = param.asInt();
  if (value4 == 1) {
    // 1st Junction
    digitalWrite(nr, LOW);
    digitalWrite(ny, LOW);
    digitalWrite(ng, HIGH);

    // 2nd Junction
    digitalWrite(er, HIGH);
    digitalWrite(ey, LOW);
    digitalWrite(eg, LOW);
    
    // 3rd Junction
    digitalWrite(sr, LOW);
    digitalWrite(sy, LOW);
    digitalWrite(sg, HIGH);
    
    // 4th Junction
    digitalWrite(wr, HIGH);
    digitalWrite(wy, LOW);
    digitalWrite(wg, LOW);

    delay(5000);

  } else {

    // Turn off all lights for all junctions
     digitalWrite(nr, LOW);
    digitalWrite(ny, LOW);
    digitalWrite(ng, LOW);


    digitalWrite(er, LOW);
    digitalWrite(ey, LOW);
    digitalWrite(eg, LOW);
    
  
    digitalWrite(sr, LOW);
    digitalWrite(sy, LOW);
    digitalWrite(sg, LOW);
    
  
    digitalWrite(wr, LOW);
    digitalWrite(wy, LOW);
    digitalWrite(wg, LOW);
  }
}


BLYNK_WRITE(V2) {


int buttonState = param.asInt();
if (buttonState == 1) {
    loopRunning = 1; // Start the loop
  } else {
    loopRunning = 0; // Exit the loop
  }

  
}

void setup()
{

  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);

  pinMode(nr, OUTPUT);
  pinMode(ny, OUTPUT);
  pinMode(ng, OUTPUT);

  pinMode(er, OUTPUT);
  pinMode(ey, OUTPUT);
  pinMode(eg, OUTPUT);

  pinMode(wr, OUTPUT);
  pinMode(wy, OUTPUT);
  pinMode(wg, OUTPUT);

  pinMode(sr, OUTPUT);
  pinMode(sy, OUTPUT);
  pinMode(sg, OUTPUT);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);


}
// Innovative feature added
void activatePedestrianSignal() {
  // Code to activate the pedestrian signal
  Serial.println("Pedestrian Detected! Activate Signal.");
}

void beepBuzzer() {
  // Beep the buzzer
  digitalWrite(buzzerPin, HIGH);
  delay(200); // Beep sound delay
  digitalWrite(buzzerPin, LOW);
}

void loop()
{
  Blynk.run();
  long distance = ultrasonic.read();

  if (distance > 350) {  // You can customaize the distance
    activatePedestrianSignal();
    beepBuzzer();
  } else {
    Serial.println("No Pedestrian Detected.");
  }
  
  delay(1000); 


if (loopRunning) {

    digitalWrite(ny,1);
    digitalWrite(ey,1);
    digitalWrite(sy,1);
    digitalWrite(wy,1);

    delay(500);

    digitalWrite(ny,0);
    digitalWrite(ey,0);
    digitalWrite(sy,0);
    digitalWrite(wy,0);

    delay(500);

    digitalWrite(ny,1);
    digitalWrite(ey,1);
    digitalWrite(sy,1);
    digitalWrite(wy,1);
  }
else{
  digitalWrite(ny,0);
    digitalWrite(ey,0);
    digitalWrite(sy,0);
    digitalWrite(wy,0);
}

// Default color light system checking
if(loopdef){
    digitalWrite(nr, HIGH); //north road red  ON
    digitalWrite(sr, HIGH); //south road red  ON
    
    digitalWrite(eg, HIGH); //east road green  ON
    digitalWrite(wg, HIGH); //west road green  ON
    delay(2500);

    digitalWrite(eg, LOW); //east road green  OFF
    digitalWrite(wg, LOW); //west road green  OFF
    
    digitalWrite(ny, HIGH); //North Yellow  ON
    digitalWrite(sy, HIGH); //South Yellow  ON
    digitalWrite(ey, HIGH); //east road Yellow  ON
    digitalWrite(wy, HIGH); //west road Yellow  ON

    digitalWrite(nr, LOW); //north road red  OFF
    digitalWrite(sr, LOW); //south road red  OFF
    delay(500);
    
    digitalWrite(eg, LOW); //east road green  OFF
    digitalWrite(wg, LOW); //west road green  OFF

    digitalWrite(er, HIGH); //east road red   ON
    digitalWrite(wr, HIGH); //west road red   ON

    digitalWrite(ey, LOW); //east road yellow  OFF
    digitalWrite(wy, LOW); //west road yellow  OFF
    digitalWrite(ny, LOW); //north road yellow  OFF
    digitalWrite(sy, LOW); //south road yellow  OFF

    digitalWrite(ng, HIGH); //north road green  ON
    digitalWrite(sg, HIGH); //south road green  ON

    delay(2500);
    
    digitalWrite(ey, HIGH); //east road yellow  ON
    digitalWrite(wy, HIGH); //west road yellow  ON
    digitalWrite(ny, HIGH); //north road yellow  ON
    digitalWrite(sy, HIGH); //south road yellow  ON

    digitalWrite(er, LOW); //east road red   OFF
    digitalWrite(wr, LOW); //west road red   OFF
    digitalWrite(ng, LOW); //north road red   OFF
    digitalWrite(sg, LOW); //south road red   OFF

    delay(500);
  
}
else{
 digitalWrite(nr, LOW);
    digitalWrite(ny, LOW);
    digitalWrite(ng, LOW);


    digitalWrite(er, LOW);
    digitalWrite(ey, LOW);
    digitalWrite(eg, LOW);
    
  
    digitalWrite(sr, LOW);
    digitalWrite(sy, LOW);
    digitalWrite(sg, LOW);
    
  
    digitalWrite(wr, LOW);
    digitalWrite(wy, LOW);
    digitalWrite(wg, LOW);

}


}