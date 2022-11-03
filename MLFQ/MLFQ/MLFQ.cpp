#include <iostream>
#include <queue>
#include <list>
#include <process.h>
#define l1size 15
#define l2size 15
#define l3size 15
using namespace std; 


/*
This will be the main strucutre that will be entered as an input 
into our List data structure. The data structure is comprised of the following:
1. pid -which is the process id value 
2.process_length how long something will take 
3. IOreq- an optional paramter that allows a process to make an IO request 
4. Default bool operator 


*/
struct Process {

    int pid;
    int process_length;
    bool IOReq = false;

   bool operator==(const Process& other) const {
        return pid == other.pid && process_length == other.process_length;
    }

};

/*
This function purpose is to kill a proccess that is running. The point of this process 
is to simulate a scenario where a process is malicous so we need to end it. This function 
will iterate through all three lists and end when the pid is found.
We just simulate one round in this example. 
Nothing will happen if we enter a wrong pid number.

*/
void kill_process(list<Process>& List1, list<Process>& List2, list<Process>& List3, int pid) {

    
    list <Process> :: iterator it =  List1.begin();
    
  
    bool found = false;
    for (it; it != List1.end(); ++it) {
        Process temp = *it;
        if (temp.pid == pid) {
            found= true;
            break;

        } 
    }
    if (found) {
       List1.erase(it);
    }

    list <Process> ::iterator it2 = List1.begin();


    //This is for testing
    for (it2; it2 != List1.end(); ++it2) {
        
        printf("%d\n", it2->pid);

    }

    

    

}

/*
This will boost the second queue to the top. This process will pop all front values in Q2 
and append it to the end of the Q1.
*/
void boost2(list<Process>& List1, list<Process>& List2) {

    while (List1.size() < l1size && !List2.empty()) {
        Process temprocess = List2.front();
        List2.pop_front();
        List1.push_back(temprocess);
    }

}

/*
This will boost the second queue to the top. This process will pop all front values in Q3
and append it to the end of the Q1.
*/
void boost3(list<Process>& List1, list<Process>& List3) {

    while (List1.size() < l1size && !List3.empty()) {
        Process temprocess2 = List3.front();
        List3.pop_front();
        List1.push_back(temprocess2);
    }

}


/*
This function will run the MLFQ. The design of the function is it starts with Queue and checks to see 
if Q1 is empty if it not it will pop from Queue 1 and run that process. IF Q1 is empty it will go Q2, then Q3 if Q2 is empty.
*/
void run(list<Process>& List1, list<Process>& List2, list<Process>& List3) {
    
    //This is the counter that will manage how long a process has ran for.
    int counter = 0; 
    
    //This is the counter for Q2 and Q3. After a certain time this amounts will be boosted to the end of Q1.
    static int globalcounter2 = 0; 
    static int globalcounter3 = 0;


    //This function will run until all lists are empty.
    while (!List1.empty() || !List2.empty() || !List3.empty() && !List2.empty()) {
        /*
        //This code is implemented to see if a person wants to kill a program
        string inputer; 
        cout << "do you wish to run a kill program enter 'yes'\n";
        cin >> inputer;
        if (inputer == "yes") {
            int pid;
            cout << "enter a PID number: '\n";
            cin >> pid;
            
            kill_process(List1, List2, List3, pid);
        
        }*/

        //This is the function to see if we should boost from Q2 to Q1. It checks to see if there is any size 
        //left in Queue 1, and checks to see if the static is larger than 35, which is an artifical time limit
        if (List1.size() < l1size && globalcounter2 > 35 && !List2.empty()) {
            printf("This boost2 was ran\n");
            boost2(List1, List2);
            globalcounter2 = 0;
           

        }

        //This is the function to see if we should boost from Q3 to Q1. It checks to see if there is any size 
        //left in Queue 1, and checks to see if the static is larger than 40, which is an artifical time limit
        else if (List1.size() < l1size && globalcounter3 > 40 && !List3.empty()) {
            printf("This boost3 was ran\n");
            boost3(List1, List3);
            globalcounter3 = 0;
            
        
        }
        
        //This part of the function will pop from Q1. If the process runs longer than 8 seconds it will be pushed to Q2 or Q3 
        //depending on if Q2 is full or not 
        if (!List1.empty()) {
            Process newprocess = List1.front();
            //printf("test newprocess %d\n", newprocess.process_length);
            List1.pop_front();
            while (newprocess.process_length > 0 && counter < 8) {
                counter++;
                globalcounter2++;
                globalcounter3++;
                newprocess.process_length--;
            }

            //printf("test newprocess %d is %d and counter %d\n", newprocess.pid, newprocess.process_length, counter);
            if (newprocess.process_length > 0) {
                if (newprocess.IOReq == true) {
                    List1.push_back(newprocess);
                    printf("Process %d was moved to Q1 from Q1 since it was an IO request\n", newprocess.pid);
                }

                else if (List2.size() >= l2size) {
                    if (List3.size() >= l3size) {
                        Process processtemp = List2.front();
                        List2.pop_front();
                        List1.push_back(processtemp);
                        List2.push_back(newprocess);
                        printf("Process %d was moved to Q3 from Q1 since Q2 was full\n", newprocess.pid);

                    }
                    else if (List3.size() <= l3size) { 
                        List3.push_back(newprocess); 
                        printf("Process %d was moved to Q3 from Q1\n", newprocess.pid);
                    }

                }
                else {
                    List2.push_back(newprocess);
                    printf("Process %d was moved to Q2 from Q1\n", newprocess.pid);
                }
            }
            else {
                printf("Process %d was finished in Q1\n", newprocess.pid);
            }


        }
        else if (!List2.empty()) {
            Process newprocess = List2.front();
            List2.pop_front();
            while (newprocess.process_length > 0 && counter < 16) {
                counter++;
                globalcounter3++;
                newprocess.process_length--;
            }

            globalcounter2 = 0;

            //printf("test newprocess %d is %d and counter %d\n", newprocess.pid, newprocess.process_length, counter);

            if (newprocess.process_length > 0) {
                if (newprocess.IOReq == true) {
                    List1.push_back(newprocess);
                    printf("Process %d was moved to Q2 from Q2 since it was an IO request\n", newprocess.pid);
                }
                else if (List3.size() >= l3size) {
                    Process processtemp = List3.front();
                    List3.pop_front();
                    List2.push_back(processtemp);
                    List3.push_back(newprocess);
                    printf("Process %d was moved to Q3 from Q2 since Q3 was full\n", newprocess.pid);
                   


                }
                else { 
                    List3.push_back(newprocess);
                    printf("Process %d was moved to Q3 from Q2", newprocess.pid);
                }

            }
            else { printf("Process %d was terminated in Q2\n", newprocess.pid); }

          



        }
        //This part of the function will pop from Q3. This can be pushed up so it will be appended to the back of Q3.
        //These globalcounter will reset since we have had access to this queue already
        else if (!List3.empty()) {
            Process newprocess = List3.front();
            List3.pop_front();
            while (newprocess.process_length > 0 && counter < 24) {
                counter++;
                globalcounter2++;
                newprocess.process_length--;
            }

            globalcounter3 = 0;
            //printf("test newprocess %d is %d and counter %d\n", newprocess.pid, newprocess.process_length, counter);
            if (newprocess.process_length > 0) {
                List3.push_back(newprocess);
                printf("Process %d was moved to Q3 from Q3\n", newprocess.pid);
            }
            else {
                printf("Process %d was finished in Q3\n", newprocess.pid);
            }
        }
        else {

            cout << "All Queues are empty \n";

        }

        //Reset the counter
        counter = 0;

    }
}

//This is a process that allows the user to manually add things to the process
void add_processes( list<Process> &List1, list<Process> &List2, list<Process> &List3) {
   

    string input;
    int input1;
    int input2;
    int counter = 0;


    while (input != "q" || input != "quit") {


    cout << "please enter a process ID and length\n";
    if (input == "q" || input == "quit") {
        return;
    }
    cin >> input1;
    cin >> input2;
    Process process{input1, input2};
    if (List1.size() <=l1size) {
        
        List1.push_back(process);
        
    }
    else if (List2.size() <= l2size) {
        
        List2.push_back(process);
    }

    else if (List3.size() <= l3size) {
        
        List3.push_back(process);
    }
    else {
        cout << "Al process are full\n";
    }
    cout << "please enter any string, if not please type q or quit to continue \n";
    cin >> input;
    }

}


int main()
{
    
    //This the first test of the MLFQ
   
    
    list<Process> *List1 = new list<Process>;
    list<Process>* List2 = new list<Process>;
    list<Process>* List3 = new list<Process>;

    add_processes(*List1, *List2, *List3);
    run(*List1, *List2, *List3);


    /*

    Process process{100, 10};
    Process process2{ 101, 8 };
    Process process3{ 102, 3 };
    Process process4{ 103, 2 };
    Process process5{104, 5};
    Process process6{ 105, 18 };
    Process process7{ 106, 3 };
    Process process8{ 107, 21 };
    Process process9{ 108, 3 };
    Process process10{ 109, 3 };
    Process process11{ 110, 4 }; 

    List1->push_back(process);
    List1->push_back(process2);
    List1->push_back(process3);
    List1->push_back(process4);

    
    List2->push_back(process5);
    List2->push_back(process6);
    List2->push_back(process7);
    List2->push_back(process8);

    List3->push_back(process8);
    List3->push_back(process10);
    List3->push_back(process11); 
    
    run(*List1, *List2, *List3); */
    
    

    /*
    //This the second test for MLFQ for Boost 
    list<Process>* List1 = new list<Process>;
    list<Process>* List2 = new list<Process>;
    list<Process>* List3 = new list<Process>;

    Process process{ 100, 7 };
    Process process2{ 101, 7 };
    Process process3{ 102, 7 };
    Process process4{ 103, 7 };

    List1->push_back(process);
    List1->push_back(process2);
    List1->push_back(process3);
    List1->push_back(process4);

    run(*List1, *List2, *List3);

    Process process5{ 104, 6 };
    Process process6{ 105, 6 };
    Process process7{ 106, 6 };
    Process process8{ 107, 6 };

    Process process9{ 108, 12 };
    Process process10{ 109, 12 };

    Process process11{ 110, 7 };
    Process process12{ 111, 7 };

    List1->push_back(process5);
    List1->push_back(process6);
    List1->push_back(process7);
    List1->push_back(process8);

    List2->push_back(process9);
    List2->push_back(process10);

    List1->push_back(process11);
  



    run(*List1, *List2, *List3);
    */

    /*
    //This the third test for MLFQ for Boost3 
    list<Process>* List1 = new list<Process>;
    list<Process>* List2 = new list<Process>;
    list<Process>* List3 = new list<Process>;

    Process process{ 100, 7 };
    Process process2{ 101, 7 };
    Process process3{ 102, 7 };
    Process process4{ 103, 7 };

    List1->push_back(process);
    List1->push_back(process2);
    List1->push_back(process3);
    List1->push_back(process4);

    run(*List1, *List2, *List3);

    Process process5{ 104, 6 };
    Process process6{ 105, 7 };
    Process process7{ 106, 6 };
    Process process8{ 107, 6 };

    Process process9{ 108, 12 };
    Process process10{ 109, 12 };

    Process process11{ 110, 7 };
  

    List1->push_back(process5);
    List1->push_back(process6);
    List1->push_back(process7);
    List1->push_back(process8);

    List3->push_back(process9);
    List3->push_back(process10);

    List1->push_back(process11);

    run(*List1, *List2, *List3); */

    //This is the test for the kill process
    
    /*
    list<Process>* List1 = new list<Process>;
    list<Process>* List2 = new list<Process>;
    list<Process>* List3 = new list<Process>;

    Process process{ 100, 7 };
    Process process2{ 101, 7 };
    Process process3{ 102, 7 };
    Process process4{ 103, 7 };

    List1->push_back(process);
    List1->push_back(process2);
    List1->push_back(process3);
    List1->push_back(process4);

    run(*List1, *List2, *List3);*/ 

    //Test for IO Request 
/*
    list<Process>* List1 = new list<Process>;
    list<Process>* List2 = new list<Process>;
    list<Process>* List3 = new list<Process>;

    Process process{ 100, 10, true };
    Process process2{ 101, 7 };
    Process process3{ 102, 7 };
    Process process4{ 103, 7 };

    List1->push_back(process);
    List1->push_back(process2);
    List1->push_back(process3);
    List1->push_back(process4);

    run(*List1, *List2, *List3);*/

   
    cout << "Hello World!\n";
}


