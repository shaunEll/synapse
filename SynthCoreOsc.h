#ifndef SynthCoreOsc_h
#define SynthCoreOsc_h

#include <MozziGuts.h>
#include <mozzi_midi.h>
#include <Oscil.h>

//Oscillator shapes
#include <tables/sin2048_int8.h> // OSC_SINE table for lfo
#include <tables/sin8192_int8.h> // OSC_SINE table for oscillator
#include <tables/saw8192_int8.h> // OSC_SAW table for oscillator
#include <tables/triangle_warm8192_int8.h> // OSC_TRIANGLE table for oscillator
#include <tables/smoothsquare8192_int8.h> // OSC_SQUARE table for oscillator
#include <tables/whitenoise8192_int8.h>
#include <tables/chum78_int8.h>
#include <tables/square_no_alias_2048_int8.h>
#include <tables/triangle_dist_cubed_2048_int8.h>

//SYNTH DEPENDENCIES
#include "SynthCoreObject.h"

#define OSC_DEFAULT_VELOCITY 100
#define OSC_NUM_WAVEFORMS 8
#define OSC_START_POSITION 0
#define OSC_BASE_MIDI_NOTE 60 //MIDDLE C
#define OSC_INIT_VOLUME 1
#define OSC_MAX_VOLUME 200
#define OSC_NUM_PARAMS 6

class SynthCoreOsc : public SynthCoreObject, public UpdatableParameterObject {
  protected:
    Oscil <SIN8192_NUM_CELLS, AUDIO_RATE> voice;
    SYNTH_P oscillatorShape;
    
    bool isEnabled = true;

    byte volumeLevel = OSC_INIT_VOLUME;
    int tuning = 0; //In semitones
    int detune = 0; //In hertz
    float phase = 0;
    byte velocity = OSC_DEFAULT_VELOCITY;

    uint8_t currentNote;

    public:
        SynthCoreOsc(String nName, int nId);
        void init() override;

        void processParameterUpdate(byte parameterID) override;
        int process();

        void toggleEnabled();
        void setEnabled(bool newState = true);
        bool enabled();

        //OSC SHAPE
        void setOscillatorShape();
        void setOscillatorShape(SYNTH_P oscType);
        SYNTH_P getOscillatorShape();

        //VOLUMES
        void setInitVolumeLevel();
        bool setVolume(byte newVolume);
        byte getVolume();
        byte getDefaultVelocity();

        //NOTES/FREQUENCY
        void setNote(int midiNote, byte newVelocity);
        void setNote(int midiNote);
        void setCurrentNote();
        void playNote(int midiNote);

        void setTuning(int newTuning);
        int getTuning();
        void setDetune(int newDetune);
        int getDetune();
        void setPhase(int newPhase);
        float getPhase();

        void copyObject(SynthCoreObject * obj) override;   
};

#endif