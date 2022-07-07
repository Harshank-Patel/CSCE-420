README.md

Step 0: Clone the repo and get inside the folder and have GCC/G++ installed in your compuer! (obvious step)
Step 1: Type "make" in the terminal to compile the program
Step 2: Type "./ttt" to run the program
Step 3: Now choose the following options:
    ttt - to start a game (you cannot skip this step because otherwise the game wont start at all)
    choose [X or O] - choose function invokes the AI's algorithm to run the program and picks the best possible move!
    move [X or O] [A or B or C] [0 or 1 or 2] - this option will move the piece X or O into the designated location. (There is no boundry check, so you can get an runtime error if youo go outside 3x3 Grid space that was given to us by professor)
    pruning - turns pruning on or off (like a toggle switch)

Sample Run (without Pruning):
make
./ttt
>ttt
>choose X
>choose O
.
.

Sample Run (with Pruning):
make
./ttt
>tttt
>move X A 0
>choose O
.
.

Results:
There is a Transcript.txt file attached in the directory for your reference. Thanks!

Please email harshank.patel@tamu.edu if you have troubble running the program!
