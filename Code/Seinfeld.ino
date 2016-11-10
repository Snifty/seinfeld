#include "SD.h"
#include "TMRpcm.h"
#include "SPI.h"
#define echoPin 7
#define trigPin 8

TMRpcm tmrpcm;
char fileName[20];
int fileToPlay;
const int CS_PIN = 10;

void setup(){
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(CS_PIN, OUTPUT);
  
  tmrpcm.quality(1);
  tmrpcm.speakerPin = 9;
  tmrpcm.setVolume(6);
  
  sdTest();
 // playSong();
}

void loop(){  
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

  Serial.print(distance);
  Serial.println(" cm");
  
if(!tmrpcm.isPlaying()){
    if(distance > 20){
      playSong();
      delay(2000);
    }
}
  delay(500);
}

void sdTest(){
  if (SD.begin()){
    Serial.println("SD card is ready to use.");
    }else{
    Serial.println("SD card initialization failed");
    return;
  }
}

void playSong(){
    int fileToplay=random(35);
    Serial.println(fileToplay);
    sprintf(fileName, "%d.wav", fileToplay);  
    Serial.println(fileName);
    tmrpcm.play(fileName);
    Serial.println(tmrpcm.isPlaying());
}
