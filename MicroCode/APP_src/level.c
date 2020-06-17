#include "level.h"
#include "ansi.h"
#include "graphics.h"

#define LEVEL_WIDTH 14
#define LEVEL_HEIGHT 13

// Only the characters # and % are used when inspecting level data, the rest are ignored!

static const char * levelData1 =
    "##############"
    "#            #"
    "#            d"
    "#  ##%%#     d"
    "#      #     #"
    "#      #     #"
    "#     ##   e #"
    "#     #      #"
    "#     #      #"
    "# p   #%%%#  #"
    "#            #"
    "#            #"
    "##############";

static const char * levelData2 =
    "##############"
    "#            #"
    "#            #"
    "#          e #"
    "#   ######   #"
    "#            #"
    "#            #"
    "#            #"
    "#   ######   #"
    "# p          #"
    "#            #"
    "#            #"
    "##############";

vector_t verticalBound(){
    //from offset to offset + width, converted to fix14
    vector_t v = {0, LEVEL_HEIGHT << 14};
    return v;
}

vector_t horizontalBound(){
    vector_t v = {0, LEVEL_WIDTH << 14};
    return v;
}

static void drawLevel(const char * data) {
    uint8_t i, j;
    char c;
    for (i = 0; i < LEVEL_HEIGHT; i++) {
        for (j = 0; j < LEVEL_WIDTH; j++) {
            c = data[i * LEVEL_WIDTH + j];
            if (c == '#') {
                printf("#");
            } else if (c == '%') {
                printf("%%");
            } else {
                printf(" ");
            }
        }
        // Go back to original position
        cursorDown(1);
        cursorLeft(LEVEL_WIDTH);
    }
}

void renderLevel(level_t level) {
    clrscr();
    cursorToXY(0, 0);
    switch(level) {
    case firstLevel:
        drawLevel(levelData1);
        // TODO: Draw entities
        // TODO: Change timer?
        break;
    case secondLevel:
        drawLevel(levelData2);
        // TODO: Draw entities
        // TODO: Change timer?
        break;
    }
}
