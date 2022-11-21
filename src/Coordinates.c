#include <stdio.h>

typedef struct Coordinates Coordinates;
struct Coordinates{
    int x;
    int y;
};

void showCoordinates(Coordinates position){
    printf("(x,y): %d %d", position.x, position.y);

}