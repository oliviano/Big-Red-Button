/* Rythmo Pole Midi Controller - for Teensy v3.1 Based on Teensy Midi example.
v5 _ Debounce At 100 | New Startup Sequence _| removed comments 
BY Olivier Jean
*/

#include <Bounce.h>

// the MIDI channel number to send messages
const int channel = 5;

// We're using INT PIN 2 & 3
// Create Bounce objects for each button.  The Bounce object
// automatically deals with contact chatter or "bounce", and
// it makes detecting changes very simple.
// Default is 5ms changed to 80ms 

Bounce button2 = Bounce(2, 100);
Bounce button3 = Bounce(3, 100);
Bounce button4 = Bounce(4, 100); 
Bounce button5 = Bounce(5, 100);

const int ledPin = 13; // onnboard led
const int led1 = 20; // pad 1
const int led2 = 21; // pad 2
const int led3 = 22; // pad 3
const int led4 = 23; // pad 4

void setup() {
  
// Initialize button Pins 
pinMode(0, INPUT_PULLUP);
pinMode(1, INPUT_PULLUP);
pinMode(2, INPUT_PULLUP);
pinMode(3, INPUT_PULLUP);
pinMode(4, INPUT_PULLUP);
pinMode(5, INPUT_PULLUP);
 
// Initialize LED's
pinMode(13, OUTPUT);
pinMode(led1, OUTPUT);
pinMode(led2, OUTPUT);
pinMode(led3, OUTPUT);
pinMode(led4, OUTPUT);
 
 // Startup blink of LED's to signal all is good
     // Quick Loop on diagnostic LED
 for ( int i = 1; i < 3; i++){
  digitalWrite(ledPin, HIGH);   
  delay(1000);                 
  digitalWrite(ledPin, LOW);    
  delay(1000);
 }
  for ( int i = 1; i < 5; i++){
  digitalWrite(ledPin, HIGH);   // set the LED on
  delay(500);                  // wait for a second
  digitalWrite(ledPin, LOW);    // set the LED off
  delay(500);
 }
}

// MAIN PROGRAM ----- 

void loop() {
  // Update all the buttons.  There should not be any long
  // delays in loop(), so this runs repetitively at a rate
  // faster than the buttons could be pressed and released.
  button2.update();
  button3.update();
  button4.update();
  button5.update();

  // Check each button for "falling" edge.
  // Send a MIDI Note On message when each button presses
  // Update the Joystick buttons only upon changes.
  // falling = high (not pressed - voltage from pullup resistor)
  //           to low (pressed - button connects pin to ground)
 
  if (button2.fallingEdge()) {
    usbMIDI.sendNoteOn(62, 99, channel);  // 62 = D4
    digitalWrite(ledPin, HIGH);
    digitalWrite(led1, HIGH);

  }
  if (button3.fallingEdge()) {
    usbMIDI.sendNoteOn(63, 99, channel);  // 63 = D#4
    digitalWrite(ledPin, HIGH);
    digitalWrite(led2, HIGH);  

  }
  if (button4.fallingEdge()) {
    usbMIDI.sendNoteOn(64, 99, channel);  // 63 = E4
    digitalWrite(ledPin, HIGH);
    digitalWrite(led3, HIGH);  

  }
  if (button5.fallingEdge()) {
    usbMIDI.sendNoteOn(65, 99, channel);  // 65 = F4
    digitalWrite(ledPin, HIGH);
    digitalWrite(led4, HIGH); 

  }


  // Check each button for "rising" edge
  // Send a MIDI Note Off message when each button releases
  // For many types of projects, you only care when the button
  // is pressed and the release isn't needed.
  // rising = low (pressed - button connects pin to ground)
  //          to high (not pressed - voltage from pullup resistor)

  if (button2.risingEdge()) {
    usbMIDI.sendNoteOff(62, 0, channel);  // 62 = D4
    digitalWrite(ledPin, LOW);
    digitalWrite(led1, LOW);
  }
  if (button3.risingEdge()) {
    usbMIDI.sendNoteOff(63, 0, channel);  // 63 = D#4
    digitalWrite(ledPin, LOW);
    digitalWrite(led2, LOW);

  }
    if (button4.risingEdge()) {
    usbMIDI.sendNoteOff(64, 0, channel);  // 63 = E4
    digitalWrite(ledPin, LOW);
    digitalWrite(led3, LOW);

  }
  if (button5.risingEdge()) {
    usbMIDI.sendNoteOff(65, 0, channel);  // 65 = F4
    digitalWrite(ledPin, LOW);
    digitalWrite(led4, LOW); 
  }



  // MIDI Controllers should discard incoming MIDI messages.
  // http://forum.pjrc.com/threads/24179-Teensy-3-Ableton-Analog-CC-causes-midi-crash
  while (usbMIDI.read()) {
    // ignore incoming messages
  }
  delay(2);
}

