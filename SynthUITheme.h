#ifndef SynthUITheme_h
#define SynthUITheme_h

#include "Arduino.h"

#define NUM_THEMES 1

class SynthUITheme {
    public:
        uint32_t THEME_BACKGROUND = 0x7BEF;
        uint32_t THEME_BACKGROUD_TOP_BAR = 0x7BEF;

        uint32_t THEME_TEXT = 0xFFFF;
        uint32_t THEME_TEXT_SELECTED = 0xFEA0;
        uint32_t THEME_TEXT_TOP_BAR = 0xFFFF;

        uint32_t THEME_BOX_OUTLINE = 0xFFFF;
        uint32_t THEME_BOX_HIGHLIGHT = 0xFFFF;

        uint32_t THEME_ENVELOPE_LINE = 0xFEA0;

        //SEQUENCER
        uint32_t THEME_SEQ_DARKROW = 0xEF7D;
        uint32_t THEME_SEQ_LIGHTROW = 0xCE79;
        uint32_t THEME_SEQ_NOTE = 0xFEA0;
        uint32_t THEME_SEQ_HIGHLIGHT_STEP = 0x07FF;
        uint32_t THEME_SEQ_PLAYING_NOTE = 0xF800;
        uint32_t THEME_SEQ_NOTES_TEXT = 0xFFFF;

        uint32_t THEME_SEQ_VERTICAL_DIVIDER = 0x7BEF;
        uint32_t THEME_SEQ_HORIZONTAL_DIVIDER = 0x0000;
        uint32_t THEME_SEQ_QUARTERBAR = 0x0000;    
        uint32_t THEME_SEQ_BORDER = 0x0000;
};

class SynthUIBlueTheme : public SynthUITheme {
    public:
        SynthUIBlueTheme() {
            THEME_BACKGROUND = 0x7BEF;
            THEME_BACKGROUD_TOP_BAR = 0x7BEF;

            THEME_TEXT = 0xFFFF;
            THEME_TEXT_SELECTED = 0xFEA0;
            THEME_TEXT_TOP_BAR = 0xFFFF;

            THEME_BOX_OUTLINE = 0xFFFF;
            THEME_BOX_HIGHLIGHT = 0xFFFF;

            THEME_ENVELOPE_LINE = 0xFEA0;
        
            //SEQUENCER
            THEME_SEQ_DARKROW = 0xEF7D;
            THEME_SEQ_LIGHTROW = 0xCE79;
            THEME_SEQ_NOTE = 0xFEA0;
            THEME_SEQ_HIGHLIGHT_STEP = 0x07FF;
            THEME_SEQ_PLAYING_NOTE = 0xF800;

            THEME_SEQ_VERTICAL_DIVIDER = 0x7BEF;
            THEME_SEQ_HORIZONTAL_DIVIDER = 0x0000;
            THEME_SEQ_QUARTERBAR = 0x0000;    
            THEME_SEQ_BORDER = 0x0000;
        }
};

class SynthUIDarkGreenTheme : public SynthUITheme {
    public:
        SynthUIDarkGreenTheme() {
            THEME_BACKGROUD_TOP_BAR = 0x44C1;

            THEME_SEQ_DARKROW = 0x4A28;
            THEME_SEQ_LIGHTROW = 0x7BEF;  
            THEME_SEQ_VERTICAL_DIVIDER = THEME_SEQ_HORIZONTAL_DIVIDER = THEME_SEQ_BORDER = THEME_SEQ_QUARTERBAR = THEME_SEQ_NOTES_TEXT = 0xBE16;
            THEME_SEQ_HIGHLIGHT_STEP = 0x764A;
            THEME_SEQ_NOTE = 0xFFFF;       
        }
};

class SynthUIDarkRedTheme : public SynthUITheme {
    public:
        SynthUIDarkRedTheme() {
            THEME_BACKGROUD_TOP_BAR = 0xB020;
            THEME_BACKGROUND = 0xEF5D;
        }
};

#endif