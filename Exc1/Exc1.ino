#define BLINKER_PIN 4
#define LED_PIN 3
#define BUTTON_PIN 6

int timeDelay = 1000;
bool lightOn = false;
bool blink = true;

void setup() {
  setupTimer1();
  Serial.begin(9600);
  pinMode(BLINKER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
}

void loop() {

  if(digitalRead(BUTTON_PIN) == HIGH) {
    lightOn = true;
  } else {
    lightOn = false;
  }

  if(lightOn) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }

  // digitalWrite(BLINKER_PIN, HIGH);
  // delay(timeDelay);
  // digitalWrite(BLINKER_PIN, LOW);
  // delay(timeDelay);
}

void setLightOn() {
  if(blink) {
    blink = false;
  } else {
    blink = true;
  }
}

void setupTimer1() {

cli();

//set timer1 interrupt at 1Hz
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
  setLightOn();

  if(blink) {
    digitalWrite(BLINKER_PIN, HIGH);
  } else {
    digitalWrite(BLINKER_PIN, LOW);
  }
}