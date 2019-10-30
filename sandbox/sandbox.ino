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

  if(Serial.available()){
    int value = Serial.read();
    if (value == 2)
      Serial.write(rtcObject.GetDateTime().Year());
  }
  delay(1000);

}
