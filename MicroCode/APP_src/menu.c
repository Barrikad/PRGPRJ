#include "lcd.h"
#include "menu.h"

typedef struct {
    const char * options;
    int8_t layer;

} menu_t;


void setMenuOptions(menu_t menu) {
    //*menu.options = {"New Game", "Help", "Highscore", "Credits"};
}



void renderMainMenu() {
    // TODO: This!
}

uint8_t processInputMainMenu() {
    // TODO: This!
    return 0;
}

void renderHelpMenu() {
    // TODO: This!
}

uint8_t processInputHelpMenu() {
    // TODO: This!
    return 0;
}

void renderScoreMenu(uint8_t clearedLevels) {
    // TODO: This!
}

uint8_t processInputScoreMenu() {
    // TODO: This!
    return 0;
}
