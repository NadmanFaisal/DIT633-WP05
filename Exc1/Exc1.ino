// (C) Mohamed Taha Jasser, Nadman Faisal, Zahid Hasan, group: 6 (2025)
// Work package 5
// Exercise 1
// Submission code: 871233 (provided by your TA-s)

#define BLINKER_PIN 4 // Blinker pin is on pin 4
#define LED_PIN 3 // LED pin is on pin 3
#define BUTTON_PIN 6 // Button pin on pin 6

bool lightOn = false; // checks if light is on
bool blink = true; // check for blinking status

// setup
void setup() { 
  setupTimer1(); // setup timer interrupts
  Serial.begin(9600); // begin serial communication  9600
  pinMode(BLINKER_PIN, OUTPUT); // set pin mode for blinker pin to Output
  pinMode(BUTTON_PIN, INPUT); // set pin mode for button pin to Input
}

void loop() {

  // we read the button and see if it is pressed
  if(digitalRead(BUTTON_PIN) == HIGH) {
    lightOn = true; // turn on the light
  } else {
    lightOn = false; // turn off the light
  }

  // if light is on
  if(lightOn) {
    digitalWrite(LED_PIN, HIGH); // turn led to on
  } else {
    digitalWrite(LED_PIN, LOW); // turn led to off
  }
}

// set blinking light on
void setLightOn() {
  if(blink) { // if it is already blinking 
    blink = false; // set blinking to false so that ISR digitalWrites to LOW
  } else { // if it is not blinking 
    blink = true; // set blinking to true so that ISR digitalWrites to HIGH
  }
}

// setting up the timer for timer1 
void setupTimer1() {

// stop interrupts
cli();

//set timer1 interrupt at 1Hz == 1s frequency
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);


sei();//allow interrupts

}//end setup

ISR(TIMER1_COMPA_vect){//timer1 interrupt 1Hz toggles pin 13 (LED)
  setLightOn(); // set blinking lights to on or off

  // if the boolean was true, meaning the state of the blink is blinking
  if(blink) {
    digitalWrite(BLINKER_PIN, HIGH); // set blinking led to on
  } else {
    digitalWrite(BLINKER_PIN, LOW); // set blinkin led to off
  }
}
