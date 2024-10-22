/* FSR simple testing sketch.
 
Connect one end of FSR to power, the other end to Analog 0.
Then connect one end of a 10K resistor from Analog 0 to ground
 
For more information see www.ladyada.net/learn/sensors/fsr.html */
#include <Wire.h> //needed for I2C
#include <Adafruit_GFX.h> //needed for OLED screen
#include <Adafruit_SSD1306.h> //needed for OLED screen
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#include <Servo.h>
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Servo myservo;  // create servo object to control a servo

 
int fsrPin = 1;     // the FSR and 10K pulldown are connected to a0
int fsrReading;     // the analog reading from the FSR resistor divider
int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin

 
void setup() {
  // We'll send debugging information via the Serial monitor
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object

  Serial.begin(9600);  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
 {
 Serial.println("failed to access OLED...");
 for(;;);
 }
 delay(500);
 display.clearDisplay(); //clear display buffer
 display.setTextSize(1); //set text size
 display.setTextColor(WHITE); //set colour of font
 display.setCursor(0, 10); //set cursor 0 pixels from left 10 pixels down from top
 // Display static text

}

 
void loop() {
  fsrReading = analogRead(fsrPin);  
 
  Serial.print("Analog reading = ");
  Serial.print(fsrReading);     // the raw analog reading
  
  display.setCursor(0, 20);
  // We'll have a few threshholds, qualitatively determined
  if (fsrReading < 10) {
    Serial.println(" - No pressure");
  
  } else if (fsrReading < 200) {
    Serial.println(" - Light touch");
   
  } else if (fsrReading < 500) {
    
  } else if (fsrReading < 800) {
    Serial.println(" - Medium squeeze");
    
  } else {
    Serial.println(" - Big squeeze");
    
  }



 val = analogRead(potpin);
 display.println(val);    
      // reads the value of the potentiometer (value between 0 and 1023)
  val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  myservo.write(val);                  // sets the servo position according to the scaled value
  delay(15);                           // waits for the servo to get there
float DATA = fsrReading; //dummy data to print to OLED

 display.clearDisplay(); //clear the display ready for new data
 display.setCursor(0, 40); //move print cursor down 20 pixels from top border
 display.print("force: ");
 display.println(DATA); //print the DATA variable to OLED screen
 display.display(); //update the display buffer so we can actually see the data
 delay(20);

 
}

