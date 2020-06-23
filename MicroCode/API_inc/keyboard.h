#ifndef KEYBOARD_H_INCLUDED
#define KEYBOARD_H_INCLUDED
#define SPACE 32

//clear stored key presses
//all pressed keys will remain stored until this function is used
void clearKeys();

uint8_t keyHasBeenPressed(char key);

#endif /* KEYBOARD_H_INCLUDED */
