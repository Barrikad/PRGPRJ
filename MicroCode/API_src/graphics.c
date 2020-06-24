#include "graphics.h"

#define DIRECTIONS 12
//strings end with \0, so we add 1 to array size
#define TILE_SIZE (TILE_WIDTH * TILE_HEIGHT + 1)

// TODO: Use UTF-8 Unicode
// Sprite for a tank
const char TANK[DIRECTIONS][TILE_SIZE] = {
    // Right
    "--- "
    " H->"
    "--- ",
    // Right/Down
    "  \\ "
    "\\H'\\"
    " \\ \\",
    // Down/Right
    "  - "
    "\\H.\\"
    " - -",
    // Down
    "|  |"
    "|HH|"
    " \\/ ",
    // Down/Left
    " /  "
    "/,H/"
    "/ / ",
    // Left/Down
    " -  "
    "/,H/"
    "- - ",
    // Left
    " ---"
    "<-H "
    " ---",
    // Left/Up
    "\\ \\ "
    "\\'H\\"
    " \\  ",
    // Up/Left
    "- - "
    "\\'H\\"
    " -  ",
    // Up
    " /\\ "
    "|HH|"
    "|  |",
    // Up/Right
    " / /"
    "/H'/"
    "  / ",
    // Right/Up
    " - -"
    "/H'/"
    "  - ",
};
const char TANK_CLEAR[TILE_SIZE] =
    "    "
    "    "
    "    ";

// Wall sprite
const char WALL[TILE_SIZE] =
    "####"
    "#%%#"
    "####";

// Box sprite
const char BOX[TILE_SIZE] =
    "####"
    "#++#"
    "####";

// Closed door sprite
const char DOOR_CLOSED[TILE_SIZE] =
    "+--+"
    "|  |"
    "+--+";

// Open door sprite
const char DOOR_OPEN[TILE_SIZE] =
    "+  +"
    "    "
    "+  +";

// PowerUp sprite
const char POWERUP[TILE_SIZE] =
    "@~  "
    "~@  "
    "    ";

// The bullet sprite
const char BULLET = 'o';

static void drawSpriteTiles(const char sprite[TILE_WIDTH * TILE_HEIGHT]) {
    uint8_t i, j;
    for (i = 0; i < TILE_HEIGHT; i++) {
        // Print all horizontal tiles
        for (j = 0; j < TILE_WIDTH; j++) {
            printf("%c", sprite[i * TILE_WIDTH + j]);
        }

        // Go down and to original x-position
        cursorDown(1);
        cursorLeft(TILE_WIDTH);
    }
}

static uint8_t getXCoordinate(fix14_t x) {
    return roundFix(x * TILE_WIDTH);
}

static uint8_t getYCoordinate(fix14_t y) {
    return roundFix(y * TILE_HEIGHT);
}

static uint8_t getRotationOffset(deg512_t rotation) {
    // Reduce angle so that 0 <= rotation < 512
    // Multiply by DIRECTIONS to choose sprite
    // Divide by 512 to get 0 <= rotationOffset < DIRECTIONS
    // Ensure within range by using modulus DIRECTIONS
    return roundFix(((DIRECTIONS * (rotation & 511)) << 14) / 512) % DIRECTIONS;
}

// Go to the position from where we can start drawing
static void goToPosition(const vector_t *position) {
    uint8_t x = getXCoordinate((*position).x);
    uint8_t y = getYCoordinate((*position).y);
    cursorToXY(x, y);
}

void undrawTank(const placement_t *placement) {
    goToPosition(&(*placement).position);
    drawSpriteTiles(TANK_CLEAR);
}

uint8_t shouldRedraw(const placement_t *previousPlacement, const placement_t *currentPlacement) {
    uint8_t previousX        = getXCoordinate((*previousPlacement).position.x);
    uint8_t currentX         = getXCoordinate((*currentPlacement).position.x);
    uint8_t previousY        = getYCoordinate((*previousPlacement).position.y);
    uint8_t currentY         = getYCoordinate((*currentPlacement).position.y);
    uint8_t previousRotation = getRotationOffset((*previousPlacement).rotation);
    uint8_t currentRotation  = getRotationOffset((*currentPlacement).rotation);

    if (previousX == currentX && previousY == currentY && previousRotation == currentRotation) {
        return 0;
    }
    return 1;
}

void drawTank(const placement_t *placement, uint8_t color) {
    goToPosition(&(*placement).position);
    fgcolor(color);
    drawSpriteTiles(TANK[getRotationOffset((*placement).rotation)]);
    resetcolor();
}

void drawWall(uint8_t x, uint8_t y, uint8_t color) {
    cursorToXY(x * TILE_WIDTH, y * TILE_HEIGHT);
    fgcolor(color);
    drawSpriteTiles(WALL);
    resetcolor();
}

void drawBox(uint8_t x, uint8_t y, uint8_t color) {
    cursorToXY(x * TILE_WIDTH, y * TILE_HEIGHT);
    fgcolor(color);
    drawSpriteTiles(BOX);
    resetcolor();
}

void drawDoor(const placement_t *placement, uint8_t color, uint8_t open) {
    goToPosition(&(*placement).position);
    fgcolor(color);
    drawSpriteTiles(open ? DOOR_OPEN : DOOR_CLOSED);
    resetcolor();
}

void undrawPowerUp(const placement_t *placement) {
    goToPosition(&(*placement).position);
    //tank clear, clears the powerup
    drawSpriteTiles(TANK_CLEAR);
}

void drawPowerUp(const placement_t *placement, uint8_t color, uint8_t blinkOn) {
    goToPosition(&(*placement).position);
    blink(blinkOn);
    fgcolor(color);
    drawSpriteTiles(POWERUP);
    blink(0);
    resetcolor();
}

void undrawBullet(const placement_t *placement) {
    goToPosition(&(*placement).position);
    printf(" ");
}

void drawBullet(const placement_t *placement, uint8_t color) {
    goToPosition(&(*placement).position);
    // TODO: Draw bullet with different character depending on where it is.
    // For example draw as "." if it's in the bottom of a character and as "\" if its in the top.
    fgcolor(color);
    printf("%c", BULLET);
    resetcolor();
}
