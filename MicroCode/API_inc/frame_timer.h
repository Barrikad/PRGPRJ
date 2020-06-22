#ifndef FRAME_TIMER_H_INCLUDED
#define FRAME_TIMER_H_INCLUDED

void initFrameTimer();

uint8_t getFrameFlag();

uint32_t getFramesSkipped();

void unsetFrameFlag();

#endif /* FRAME_TIMER_H_INCLUDED */
