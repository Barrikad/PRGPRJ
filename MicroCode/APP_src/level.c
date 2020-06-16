#include "level.h"

vector_t verticalBound(){
    //from offset to offset + width, converted to fix14
    vector_t v = {VERTICAL_OFFSET << 14, (VERTICAL_OFFSET + LEVEL_HEIGHT) << 14};
    return v;
}

vector_t horizontalBound(){
    vector_t v = {HORIZONTAL_OFFSET << 14, (HORIZONTAL_OFFSET + LEVEL_WIDTH) << 14};
    return v;
}

void enterLevel(level_t level) {
    // TODO
}

void renderLevel() {
    // TODO
}

void processInputLevel() {
    // TODO
}
