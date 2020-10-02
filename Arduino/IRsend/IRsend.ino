#include <IRremote.h>

// Declare driver, max characters per message, and where to store each message
IRsend irsend; // Use pin 3, hardcoded into the library
const int splitLength = 4;
char splitText[splitLength + 1];

void setup() {
  Serial.begin(115200); // For debuggin
}

void loop() {
  // Get everything new the serial port has received
  String recvString = Serial.readString();

  if (recvString.length() != 0) {
    int numSubstring = recvString.length() / splitLength + 1;
    // Remove additional blank message if message length is multiple of split length
    if (recvString.length() % splitLength == 0)
      numSubstring -= 1;

    for (int i = 0; i < numSubstring; i++) {
      // Split the text into managable lengths
      memcpy(splitText, &recvString[i * splitLength], splitLength);

      // Convert the ascii to hex string
      String hexMessage = asciiToHexString(splitText);

      // Convert the string to an integer format, specifying base 16 (unsigned long required)
      unsigned long finalMessage = strtoul(hexMessage.c_str(), nullptr, 16);

      // Send the message using RC5 protocol and delay to make sure finished
      // Second param is the message length in bits
      irsend.sendRC5(finalMessage, strlen(splitText) * 8);
      delay(35);

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

String asciiToHexString(char* input) {
  // Prep buffer, will be twice as long as 2 hex digits = 1 char
  char hexMessage[strlen(input) * 2];

  // Loop through and convert each char to hex
  for (int i = 0, j = 0; i < strlen(input); ++i, j += 2)
    sprintf(hexMessage + j, "%02X", input[i]);

  // return string with hex prefix
  return "0x" + (String)hexMessage;
}
