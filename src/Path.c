#include "./include/Map.h"
#include "./include/Path.h"
#include "./include/CoordinatesQueue.h"

/*
* @brief Check if a position is the exitPosition.
* @param position The coordinates of the position to check.
* @return true if the position is the exitPosition, false otherwise.
*/
int isExitPosition(Coordinates position, int mapSize) {
    return areEqual(position, (Coordinates){mapSize -1, mapSize -1}); // TODO: use the EXIT constant when the relevant PR is merged
}

/*
* @brief Check if a position is the startPosition.
* @param position The coordinates of the position to check.
* @return true if the position is the startPosition, false otherwise.
*/
int isStartPosition(Coordinates position) {
    return areEqual(position, (Coordinates) {0, 0});
}

/*
* @brief Check if a position has not been visited yet.
* @param position The coordinates of the position to check.
* @return true if the position has not been visited yet, false otherwise.
*/
int isUnvisitedPosition(Coordinates position) {
    return areEqual(position, (Coordinates) {-1, -1});
}

/*
* @brief Check if a position is valid : inside the map and not an obstacle.
* @param position The coordinates of the position to check.
* @param map The map.
* @return true if the position is valid, false otherwise.
*/
int isValidPosition(Coordinates position, int** map, int mapSize) {
    return position.x >= 0 && position.x < mapSize 
        && position.y >= 0 && position.y < mapSize 
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
Coordinates* breadthFirstSearchTheExit(int** map, int mapSize)
{   

    unsigned int numberOfPositions = mapSize * mapSize;
    Coordinates startPosition = {0, 0};
    
    // The frontier is a queue of positions to explore.
    CoordinatesQueue* frontier = createQueue();
    addToQueue(frontier, startPosition);

    Coordinates unvisitedPosition = {-1, -1};

    Coordinates* closestPredecessors =  malloc(sizeof(Coordinates) * numberOfPositions); 
    for (unsigned int i = 0; i < numberOfPositions; i++) {
        closestPredecessors[i] = unvisitedPosition;
    }

    closestPredecessors[0] = startPosition;

    while (!isEmpty(frontier)) {
        Coordinates currentPosition = removeFromQueue(frontier);
        if (isExitPosition(currentPosition, mapSize)) {
            break;
        }

        Coordinates* neighbours = getNeighbours(currentPosition);
        for (unsigned int i = 0; i < 8; i++) {
            Coordinates currentPositionNeighbour = neighbours[i];
            unsigned int currentPositionIndex = currentPositionNeighbour.x + currentPositionNeighbour.y * mapSize;
            // if the currentPositionNeighbour position is valid and has not been visited yet, add it to the frontier
            if (isValidPosition(currentPositionNeighbour, map, mapSize) && isUnvisitedPosition(closestPredecessors[currentPositionIndex])) {
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
* If the exitPosition is not reachable, the function returns NULL.
*/
cvector_vector_type(Coordinates) getShortestPathToExit(int ** map, int mapSize) {
    
    unsigned int numberOfPositions = mapSize * mapSize;
    
    Coordinates* closestPredecessors = breadthFirstSearchTheExit(map, mapSize);

    Coordinates startPosition = {0, 0};
    Coordinates exitPosition = {mapSize - 1, mapSize - 1};
    
    Coordinates* shortestPath = malloc(sizeof(Coordinates) * numberOfPositions);

    shortestPath[0] = exitPosition;

    Coordinates currentPosition = exitPosition;
    unsigned int index = 0;
    
    /*
    * add the closest predecessor of each position starting from the exitPosition 
    * until we reach the startPosition to construct the shortestPath
    */
    while (!isStartPosition(currentPosition)) {
        shortestPath[index] = currentPosition;
        
        unsigned int currentPositionIndex = currentPosition.x + currentPosition.y * mapSize;
        // if the currentPositionIndex is out of bounds, the shortestPath is not valid so we return NULL
        // (this probably means that the exitPosition is not reachable)
        if (currentPositionIndex >= numberOfPositions) {
            return NULL;
        }
        
        currentPosition = closestPredecessors[currentPositionIndex];
        index++;
    }

    shortestPath[index++] = startPosition;

    //reverse shortestPath to get it in the right order (from startPosition to exitPosition)
    Coordinates* reversedShortestPath = malloc(sizeof(Coordinates) * index);

    for (unsigned int i = 0; i < index; i++) {
        reversedShortestPath[i] = shortestPath[index - i - 1];
    }

    // remove the positions that are not part of the shortest shortestPath
    // (don't ask me why)
    cvector_vector_type(Coordinates) cleanShortestpath = NULL;

     for (unsigned int i = 0; i < index; i++) {
        cvector_push_back(cleanShortestpath, reversedShortestPath[i]);
        if (isExitPosition(reversedShortestPath[i], mapSize)) {
            break;
        }
    }

    free(closestPredecessors);
    free(shortestPath);
    free(reversedShortestPath);

    return cleanShortestpath;
}

