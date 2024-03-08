#include "SynthSeqEvent.h"

SynthSeqEvent::SynthSeqEvent() {
    isConfigured = false;
}

void SynthSeqEvent::configureEvent(SYNTH_SEQ_MIDI_EVENT eType, byte number, byte value) {
    configureEvent(eType, number, value, DEFAULT_NOTE_LENGTH, DEFAULT_MIDI_CHANNEL);
}

void SynthSeqEvent::configureEvent(SYNTH_SEQ_MIDI_EVENT eType, byte number, byte value, int length) {
    configureEvent(eType, number, value, length, DEFAULT_MIDI_CHANNEL);
}

void SynthSeqEvent::configureEvent(SYNTH_SEQ_MIDI_EVENT eType, byte number, byte value, int length, byte channel) {
    onMessage = SynthSeqMidiMessage(eType, number, value, channel);

    eventType = eType;
    lengthInSteps = length;
    accumulatedSteps = 0;

    switch(eventType) {
        case SYNTH_SEQ_MIDI_EVENT::NOTEON:
            offMessage = SynthSeqMidiMessage(SYNTH_SEQ_MIDI_EVENT::NOTEOFF,number,value,channel);
            break;
        default:
            offMessage = SynthSeqMidiMessage(SYNTH_SEQ_MIDI_EVENT::NOMESSAGE,0,0,0);
            break;
    } 

    isConfigured = true; 
}

SynthSeqMidiMessage * SynthSeqEvent::triggerEvent(int stepNumber) {
    accumulatedSteps = 0;
    isRunning = true;
    return &onMessage;
}

void SynthSeqEvent::removeEvent() {
    accumulatedSteps = 0;
    isConfigured = false;
    isRunning = false;
}

SynthSeqMidiMessage * SynthSeqEvent::process(int stepNumber) {
    if(isRunning){
        accumulatedSteps ++;

        if(accumulatedSteps >= lengthInSteps) {
            isRunning = false;
            accumulatedSteps = 0;
            return &offMessage;
        }
    }

    return NULL;                
}

bool SynthSeqEvent::running() {
    return isRunning;
}

bool SynthSeqEvent::ready() {
    return isConfigured;
}

byte SynthSeqEvent::getNote() {
    if(onMessage.getEventType() == SYNTH_SEQ_MIDI_EVENT::NOTEON || onMessage.getEventType() == SYNTH_SEQ_MIDI_EVENT::NOTEOFF) {
        return onMessage.getN();
    } else {
        return 0;
    }
}

byte SynthSeqEvent::getVelocity() {
    if(onMessage.getEventType() == SYNTH_SEQ_MIDI_EVENT::NOTEON || onMessage.getEventType() == SYNTH_SEQ_MIDI_EVENT::NOTEOFF) {
        return onMessage.getV();
    } else {
        return 0;
    }
}

int SynthSeqEvent::getLength() {
    return lengthInSteps;
}

SYNTH_SEQ_MIDI_EVENT SynthSeqEvent::getEventType() {
    return eventType;
}
