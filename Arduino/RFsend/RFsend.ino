#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

// Set up driver (Speed, receive pin, transmit pin) - receive pin does not matter as no receiving is done
RH_ASK driver(2000, 5, 3);

// Set the max characters per message and declare buffer to store each message
const int splitLength = 59;
char splitText[splitLength + 1];

void setup() {
  Serial.begin(115200);	  // Debugging only
  if (!driver.init())
    Serial.println("init failed");
}

void loop() {
  // Get everything from serial currently received
  String recvString = Serial.readString();

  if (recvString.length() != 0) {
    int numSubstring = recvString.length() / splitLength + 1;
    // Remove additional blank message if message length is multiple of split length
    if (recvString.length() % splitLength == 0) {
      numSubstring -= 1;
    }

    // For each substring required
    for (int i = 0; i < numSubstring; i++) {
      // Split the text into managable lengths
      memcpy(splitText, &recvString[i * splitLength], splitLength);

      // Send each message then delay to make sure finished
      driver.send((uint8_t *)splitText, strlen(splitText));
      driver.waitPacketSent();
      delay(100);

      // For debugging/piece of mind
      Serial.print("Sent (");
      Serial.print(i + 1);
      Serial.print(" of ");
      Serial.print(numSubstring);
      Serial.print("): ");
      Serial.println(splitText);
    }
  }
}
