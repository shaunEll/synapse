#ifndef SynthUISequencer_h
#define SynthUISequencer_h

#include "SynthCore.h"
#include "SynthSeq.h"
#include "SynthUI.h"
#include "SynthUITheme.h"
#include "SynthUICustomScreen.h"

#define SEQ_LEFT_MARGIN 15
#define SEQ_NOTE_RANGE 12
#define SEQ_NOTE_MARGIN 2
#define SEQ_BAR_WIDTH 2
#define SEQ_NOTES_IN_SCALE 12
#define SEQ_NOTES_LOWEST 20
#define SEQ_NOTES_HIGHEST 127
#define SEQ_BASE_MIDI_NOTE 24
#define SEQ_DEFAULT_OCTAVE 4
#define SEQ_MAX_OCTAVE 10
#define SEQ_MIN_OCTAVE 1
#define SEQ_MIN_VELOCITY 0
#define SEQ_MAX_VELOCITY 127
#define SEQ_DEFAULT_VELOCITY 100

#define SEQ_POPUP_WIDTH 100
#define SEQ_POPUP_HEIGHT 50

#define DEBUG_UI false

enum SEQ_INTERNAL_STATE {
    SEQUENCER,
    OCTAVESELECT,
    BPMSELECT,
    PATTERNLENGTH
};

class SynthUISequencer : public SynthUICustomScreen {
    public:
        SynthUISequencer() : SynthUICustomScreen(240, 320, 5, 3, NULL, NULL){
            octave = SEQ_DEFAULT_OCTAVE;
            state = SEQ_INTERNAL_STATE::SEQUENCER;
        }

        SynthUISequencer(int tHeight, int tWidth, byte topHeight, byte margins, SynthUITheme * newTheme, TFT_eSprite * sSprite, SynthSeq * nSeq) : SynthUICustomScreen(tHeight, tWidth, topHeight, margins, newTheme, sSprite) {
            octave = SEQ_DEFAULT_OCTAVE;
            state = SEQ_INTERNAL_STATE::SEQUENCER;
            seqSprite = sSprite;
            seq = nSeq;
            seqPopup = SynthUIPopup(seqSprite, newTheme, "Velocity", SEQ_DEFAULT_VELOCITY, 
                                    tWidth / 2 - SEQ_POPUP_WIDTH / 2, tHeight / 2 - SEQ_POPUP_HEIGHT / 2, SEQ_POPUP_WIDTH, SEQ_POPUP_HEIGHT);
        }

        void generateScreen(byte selectedP) override {
            byte octaveFirstNote = ((octave - 1) * SEQ_NOTES_IN_SCALE) + SEQ_BASE_MIDI_NOTE;
            numParameters = seq->getSequenceSteps();

            if(DEBUG_UI) {
                Serial.println("GENERATING SEQ SCREEN");
                Serial.print("# Steps: ");
                Serial.print(numParameters);
                Serial.print(", Selected Step: ");
                Serial.println(selectedP + 1);
                Serial.print("seqSprite is: ");
                Serial.println((seqSprite == NULL) ? "NULL" : "NOT NULL");
            }

            byte fromTop = pageMargins + topBarHeight;
            byte fromBottom = pageMargins;
            byte fromLeft = SEQ_LEFT_MARGIN + pageMargins;
            byte fromRight = pageMargins;

            int vGap = (tftWidth - fromLeft - fromRight) / numParameters;
            int hGap = (tftHeight - fromBottom - fromTop) / SEQ_NOTE_RANGE;

            //Coloured lines & Notes
            seqSprite->setTextColor(theme->THEME_SEQ_NOTES_TEXT);
            seqSprite->setTextSize(1); // Font size scaling is x1

            for(byte y = 0; y < SEQ_NOTE_RANGE; y++) {
                seqSprite->fillRect(fromLeft, fromTop + (y * hGap), (vGap * numParameters), vGap, (y%2)? theme->THEME_SEQ_DARKROW : theme->THEME_SEQ_LIGHTROW);

                seqSprite->setCursor(1,fromTop + (y * hGap) + pageMargins);
                seqSprite->print(noteScale[SEQ_NOTES_IN_SCALE - ((SEQ_NOTES_IN_SCALE + y)%SEQ_NOTES_IN_SCALE) - 1] + String(octave));
            }

            seqSprite->setTextColor(theme->THEME_TEXT);

            //CURRENTLY SELECTED STEP
            seqSprite->fillRect(fromLeft + (selectedP * vGap), fromTop, vGap, hGap * SEQ_NOTE_RANGE , theme->THEME_SEQ_HIGHLIGHT_STEP);

            //VERTICAL Dividers
            for(byte x = 0; x < numParameters; x++) {
                if(x == 0 ) {
                    seqSprite->drawFastVLine(fromLeft + (x * vGap), fromTop, hGap * SEQ_NOTE_RANGE, theme->THEME_SEQ_BORDER);
                } else {
                    seqSprite->drawFastVLine(fromLeft + (x * vGap), fromTop, hGap * SEQ_NOTE_RANGE, theme->THEME_SEQ_VERTICAL_DIVIDER);
                }
            }
            seqSprite->drawFastVLine(fromLeft + (numParameters * vGap), fromTop, hGap * SEQ_NOTE_RANGE, theme->THEME_SEQ_BORDER);

            //Beat lines
            for(byte x = 0; x < numParameters; x += 4) {
                seqSprite->fillRect(fromLeft + (x * vGap) - 1, fromTop, SEQ_BAR_WIDTH, hGap * SEQ_NOTE_RANGE, theme->THEME_SEQ_QUARTERBAR);
            }

            //HORIZONTAL Dividers
            for(byte y = 0; y < SEQ_NOTE_RANGE + 1; y++) {
                seqSprite->drawFastHLine(pageMargins, fromTop + (y * hGap), (vGap * (numParameters + 1) - 2), theme->THEME_SEQ_HORIZONTAL_DIVIDER);
            }

            // DRAW NOTES
            for(int x = 0; x < numParameters; x++) {
                int note = seq->getNoteForStep(x);
                byte length = seq->getLengthForStep(x);

                if(DEBUG_UI) {
                    Serial.print("Note at step ");
                    Serial.print(x);
                    Serial.print(": ");
                    Serial.println(note);
                }

                if(note >= octaveFirstNote && note < (octaveFirstNote + SEQ_NOTES_IN_SCALE)) {
                    seqSprite->fillRect((fromLeft + x * vGap) + SEQ_NOTE_MARGIN, 
                                    fromTop + ((SEQ_NOTE_RANGE - 1 - (note % 12)) * hGap) + SEQ_NOTE_MARGIN, 
                                    (vGap * length) - (SEQ_NOTE_MARGIN), 
                                    hGap - (SEQ_NOTE_MARGIN * 2), 
                                    theme->THEME_SEQ_NOTE);
                }
            }

            switch(state) {
                case SEQ_INTERNAL_STATE::OCTAVESELECT:
                    seqPopup.show("Octave", octave);
                    break;
                
                case SEQ_INTERNAL_STATE::BPMSELECT:
                    seqPopup.show("BPM", seq->getBpm());
                    break;

                case SEQ_INTERNAL_STATE::PATTERNLENGTH:
                    seqPopup.show("Steps", seq->getSequenceSteps());
                    break;
                default:
                  break;
            }

            //show popup
            seqPopup.display();
        }

        void increaseMenu(byte selectedP) override {
            byte sVel = seq->getVelocityForStep(selectedP);

            if(sVel < SEQ_MAX_VELOCITY - 1 && seq->getNoteForStep(selectedP != 255)) {
                seq->editEvent(selectedP, seq->getNoteForStep(selectedP), sVel + 1, seq->getLengthForStep(selectedP));
            }

            seqPopup.show("Velocity", sVel + 1);
        }

        void decreaseMenu(byte selectedP) override {
            byte sVel = seq->getVelocityForStep(selectedP);

            if(sVel > SEQ_MIN_VELOCITY + 1 && seq->getNoteForStep(selectedP != 255)) {
                seq->editEvent(selectedP, seq->getNoteForStep(selectedP), sVel - 1, seq->getLengthForStep(selectedP));
            }

            seqPopup.show("Velocity", sVel - 1);
        }

        void increaseParameter(byte selectedP, bool shiftisPressed = false) override {
            byte noteForStp = seq->getNoteForStep(selectedP);

            if(!shiftisPressed) {
                switch(state) {
                    case SEQ_INTERNAL_STATE::SEQUENCER:
                        if(noteForStp < 127) {
                            seq->editEvent(selectedP, noteForStp + 1, seq->getVelocityForStep(selectedP), seq->getLengthForStep(selectedP));
                        }

                        if(noteForStp == 255) {
                            seq->addNoteOnEvent(selectedP, ((octave - 1) * SEQ_NOTES_IN_SCALE) + SEQ_BASE_MIDI_NOTE, SEQ_DEFAULT_VELOCITY);
                        }
                        break;
                    
                    case SEQ_INTERNAL_STATE::OCTAVESELECT:
                        if (octave < SEQ_MAX_OCTAVE) {
                            octave++;
                        }
                        break;
                    
                    case SEQ_INTERNAL_STATE::BPMSELECT:
                        if (seq->getBpm() < seq->getMaxBpm()) {
                            seq->updateBpm(seq->getBpm() + 1);
                        }
                        break;

                    case SEQ_INTERNAL_STATE::PATTERNLENGTH:
                        if(seq->getSequenceSteps() * 2 <= seq->getMaxSteps()) {
                            seq->setSequenceSteps(seq->getSequenceSteps() * 2);

                        }
                        break;

                    default:
                        break;
                }
            } else {
                //INCREASE CURRENT NOTE LENGTH (CREATE IT IF IT DOESN'T EXIST) AND DELETE ANY CLASHING ONES
                seq->editEvent(selectedP, noteForStp, seq->getLengthForStep(selectedP) + 1);
            }
        }

        void decreaseParameter(byte selectedP, bool shiftisPressed = false) override {
            byte noteForStp = seq->getNoteForStep(selectedP);

            if(!shiftisPressed) {

                switch(state) {
                    case SEQ_INTERNAL_STATE::SEQUENCER:                    
                        if(noteForStp > SEQ_NOTES_LOWEST) {
                            seq->editEvent(selectedP, noteForStp - 1, seq->getVelocityForStep(selectedP), seq->getLengthForStep(selectedP));;
                        }

                        if(noteForStp == 255) {
                            seq->addNoteOnEvent(selectedP, ((octave - 1) * SEQ_NOTES_IN_SCALE) + SEQ_BASE_MIDI_NOTE, SEQ_DEFAULT_VELOCITY);
                        }

                        break;
                    
                    case SEQ_INTERNAL_STATE::OCTAVESELECT:
                        if (octave > SEQ_MIN_OCTAVE) {
                            octave--;
                        }

                        break;
                    
                    case SEQ_INTERNAL_STATE::BPMSELECT:
                        if (seq->getBpm() > seq->getMinBpm()) {
                            seq->updateBpm(seq->getBpm() - 1);
                        }

                        break;

                    case SEQ_INTERNAL_STATE::PATTERNLENGTH:
                        seq->setSequenceSteps(seq->getSequenceSteps() / 2);
                        break;

                    default:
                        break;
                }
            } else {
                //DECREASE CURRENT NOTE LENGTH (CREATE IT IF IT DOESN'T EXIST) AND DELETE ANY CLASHING ONES
                if(seq->getLengthForStep(selectedP) - 1 > 0){
                    seq->editEvent(selectedP, noteForStp, seq->getLengthForStep(selectedP) - 1);
                }
            }
            
        }

        void pressMultiButton(byte selectedP, bool shiftisPressed = false) override {
            if(!shiftisPressed) {
                switch (state)
                {
                    case SEQ_INTERNAL_STATE::SEQUENCER:
                        state = SEQ_INTERNAL_STATE::OCTAVESELECT;
                        break;
                    
                    case SEQ_INTERNAL_STATE::OCTAVESELECT:
                        state = SEQ_INTERNAL_STATE::PATTERNLENGTH;
                        break;

                    case SEQ_INTERNAL_STATE::PATTERNLENGTH:
                        state = SEQ_INTERNAL_STATE::BPMSELECT;
                        break;

                    case SEQ_INTERNAL_STATE::BPMSELECT:
                        state = SEQ_INTERNAL_STATE::SEQUENCER;
                        break;

                    default:
                        break;
                }
            } else {
                //DELETE HIGHLIGHTED NOTE
                seq->removeEvent(selectedP);
            }
        }
    
    private:
        String noteScale[SEQ_NOTES_IN_SCALE] = {"C","C#","D","D#","E","F","F#","G","G#","A","A#","B"}; 
        byte octave = 4;
        byte midiChannel = 1;

        SEQ_INTERNAL_STATE state = SEQ_INTERNAL_STATE::SEQUENCER;

        SynthSeq * seq;
        SynthUIPopup seqPopup;
};

#endif