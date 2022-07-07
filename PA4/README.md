Harshank Patel
PA4 - DPLL

How to run it:

Step-1: Clone this repo
Step-2: Go to the directory via your terminal
Step-3: Run 'make' command in your terminal
Step-4: 
    Run './dpll <filename> -UCH' to run WITHOUT UCH
    Run './dpll <filename> -UCH' to run WITH UCH
Step-5: Enjoy!

Example Format of File:
# This is how you can write comments!
-a -b c
-raining GroundWet
a
b
-GroundWet
# End of the file comments!




TO RUN AND COMPILE THE JAVA PROGRAM, RUN THE FOLLOWING COMMANDS
Step-1: dirname $(dirname $(readlink -f $(which javac)))
Step-2: Run the following command:
            javac -cp <WHAT_YOU_GOT_FROM_PREVIOUS_COMMAND> Queens_Generator.java && java -cp . Main

            EXAMPLE MINE WAS THIS : javac -cp /usr/lib/jvm/java-1.8.0-openjdk-1.8.0.322.b06-1.el7_9.x86_64 Queens_Generator.java && java -cp . Main

Step-3: See the .cnf file being printed to the directory!