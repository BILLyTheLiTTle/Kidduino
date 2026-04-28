#include "Debugger.h"

// The object is initialized in Debugger.h or here. 
// Given your snippet, we'll assume it's available globally.

void setup() {
  // Initialize the debugger at 9600 baud
  dbg.begin(9600);
  
  dbg.separator();
  Serial.println(F("System Initializing..."));
  dbg.separator();
}

void loop() {
  Serial.println(F("Looping..."));
  
  // Example of toggling debugger off after 5 seconds
  if (millis() > 5000) {
    dbg.setEnabled(false);
  }
  
  delay(1000);
}