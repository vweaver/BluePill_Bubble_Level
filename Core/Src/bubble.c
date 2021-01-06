/*
 * Bubble.c
 *
 *  Created on: Jan 2, 2021
 *      Author: mint
 */

#include <bubble.h>
#include "stm32f1xx_hal.h"
#include "graphics.h"
#include "utils.h"


/**
  * @brief Bubble constructor
  * @param me: pointer to a Bubble struct
  * @retval None
  */
void Bubble_ctor(Bubble * const me, int8_t X, int8_t Y, int8_t Radius)
{
	me->XPos = X;
	me->YPos = Y;
	me->Radius = Radius;
	GraphicsFilledCircle(me->XPos, me->YPos, me->Radius, true);
	GraphicsUpdateDisplay();
}

/**
  * @brief Move a Bubble on the Oled
  * @param me: pointer to a Bubble struct
  * @param dX: distance to move in the X direction
  * @param dY: distance to move in the Y direction
  * @retval None
  */
void moveBubble(Bubble * const me, int8_t dX, int8_t dY)
{
	// Erase the current bubble
	GraphicsFilledCircle(me->XPos, me->YPos, me->Radius, false);

	// Update the position
	uint8_t Xnew = me->XPos + dX;
	uint8_t Ynew = me->YPos + dY;

	// constraining to the screen size
	me->XPos = constrain_i8(Xnew, 0+me->Radius, SSD1306_OLED_WIDTH - me->Radius);
	me->YPos = constrain_i8(Ynew, 0+me->Radius, SSD1306_OLED_HEIGHT - me->Radius);

	// Draw the new bubble
	GraphicsFilledCircle(me->XPos, me->YPos, me->Radius, true);

	// Redraw the bulls eye
	GraphicsCircle(64, 32, 13, true);

	GraphicsUpdateDisplay();
}


