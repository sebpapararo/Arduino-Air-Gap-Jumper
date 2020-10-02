#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

// Set up driver (Speed, receive pin, transmit pin) - transmit pin does not matter as no transmitting is done
RH_ASK driver(2000, 3, 5);

void setup() {
  Serial.begin(9600);	  // Debugging only
  if (!driver.init())
    Serial.println("init failed");
}

void loop() {
  // Declare and prepare buffer for received message
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  memset(buf, 0, sizeof(buf)); // Flush the buffer of garbage from previous loop
  uint8_t buflen = sizeof(buf);

  // If something new has been received, print it
  if (driver.recv(buf, &buflen)) {
    Serial.println((char*)buf);
  }
}
