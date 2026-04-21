#include "SleepMode.h"

// Initialize SleepMode on Pin 2 (supports interrupts on Uno/Nano)
// Using 50ms for debounce logic
SleepMode sleepController(2);

void setup() {
    Serial.begin(9600);
    while (!Serial); // Wait for Serial to be ready
    
    Serial.println(F("System Initializing..."));
    
    // Initialize pin modes and initial state
    sleepController.begin();
    
    Serial.println(F("System Ready. Press button to wake or wait for sleep."));
}

void loop() {
    // 1. Always call update to keep the internal state (ACTIVE/SLEEP) synced
    sleepController.update();

    // 2. Check the current state
    if (sleepController.getState() == SystemState::ACTIVE) {
        Serial.println(F("System is ACTIVE. Working..."));
        delay(1000); // Simulate work
        
        Serial.println(F("Work done. Checking if I should sleep..."));
    }

    // 3. Logic to enter sleep
    // For this sample, we'll sleep if the button is NOT pressed (HIGH)
    // after we finish our "work".
    if (digitalRead(2) == HIGH) {
        Serial.println(F("Entering Deep Sleep Mode..."));
        
        // This will block until the interrupt (LOW) fires
        sleepController.enable(); 
        
        // --- The code pauses here during sleep ---
        
        // After waking up:
        Serial.println(F("WOKE UP! Returning to ACTIVE state."));
    }
}