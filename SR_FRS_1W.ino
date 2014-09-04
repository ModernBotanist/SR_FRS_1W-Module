#include <SoftwareSerial.h>

byte radTX = 5; //serial pins for radio module
byte radRX = 4;
byte radSleep = 7; //"PD" low to sleep
byte radioPin = 9; //actual tone encodeing (Must be PWM)
byte PTT = 8; //push-to-talk pin, low to TX
char Buffer[30];
byte i;

char *handShake = "AT+DMOCONNECT";
char *setting = "AT+DMOSETGROUP=0,145.5500,145.5500,0,8,0,1";
  //0 = narrow FM
  //145.5500 = TX freq
  //145.5500 = RX freq
  //0 = RXCTCSS (none)
  //8 = Squelch (highest)
  //0 = TXCTCSS (none)
  //Flag??

SoftwareSerial radio(radTX, radRX);


void setup() {

  pinMode(radioPin, OUTPUT); //tone pin
  pinMode(PTT, OUTPUT);
  pinMode(radSleep, OUTPUT);
  digitalWrite(PTT, HIGH); //high to rx
  digitalWrite(radSleep, HIGH); //high is 'ON'
  delay(1000); //let it wake-up
  
  Serial.begin(115200);
  
  //delay(2000);
  //startup the radio module
  radio.begin(9600);
  delay(100);
  
  radio.println(handShake); //send AT handshake
  
  Serial.print("trying to connect, Response = ");
  radio.readBytesUntil(4,Buffer,15); //listen until "end of comm" (4) or 15 char
  for (i = 0; i < 13; i = i + 1) {
    Serial.print(Buffer[i]); //print out char one at a time
  }
  Serial.println(); //return
  Serial.print("Success??");
  if (Buffer[12] == '0') {
    Serial.println("YES!");
  } else {
    Serial.println("No.");
  }
  
  delay(1000); //otherwise radio module responds with handshake again
  
  Serial.println("initializing settings");
  radio.println(setting); //send AT setting
  Serial.print("response = ");

  radio.readBytesUntil(4,Buffer,15);
  for (i = 0; i < 14; i = i + 1) {
    Serial.print(Buffer[i]);
  }  
  Serial.println();
  Serial.println(); //return
  Serial.print("Success??");
  if (Buffer[13] == '0') {
    Serial.println("YES!");
  } else {
    Serial.println("No.");
  }
  
 //digitalWrite(radSleep, LOW);
  

}

void loop() {
  // put your main code here, to run repeatedly:



    //digitalWrite(radSleep, HIGH); //wake up radio
    //delay(500); //let it wake up

  /*  digitalWrite(PTT, LOW); //push-to-talk pin high
      tone(radioPin, 262);
      delay(1000);
      noTone(radioPin);
      delay(5000);
   
    digitalWrite(PTT, HIGH); //turn off radio when you're done
  
*/
  
}

