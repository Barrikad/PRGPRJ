#include "lcd.h"
#include "menu.h"

typedef struct {
    const char * options;
    int8_t layer;

} menu_t


void setMenuOptions(menu_t menu) {
    *menu.options = {"New Game", "Help", "Highscore", "Credits"};
}

void currentOptions


void renderMainMenu() {

}

uint8_t processInputMainMenu() {
    return 0;
}

void renderHelpMenu() {

}

uint8_t processInputHelpMenu() {
    return 0;
}

void renderScoreMenu(uint8_t clearedLevels) {

}

uint8_t processInputScoreMenu() {
    return 0;
}
