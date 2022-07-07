import java.util.*;
import java.io.*;

class Main {
    public static void main(String[] args) {
        Scanner myObj = new Scanner(System.in);  // Create a Scanner object
        System.out.print("Enter number of Queens (n) : ");
        Integer num_queens = myObj.nextInt();  // Read user input
        System.out.println("Generating Model for " + num_queens + " queens!");  // Output user input

        StringBuilder output_string = new StringBuilder();
        ArrayList<ArrayList<Integer>> board = new ArrayList<ArrayList<Integer>>();
        for(int i = 0; i < num_queens; i++){
            output_string.append("# ");
            for(int j = 0; j < num_queens; j++){
                output_string.append("Q"+(i+1)+(j+1)+" ");
            }
            output_string.append("\n");
        }

        output_string.append("\n");
        output_string.append("\n");
        output_string.append("\n");

        //Atleast one queen per row and column!
        output_string.append("# One Queen Per Row\n");
        output_string.append("\n");
        for(int i = 0; i < num_queens; i++){
            for(int j = 0; j < num_queens; j++){
                output_string.append("Q"+(i+1)+(j+1)+" ");
            }
            output_string.append("\n");
        }

        output_string.append("\n");
        output_string.append("\n");
        output_string.append("\n");

        //Atleast one queen per row and column!
        output_string.append("# One Queen Per Col\n");
        output_string.append("\n");
        for(int i = 0; i < num_queens; i++){
            for(int j = 0; j < num_queens; j++){
                output_string.append("Q"+(j+1)+(i+1)+" ");
            }
            output_string.append("\n");
        }
        
        output_string.append("\n");
        output_string.append("\n");
        output_string.append("\n");


        output_string.append("# Atmost One Queen Per Row\n");
        output_string.append("\n");
        for(int i = 0; i < num_queens; i++){
            for(int j = 0; j < num_queens; j++){
                for(int k = 0; k < num_queens; k++){
                    if(k >= j){
                        continue;
                    }
                    output_string.append("-Q"+(i+1)+(k+1));
                    output_string.append(" -Q"+(i+1)+(j+1));
                    output_string.append("\n");
                }   
            }
            output_string.append("\n");
        }

        output_string.append("\n");
        output_string.append("\n");
        output_string.append("\n");


        output_string.append("# Atmost One Queen Per Col\n");
        output_string.append("\n");
        for(int i = 0; i < num_queens; i++){
            for(int j = 0; j < num_queens; j++){
                for(int k = 0; k < num_queens; k++){
                    if(k >= j){
                        continue;
                    }
                    output_string.append("-Q"+(k+1)+(i+1));
                    output_string.append(" -Q"+(j+1)+(i+1));
                    output_string.append("\n");
                }   
            }
            output_string.append("\n");
        }


        output_string.append("\n");
        output_string.append("\n");
        output_string.append("\n");

        output_string.append("# Atmost One Queen Per Left Diagonal\n");
        output_string.append("\n");
        for(int i = 0; i < num_queens; i++){
            for(int j = 0; j < num_queens; j++){
                for(int k = j-1; k > -1; k--){
                    if(j >= num_queens){
                        break;
                    }
                    if (i+(j-k) >= num_queens){
                        break;
                    }
                    output_string.append("-Q"+(i+1)+(j+1));
                    output_string.append(" -Q"+(i+(j-k)+1)+(k+1));
                    output_string.append("\n");
                }   
            }
            output_string.append("\n");
        }

        output_string.append("# Atmost One Queen Per Right Diagonal\n");
        output_string.append("\n");
        for(int i = 0; i < num_queens; i++){
            for(int j = 0; j < num_queens; j++){
                for(int k = j+1; k < num_queens; k++){
                    if (i + (k-j) >= num_queens){
                        break;
                    }
                    output_string.append("-Q"+(i+1)+(j+1));
                    output_string.append(" -Q"+(i+(k-j)+1)+(k+1));
                    output_string.append("\n");
                }   
            }
            output_string.append("\n");
        }
        try {
            FileWriter myWriter = new FileWriter(""+num_queens+"_Queens.cnf");
            myWriter.write(output_string.toString());
            myWriter.close();
            System.out.println("Successfully wrote to the file.");
        }
        catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }
}