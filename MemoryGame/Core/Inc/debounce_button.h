/*
 * debounce_button.h
 *
 *  Created on: 18 sept. 2026
 *      Author: Effaceur
 */

#include "main.h"
#include <stdbool.h>
#include <stdint.h>

#ifndef INC_DEBOUNCE_BUTTON_H_
#define INC_DEBOUNCE_BUTTON_H_

#define DEBOUNCETIME 20




bool debounce_button(GPIO_TypeDef *BUTTON_GPIO_Port, uint16_t BUTTON_Pin);


#endif /* INC_DEBOUNCE_BUTTON_H_ */
