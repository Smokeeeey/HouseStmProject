/*
 * game.h
 *
 *  Created on: 19 sept. 2026
 *      Author: Effaceur
 */

#ifndef INC_GAME_H_
#define INC_GAME_H_

int random_1_3(void);
void game_init();
void blinkLed(int current);
void correctAnswer();
void wrongAnswer();
void playGame();
bool startGame();


#endif /* INC_GAME_H_ */
