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
int buttonPressed[5] = {0, 0, 0, 0, 0};
int nbreButtonPressed = 0;
int score = 0;
bool gameIsStart = false;
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
    nbreButtonPressed = 0;


    //New sequence
    for (int i = 0; i < 20; i++)
    {
        memory[i] = random_1_4();
    }

    //Turn off the leds
    HAL_GPIO_WritePin(led1_GPIO_Port, led1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(led2_GPIO_Port, led2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(led3_GPIO_Port, led3_Pin, GPIO_PIN_RESET);

    //Display
    ssd1306_Fill(Black);

    ssd1306_SetCursor(10, 5);
    ssd1306_WriteString("Memory Game", Font_7x10, White);

    ssd1306_SetCursor(10, 25);
    ssd1306_WriteString("Btn to start !", Font_7x10, White);

    ssd1306_UpdateScreen();
}



void playGame()
{

}



void correctAnswer()
{

}


void wrongAnswer()
{

}



int random_1_4(void)
{
    return (rand() % 4) + 1;
}
