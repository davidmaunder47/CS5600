This program is an experiment that is designed to simulate a "loader" i.e. a software application that swaps programs in and out of Disk. The program works by swapping programs in and out of RAM with the following specifications:


   
            <li>
                Fixed RAM size. A fixed RAM size will mimic real world hardware limitations.
            </li>
            <li>
                Limited buffer/Cache (16 bytes) space between main and secondary memory to represent real world buffer storage.
            </li>
            <li>
                We will have a finite amount of disk space as well. The size of this space will be 100 bytes.
            </li>
            <li>
                Kill requests are allowed. A kill request will kick a program out of memory. 
                This request will also be sent to the front of a Queue.
                This will shift all programs back in the Queue if there is space and will kick the last added program out of memory if there is no space.
       

The experiment is designed to determine which swapping policy (random Vs. FIFO) will terminate faster when given a pre-defined set of programs to run. 
The experiment will take 8 programs with various commands and will run them 200, 400, 800 and 1600 times per experiment.
We will run four different experiments (each containing 8 programs) on the two swapping policies. 
The time taken to get through the four iterations will be plotted for each experiment. The program specifications for each experiment are listed below.

            <li> Test 1 - No I/O & no Kill requests</li>
            <li> Test 2 - Two Kill and no I/O requests </li>
            <li> Test 3 - No Kill and 2 I/O requests </li>
            <li> Test 4 - Two Kill and two I/O requests </li>

Please see the attached PDF as it includes the results of this experiment.
