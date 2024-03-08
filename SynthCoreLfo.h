#ifndef SynthCoreLfo_h
#define SynthCoreLfo_h
#include "Arduino.h" 
#include <MozziGuts.h>
#include <mozzi_midi.h>
#include <Oscil.h>

//Oscillator shapes
#include <tables/sin2048_int8.h> // LFO_SINE table for lfo
#include <tables/sin8192_int8.h> // LFO_SINE table for oscillator
#include <tables/saw8192_int8.h> // LFO_SAW table for oscillator
#include <tables/triangle_warm8192_int8.h> // LFO_TRIANGLE table for oscillator
#include <tables/smoothsquare8192_int8.h> // LFO_SQUARE table for oscillator
#include <tables/whitenoise8192_int8.h>


//DEPENDENCIES
#include "SynthCoreObject.h"
#include "SynthModifierObject.h"

#define LFO_NUM_PARAMS 2
#define LFO_WAVEFORMS 5
#define LFO_START_POSITION 11

#define DEFAULT_LFO_FREQUENCY 0.5f

class SynthCoreLFO : public SynthCoreObject, public SynthModifierObject, public UpdatableParameterObject {
    Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> lfo;
    float lfoFrequency;

    SYNTH_P lfoShape;

    float lfoValue;

    public:
      SynthCoreLFO(String nName, int nId);

      void init() override;
      void processParameterUpdate(byte parameterID) override;

      void setLFOShape(SYNTH_P lfoType);
      float process();
      void restartLFO();
      void updateFrequency();

        //MODIFIER
      int getModifierValueInt() override;
      float getModifierValueFloat() override;
      byte getModifierValueByte() override;
      bool getModifierValueBool() override;

      void copyObject(SynthCoreObject * obj) override; 
};

#endif