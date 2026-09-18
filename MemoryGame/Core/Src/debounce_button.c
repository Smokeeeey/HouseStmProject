/*
 * debounce_button.c
 *
 *  Created on: 18 sept. 2026
 *      Author: Effaceur
 */

#include "debounce_button.h"

static uint32_t lastDebounceTime = 0;
static GPIO_PinState lastState = GPIO_PIN_RESET;
static GPIO_PinState stableState = GPIO_PIN_RESET;

bool debounce_button(GPIO_TypeDef *BUTTON_GPIO_Port, uint16_t BUTTON_Pin)
{
	GPIO_PinState currentState = HAL_GPIO_ReadPin(BUTTON_GPIO_Port, BUTTON_Pin);

	 // Le signal a changé : on recommence le chronomètre
	if (currentState != lastState)
	{
	  lastDebounceTime = HAL_GetTick();
	  lastState = currentState;
	}

	// Le signal est resté stable pendant 20 ms
	if ((HAL_GetTick() - lastDebounceTime) >= DEBOUNCETIME)
	{
	  if (currentState != stableState)
	  {
		  stableState = currentState;

		  // Bouton appuyé
		  if (stableState == GPIO_PIN_SET)
		  {
			  return true;
		  }
	  }
	}
	return false;
}


