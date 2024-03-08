#ifndef SynthModifierObject_h
#define SynthModifierObject_h

#include "Arduino.h"

class SynthModifierObject {
    String modifierName;

    public:
      SynthModifierObject(String nName) {
        modifierName = nName;
      }

      String getModifierName() {
        return modifierName;
      }

      virtual int getModifierValueInt() {
        return 0;
      };

      virtual float getModifierValueFloat() {
        return 0;
      };

      virtual byte getModifierValueByte() {
        return 0;
      };

      virtual bool getModifierValueBool() {
        return false;
      };
};

#endif