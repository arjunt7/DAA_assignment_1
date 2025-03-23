# DAA_assignment_1

website link : https://arjunt7.github.io/DAA_assignment_1/

********** GROUP INFORMATION **********

S. No.		Member				ID
1.		Arjun Tyagi			2021B3A72272H
2.		Kush Gadia			2021B4A72386H
3.		Divya Ramanan			2022A7PS2009H
4. 		Taanvi Dande			2022A7PS2007H
5.		Mahima Pragnya Bhattaram	2022A7PS2018H

----------X----------X----------

********** EXECUTION INSTRUCTIONS **********

On the Ubuntu terminal, write the following command to increase stack size: 
ulimit -s unlimited
This would ensure that the codes do not abruptly terminate due to too many recursive calls.

Install g++ compiler (if not already installed) using the following commands in the terminal: 
sudo apt update
sudo apt build-essential

(Recommended, but not necessary) Also install the GDB compiler using the following command in the the terminal:
sudo apt-get install gdb

In this file, 
First algorithm refers to the algorithm explained by the procedure CLIQUE on page 31 of the paper titled 'The worst-case time complexity for generating all maximal cliques and computational experiments'
Second algorithm refers to the algorithm shown in figure 4 of the paper titled 'Listing All Maximal Cliques in Sparse Graphs in Near-Optimal Time'
Third algorithm refers to the algorithm explained by the procedure CLIQUE on pages 220-222 of the paper titled 'Arboricity and Subgraph Listing Algorithms'

In general, we recommend having all of the following in the same directory:
01. Raw txt file of the Email-Enron dataset
02. Raw txt file of the as-skitter dataset
03. Raw txt file of the Wiki-Vote dataset
04. Preprocessed file of the Email-Enron dataset
05. Preprocessed file of the as-skitter dataset
06. Preprocessed file of the Wiki-Vote dataset
07. helper.h
08. convert.cpp
09. renumber.cpp
10. q1.cpp file
11. q2.cpp file
12. q3.cpp file
Exact dependecies and details about preprocessing are mentioned in the following section. 


Executing the code for the first algorithm -

Before executing the code for the first algorithm, ensure that the raw txt file of the dataset that you want to run it on and the file helper.h is present in the same directory as the code. 

For executing the code, run the following commands in the terminal (if you have installed GDB):
g++ -g -O2 q1.cpp -o q1
gdb ./q1
(The '-O2' is for level 2 optimization. We recommend running the first algorithm with level 2 optimization as it makes execution faster, but not as fast as to make it difficult to see the difference between the first and the third algorithm. You may choose to run it using level 1 or level 3 optimization by writing '-O1' or 'O3' respectively, or even without any optimization by omitting that part too.)
After the '(gdb)' prompt, enter 'run'. When asked if you want to enable debuginfod for the session, enter 'n'.

If you have not installed GDB, run the following commands in the terminal to execute the code for the first algorithm:
g++ q1.cpp -o q1
./q1


Executing the code for the second algorithm -

Before executing the code for the first algorithm, ensure that the raw txt file of the dataset that you want to run it on is present in the same directory as the code. 

For executing the code, run the following commands in the terminal (if you have installed GDB):
g++ -g -O2 q2.cpp -o q2
gdb ./q2
(Here again, we recommend using level 2 optimization for the same reasons, but you are free to choose a different (or no) optimiation too.)
In the (gdb) prompt, type 'run'. When asked is you want to enable debuginfod for the session, enter 'n'.

If you have not installed GDB, run the following commands in the terminal to execute the code for the second algorithm:
g++ q2.cpp -o q2
./q2


Executing the code for the third algorithm -

Before executing the code for the third algorithm, ensure that the preprocessed txt file of the dataset that you want to run it on is present in the same directory as the code. 

For executing the code, run the following commands in the terminal (if you have installed GDB):
g++ -g -O2 q3.cpp -o q3
gdb ./q3
(Here, we recommend running the algorithm with level 2 or level 3 optimization - level 2 so that it gives a more genuine comparison against the other two algorithms, or level 3 because it is faster.)
In the (gdb) prompt, type 'run'. When asked is you want to enable debuginfod for the session, enter 'n'.

If you have not installed GDB, run the following commands in the terminal to execute the code for the third algorithm:
g++ q3.cpp -o q3
./q3

----------X----------X----------

********** DATASET PREPARATION **********

For executing the codes of the first and second algorithms, no separate preprocesing of the datasets is necessary. For the first algorithm code, however, the helper.h file helps in reading the data seamlessly from the raw txt files. Hence, the line #include<helper.h> has been mentioned in the code for the first algorithm. The second algorithm code does not need this header file though. For the Email-Enron and as-skitter datasets, (where input is such that for all edges a to b, there also exists an edge b to a, for all nodes a, b), you could comment out (by adding two backslashes, '//' at the start of the line) the line 'graph[to].insert(from);' to make execution faster. However, the code will still run (though slightly slower) even if this is not done.

For the third algorithm code, for the Email-Enron and as-skitter datasets, the following preprocessing is needed -
Open the raw txt file of the dataset. 
Delete the lines (at the top) of the dataset that have aphanumeric text written and save it as Email-Enron_3.txt or as-skitter_3.txt for the Email-Enron and as-skitter datasets respectively. 
After doing this, the preprocessed dataset should only contain lines that contain two numbers each representing endpoints of the edges. 
The code for the third algorithm can now be used for the preprocessed Email-Enron and as-skitter datasets respectively.

For the third algorithm code, for the Wiki-Vote dataset, the following preprocessing is needed -
Place the raw dataset and the file convert.cpp in the same directory. Then, convert.cpp compile and run using the following commands: 
g++ convert.cpp -o convert
./convert
This code converts the directed graph to an undirected graph (that is, if two edges a->b and b->a exist in the graph, it discards the b->a edge, and retains only the a->b edge, which would be considered as an undirected edge). Running this would generate an intermediate file named Wiki-Vote_31.txt. 
Place this intermediate file in the same directory as the file renumber.cpp. Then, compile and run renumber.cpp using the following commands:
g++ renumber.cpp -o renumber
./renumber
This code maps the discontinuous nodes to continuous nodes. (For example, if a graph has 5 nodes numbered 0, 1, 3, 4, and 6, they would be mapped to nodes numbered 0, 1, 2, 3, and 4 respectively.) This would generate the preprocessed file named Wiki-Vote_32.txt. 
The code for the third algorithm can now be used for the preprocessed Wiki-Vote dataset. 

----------X----------X----------

********** INDIVIDUAL CONTRIBUTIONS **********

We shall first explain how the work was structured, and then explain how each member contributed individually. 

This is how our work was structured  - 
A. We started off by inidividually reading and understanding all the three algorithms we had to implement. 
B. Next, we had a group discussion where we talked about and helped each other improve our understanding of each of the three algorithms. 
C. We then divided work amongst ourselves. 
D. We set small deadlines for portions of the work, and had online meets or calls frequently to discuss and give updates about our progress. In these meets, we also took feedback and planned the work ahead. 
E. After completion, we are now sitting down together once again to compile everything and shall submit the assignment soon.

Following are individual contributions in the divided work - 

1. Arjun Tyagi
- assisted on the implementation of the code for preprocessing the datasets
- worked on the implementation, debugging, and testing of the first algorithm
- worked on the implementation and debugging of the third algorithm
- created the front end (webpage) to host the assignment files

2. Kush Gadia
- worked on the implementation, debugging, and testing of the first algorithm
- worked on the implementation, debugging, and testing of the third algorithm
- edited and reviewed the project report
- writing the readme file

3. Divya Ramanan 
- worked on the implementation, debugging, and testing of the second algorithm
- compiled, analysed, and documented all obserservations after running all the three codes on all the three datasets
- plotted the histograms for the observations
- drafted, compiled, and edited the project report

4. Taanvi Dande
- worked on the implementation of the code for preprocessing the datasets 
- worked on the implementation, debugging, and testing of the second algorithm
- compiled, analysed, and documented all obserservations after running all the three codes on all the three datasets
- assisted in plotting the histograms for the observations
- assisted in drafting and compiling the project report

5. Mahima Pragnya Bhattaram
- worked on the testing of the first algorithm
- worked on the debugging and testing of the second algorithm
- worked on the implementation and testing of the third algorithm 
- drafted, compiled and edited the project report

----------X----------X----------

********** WEBPAGE LINK **********

Below is the link to the webpage, where the assignment has been hosted:
<LINK>

----------X----------X----------
----------X----------X----------




