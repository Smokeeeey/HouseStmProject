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
	sprintf(text, "%d", score);

	ssd1306_Fill(Black);

	ssd1306_SetCursor(10, 5);
	ssd1306_WriteString("Press btn to start !", Font_7x10, White);

	ssd1306_SetCursor(10, 25);
	ssd1306_WriteString("Score:" + text, Font_7x10, White);

	ssd1306_UpdateScreen();

}

void playGame()
{

	//Read the buttons
	if (debounce_button(bouton1_GPIO_Port, bouton1_Pin))
	{
		buttonPressed[1] = 1;
		nbreButtonPressed++;
	}
	if (debounce_button(bouton2_GPIO_Port, bouton2_Pin))
	{
		buttonPressed[2] = 1;
		nbreButtonPressed++;
	}
	if (debounce_button(bouton3_GPIO_Port, bouton3_Pin))
	{
		buttonPressed[3] = 1;
		nbreButtonPressed++;
	}
	if (debounce_button(bouton4_GPIO_Port, bouton4_Pin))
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
					ssd1306_Fill(Black);

					ssd1306_SetCursor(10, 5);
					ssd1306_WriteString("Memory Game", Font_7x10, White);

					sequenceLed();
					gameIsStart = true;
				}
				else
				{
					//Use the pressed button
					if (buttonPressed[i] = 1)
					{
						//Correct answer
						if (buttonPressed[i] = memory[score])
						{
							correctAnswer();
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


}

void sequenceLed()
{
	for (int i = 0; i <= score; i++)
	{
		switch (i)
		{
			case 1:
				HAL_GPIO_WritePin(led1_GPIO_Port, led1_Pin, GPIO_PIN_RESET);
				HAL_Delay(300);
				HAL_GPIO_WritePin(led1_GPIO_Port, led1_Pin, GPIO_PIN_SET);
				break;
			case 2:
				HAL_GPIO_WritePin(led2_GPIO_Port, led2_Pin, GPIO_PIN_RESET);
				HAL_Delay(300);
				HAL_GPIO_WritePin(led2_GPIO_Port, led2_Pin, GPIO_PIN_SET);
				break;
			case 3:
				HAL_GPIO_WritePin(led3_GPIO_Port, led3_Pin, GPIO_PIN_RESET);
				HAL_Delay(300);
				HAL_GPIO_WritePin(led3_GPIO_Port, led3_Pin, GPIO_PIN_SET);
				break;
			case 4:
				HAL_GPIO_WritePin(led4_GPIO_Port, led4_Pin, GPIO_PIN_RESET);
				HAL_Delay(300);
				HAL_GPIO_WritePin(led4_GPIO_Port, led4_Pin, GPIO_PIN_SET);
				break;

		}
	}
}

void correctAnswer()
{
	score++;

	ssd1306_SetCursor(10, 25);
	ssd1306_WriteString("Score:" + text, Font_7x10, White);

	ssd1306_UpdateScreen();
}

void wrongAnswer()
{
	score = 0;

	ssd1306_SetCursor(10, 25);
	ssd1306_WriteString("Perdu looser !", Font_7x10, White);

	ssd1306_UpdateScreen();

	//Restart the game
	game_init();
	gameIsStart = false;
}



int random_1_4(void)
{
	//Return a number between 1 to 4
    return (rand() % 4) + 1;
}
