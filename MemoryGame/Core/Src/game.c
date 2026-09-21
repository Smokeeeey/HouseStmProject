/*
 * game.c
 *
 * Created on: 19 sept. 2026
 * Author: Effaceur
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
int score = 0;
char text[20];
int currentSequence = 0;


// --------------------------------------------------
// Fonctions
// --------------------------------------------------

void game_init()
{
    // Reset the game
    score = 0;
    currentSequence = 0;


    //New sequence
    for (int i = 0; i < 20; i++)
    {
        memory[i] = random_1_3();
    }

    // --------- Turn off the leds --------------------------------
    HAL_GPIO_WritePin(led1_GPIO_Port, led1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(led2_GPIO_Port, led2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(led3_GPIO_Port, led3_Pin, GPIO_PIN_RESET);



    // ---------- Display ------------------------------------------
    ssd1306_Fill(Black);

    ssd1306_SetCursor(10, 5);
    ssd1306_WriteString("Memory Game", Font_7x10, White);

    ssd1306_SetCursor(10, 25);
    ssd1306_WriteString("Btn to start !", Font_7x10, White);

    ssd1306_UpdateScreen();
    // --------------------------------------------------------------
}



void playGame()
{
	if (startGame())
	{

	}
}

bool startGame()
{
	//Btn relaché = 1
	if (
		!debounce_button(button1_GPIO_Port, button1_Pin) ||
		!debounce_button(button2_GPIO_Port, button2_Pin) ||
		!debounce_button(button3_GPIO_Port, button3_Pin)
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}



void correctAnswer()
{
    // ---------- Display ------------------------------------------
    ssd1306_Fill(Black);

    ssd1306_SetCursor(10, 5);
    ssd1306_WriteString("Memory Game", Font_7x10, White);

    ssd1306_SetCursor(10, 25);
    ssd1306_WriteString("Good answer !", Font_7x10, White);

    ssd1306_UpdateScreen();
    // --------------------------------------------------------------

    HAL_Delay(3000);
}


void wrongAnswer()
{
    // ---------- Display ------------------------------------------
    ssd1306_Fill(Black);

    ssd1306_SetCursor(10, 5);
    ssd1306_WriteString("Memory Game", Font_7x10, White);

    ssd1306_SetCursor(10, 25);
    ssd1306_WriteString("Wrong answer !", Font_7x10, White);

    ssd1306_UpdateScreen();
    // --------------------------------------------------------------

    HAL_Delay(3000);

}

void blinkLed(int current)
{
	switch (current)
	{
		//ON -> 2sec -> OFF -> 2sec
		case 1:
			HAL_GPIO_WritePin(led1_GPIO_Port, led1_Pin, GPIO_PIN_SET);
			HAL_Delay(2000);
			HAL_GPIO_WritePin(led1_GPIO_Port, led1_Pin, GPIO_PIN_RESET);
			HAL_Delay(2000);
			break;
		case 2:
			HAL_GPIO_WritePin(led2_GPIO_Port, led2_Pin, GPIO_PIN_SET);
			HAL_Delay(2000);
			HAL_GPIO_WritePin(led2_GPIO_Port, led2_Pin, GPIO_PIN_RESET);
			HAL_Delay(2000);
			break;
		case 3:
			HAL_GPIO_WritePin(led3_GPIO_Port, led3_Pin, GPIO_PIN_SET);
			HAL_Delay(2000);
			HAL_GPIO_WritePin(led3_GPIO_Port, led3_Pin, GPIO_PIN_RESET);
			HAL_Delay(2000);
			break;
		default:
			break;
	}
}

void playRound ()
{

    // ---------- Display ------------------------------------------

    ssd1306_Fill(Black);

    ssd1306_SetCursor(10, 5);
    ssd1306_WriteString("Memory Game", Font_7x10, White);

    ssd1306_SetCursor(10, 25);
    ssd1306_WriteString("Look the leds !", Font_7x10, White);

    ssd1306_UpdateScreen();

    // ----------- Blink leds -------------------------------------------

	for (int i = 0; i < (score + 1); i++)
	{
		blinkLed(memory[i]);
	}

    // ---------- Display ------------------------------------------

    ssd1306_Fill(Black);

    ssd1306_SetCursor(10, 5);
    ssd1306_WriteString("Memory Game", Font_7x10, White);

    ssd1306_SetCursor(10, 25);
    ssd1306_WriteString("Look the leds !", Font_7x10, White);

    ssd1306_UpdateScreen();

    // ----------- Guess time -------------------------------------------

    while (currentSequence < score)
    {
    	if (!debounce_button(button1_GPIO_Port, button1_Pin))
    	{
    		if (!(memory[currentSequence] == 1))
    		{
    			wrongAnswer();
    		}
    	}
    }



}



int random_1_3(void)
{
    return (rand() % 3) + 1;
}
