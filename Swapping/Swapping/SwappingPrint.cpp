#include "SwappingPrint.h"
#include <forward_list>
#include <array>



/*

This file is almost identical to "Swapping.cpp" 
except it is just running the print version of "Swapping.h" and header. I.e it is not showing the time to complete 
the program. Since 1600 iterations with a bunch of prints will take to long to run, we will only do one iteration for each test.

To see the speed test run "swapping.cpp"

*/

//First test is no I/O and no Kill requests.
void test() {
    program program1 = { 0, "something", 3, false };
    program program2 = { 0, "something2", 3, false };
    program program3 = { 0, "something3", 3, false };
    program program4 = { 0, "something4", 3, false };
    program program5 = { 0, "something5", 3, false };
    program program6 = { 0, "something6", 3, false };
    program program7 = { 0, "something7", 3, false };

    memory_swap test1 = memory_swap();
    test1.add(program1, false);
    test1.add(program2, false);
    test1.add(program3, false);
    test1.add(program4, false);
    test1.add(program5, false);
    test1.add(program6, false);
    test1.add(program7, false);

    test1.run();
}

//Second test is no I/O but two Kill Requests
void test2() {

    program program1 = { 0, "something", 3, false };
    program program2 = { 0, "something2", 3, false };
    program program3 = { 0, "something3", 3, false };
    program program4 = { 0, "something4", 3, false };
    program program5 = { 0, "something5", 3, false };
    program program6 = { 0, "something6", 3, false };
    program program7 = { 0, "something7", 3, false };

    memory_swap test1 = memory_swap();
    test1.add(program1, false);
    test1.add(program2, true);
    test1.add(program3, false);
    test1.add(program4, true);
    test1.add(program5, false);
    test1.add(program6, false);
    test1.add(program7, false);

    test1.run();

}


//Third test is two I/O and no kill requests
void test3() {

    program program1 = { 0, "something", 3, true };
    program program2 = { 0, "something2", 3, false };
    program program3 = { 0, "something3", 3, false };
    program program4 = { 0, "something4", 3, false };
    program program5 = { 0, "something5", 3, true };
    program program6 = { 0, "something6", 3, false };
    program program7 = { 0, "something7", 3, false };

    memory_swap test1 = memory_swap();
    test1.add(program1, false);
    test1.add(program2, false);
    test1.add(program3, false);
    test1.add(program4, false);
    test1.add(program5, false);
    test1.add(program6, false);
    test1.add(program7, false);

    test1.run();

}

//Last test is two IO and two Kill requests.
void test4() {

    program program1 = { 0, "something", 8, true };
    program program2 = { 0, "something2", 3, false };
    program program3 = { 0, "something3", 3, false };
    program program4 = { 0, "something4", 3, false };
    program program5 = { 0, "something5", 3, true };
    program program6 = { 0, "something6", 3, false };
    program program7 = { 0, "something7", 3, false };

    memory_swap test1 = memory_swap();
    test1.add(program1, false);
    test1.add(program2, true);
    test1.add(program3, false);
    test1.add(program4, true);
    test1.add(program5, false);
    test1.add(program6, false);
    test1.add(program7, false);

    test1.run();

}

//The next four tests are the same as the above tests but with the "add_back" method.
void test_back() {
    program program1 = { 0, "something", 3, false };
    program program2 = { 0, "something2", 3, false };
    program program3 = { 0, "something3", 3, false };
    program program4 = { 0, "something4", 3, false };
    program program5 = { 0, "something5", 3, false };
    program program6 = { 0, "something6", 3, false };
    program program7 = { 0, "something7", 3, false };

    memory_swap test1 = memory_swap();
    test1.add_back(program1, false);
    test1.add_back(program2, false);
    test1.add_back(program3, false);
    test1.add_back(program4, false);
    test1.add_back(program5, false);
    test1.add_back(program6, false);
    test1.add_back(program7, false);

    test1.run();
}

void test2_back() {

    program program1 = { 0, "something", 3, false };
    program program2 = { 0, "something2", 3, false };
    program program3 = { 0, "something3", 3, false };
    program program4 = { 0, "something4", 3, false };
    program program5 = { 0, "something5", 3, false };
    program program6 = { 0, "something6", 3, false };
    program program7 = { 0, "something7", 3, false };

    memory_swap test1 = memory_swap();
    test1.add_back(program1, false);
    test1.add_back(program2, true);
    test1.add_back(program3, false);
    test1.add_back(program4, true);
    test1.add_back(program5, false);
    test1.add_back(program6, false);
    test1.add_back(program7, false);

    test1.run();

}



void test3_back() {

    program program1 = { 0, "something", 3, true };
    program program2 = { 0, "something2", 3, false };
    program program3 = { 0, "something3", 3, false };
    program program4 = { 0, "something4", 3, false };
    program program5 = { 0, "something5", 3, true };
    program program6 = { 0, "something6", 3, false };
    program program7 = { 0, "something7", 3, false };

    memory_swap test1 = memory_swap();
    test1.add_back(program1, false);
    test1.add_back(program2, false);
    test1.add_back(program3, false);
    test1.add_back(program4, false);
    test1.add_back(program5, false);
    test1.add_back(program6, false);
    test1.add_back(program7, false);

    test1.run();

}

void test4_back() {

    program program1 = { 0, "something", 8, true };
    program program2 = { 0, "something2", 3, false };
    program program3 = { 0, "something3", 3, false };
    program program4 = { 0, "something4", 3, false };
    program program5 = { 0, "something5", 3, true };
    program program6 = { 0, "something6", 3, false };
    program program7 = { 0, "something7", 3, false };

    memory_swap test1 = memory_swap();
    test1.add_back(program1, false);
    test1.add_back(program2, true);
    test1.add_back(program3, true);
    test1.add_back(program4, false);
    test1.add_back(program5, false);
    test1.add_back(program6, false);
    test1.add_back(program7, false);

    test1.run();

}
/*
 *This function is used to run our tests.
 * We will all four tests for the two different swapping functions and time them.
 */
int main()
{
    test1();
    //test2();
    //test3();
    //test4();

    //test_back();
    //test2_back();
    //test3_back();
    //test4_back();


}
