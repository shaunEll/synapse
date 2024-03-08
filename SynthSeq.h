#ifndef SynthSeq_h
#define SynthSeq_h

#include "Arduino.h" 
#include <MozziGuts.h>
#include <Metronome.h>
#include "SynthSeqEvent.h"

#define DEBUG_ON false

//BPM Settings
#define INIT_BPM 128
#define BPM_MIN 20
#define BPM_MAX 300

#define MAX_STEPS 64
#define DEFAULT_STEPS 16
#define STEPS_PER_BEAT 4

#define BASE_MIDI_NOTE 60 //MIDDLE C
#define MAX_MIDI_NOTE 127
#define DEFAULT_MIDI_CHANNEL 1

#define DEFAULT_VELOCITY 100
#define DEFAULT_NOTE_LENGTH 1

class SynthSeq {
    //The proccessing trigger
    Metronome trigger;

    //State variables
    float BPM;
    bool playing = false;

    byte targetMidiChannel = DEFAULT_MIDI_CHANNEL;
    int currentStep = 0;
    int currentEvent = -1;
    int sequenceLength = DEFAULT_STEPS;

    //The actual step events
    SynthSeqEvent steps[MAX_STEPS];

    public:
        SynthSeq();
        SynthSeq(int bpm);

        //UPDATE SEQUENCER SETTINGS
        void updateBpm(int bpm);
        void setSequenceSteps(int newLength);
        //END UPDATE SEQUENCER SETTINGS

        //SEQUENCER INFORMATION
        int getBpm();
        int getMaxBpm();
        int getMinBpm();
        int getSequenceSteps();
        int getMaxSteps();
        int getCurrentStep();
        byte getNoteForStep(byte step);
        byte getLengthForStep(byte step);
        byte getVelocityForStep(byte step);
        byte getBaseNote();
        //END SEQUENCER INFORMATION

        //PLAYBACK CONTROL
        bool isPlaying();
        bool isReady();
        void start();
        void pause();
        void stop(bool pause = false);
        void restart();
        //END PLAYBACK CONTROL

        //MANAGING EVENTS
        void addEvent(byte stepNumber, SYNTH_SEQ_MIDI_EVENT eventType, byte newNote, byte velocity, byte length, byte channel);
        void addEvent(byte stepNumber, SYNTH_SEQ_MIDI_EVENT eventType, byte newNote, byte velocity, byte length);
        void addNoteOnEvent(byte stepNumber, byte newNote, byte velocity, byte length);
        void addNoteOnEvent(byte stepNumber, byte newNote, byte velocity);
        void addNoteOnEvent(byte stepNumber, byte newNote);
        void removeEvent(byte stepNumber);
        void editEvent(byte stepNumber, byte newNote);
        void editEvent(byte stepNumber, byte newNote, byte length);
        void editEvent(byte stepNumber, byte newNote, byte velocity, byte length);
        //END MANAGING EVENTS

        //PROCESSING
        SynthSeqMidiMessage * process();
        //END PROCESSING

        void loadDemo();    
};

#endif