#include "./include/Map.h"
#include "./include/Path.h"
#include "./include/CoordinatesQueue.h"

/*
* @brief Check if a position is the exitPosition.
* @param position The coordinates of the position to check.
* @return true if the position is the exitPosition, false otherwise.
*/
int isExitPosition(Coordinates position) {
    return position.x == MAP_SIZE - 1 && position.y == MAP_SIZE - 1;
}

/*
* @brief Check if a position is the startPosition.
* @param position The coordinates of the position to check.
* @return true if the position is the startPosition, false otherwise.
*/
int isStartPosition(Coordinates position) {
    return position.x == 0 && position.y == 0;
}

/*
* @brief Check if a position is valid : inside the map and not an obstacle.
* @param position The coordinates of the position to check.
* @param map The map.
* @return true if the position is valid, false otherwise.
*/
int isPositionValid(Coordinates position, int** map) {
    return position.x >= 0 && position.x < MAP_SIZE 
        && position.y >= 0 && position.y < MAP_SIZE 
        && map[position.x][position.y] != OBSTACLE;
}

/*
* @brief Get the eight neighbors of a position.
* @param position The coordinates of the position.
* @return An array of Coordinates containing the eight neighbors of the position. 
*/
Coordinates* getNeighbours(Coordinates position) {
    Coordinates* neighbours = malloc(sizeof(Coordinates) * 8);

    // array of x and y offsets for the eight neighbor positions
    int dx[] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int dy[] = {0, -1, -1, -1, 0, 1, 1, 1};

    for (int i = 0; i < 8; i++) {
        // compute the x and y position of the neighbor position
        // for example, if the position is {0, 0} by adding the first offset one of the neighbor position is {-1, 0}
        // and so on until we get the eight neighbor positions
        int x = position.x + dx[i];
        int y = position.y + dy[i];

        Coordinates neighbor = {x, y};
        neighbours[i] = neighbor;
    }

    return neighbours;
}

/*
* @brief Use the breadth-first search algorithm to recursively find the closest predecessor of each position.
* The function stops when it finds the exitPosition.
* See https://www.redblobgames.com/shortestPathfinding/a-star/introduction.html#breadth-first-search for more information.
* @param map The map.
* @return An array of Coordinates containing the closest predecessor of each position.
*/
Coordinates* breadthFirstSearchTheExit(int** map)
{
    Coordinates startPosition = {0, 0};
    
    // The frontier is a queue of positions to explore.
    CoordinatesQueue* frontier = createQueue();
    addToQueue(frontier, startPosition);

    Coordinates unvisitedPosition = {-1, -1};

    Coordinates* closestPredecessors =  malloc(sizeof(Coordinates) * NUMBER_OF_POSITIONS); 
    for (unsigned int i = 0; i < NUMBER_OF_POSITIONS; i++) {
        closestPredecessors[i] = unvisitedPosition;
    }

    closestPredecessors[0] = startPosition;

    while (!isEmpty(frontier)) {
        Coordinates currentPosition = removeFromQueue(frontier);
        if (isExitPosition(currentPosition)) {
            break;
        }

        Coordinates* neighbours = getNeighbours(currentPosition);
        for (unsigned int i = 0; i < 8; i++) {
            Coordinates currentPositionNeighbour = neighbours[i];
            unsigned int currentPositionIndex = currentPositionNeighbour.x + currentPositionNeighbour.y * MAP_SIZE;
            // if the currentPositionNeighbour position is valid and has not been visited yet, add it to the frontier
            if (isPositionValid(currentPositionNeighbour, map) && areEqual(closestPredecessors[currentPositionIndex], unvisitedPosition)) {
                addToQueue(frontier, currentPositionNeighbour);
                closestPredecessors[currentPositionIndex] = currentPosition;
            }
        }
    }

    free(frontier);

    return closestPredecessors;
    
}

/*
* @brief Compute the shortest shortestPath to the exitPosition from the closest predecessor of each position.
* @param map The map.
* @return An array of Coordinates containing the shortest shortestPath to the exitPosition. 
* Note that the array is not null-terminated (the last element is not {0, 0}).
*/
Coordinates* getShortestPathToExit(int ** map) {
    
    Coordinates* closestPredecessors = breadthFirstSearchTheExit(map);

    Coordinates startPosition = {0, 0};
    Coordinates exitPosition = {MAP_SIZE - 1, MAP_SIZE - 1};
    
    Coordinates* shortestPath = malloc(sizeof(Coordinates) * NUMBER_OF_POSITIONS);

    shortestPath[0] = exitPosition;

    Coordinates currentPosition = exitPosition;
    unsigned int index = 0;
    
    /*
    * add the closest predecessor of each position starting from the exitPosition 
    * until we reach the startPosition to construct the shortestPath
    */
    while (!isStartPosition(currentPosition)) {
        shortestPath[index] = currentPosition;
        
        unsigned int currentPositionIndex = currentPosition.x + currentPosition.y * MAP_SIZE;
        currentPosition = closestPredecessors[currentPositionIndex];
        index++;
    }

    shortestPath[index++] = startPosition;

    //reverse shortestPath to get it in the right order (from startPosition to exitPosition)
    Coordinates* reversedShortestPath = malloc(sizeof(Coordinates) * index);

    for (unsigned int i = 0; i < index; i++) {
        reversedShortestPath[i] = shortestPath[index - i - 1];
    }

    free(shortestPath);

    return reversedShortestPath;
}

