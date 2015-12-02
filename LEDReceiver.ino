// Receiver for 3 digit number display
// MSBFIRST
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
/*-----( Declare Constants and Pin Numbers )-----*/
#define CE_PIN   9
#define CSN_PIN 10

const uint64_t pipe = 0xE8E8F0F0E1LL; // Define the transmit pipe
RF24 radio(CE_PIN, CSN_PIN); // Create a Radio

int number[1];//number to display
int current = 0;

//Segment Values
int a = 128; // top
int b = 64; // top left
int c = 8; // middle
int d = 4; // bot left
int e = 2; // bot
int f = 16; // bot right
int g = 32; // top right

int latchPin = 3;
int clockPin = 4;
int dataPin = 2;

int numberValue(int n){ // returns the appropirate shiftout MSBFIRST
 switch(n) {
   case 1:
     return g+f;
   case 2:
     return a+g+c+d+e;
   case 3:
     return a+g+c+f+e;
   case 4:
     return b+c+g+f;
   case 5:
     return a+b+c+f+e;
   case 6:
     return a+b+c+d+e+f;
   case 7:
     return a+g+f;
   case 8:
     return 254;
   case 9:
     return 254-d;
   case 0: 
     return 254-c;
 }
}

void displayNumber(int n){
  int one = n%10;
  int ten = (n/10)%10;
  int hun = (n/100)%10;
  
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, numberValue(hun));
  shiftOut(dataPin, clockPin, MSBFIRST, numberValue(ten));
  shiftOut(dataPin, clockPin, MSBFIRST, numberValue(one));
  digitalWrite(latchPin, HIGH);
  
}

void setup()   /****** SETUP: RUNS ONCE ******/
{
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
}//--(end setup )---


void loop()
{
  if ( radio.available() )
  {
    // Read the data payload until we've received everything
    bool done = false;
    while (!done)
    {
      // Fetch the data payload
      done = radio.read( number, sizeof(number) );
    }
    
    if (current != number[0]){
      current = number[0];
      displayNumber(current);
    }
  }
  
}
