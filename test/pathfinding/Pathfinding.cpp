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

    map.map[1] = new Room("Foyer", 1);
    map.map[1]->exits[2] = new DoorPortal(11);

    map.map[2] = new Room("Hub", 2);
    map.map[2]->exits[1] = new DoorPortal(21);
    map.map[2]->exits[3] = new DoorPortal(23);
    map.map[2]->exits[4] = new DoorPortal(24);

    map.map[3] = new Room("Porch", 3);
    map.map[3]->exits[2] = new DoorPortal(32);
    map.map[3]->exits[5] = new DoorPortal(35);

    map.map[4] = new Room("SideRoom",4);
    map.map[4]->exits[2] = new DoorPortal(42);

    map.map[5] = new Room("Garden",5);
    map.map[5]->exits[4] = new DoorPortal(54);

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
