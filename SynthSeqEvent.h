#ifndef SynthSeqEvent_h
#define SynthSeqEvent_h

#include "Arduino.h" 
#include "SynthSeqMidiMessage.h"

#define DEFAULT_NOTE_LENGTH 1

class SynthSeqEvent {
    private:
        SYNTH_SEQ_MIDI_EVENT eventType;

        SynthSeqMidiMessage onMessage = SynthSeqMidiMessage(SYNTH_SEQ_MIDI_EVENT::NOMESSAGE,0,0,0);
        SynthSeqMidiMessage offMessage = SynthSeqMidiMessage(SYNTH_SEQ_MIDI_EVENT::NOMESSAGE,0,0,0);;

        int lengthInSteps = 1;
        int accumulatedSteps = 0;

        bool isRunning = false;
        bool isConfigured = false;

    public:
        SynthSeqEvent();
        
        void configureEvent(SYNTH_SEQ_MIDI_EVENT eType, byte number, byte value);
        void configureEvent(SYNTH_SEQ_MIDI_EVENT eType, byte number, byte value, int length);
        void configureEvent(SYNTH_SEQ_MIDI_EVENT eType, byte number, byte value, int length, byte channel);
        void removeEvent();

        SynthSeqMidiMessage * triggerEvent(int stepNumber);
        SynthSeqMidiMessage * process(int stepNumber);

        bool running();
        bool ready();
        byte getNote();
        byte getVelocity();
        int getLength();
        SYNTH_SEQ_MIDI_EVENT getEventType();
};

#endif