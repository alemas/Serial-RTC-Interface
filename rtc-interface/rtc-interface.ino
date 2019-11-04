#include <Wire.h>
#include <RtcDS3231.h>

RtcDS3231<TwoWire> rtcObject(Wire);

void setup() {

  Serial.begin(9600);
  rtcObject.Begin();

  RtcDateTime currentTime = RtcDateTime(__DATE__, __TIME__);
  rtcObject.SetDateTime(currentTime);

  Serial.println(rtcObject.GetDateTime());

}

void loop() {

  if (Serial.available()){
    
    char value = Serial.read();
    RtcDateTime currentDate = rtcObject.GetDateTime();
    
    switch(value) {
      
      case 'd': Serial.print(String(currentDate.Day()));
        break;
      case 'M': Serial.print(String(currentDate.Month()));
        break;
      case 'y': Serial.print(String(currentDate.Year()));
        break;
      case 'h': Serial.print(String(currentDate.Hour()));
        break;
      case 'm': Serial.print(String(currentDate.Minute()));
        break;
      case 's': Serial.print(String(currentDate.Second()));
        break;
      case 'F': {
      
        String day = String(currentDate.Day());
        String month = String(currentDate.Month());
        String year = String(currentDate.Year());
        String result = day + "/" + month + "/" + year;
        
        Serial.print(result);
      }
        
        break;
      case 'f': {

        String hour = String(currentDate.Hour());
        String minute = String(currentDate.Minute());
        String second = String(currentDate.Second());
        String result = hour + ":" + minute + ":" + second;
        
        Serial.print(result);
      }
        break;
      case 'T':
        Serial.print(rtcObject.GetTemperature().AsFloatDegC());
        break;
      case 't':
        Serial.print(rtcObject.GetTemperature().AsFloatDegF());
        break;
      default: Serial.print("n entendi");
        break;
    }
  }
  delay(1000);
}
