#include "Map.h"
#include "unity.h"
#include "Puzzle.h"
#include <iostream>

void dumpVector(path_t *vector) {
    std::cerr << "Here comes a vector: ";
    for (path_t::const_iterator i = vector->begin(); i != vector->end(); i++) {
        std::cerr << *i;
    }
    std::cerr << "\n";
}

void print(const char *) { }

void test_Pathfinding() {

    Map map;

    // 1---2---3---5
    //     |   |
    //     4---6

    map.newRoom("Foyer", 1,1);
    map.newRoom("Hub", 2,1);
    map.newRoom("Porch", 3,1);
    map.newRoom("SideRoom",4,1);
    map.newRoom("Garden",5,1);
    map.newRoom("Passage",6,1);

    map.newBiDoor(1,2);
    map.newBiDoor(2,4);
    map.newBiDoor(2,3,"023");    // Lockable
    map.newBiDoor(5,3);
    map.newBiDoor(4,6);
    map.newBiDoor(6,3);

    std::cerr << map.errors;

    // Simple path
    path_t path;
    map.findPath(1,2,&path,print);

    TEST_ASSERT_EQUAL(2,path.at(0));

    std::cerr << "Tested assertion\n";

    std::cerr << "Path freed\n";

    std::cerr << "\n--- Plotting route: 1-5 ---\n\n";
    map.findPath(1,5,&path,print);
    
    std::cerr << "New path found\n";

    TEST_ASSERT_EQUAL(2,path.at(0));
    TEST_ASSERT_EQUAL(3,path.at(1));
    TEST_ASSERT_EQUAL(5,path.at(2));

    std::cerr << "\n--- Plotting route: 1-4 ---\n\n";
    map.findPath(1,4,&path,print);

    TEST_ASSERT_EQUAL(2,path.at(0));
    TEST_ASSERT_EQUAL(4,path.at(1));

    std::cerr << "\n--- Testing door lock ---\n";

    // Make sure our door isn't locked (yet)
    TEST_ASSERT(! map.isLocked(2,3));

    std::cerr << "\n--- Locking door ---\n";

    // Now let's lock a door, and see if we work around it.
    map.lockDoor("023",new Puzzle(DOOR));

    std::cerr << "\n--- Testing door lock (again) ---\n";

    // Make sure our door is now locked.
    TEST_ASSERT(map.isLocked(2,3));

    // Plot new path!
    
    std::cerr << "\n--- Plotting route: 1-5 (locked door) ---\n\n";
    
    map.findPath(1,5,&path,print);
    TEST_ASSERT_EQUAL(2,path.at(0));
    TEST_ASSERT_EQUAL(4,path.at(1));
    TEST_ASSERT_EQUAL(6,path.at(2));
    TEST_ASSERT_EQUAL(3,path.at(3));
    TEST_ASSERT_EQUAL(5,path.at(4));

}

int main(int argc, char **argv) {
    UNITY_BEGIN();

    RUN_TEST(test_Pathfinding);

    UNITY_END();
    
    return 0;
}
