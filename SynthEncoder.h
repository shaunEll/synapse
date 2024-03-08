#ifndef SynthEncoder_h
#define SynthEncoder_h
#include "Arduino.h" 

class SynthEncoder {
    public:
        SynthEncoder(byte pButton, byte pLeft, byte pRight) {
            pin_button = pButton;
            pin_left = pLeft;
            pin_right = pRight;

            pinMode(pLeft,INPUT);
            pinMode(pRight,INPUT);

           lastStateCLK  = digitalRead(pLeft);
            
            //encoder button is pullup
            pinMode(pButton, INPUT_PULLUP);
        }

        int ReadEncoder() {
            currentStateCLK = digitalRead(pin_right);

            if (currentStateCLK != lastStateCLK  && currentStateCLK == 0){
                if((millis() - EncoderLastDebounceTime) > EncoderDebounceDelay){
                    // If the DT state is different than the CLK state then
                    // the encoder is rotating CCW so decrement
                    EncoderLastDebounceTime = millis();
                    
                    if (digitalRead(pin_left) != currentStateCLK) { //Turn left
                        return -1;
                    } else { //Turn right
                        return 1;
                    }	
                }
            }

            return 0;
        }

        int ReadButton() {
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
        
        void setLongPressTime(uint16_t newTime) {
            long_press_milliseconds = newTime;
        }

    private:
        byte pin_button = 0; // Rotary Encoder Button
        byte pin_left = 0; 
        byte pin_right = 0;
        uint16_t long_press_milliseconds = 500; //MS for a long press

        byte currentStateCLK = 0;
        int lastStateCLK = 0;

        //encoder debouncing
        unsigned long EncoderLastDebounceTime = 0;  // the last time the output pin was toggled
        unsigned long EncoderDebounceDelay = 10;    // the debounce time; increase if the output flickers

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