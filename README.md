# CS201
###
-	Jugal Chapatwala: 2020CSB1082
-	Shruti Sikri: 2020CSB1128
-	Richa Pal:  2020MCB1245
 
 Our Project consists of 3 files:
 -	"matrix.c":
		In this file we have implemented matrix data structure using the Compressed Sparse Rows (CSR) representation. It has functions to create and initialise a CSR
		Matrix, Add non-zero elements to the matrix, Change values of already added elements, Delete the elements, Print the entire matrix etc.
-	"graph.c":
		In this file we have implemented a graph data structure using the adjacency matrix representation. We have chosen this representation to reduce some redundancy
		in the code. The adjancency matrix is represent in the CSR format whose functions are written in "matrix.c". It has functions to create/initialise a graph,
		Add\remove edges in a graph, PageRank function to rank vertices on the basis of importance
-	"main.c":
		This file contains the main() function. It brings together all the files files through include statements and displays the PageRank functionality.

### Compilation 
To compile:
```
gcc main.c -o PageRank
```
To run:
```
./PageRank
```

### Input Format
Write the input in a file and name it "input.txt". Our programs reads its input from "input.txt" and creates an output file "output.txt"
It takes a graph an input. The input format should be of type:
```
5
0 1
0 2
1 3
1 2
3 0
-1 -1

```
Here the first line indicates that our graph should have 5 vertices. The next lines untill -1 -1 are edge inputs. The line 1 3 tells the program that our graph should have an edge going from vertex 1 to vertex 3. The -1 -1 in the last is used to tell the program that no more edge inputs are ther to be taken.

### Output Format
For the given example input the program will output the following in a newly created "output.txt" file:
```
3 (0.006250)
1 (0.003125)
2 (0.003125)
4 (0.003125)
5 (0.000000)

0.003125 0.003125 0.006250 0.003125 0.000000 

```
The first v lines (v being the number of vertices) being the ranking of vertices on the basis of its importance as calculated by PageRank and then after an empty line the rank vector printed in a line.
