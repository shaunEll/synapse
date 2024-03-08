#ifndef SynthCore_h
#define SynthCore_h

#include "Arduino.h"
#include <MozziGuts.h>


//SYNTH DEPENDENCIES
#include "SynthCoreObject.h"
#include "SynthModifierObject.h"
#include "SynthCoreOsc.h"
#include "SynthCoreEnvelope.h"
#include "SynthCoreFilter.h"
#include "SynthCoreLFO.h"
#include "SynthSeqMidiMessage.h"

#define MOZZI_CONTROL_RATE 256 // Hz, powers of 2 are most reliable

#define MAX_MODULES 10
#define MAX_MODULES_TYPE 3

//VOLUME DEFINES
#define MAX_VOLUME 200
#define INIT_VOLUME 10

#define DEFAULT_MIDI_CHANNEL 1
#define MAX_MIDI_CHANNEL 16

class SynthCore {
  SynthCoreEnvelope * envelopes[MAX_MODULES_TYPE];
  SynthCoreOsc * oscillators[MAX_MODULES_TYPE];
  SynthCoreFilter * filters[MAX_MODULES_TYPE];
  SynthCoreLFO * lfos[MAX_MODULES_TYPE];

  int numOscillators, numFilters, numEnvelopes, numLfos, numModules;

  protected:
    SynthCoreObject * modules[MAX_MODULES];

  public:
    SynthCore();

    int getVolume();
    int getMaxVolume();
    void setVolume(int nVolume);

    void addModule(SYNTH_MODULE_TYPE);
    void removeModule(int moduleId);
    SynthCoreObject * getModule(int moduleId);
    void copyModule(int targetModuleId, SynthCoreObject * clipboard);

    SynthCoreObject * getModules();
    int getNumModules();
    
    SynthModifierObject * getModfierObjects();
    int getNumModifiers();
    
};

#endif