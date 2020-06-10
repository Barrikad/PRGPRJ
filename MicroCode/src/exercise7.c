#include "exercise7.h"

#define BUFFER_SIZE 512

void exercise7() {
	uint8_t buffer[BUFFER_SIZE];
	// Sets each element of the buffer to 0xAA
	memset(buffer, 0xAA, BUFFER_SIZE);
	lcd_init();
	lcd_push_buffer(buffer);

	while(1) {}
}
