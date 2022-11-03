#include "Swapping.h"
#include <forward_list>
#include <array>
#include <chrono>

//First test is no I/O and no Kill requests.
void test() {
    program program1 = { 0, "something", 3, false };
    program program2 = { 0, "something2", 3, false };
    program program3 = { 0, "something3", 3, false };
    program program4 = { 0, "something4", 3, false };
    program program5 = {0, "something5", 3, false};
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
    program program7 = { 0, "something7", 3, false};

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
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;
    int amount = 1;

    auto t1 = high_resolution_clock::now();
    for (int i = 0; i < amount; i++) {
        test2();
    }
    auto t2 = high_resolution_clock::now();

    /* Getting number of milliseconds as an integer. */
    auto ms_int = duration_cast<milliseconds>(t2 - t1);

    /* Getting number of milliseconds as a double. */
    duration<double, std::milli> ms_double = t2 - t1;

   

    auto t1_1 = high_resolution_clock::now();
    for (int i = 0; i < amount; i++) {
        test2_back();
    };
    auto t2_2 = high_resolution_clock::now();

    /* Getting number of milliseconds as an integer. */
    auto ms_int_2 = duration_cast<milliseconds>(t2_2 - t1_1);

    /* Getting number of milliseconds as a double. */
    duration<double, std::milli> ms_double_2 = t2_2 - t1_1;

   // std::cout << ms_int.count() << "ms\n";
    std::cout << "Random" << ms_double.count() << "ms" << endl;


    //std::cout << ms_int_2.count() << "ms\n";
    std::cout << "Back" << ms_double_2.count() << "ms" << endl;
    return 0; 
    //test2();
    //test3();
    //test4();

    //test_back();
    //test2_back();
    //test3_back();
    //test4_back();

    
}
