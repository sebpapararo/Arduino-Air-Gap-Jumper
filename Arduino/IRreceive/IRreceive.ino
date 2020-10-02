#include <IRremote.h>

// Declare the pin used on the arduino board, the receiver object, and results object
int IR_RECEIVE_PIN = 3;
IRrecv irrecv(IR_RECEIVE_PIN);
decode_results results;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  // If something new receieved and is of type RC5
  if (irrecv.decode(&results)) {
    if (results.decode_type == RC5) {
      // Buffer to store received  message (max length of 4 char is 8 hex digits)
      char temp[8];

      // Convert from long to string
      sprintf(temp, "%lx", results.value);

      // Convert back to readable form and print
      String ascii = hexStringToAscii(temp);
      Serial.println(ascii);
    }
    irrecv.resume(); // Receive the next value
  }
}

String hexStringToAscii(char* hex) {
  String ascii = "";
  // Loop over the hex string 2 at time, as 2 hex digits represent 1 char
  for (size_t i = 0; i < strlen(hex); i += 2) {
    // Split the hex string into substrings of 2
    char part[2];
    memcpy(part, &hex[i], 2);

    // Convert from base 16 to char and append it
    char ch = strtoul(part, nullptr, 16);
    ascii += ch;
  }
  return ascii;
}
