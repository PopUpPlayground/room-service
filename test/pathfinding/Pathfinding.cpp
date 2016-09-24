#include "Map.h"
#include "unity.h"
#include <iostream>

void dumpVector(path_t *vector) {
    std::cerr << "Here comes a vector: ";
    for (path_t::const_iterator i = vector->begin(); i != vector->end(); i++) {
        std::cerr << *i;
    }
    std::cerr << "\n";
}

void test_Pathfinding() {

    Map map;

    // 1---2---3---5
    //     |
    //     4

    map.newRoom("Foyer", 1);
    map.newRoom("Hub", 2);
    map.newRoom("Porch", 3);
    map.newRoom("SideRoom",4);
    map.newRoom("Garden",5);

    map.newBiDoor(1,2,11);
    map.newBiDoor(2,4,42);
    map.newBiDoor(2,3,32);
    map.newBiDoor(5,3,35);

    // Simple path
    path_t *path = map.findPath(1,2,NULL);

    TEST_ASSERT_EQUAL(1,path->at(0));
    TEST_ASSERT_EQUAL(2,path->at(1));

    std::cerr << "Tested assertion\n";

    delete path;

    std::cerr << "Path freed\n";

    std::cerr << "\n--- Plotting route: 1-5 ---\n\n";
    path = map.findPath(1,5, NULL);
    
    std::cerr << "New path found\n";

    TEST_ASSERT_EQUAL(1,path->at(0));
    TEST_ASSERT_EQUAL(2,path->at(1));
    TEST_ASSERT_EQUAL(3,path->at(2));
    TEST_ASSERT_EQUAL(5,path->at(3));

    delete path;

    std::cerr << "\n--- Plotting route: 1-4 ---\n\n";
    path = map.findPath(1,4, NULL);

    TEST_ASSERT_EQUAL(1,path->at(0));
    TEST_ASSERT_EQUAL(2,path->at(1));
    TEST_ASSERT_EQUAL(4,path->at(2));

    delete path;

}

int main(int argc, char **argv) {
    UNITY_BEGIN();

    RUN_TEST(test_Pathfinding);

    UNITY_END();
    
    return 0;
}
