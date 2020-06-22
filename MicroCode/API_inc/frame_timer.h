#ifndef FRAME_TIMER_H_INCLUDED
#define FRAME_TIMER_H_INCLUDED

void initFrameTimer();

uint8_t getFlag();

uint32_t getFramesSkipped();

void unsetFlag();

#endif /* FRAME_TIMER_H_INCLUDED */
