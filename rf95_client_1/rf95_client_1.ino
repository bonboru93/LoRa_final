#include <SPI.h>
#include <RH_RF95.h>
RH_RF95 rf95;
void setup() 
{
  //Serial.begin(9600);
  Serial1.begin(9600);
  if (!rf95.init())
    Serial1.println("[init failed]");
}

uint8_t data[RH_RF95_MAX_MESSAGE_LEN];
void loop()
{
  if (Serial1.available())
  {
    Serial1.readBytes(data, 64);
    //Serial.write(data, 40);
    Serial1.flush();
    rf95.send(data, sizeof(data));
  }
}

