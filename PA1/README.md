CSCE-420 Assignment-1
Author: Harshank Patel
UIN: 527009145

Explanation of how the program works:

Step 1: Make sure you have gcc or g++ installed in your computer (OS independent)
Step 2: Clone repo and check if you are in the right folder
Step 3: Make sure you have the .bwp files in the same directory as the blockwords.cpp file
Step 4: Type 'make' in your terminal to compile the program
Step 5: Now type './blocksworld -f probA03.bwp -i 100000 -a' or './blocksworld -f probA03.bwp -i 100000' to run the program


Examples & explanation of the flags are:

./blocksworld -f probA03.bwp -i 100000 -h 1 -b
./blocksworld -f probA03.bwp -i 100000 -h 2 -b
             .
             .
             .
./blocksworld -f probA03.bwp -i 100000 -h 4 -b

-f = File to be read
-i = Iterations
-h = Which heuristic to run (Number 1,2,3 or 4 MANDATORY ARGUMENTS OTHERWISE IT WILL RUN THE DEFAULT!)
-b = To turn on the BFS and A* both algorithms in this run!

./blocksworld -f probA03.bwp -i 100000 -b
-f = File to be read
-i = Iterations
(NOTE: If you skip the -a, it will only run the A* algorithm by default i.e. Best-Algorithm)



Types of heuristic functions I have used:
1. DEFAULT: heuristic which is using the (incorrect blocks in the state) + (sum of distance of each blocks currently from the destination state i.e. Distance Formula) + (depth) + (estimate of min blocks required to move)
2. (sum of distance of each blocks currently from the destination state i.e. Distance Formula) + (depth of node in the search tree)
3. (count how many incorrect blocks in the state) + (depth in the tree)
4. ALL THREE COMBINED : (incorrect blocks in the state) + (depth in the tree) + (sum of distance of each blocks currently from the destination state)