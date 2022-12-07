
#include "./include/minunit.h"
#include "../src/include/CoordinatesQueue.h"


void test_setup(void) {
}

void test_teardown(void) {
}

MU_TEST(test_create_queue){
    
    CoordinatesQueue* queue = createQueue();
    
    mu_check(queue != NULL);
    mu_check(queue->head == NULL);
    mu_check(queue->tail == NULL);
}

MU_TEST(test_add_to_queue){
    CoordinatesQueue* queue = createQueue();
    Coordinates coordinates = {0, 0};
   
    addToQueue(queue, coordinates);
   
    mu_check(queue->head != NULL);
    mu_check(queue->tail != NULL);
    mu_check(queue->head == queue->tail);
    mu_check(areEqual(queue->head->coordinates, coordinates));
}

MU_TEST(test_remove_from_queue){
    
    CoordinatesQueue* queue = createQueue();
    Coordinates coordinates = {0, 0};
    Coordinates coordinates2 = {1, 1};
    addToQueue(queue, coordinates);
    addToQueue(queue, coordinates2);
    Coordinates removedCoordinates = removeFromQueue(queue);
    
    mu_check(areEqual(removedCoordinates, coordinates));
    mu_check(areEqual(queue->head->coordinates, coordinates2));
    mu_check(areEqual(queue->tail->coordinates, coordinates2));
}

MU_TEST(test_is_empty){
    CoordinatesQueue* queue = createQueue();
    
    mu_check(isEmpty(queue) == true);
    
    Coordinates coordinates = {0, 0};
    addToQueue(queue, coordinates);
    
    mu_check(isEmpty(queue) == false);
    
    removeFromQueue(queue);
    
    mu_check(isEmpty(queue) == true);
}


MU_TEST_SUITE(test_suite) {
	MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

    MU_RUN_TEST(test_create_queue);
    MU_RUN_TEST(test_add_to_queue);
    MU_RUN_TEST(test_remove_from_queue);
    MU_RUN_TEST(test_is_empty);

}

int main(void) {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}