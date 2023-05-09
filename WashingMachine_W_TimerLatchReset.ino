const uint8_t ledPin = 13;                          // Digital output pin that has the on board LED
const uint8_t zeroPin = 2;                          // Digital input pin to which the zero crossing detector is connected
const uint8_t relayPin = 12;   
int buttonState = 1;         // current state of the button 
boolean toggle = false;

#include <arduino-timer.h>
auto timer = timer_create_default();


bool toggle_latch(void *) {
  digitalWrite(8, LOW);
  delay(1000);
  digitalWrite(8, HIGH);
  return false; // repeat? true
}

void setup() {
  Serial.begin(9600);                       // Enable output driver for LED pin
  pinMode( zeroPin , INPUT );
  pinMode( relayPin , OUTPUT );
  pinMode( 8 , OUTPUT );
}

void loop() {
  timer.tick();

  digitalWrite(8, HIGH);

  if (digitalRead(zeroPin) == 1) {
    buttonState = 1;

   }
  
  if ( digitalRead(zeroPin) == 0 ) { 
    if (buttonState == 1) {
        buttonState = 0; 
        Serial.println(toggle);   
if(toggle)
    {
      Serial.println("LOW");
      digitalWrite(12, LOW);   // set the LED on
      toggle = !toggle;

     timer.in(5000000, toggle_latch);
    }
    else
    {
      delay(100);
      Serial.println("HIGH");
      digitalWrite(12, HIGH); 
      toggle = !toggle;

     timer.cancel();
    }



      
    } 
  }


  
}
