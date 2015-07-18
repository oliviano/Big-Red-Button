/* BIG RED BUTTON Midi Controller - f
or Teensy v3.1 Based on Teensy Midi example.
v2 _ Debounce At 80 | New Startup Sequence _|

By Olivier Jean for Perceptual Engineering

*/

#include <Bounce.h>

// the MIDI channel number to send messages
const int channel = 5;

// We're using INT PIN 2 & 3
// Create Bounce objects for each button.  The Bounce object
// automatically deals with contact chatter or "bounce", and
// it makes detecting changes very simple.
// Default is 5ms changed to 80ms 

Bounce button4 = Bounce(4, 80);  // small button
Bounce button5 = Bounce(5, 150);  // big red button

const int ledPin = 13; // onnboard led
const int led1 = 14; // pad 1
const int led2 = 15; // pad 2


void setup() {
  
// Initialize button Pins 

pinMode(4, INPUT_PULLUP); // Button 1 ( toggle switch always open )
pinMode(5, INPUT_PULLUP); // Button 2 ( Big RED ONE ( always closed ) )
 
// Initialize LED's
pinMode(ledPin, OUTPUT);
pinMode(led1, OUTPUT);
pinMode(led2, OUTPUT);

 
 // Startup blink of LED's to signal all is good
     // Quick Loop on diagnostic LED
 for ( int i = 1; i < 3; i++){
  digitalWrite(ledPin, HIGH);   
  delay(1000);                 
  digitalWrite(ledPin, LOW);    
  delay(1000);
 }

// Fancy LED chase :)
for (int i=0; i<3; i++){
  for(int i=0;i<12;i++){  // increment automatically from 0 to 15 
    int a=i%2;      // calculate LSB   
    int b=i/2 %2;     
    int c=i/4 %2;        
    int d=i/8 %2;  //claculate MSB
    digitalWrite(led1,d);   //write MSB
    digitalWrite(led2,c);   
    digitalWrite(led1,b);    
    digitalWrite(led2,a);  // write LSB  
    delay(100);     // wait for a second  
    }
  digitalWrite(ledPin, HIGH);
  digitalWrite(led1, HIGH);  // turn the LED on (HIGH is the voltage level)
  digitalWrite(led2, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(500);               // wait for a second
  digitalWrite(ledPin, LOW);
  digitalWrite(led1, LOW);  // turn the LED off by making the voltage LOW
  digitalWrite(led2, LOW);  // turn the LED off by making the voltage LOW
  delay(500); 
  }  
}

// MAIN PROGRAM ----- 

void loop() {
  // Update all the buttons.  There should not be any long
  // delays in loop(), so this runs repetitively at a rate
  // faster than the buttons could be pressed and released.

  button4.update();
  button5.update();

  // Check each button for "falling" edge.
  // Send a MIDI Note On message when each button presses
  // Update the Joystick buttons only upon changes.
  // falling = high (not pressed - voltage from pullup resistor)
  //           to low (pressed - button connects pin to ground)
 

if (button4.fallingEdge()) {
    usbMIDI.sendNoteOff(64, 00, channel);  // 63 = E4
    digitalWrite(ledPin, LOW);
    digitalWrite(led1, LOW);  
    }
  
if (button5.fallingEdge()) {
    usbMIDI.sendNoteOn(65, 99, channel);  // 65 = F4
    digitalWrite(ledPin, HIGH);
    digitalWrite(led2, HIGH); 
    }
  


  // Check each button for "rising" edge
  // Send a MIDI Note Off message when each button releases
  // For many types of projects, you only care when the button
  // is pressed and the release isn't needed.
  // rising = low (pressed - button connects pin to ground)
  //          to high (not pressed - voltage from pullup resistor)

  if (button4.risingEdge()) {
    usbMIDI.sendNoteOn(64, 99, channel);  // 63 = E4
    digitalWrite(ledPin, HIGH);
    digitalWrite(led1, HIGH);

  }
  if (button5.risingEdge()) {
    usbMIDI.sendNoteOff(65, 0, channel);  // 65 = F4
    digitalWrite(ledPin, LOW);
    digitalWrite(led2, LOW); 
  }



  // MIDI Controllers should discard incoming MIDI messages.
  // http://forum.pjrc.com/threads/24179-Teensy-3-Ableton-Analog-CC-causes-midi-crash
  while (usbMIDI.read()) {
    // ignore incoming messages
  }
  delay(2);
}

