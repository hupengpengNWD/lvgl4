#ifndef _KEY_IT_H
#define _KEY_IT_H

#include <stdbool.h>
#include <stdint.h>

#define MY_KEY_SUM 4

void Key_IRQ_Callback(uint16_t GPIO_Pin);
bool key_is_pressed(uint8_t id);



#endif /* _DRIVER_KEY_H */