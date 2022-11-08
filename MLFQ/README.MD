The Multi Level Feedback Queue is setup to have three Queues (implemented as Lists). The three Queues are designed to represent the High/1, Medium/2, and Low/3 Priority
Queues that are used to hold processes before they are utilized by the CPU. The program is implemented by creating three Lists (Level 1, Level 2, Level 3)
and adding various processes to these Lists until the user stops the program.

 


The "Process" added to the MLFQ has three parameters:  

 
            int pid -which is the process id of the program</li>
            int process_length - which is how long the process will take in seconds to run</li>
            bool IOreq - which is an optional parameter that allows a progam to make an I/O request </li>


As programs are added, the user can use three functions to manipulate the program: 

       add_process - Add another process to the queue </li>
       boost 2- This will boost queue 2 to the highest Priority Queue </li>
       boost 3- This will boost queue 3 to the highest Priority Queue </li>
       kill - This will delete a process. This is used to represent a frozen process that needs to be deleted (ex. contorl+shift+esc)    </li>

Things to note about the program:

If a process is added and all three queues are full, the program will not be added unless it has high priority. If it has high priority
 the last program added to Queue 3 will be removed from the Queue.

Processes only have a finite amount of time to use the CPU. If these processes run out of time (i.e. process_length > CPU time allotted)
they will get re-added to the end of Queue 3. This process is used to simulate a real Linux based concurrent operating system.

If a program is using an I/O request the program is kicked out of the CPU while the I/O request is being completed. Once complete, the process goes back
to the front of Queue 1. This will increase CPU utilization even through it increases CPU trapping.
