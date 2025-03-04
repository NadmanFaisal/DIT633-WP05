// (C) Mohamed Taha Jasser, Nadman Faisal, Zahid Hasan, group: 6 (2025)
// Work package 5
// Exercise 2.2
// Submission code: 871233 (provided by your TA-s)

#include <DHT.h>

#define RED_PIN  5// defining pin for red led
#define GREEN_PIN  7// defining pin for green led
#define YELLOW_PIN 6 // defining pin for yellow led
#define TIME_DELAY 1000

#define DHT_PHOTOPIN A1 // defining photoresistor pin 

int intervalPerSecond = 1000;
int previousMillis = 0;


#define DHTPIN 2             // pin of DHT

#define DHTTYPE DHT11       // Temp sens type which is DHT11


float temperature;             // Global variable to hold temp value
int perPhoto;                 // as per photo sensor
int photoSen;                 // reading from photo Sens

// Define data rate for Serial
#define DATA_RATE 9600

DHT dht(DHTPIN, DHTTYPE);  // initialize DHT sensor


void setup()
{
  Serial.begin(DATA_RATE); // initializing the serial
  dht.begin();  // starting DHT sensor
  pinMode(RED_PIN, OUTPUT); // initializing red led as output
  pinMode(GREEN_PIN, OUTPUT); // initilizing green led as output
  pinMode(YELLOW_PIN, OUTPUT); // initilizing yellow led as output

}

void readTempAndLight(){
  // int currentMillis = millis();

  // if (currentMillis - previousMillis >= intervalPerSecond) {
    // previousMillis = currentMillis;
    temperature =  dht.readTemperature();
    Serial.print("Temperature: "); // print temp
    Serial.println(temperature); // print temp value


    photoSen = analogRead(DHT_PHOTOPIN); // storing the photoresistor value
    perPhoto = map(photoSen, 1023, 143, 0, 100);  // mapping the photoresistor value to (0-100)
                                                  // The max and min values of the photoresistor 
                                                  // sensor is taken manually in first, at a brightly
                                                  // lit environment, then at a dark environment.

  // } 
}

void loop()
{
  readTempAndLight();
  digitalWrite(RED_PIN, LOW); // turing red led off
  digitalWrite(GREEN_PIN, LOW); // turing green led off
  digitalWrite(YELLOW_PIN, LOW); // turing yellow led off

  if((perPhoto <= 100 && perPhoto >=61)){ // check if photoresistor value is between 100-60
    if(temperature >= 21){ // check if temperature is above 21
      digitalWrite(GREEN_PIN, HIGH); // turn green led on
    }else if (temperature < 21){ // check if temperature is below 21
      digitalWrite(YELLOW_PIN, HIGH); // turn yellow led on
    }
  }

  if((perPhoto <= 60 && perPhoto >=21)){ // check if photoresistor value is between 60-21
    if(temperature <= 20 && temperature >= 0){ // check if temperature is between 20-0
      digitalWrite(GREEN_PIN, HIGH); // turn green led on
    } else if (temperature > 21){ // check if temperature is above 21
      digitalWrite(RED_PIN, HIGH); // turn red led on
    } else if (temperature < 0){ // check if temperature is below 0
      digitalWrite(YELLOW_PIN, HIGH); // turn yellow led on
    }
  }

  if((perPhoto <= 20 && perPhoto >=1)){ // check if photoresistor value is between 20-1
    if(temperature <= 0 && temperature >= -12){ // check if temperature is between 0-(-12)
      digitalWrite(GREEN_PIN, HIGH); // turn green led on
    } else if (temperature > 0){ // check if temperature is above 0
      digitalWrite(RED_PIN, HIGH); // turn red led on
    } else if (temperature < -12){ // check if temperature is below -12
      digitalWrite(YELLOW_PIN, HIGH); // turn yellow led on
    }

  } 

  if(perPhoto == 0){ // check if photoresistor value is equal to 0
    if(temperature < -12){ // check if temperature is below -12
      digitalWrite(GREEN_PIN, HIGH); // turn green led on
    } else if (temperature > -12){ // check if temperature is above -12
      digitalWrite(RED_PIN, HIGH); // turn red led on
    }

  } 

  Serial.println("Photoresistor: "); // printline for Photoresistor
  Serial.println(perPhoto); // print Photoresistor value
  Serial.print("degrees C: "); // printline for for temperature
  Serial.println(temperature); // print temperature value
  delay(TIME_DELAY);
 
}
