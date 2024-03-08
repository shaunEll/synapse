#include "SynthSeq.h"

SynthSeq::SynthSeq() {
    updateBpm(INIT_BPM);
    trigger.stop();

    loadDemo();
}

SynthSeq::SynthSeq(int bpm) {
    updateBpm(bpm);
    trigger.stop();

    loadDemo();
}

//UPDATE SEQUENCER SETTINGS
void SynthSeq::updateBpm(int bpm) {
    if (bpm >= BPM_MIN && bpm <= BPM_MAX) {
        BPM = bpm;
    }

    trigger.setBPM(bpm * STEPS_PER_BEAT);

    if(playing) {
        trigger.start();
    }
}

void SynthSeq::setSequenceSteps(int newLength) {
    if(newLength > 0 && newLength <= MAX_STEPS) {
        sequenceLength = newLength;
    }
}
//END UPDATE SEQUENCER SETTINGS

//SEQUENCER INFORMATION
int SynthSeq::getBpm() {
    return (int)BPM;
}

int SynthSeq::getMaxBpm() {
    return BPM_MAX;
}

int SynthSeq::getMinBpm() {
    return BPM_MIN;
}

int SynthSeq::getSequenceSteps() {
    return sequenceLength;
}

int SynthSeq::getMaxSteps() {
    return MAX_STEPS;
}

int SynthSeq::getCurrentStep() {
    return currentStep;
}

byte SynthSeq::getNoteForStep(byte step) {
    return steps[step].ready() ? steps[step].getNote() : 255;
}

byte SynthSeq::getLengthForStep(byte step) {
    return steps[step].ready() ? steps[step].getLength() : 0;
}

byte SynthSeq::getVelocityForStep(byte step) {
    return steps[step].ready() ? steps[step].getVelocity() : 0;
}

byte SynthSeq::getBaseNote() {
    return BASE_MIDI_NOTE;
}
//END SEQUENCER INFORMATION

//PLAYBACK CONTROL
bool SynthSeq::isPlaying() {
    return playing;
}

bool SynthSeq::isReady() {
    return trigger.ready();
}

void SynthSeq::start() {
    playing = true;
    trigger.start();
}

void SynthSeq::pause() {
    stop(true);
}

void SynthSeq::stop(bool pause) {
    playing = false;
    trigger.stop();

    if(!pause) {
        currentStep = 0;
        currentEvent = -1;
    }
}

void SynthSeq::restart() {
    stop();
    start();
}
//END PLAYBACK CONTROL

//MANAGING EVENTS
void SynthSeq::addEvent(byte stepNumber, SYNTH_SEQ_MIDI_EVENT eventType, byte newNote, byte velocity, byte length, byte channel) {
    steps[stepNumber].configureEvent(eventType, newNote, velocity, length, channel);
}

void SynthSeq::addEvent(byte stepNumber, SYNTH_SEQ_MIDI_EVENT eventType, byte newNote, byte velocity, byte length) {
    addEvent(stepNumber, SYNTH_SEQ_MIDI_EVENT::NOTEON, newNote, velocity, length, DEFAULT_MIDI_CHANNEL);
}

void SynthSeq::addNoteOnEvent(byte stepNumber, byte newNote, byte velocity, byte length) {
    addEvent(stepNumber, SYNTH_SEQ_MIDI_EVENT::NOTEON, newNote, velocity, length);
}

void SynthSeq::addNoteOnEvent(byte stepNumber, byte newNote, byte velocity) {
    addNoteOnEvent(stepNumber, newNote, velocity, DEFAULT_NOTE_LENGTH);
}

void SynthSeq::addNoteOnEvent(byte stepNumber, byte newNote) {
    addNoteOnEvent(stepNumber, newNote, DEFAULT_VELOCITY, DEFAULT_NOTE_LENGTH);
}

void SynthSeq::removeEvent(byte stepNumber) {
    steps[stepNumber].removeEvent();
}

void SynthSeq::editEvent(byte stepNumber, byte newNote) {
    editEvent(stepNumber, newNote, steps[stepNumber].getVelocity(), steps[stepNumber].getLength());
}

void SynthSeq::editEvent(byte stepNumber, byte newNote, byte length)  {
    editEvent(stepNumber, newNote, steps[stepNumber].getVelocity(), length);
}

void SynthSeq::editEvent(byte stepNumber, byte newNote, byte velocity, byte length) {
    switch(steps[stepNumber].getEventType()) {
        case SYNTH_SEQ_MIDI_EVENT::NOTEON:
            addNoteOnEvent(stepNumber, newNote, velocity, length);

            for(int x = stepNumber+1; x < (stepNumber+length); x++) {
                if(steps[x].ready()) {
                    steps[x].removeEvent();
                }
            }

            break;
          
          default:
            break;
    }
}
//END MANAGING EVENTS

//PROCESSING
SynthSeqMidiMessage * SynthSeq::process() {
    SynthSeqMidiMessage * message = NULL;

    if(playing) {
            if(DEBUG_ON) {
                Serial.print("PROCESSING STEP: ");
                Serial.println(currentStep);
            }

            if(currentEvent >= 0 && steps[currentEvent].running()) {
                message = steps[currentEvent].process(currentStep);
            }

            if(steps[currentStep].ready() && !steps[currentStep].running()){
                message = steps[currentStep].triggerEvent(currentStep);
                currentEvent = currentStep;
            }

            //MOVE THE SEQUENCE ALONG                 
            currentStep++;

            if(currentStep >= sequenceLength){
                currentStep = 0;
            }
    }

    if(DEBUG_ON) {
        if(message == NULL) {
            Serial.println("NO MESSAGE");
        } else {
            Serial.println(message->toString());
        }
    }

    return message;
}
//END PROCESSING

void SynthSeq::loadDemo() {
    steps[0].configureEvent(SYNTH_SEQ_MIDI_EVENT::NOTEON, 60, 100, 1);
    steps[4].configureEvent(SYNTH_SEQ_MIDI_EVENT::NOTEON, 60, 50, 1);
    steps[8].configureEvent(SYNTH_SEQ_MIDI_EVENT::NOTEON, 60, 100, 1);
    steps[12].configureEvent(SYNTH_SEQ_MIDI_EVENT::NOTEON, 68, 100, 1);
    steps[14].configureEvent(SYNTH_SEQ_MIDI_EVENT::NOTEON, 62, 50, 1);
}