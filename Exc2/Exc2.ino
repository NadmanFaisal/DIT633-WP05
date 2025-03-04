// (C) Mohamed Taha Jasser, Nadman Faisal, Zahid Hasan, group: 6 (2025)
// Work package 5
// Exercise 2
// Submission code: 871233 (provided by your TA-s)

#include <DHT.h>

// Defined pins for the LEDs
#define LED_1 9
#define LED_2 10
#define LED_3 11
#define LED_4 12
#define LED_5 13

// Defined ranges for temperature
#define RANGE_1 10
#define RANGE_2 20
#define RANGE_3 30
#define RANGE_4 40

#define DHTPIN 2             // pin of DHT

#define DHTTYPE DHT11       // Temp sens type which is DHT11

#define hundredms 100     // Hundred ms delay

float temp;             // Global variable to hold temp value

// Define data rate for Serial
#define DATA_RATE 9600

DHT dht(DHTPIN, DHTTYPE);  // initialize DHT sensor

void setup()
{
  Serial.begin(DATA_RATE);      // Initializes the Serial monitor
  
  dht.begin();  // starting DHT sensor

  pinMode(LED_1, OUTPUT);       // LED_1 initialized as output to show light
  pinMode(LED_2, OUTPUT);       // LED_2 initialized as output to show light
  pinMode(LED_3, OUTPUT);       // LED_3 initialized as output to show light
  pinMode(LED_4, OUTPUT);       // LED_4 initialized as output to show light
  pinMode(LED_5, OUTPUT);       // LED_5 initialized as output to show light
    
}

void loop()
{

  setTemp();
  delay(hundredms);

  digitalWrite(LED_1, LOW);       // Turns off LED_1
  digitalWrite(LED_2, LOW);       // Turns off LED_2
  digitalWrite(LED_3, LOW);       // Turns off LED_3
  digitalWrite(LED_4, LOW);       // Turns off LED_4
  digitalWrite(LED_5, LOW);       // Turns off LED_5
  
  if(temp <= RANGE_1) {           // If temperature less than the first defined range, 
    digitalWrite(LED_1, HIGH);    // turns on LED_1
  } else if(temp <= RANGE_2) {    // If temperature less than the second defined range, 
    digitalWrite(LED_1, HIGH);    // turns of LED_1 and
    digitalWrite(LED_2, HIGH);    // LED_2
  } else if(temp <= RANGE_3) {    // If temperature less than the third defined range, 
    digitalWrite(LED_1, HIGH);    // turns on LED_1,
    digitalWrite(LED_2, HIGH);    // turns on LED_2, and 
    digitalWrite(LED_3, HIGH);    // turns on LED_3
  } else if(temp <= RANGE_4) {    // If temperature less than fourth defined range, 
    digitalWrite(LED_1, HIGH);    // turns on LED_1, 
    digitalWrite(LED_2, HIGH);    // turns on LED_2,
    digitalWrite(LED_3, HIGH);    // turns on LED_3, and 
    digitalWrite(LED_4, HIGH);    // turns on LED_4
  } else {                        // If temperature is outside of those ranges, 
                                  // turns on all the LEDs.
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, HIGH);
    digitalWrite(LED_3, HIGH);
    digitalWrite(LED_4, HIGH);
    digitalWrite(LED_5, HIGH);
  }
  
}

/* 
This method is responsible for setting the global temp variable 
to the value which is read from the digital pin from the 
temperature sensor.
*/
void setTemp(){
  temp = dht.readTemperature();     // Digital readings taken from the temp sensor
  Serial.print("Temperature: "); // print temp
  Serial.println(temp); // print temp value

}
