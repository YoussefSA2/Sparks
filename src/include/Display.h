/**
 * @file Display.h
 * @brief Prototypes for functions displaying basic informations in the console
 * @author Charles-Meldhine Madi Mnemoi, Sitursha Sivathevan, Marwa Tourabi 
*/

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "./Constants.h"
#include "./Path.h"
#include "./Player.h"

void displayAvailableCommands();
int handlePlayerVictory(Player player, int** map);
int killPlayer();
void showStatistics(Player player, int** map);

#endif