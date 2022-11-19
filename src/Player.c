/**
* File which handles the Map structure and functions.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

typedef struct Player Player;
struct Player{
    float energy;
    int position[2];// Quand la struct coord seras pretes il faudras remplacé
    int nbRewinds;
};
Player initPlayer(){
   Player p;// Je créer un nouveau player et je lui initialise ces valeurs
   p.position[0]=0;// Quand la struct coord seras pretes il faudras remplacé
   p.position[1]=0;
   p.energy=100;
   p.nbRewinds=20;

   return p;
}
void move(Player* player, int direction){
    switch(direction){
        case 1://A faire quand les fonction de map seront prets
            printf("UP");
            break;
        case 2:
            printf("DOWN");
            break;
        case 3:
            printf("LEFT");
            break;
        case 4:
            printf("RIGHT");
            break;
    }
}
void modifyEnergy(Player* player, int value){
    player->energy=value;
}
