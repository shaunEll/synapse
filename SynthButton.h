#ifndef SynthButton_h
#define SynthButton_h
#include "Arduino.h" 

class SynthButton {
    public:
        SynthButton(byte pButton, bool internalPullup = true){
            pin_button = pButton;
            pinMode(pButton, internalPullup? INPUT_PULLUP : INPUT);
        }

        int readButton() {
            int reading = digitalRead(pin_button);
    
            // If the switch changed, due to noise or pressing:
            if (reading != lastButtonState) {
                // reset the debouncing timer
                lastDebounceTime = millis();
            }

            if ((millis() - lastDebounceTime) > debounceDelay) {
                // whatever the reading is at, it's been there for longer than the debounce
                // delay, so take it as the actual current state:

                // if the button state has changed:
                if (reading != buttonState) {
                    buttonState = reading;

                    // if we just started pressing trigger a counter
                    if (buttonState == LOW) {
                        if(!isPressed) {
                        isPressed = true;
                        pressLength = millis();
                        }
                    }
                    else if (buttonState == HIGH) { 
                        //When we let go check how much time has passed
                        if(isPressed) {
                            isPressed = false;
                            lastButtonState = reading;
                            
                            if(millis() - pressLength >= long_press_milliseconds) {
                                return 2; //Long press
                            } else {
                                return 1; //Normal press
                            }

                            return 0; //Not Pressed
                        }
                    }
                }
            }

            // save the reading. Next time through the loop, it'll be the lastButtonState:
            lastButtonState = reading;

            return 0;
        }

        bool pressed() {
            return isPressed;
        }

        void setLongPressTime(uint16_t newTime) {
            long_press_milliseconds = newTime;
        }

    private:
        byte pin_button = 0; // Button pin
        uint16_t long_press_milliseconds = 500; //MS for a long press

        //button debouncing
        int buttonState;            // the current reading from the input pin
        int lastButtonState = HIGH;  // the previous reading from the input pin
        unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
        unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

        //long button presses
        bool isPressed = false;
        unsigned long pressLength = 0;
};

#endif