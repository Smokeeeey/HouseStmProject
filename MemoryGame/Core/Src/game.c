/*
 * game.c
 *
 *  Created on: 19 sept. 2026
 *      Author: Effaceur
 */

#include "game.h"
#include "main.h"
#include "debounce_button.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "ssd1306.h"
#include "ssd1306_fonts.h"

int memory[20];
int buttonPressed[5] = {0,0,0,0,0};
int nbreButtonPressed;
int score = 0;
bool gameIsStart = false;
char text[20];
int currentSequence = 0;







// ----------- Functions -----------

void game_init()
{
	//----------- Initialize the sentence to memorise -----------
	for (int i = 0; i < 20; i++)
	{
		memory[i] = random_1_4();
	}

	//----------- Turn off the led -----------
	HAL_GPIO_WritePin(led1_GPIO_Port, led1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(led2_GPIO_Port, led2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(led3_GPIO_Port, led3_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(led4_GPIO_Port, led4_Pin, GPIO_PIN_SET);


	//----------- Write on screen -----------
	sprintf(text, "Score: %d", score);

	ssd1306_Fill(Black);

	ssd1306_SetCursor(10, 5);
	ssd1306_WriteString("Press btn to start !", Font_7x10, White);

	ssd1306_SetCursor(10, 25);
	ssd1306_WriteString(text, Font_7x10, White);

	ssd1306_UpdateScreen();

}

void playGame()
{

	/*
	//Read the buttons
	if (debounce_button(button1_GPIO_Port, button1_Pin))
	{
		buttonPressed[1] = 1;
		nbreButtonPressed++;
	}
	if (debounce_button(button2_GPIO_Port, button2_Pin))
	{
		buttonPressed[2] = 1;
		nbreButtonPressed++;
	}
	if (debounce_button(button3_GPIO_Port, button3_Pin))
	{
		buttonPressed[3] = 1;
		nbreButtonPressed++;
	}
	if (debounce_button(button4_GPIO_Port, button4_Pin))
	{
		buttonPressed[4] = 1;
		nbreButtonPressed++;
	}
	*/

	if (HAL_GPIO_ReadPin(button1_GPIO_Port, button1_Pin))
	{
		buttonPressed[1] = 1;
		nbreButtonPressed++;
	}
	if (HAL_GPIO_ReadPin(button2_GPIO_Port, button2_Pin))
	{
		buttonPressed[2] = 1;
		nbreButtonPressed++;
	}
	if (HAL_GPIO_ReadPin(button3_GPIO_Port, button3_Pin))
	{
		buttonPressed[3] = 1;
		nbreButtonPressed++;
	}
	if (HAL_GPIO_ReadPin(button4_GPIO_Port, button4_Pin))
	{
		buttonPressed[4] = 1;
		nbreButtonPressed++;
	}

	//Check if on or more button is pressed
	switch (nbreButtonPressed)
	{
		case 0:
			break;

		case 1:

			//Reset the state button
			for (int i = 0; i < 5; i++)
			{
				//Start the game
				if (!gameIsStart)
				{
				    // Reset les boutons qui ont servi à démarrer
				    for (int j = 0; j < 5; j++)
				    {
				        buttonPressed[j] = 0;
				    }

				    nbreButtonPressed = 0;

					ssd1306_Fill(Black);

					ssd1306_SetCursor(10, 5);
					ssd1306_WriteString("Memory Game", Font_7x10, White);


					gameIsStart = true;

					sequenceLed();
				}
				else
				{
					//Use the pressed button
					if (buttonPressed[i] == 1)
					{
						//Correct answer
						if (i == memory[currentSequence])
						{
							currentSequence++;

							if (currentSequence > score)
							{
								currentSequence = 0;
								correctAnswer();
							}
						}
						else
						{
							wrongAnswer();
						}
					}
				}

				//Reset the state button
				buttonPressed[i] = 0;
			}
			break;

		default:
			//Reset the state button
			for (int i = 0; i < 5; i++)
			{
				buttonPressed[i] = 0;
			}
			break;
	}

	nbreButtonPressed = 0;


}

void sequenceLed()
{
	for (int i = 0; i <= score; i++)
	{
		HAL_Delay(500);

		switch (memory[i])
		{
			case 1:
				HAL_GPIO_WritePin(led1_GPIO_Port, led1_Pin, GPIO_PIN_RESET);
				HAL_Delay(700);
				HAL_GPIO_WritePin(led1_GPIO_Port, led1_Pin, GPIO_PIN_SET);
				break;
			case 2:
				HAL_GPIO_WritePin(led2_GPIO_Port, led2_Pin, GPIO_PIN_RESET);
				HAL_Delay(700);
				HAL_GPIO_WritePin(led2_GPIO_Port, led2_Pin, GPIO_PIN_SET);
				break;
			case 3:
				HAL_GPIO_WritePin(led3_GPIO_Port, led3_Pin, GPIO_PIN_RESET);
				HAL_Delay(700);
				HAL_GPIO_WritePin(led3_GPIO_Port, led3_Pin, GPIO_PIN_SET);
				break;
			case 4:
				HAL_GPIO_WritePin(led4_GPIO_Port, led4_Pin, GPIO_PIN_RESET);
				HAL_Delay(700);
				HAL_GPIO_WritePin(led4_GPIO_Port, led4_Pin, GPIO_PIN_SET);
				break;

		}
	}
}

void correctAnswer()
{
	score++;

	sprintf(text, "Score: %d", score);

	ssd1306_SetCursor(10, 25);
	ssd1306_WriteString(text, Font_7x10, White);

	ssd1306_UpdateScreen();

	//----------- Blink the led -----------
	HAL_GPIO_WritePin(led1_GPIO_Port, led1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(led2_GPIO_Port, led2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(led3_GPIO_Port, led3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(led4_GPIO_Port, led4_Pin, GPIO_PIN_RESET);

	HAL_Delay(500);

	HAL_GPIO_WritePin(led1_GPIO_Port, led1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(led2_GPIO_Port, led2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(led3_GPIO_Port, led3_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(led4_GPIO_Port, led4_Pin, GPIO_PIN_SET);

	HAL_Delay(500);

	HAL_GPIO_WritePin(led1_GPIO_Port, led1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(led2_GPIO_Port, led2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(led3_GPIO_Port, led3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(led4_GPIO_Port, led4_Pin, GPIO_PIN_RESET);

	HAL_Delay(500);

	HAL_GPIO_WritePin(led1_GPIO_Port, led1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(led2_GPIO_Port, led2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(led3_GPIO_Port, led3_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(led4_GPIO_Port, led4_Pin, GPIO_PIN_SET);

	//Relance une sequence
	sequenceLed();

}

void wrongAnswer()
{
	score = 0;

	ssd1306_SetCursor(10, 25);
	ssd1306_WriteString("Perdu looser !", Font_7x10, White);

	ssd1306_UpdateScreen();

	HAL_Delay(2000);

	//Restart the game
	game_init();
	gameIsStart = false;
}



int random_1_4(void)
{
	//Return a number between 1 to 4
    return (rand() % 4) + 1;
}
