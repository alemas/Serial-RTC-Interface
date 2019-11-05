#include <Wire.h>
#include <RtcDS3231.h>

RtcDS3231<TwoWire> rtcObject(Wire);

void setup() {

  Serial.begin(9600);
  rtcObject.Begin();

  RtcDateTime currentTime = RtcDateTime(__DATE__, __TIME__);
  rtcObject.SetDateTime(currentTime);

}

void sendString(String message) {

  uint8_t length = message.length() + 2;
  message = ((uint8_t) message.length()) + message;
  byte buffer[length];
  message.getBytes(buffer, length);
  
  Serial.write(buffer, length);
}

void loop() {

  if (Serial.available()){
    
    char value = Serial.read();
    RtcDateTime currentDate = rtcObject.GetDateTime();
    
    switch(value) {
      
      case 'd': sendString(String(currentDate.Day()));
        break;
      case 'M': sendString(String(currentDate.Month()));
        break;
      case 'y': sendString(String(currentDate.Year()));
        break;
      case 'h': sendString(String(currentDate.Hour()));
        break;
      case 'm': sendString(String(currentDate.Minute()));
        break;
      case 's': sendString(String(currentDate.Second()));
        break;
      case 'F': {
      
        String day = String(currentDate.Day());
        String month = String(currentDate.Month());
        String year = String(currentDate.Year());
        String result = day + "/" + month + "/" + year;
        
        sendString(result);
      }
        
        break;
      case 'f': {

        String hour = String(currentDate.Hour());
        String minute = String(currentDate.Minute());
        String second = String(currentDate.Second());
        String result = hour + ":" + minute + ":" + second;
        
        sendString(result);
      }
        break;
      case 'T':
        sendString(String(rtcObject.GetTemperature().AsFloatDegC()));
        break;
      case 't':
        sendString(String(rtcObject.GetTemperature().AsFloatDegF()));
        break;
      default: sendString("n entendi");
        break;
    }
  }
  delay(1000);
}
