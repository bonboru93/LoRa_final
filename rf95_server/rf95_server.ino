#include <SPI.h>
#include <RH_RF95.h>
RH_RF95 rf95;
void setup() 
{ 
  Serial.begin(9600);
  if (!rf95.init())
    Serial.println("[init failed]");  
}

uint8_t buf[64];
uint8_t len = sizeof(buf);
void loop()
{
  if (rf95.recv(buf, &len))
  {
    Serial.flush();
    Serial.print((char*)buf);
  }
}


