#ifndef SynthSeqMidiMessage_h
#define SynthSeqMidiMessage_h

#include "Arduino.h"

#define DEFAULT_VELOCITY 100
#define DEFAULT_MIDI_CHANNEL 1


enum SYNTH_SEQ_MIDI_EVENT {
    NOTEON = 1001,
    NOTEOFF = 1000,
    CONTROLCHANGE = 1011,
    PROGRAMCHANGE = 1100,
    NOMESSAGE
};

class SynthSeqMidiMessage {
    private:
        SYNTH_SEQ_MIDI_EVENT midiEventType = SYNTH_SEQ_MIDI_EVENT::NOMESSAGE;

        byte noteOrNumber = 0;
        byte valueOrVelocity = DEFAULT_VELOCITY;
        byte channel = DEFAULT_MIDI_CHANNEL;
        
    public:
        SynthSeqMidiMessage() {

        }

        SynthSeqMidiMessage(SYNTH_SEQ_MIDI_EVENT eventType, byte number, byte value, byte ch) {
            midiEventType = eventType;
            noteOrNumber = number;
            valueOrVelocity = value;
            channel = ch;
        }

        SYNTH_SEQ_MIDI_EVENT getEventType() {
            return midiEventType;
        }

        byte getN() {
            return noteOrNumber;
        }

        byte getV() {
            return valueOrVelocity;
        }

        byte getC() {
            return channel;
        }

        String toString() {
            return eventTypeToString() + "," + String(noteOrNumber) + "," + String(valueOrVelocity) + "," + String(channel);
        }

        String eventTypeToString() {
            switch(midiEventType) {
                case SYNTH_SEQ_MIDI_EVENT::NOTEON:
                    return "NOTE_ON";
                case SYNTH_SEQ_MIDI_EVENT::NOTEOFF:
                    return "NOTE_OFF";
                case SYNTH_SEQ_MIDI_EVENT::CONTROLCHANGE:
                    return "CC";
                case SYNTH_SEQ_MIDI_EVENT::PROGRAMCHANGE:
                    return "PC";
                default:
                    return "NOMESSAGE";
            }
        }
};

#endif