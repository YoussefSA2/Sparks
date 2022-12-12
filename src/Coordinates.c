#include "./include/Coordinates.h"

void showCoordinates(Coordinates position){
    printf("(%d, %d)", position.x, position.y);

}

int areEqual(Coordinates position1, Coordinates position2){
    return position1.x == position2.x && position1.y == position2.y;
}
