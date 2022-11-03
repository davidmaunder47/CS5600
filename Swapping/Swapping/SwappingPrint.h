#pragma once
/*
This is the exact same code as "Swapping.h" expect the only difference is the printf and printing methods are uncommented. 

This version of the code is to illustrate how the four method for each test work. 






*/

#include <iostream>
#include <string>
#include <time.h>
#include <stdio.h>
using namespace std;

/*
* process_location is used to show where in memory the location is stored
* program name is used to identify the name of the program does not have to be unqiue since a program can have acess
* to multiple locations in main memory
* An i/o request is used to kick out a program.
*/
typedef struct program_t {

    int process_location = 0;
    string program_name;
    int process_length;
    bool i_o_request;

}program;

class memory_swap {

private:

    //program_temp is used to mimic our array. It will be placed on the heap
    //since it has to last past function calls. 
    program* temp_ram;
    //Show how big the page size is. 
    int page_size;
    //Ram size is used to allocate the size of our main memory. 
    int ram_size;

    //Tracks how many programs have been created/ 
    int program_counter;

    //Mimic a buffer between main and secondary memory.
    program* swap_space;

    //Count how many programs are on disk. 
    int disk_counter;

    //Count how many programs are on swap space. 
    int swap_space_counter;

    int time_counter;

    //Allocating our disk space on heap.
    program* disk_space2;

    /*
    *This will shift all programs in this buffer down by one.
    * We use this when we swap out programs so we dont have empty spaces in an array after we
    * swap spaces.
    */
    void moveSwapSpace() {
        int i = 0;
        if (swap_space_counter == 0) {
            return;
        }
        for (i; i < swap_space_counter; i++) {
            swap_space[i] = swap_space[i + 1];
        }

    }

    /*
   *This will shift all programs in our main memory/RAM buffer down by one.
   * We use this when we swap out programs so we dont have empty spaces in an array after we
   * swap spaces.
   */
    void moveRamSpace() {
        if (program_counter == 0) {
            return;
        }
        int i = 0;
        for (i; i < program_counter; i++) {
            temp_ram[i] = temp_ram[i + 1];
        }

    }

    /*
   *This will shift all programs in disk space down by one.
   * We use this when we swap out programs so we dont have empty spaces in an array after we
   * swap spaces.
   */
    void moveDiskSpace() {
        int i = 0;
        if (disk_counter == 0) {
            return;
        }
        for (i; i < disk_counter; i++) {
            disk_space2[i] = disk_space2[i + 1];
        }

    }

    /*
    *This is used for testing purposes to see if our program is running as intended.
    * It will print out all arrays (main, secondary and buffer).
    */
    void printEverything() {
        printf("swap_space:\n");
        for (int i = 0; i < 2; i++) {
            cout << swap_space[i].program_name << endl;
        } printf("\n");
        printf("ram space:\n");
        for (int j = 0; j < 6; j++) {
            cout << temp_ram[j].program_name << endl;

        } printf("\n");
        printf("disk_sapce:\n");
        for (int k = 0; k < 5; k++) {
            cout << disk_space2[k].program_name << endl;
        } printf("\n");
    }

    /*
    *Same as above function (for testing purposes).
    * Sometimes we just want to see only main and secondary memory
    */
    void printEverythingExceptSwap() {
        printf("ram space:\n");
        for (int j = 0; j < 6; j++) {
            cout << temp_ram[j].program_name << endl;
        } printf("\n");
        printf("disk_sapce:\n");
        for (int k = 0; k < 3; k++) {
            cout << disk_space2[k].program_name << endl;
        } printf("\n");
    }

public:
    /*
    * page size is to simulate a program/process in RAM
    * Ram is the amount of process we can fit into memory
    * program counter is used to see when RAM is full, we will need this to swap
    * disk_counter is used to see if the disk space is full or not
    * swap counter is used to see if our swap cache is full or not.
    */
    memory_swap() {

        this->page_size = sizeof(program);
        this->ram_size = this->page_size * 5;
        this->program_counter = 0;
        this->disk_counter = 0;
        this->swap_space_counter;
        this->time_counter;
        //represent the amount of programs we can fit on our array
        temp_ram = new program[6];
        swap_space = new program[2];
        //This wouldnt be malloced in real life 
        disk_space2 = new program[10];
    }
    /*
    * Program is our program structure from above.
    * bool important is used to push the program into RAM no matter what.
    * We will have two different add methods.
    * This is our first add method, this add mehtod will try to simulate the random swapping algorithm.
    */
    void add(program program_1, bool important = false) {


        if (program_1.process_length > 5 && important == true) {
            printf("this is not allowed important processes must be smaller than one page\n");
        }

        //we will keep adding to our RAM/ main memory space until its full. 
        else if (program_counter < 5) {
            program_1.process_location = program_counter;
            temp_ram[program_counter] = program_1;
            program_counter++;
            program_1.process_length = program_1.process_length - 5;

            if (program_1.process_length > 0) {
                //This is if the program is larger than one page
                //We need to allocate mutiple pages for this process 
                while (program_counter < 5 && program_1.process_length > 0) {
                    program_1.process_location = program_counter;
                    temp_ram[program_counter] = program_1;
                    program_1.process_length = program_1.process_length - 5;
                    program_counter++;
                }
                //This goes here if we have to divy up our program still after our array 
                //is maxed out. Space will go to hard disk. 
                if (program_1.process_length > 0) {
                    program_1.process_location = NULL;
                    disk_space2[disk_counter] = program_1;
                    program_1.process_length = program_1.process_length - 5;
                    disk_counter++;
                }
            }
        }
        //Add rest of the programs to disk
        else {

            if (important) {

                printEverythingExceptSwap();
                srand(time(NULL));
                int random = rand() % 5;
                program temp = temp_ram[random];
                program_1.process_location = random;
                temp_ram[random] = program_1;
                disk_space2[disk_counter] = temp;
                disk_counter++;
                printEverythingExceptSwap();


            }
            else {
                while (program_1.process_length > 0) {

                    program_1.process_location = NULL;
                    disk_space2[disk_counter] = program_1;
                    program_1.process_length = program_1.process_length - 5;
                    disk_counter++;
                }
            }

        }

    }
    /*
    * Program is our program structure from above.
    * bool important is used to push the program into RAM no matter what.
    * We will have two different add methods.
    * This is our second add method, this add method will try to simulate the last in last out swapping algorithm.
    */
    void add_back(program program_1, bool important = false) {

        if (program_1.process_length > 5 && important == true) {
            printf("this is not allowed important processes must be smaller than one page\n");
        }

        else if (program_counter < 5) {
            program_1.process_location = program_counter;
            temp_ram[program_counter] = program_1;
            program_counter++;
            program_1.process_length = program_1.process_length - 5;

            if (program_1.process_length > 0) {
                //This is if the program is larger than one page
                //We need to allocate mutiple pages for this process 
                while (program_counter < 5 && program_1.process_length > 0) {
                    program_1.process_location = program_counter;
                    temp_ram[program_counter] = program_1;
                    program_1.process_length = program_1.process_length - 5;
                    program_counter++;
                }
                //This goes here if we have to divy up our program still after our array 
                //is maxed out. Space will go to hard disk. 
                if (program_1.process_length > 0) {
                    program_1.process_location = NULL;
                    disk_space2[disk_counter] = program_1;
                    program_1.process_length = program_1.process_length - 5;
                    disk_counter++;
                }
            }
        }
        //Add rest of program to disk
        else {

            if (important) {

                printEverythingExceptSwap();
                program temp = temp_ram[program_counter];
                program_1.process_location = program_counter;
                temp_ram[program_counter] = program_1;
                disk_space2[disk_counter] = temp;
                disk_counter++;
                printEverythingExceptSwap();


            }
            else {
                while (program_1.process_length > 0) {

                    program_1.process_location = NULL;
                    disk_space2[disk_counter] = program_1;
                    program_1.process_length = program_1.process_length - 5;
                    disk_counter++;
                }
            }

        }

    }

    /*
    *This method will work on both of our programs. This program will work by checking to see if we have
    * made an IO request. If we have we will swap out this program to the buffer array and put
    *a new program into main memory until the IO request is complete.
    */
    void run() {
        cout << "start" << endl;
        printEverything();

        if (program_counter < 0) {
            printf("ram is empty process will end\n");
            return;
        }

        //SWap out the IO request to temp space. We cant issue an IO request until the program
        //is the first position in the Queue.
        else if (temp_ram[0].i_o_request == true && program_counter >= 5) {
            //We first reduce the process length by one
            temp_ram[0].process_length--;
            //IF the IO request is not done we move it to our buffer space.
            if (temp_ram[0].process_length > 0) {
                int temp_location = temp_ram[0].process_location;
                //We check to see if there is swap_space left before we allocate it.
                if (swap_space_counter < 3) {
                    swap_space[swap_space_counter] = temp_ram[0];
                    swap_space_counter++;
                    printf("moving ram and swaping out IO request\n");
                    moveRamSpace();
                    printEverything();

                    int i = 5;
                    int k = 0;
                    //We will run the next program until 5 clock ticks or until the program ends. 
                    while (i > 0)
                    {
                        if (temp_ram[0].process_length > 0) {
                            temp_ram[0].process_length--;


                        }
                        else {
                            printf("move new process in to front of RAM\n");
                            moveRamSpace();
                            printEverything();
                            if (disk_counter < 0) {
                                printf("disk is empty no more swapping\n");
                            }
                            else if (k != temp_location) {
                                //we use k since we want zero for now,
                                temp_ram[program_counter - 1] = disk_space2[k];
                                k++;
                                disk_counter--;
                            }
                            else if (k == temp_location) {
                                continue;
                            }


                        }
                        i--;
                    }
                    //We will now swap our I/O requets back to the front of main memory. 
                    program temp = temp_ram[0];
                    temp_ram[0] = swap_space[0];
                    swap_space[0] = temp;

                    cout << "swap back in old IO" << endl;
                    printEverything();
                    while (temp_ram[0].process_length > 0) {
                        temp_ram[0].process_length--;

                    }
                    temp_ram[0] = swap_space[0];
                    moveSwapSpace();
                    program_counter--;
                    int w = program_counter;
                    while (w < 6 && disk_counter > 0) {
                        temp_ram[program_counter - 1] = disk_space2[0];
                        moveDiskSpace();
                        disk_counter--;
                        program_counter++;

                    }
                    cout << "last print" << endl;
                    printEverything();

                }
                //This is for the rare case if swap space is full
                else {
                    if (disk_counter > temp_location) {
                        program temp = disk_space2[temp_ram[0].process_location];
                        disk_space2[temp_ram[0].process_location] = temp_ram[0];
                        temp_ram[0] = disk_space2[0];

                        while (temp_ram[0].process_length > 0) {
                            temp_ram[0].process_length--;
                        }
                        temp_ram[0] = disk_space2[temp_location];
                        printf("moving ram\n");

                        moveRamSpace();
                        printf("moving disk\n");
                        moveDiskSpace();


                    }
                    else {
                        disk_space2[temp_ram[0].process_location] = temp_ram[0];
                        temp_ram[0] = disk_space2[0];

                        while (temp_ram[0].process_length > 0) {
                            temp_ram[0].process_length--;
                        }
                        temp_ram[0] = disk_space2[temp_location];
                        printf("moving ram\n");
                        moveRamSpace();
                        printf("moving disk\n");
                        moveDiskSpace();

                    }

                }

            }
            else {
                moveRamSpace();
                moveDiskSpace();
                printEverything();
            }
        }

        //This is our normal FIFO policy for swapping programs in and out of memory. 
         //We will excute programs in the order they are added.
        else {
            int i = 0;
            while (temp_ram[0].process_length > 0 && i < 5) {
                temp_ram[0].process_length--;
                i++;

            }
            if (temp_ram[0].process_length > 0) {
                cout << "this is a test" << endl;
                disk_space2[disk_counter] = temp_ram[0];
                disk_counter++;
                printf("moving ram\n");
                moveRamSpace();
                temp_ram[program_counter - 1] = disk_space2[0];
                printf("moving disk\n");
                moveDiskSpace();
            }

            else {
                cout << "this is a test for second" << endl;
                printf("moving ram\n");
                moveRamSpace();
                temp_ram[program_counter - 1] = disk_space2[0];
                printf("moving disk\n");
                moveDiskSpace();
                disk_counter--;

            }
            cout << "end of run" << endl;
            printEverything();
        }
    }


};
