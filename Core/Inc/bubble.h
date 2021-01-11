/*
 * Bubble.h
 *
 *  Created on: Jan 2, 2021
 *      Author: mint
 */

#ifndef INC_BUBBLE_H_
#define INC_BUBBLE_H_

#include <stdint.h>
#include <stdbool.h>

typedef struct Bubble {
	int8_t XPos;
	int8_t YPos;
	int8_t Radius;
} Bubble;

void Bubble_ctor(Bubble * const me, int8_t X, int8_t Y, int8_t Radius);
void Bubble_moveby(Bubble * const me, int8_t dX, int8_t dY);

#endif /* INC_BUBBLE_H_ */
