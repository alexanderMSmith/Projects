
/**
 * Spreadsheet File Header
 * 
 * Name: Alexander Smith
 * 
 * Description: This program creates a spreadsheet for the user to use a variety of inherent commands for the purposes 
 * manipulating the spreadsheet. These commands include inputing a value for a spot,
 * getting the sum of a collumn or row,getting the average of a collumn and row,
 * getting the average and sum of the overall spreadsheet, and quitting the 
 * program.
 * 
 * Preconditions: The user requires the use of a spreadsheet program capable of 
 * summing rows and collumns, computing averages of rows and collumns, 
 * computing te sums and averages of the whole array, and allows the user
 * to input values.
 * Assumes that the array will always have a equal amount of rows and columns.
 * 
 * Postconditions: The user is done using the spreadsheet program and wants to stop.
 * The user does this by hitting 8 when prompted to select a method.
 * At this point a spreadsheet has been created of the size specified by the code.
 */ 

import java.util.Scanner;
import java.text.DecimalFormat;


public class Spreadsheet{
        //Declaring variables as static globals is usually bad design. Do *NOT* use this strategy in future assignments.
    
    public static void main(String[] args) {
         
        /*
         * This method is called when the program is run. It handles the main menu user interface
         * and is the means to which the user calls all the other methods
         * in the program.
         */
         int size = 4; //This variable controls the size of the spreadsheets x and y axis
        double[][] spreadsheet = new double[size][size];

        
        int input;
        
        initializeSpreadsheet(spreadsheet, size);
        
        Scanner userInput = new Scanner(System.in);
        boolean stillUsing = true; //Is the user still using
       
        while(stillUsing) { //While the user is still using the program
            printSpreadsheet(spreadsheet); //Method to print spreadsheet in correct format is called
            System.out.println("(1) Input (2) Row Sum (3) Col Sum (4) Row Ave (5) Col Ave (6) Sum (7) Average (8) Quit"); //User instructions
            input = userInput.nextInt(); //Gets user input and compares it to the instructions
            int userChoice = 0; //Initialises a shared choice method for the user.
            //get the next operation from the user
            switch(input) { //Takes the users method selection.
            case 1: 
                System.out.println("Please input the x coordinate, the y coordinate, and the input value in that order. Both x and y start at 0.");
                int xInput = userInput.nextInt(); //Takes users X selection
                int yInput = userInput.nextInt(); //Takes users Y selection
                double valueInput = userInput.nextDouble(); //Takes users input value
                inputData(xInput, yInput, valueInput,spreadsheet); //Calls the input data method
                break;
            case 2: 
                System.out.println("Which row do you want to sum? Y starts at 0.");
                userChoice= userInput.nextInt(); //user chooses the row they want to sum
                System.out.println(sumRow(userChoice,spreadsheet)); //Method for summing Row is called
                break;
            
            case 3: 
                System.out.println("Which column do you want to sum? X starts at 0.");
                userChoice = userInput.nextInt(); //User chooses the column they want to sum
                System.out.println(sumCol(userChoice,spreadsheet)); //Method for summing column is called
                break;
            
            case 4: 
                System.out.println("Which row do you want to average? Y starts at 0.");
                userChoice= userInput.nextInt(); //user chooses the row they want to sum
                System.out.println(rowAve(userChoice,spreadsheet)); //Method for summing Row is called
                break;
            case 5: 
                System.out.println("Which column do you want to average? X starts at 0.");
                userChoice= userInput.nextInt(); //user chooses the row they want to sum
                System.out.println(colAve(userChoice,spreadsheet)); //Method for summing Row is called
                break;
            case 6:
                System.out.println("The total is: " +sumTotal(spreadsheet));
                break;
            case 7: 
                System.out.println("The total is: " +average(size, spreadsheet));
                break;
            case 8:
                System.out.println("Good bye!");
		System.exit(0);
		break;
            
            default: //Gets called if the user used the program improperly
               System.out.println("Unrecognized command. Please try again!");
               break; //Resets the loop to ask a different input from the user.
            }
        }   
    }
   
    public static void initializeSpreadsheet(double[][] spreadsheet, int size){
            //todo: this method is called anytime the size global variable is changed, so you can rebuild the spreadsheet
            /*
             * This method initialisses the spreadsheet and is capable of resizing it
             * if the size global variable is changed. Additionally it wlil
             * transplant information from the old spreadsheet.
             */
            double[][] tempArray = new double[0][0]; //Sets a default value to check for later.
            if(spreadsheet!= null){ //if spreadsheet has a value, import the old data
                tempArray = new double[spreadsheet.length][spreadsheet.length]; //makes tempArray a copy of spreadSheet
                for(int y= 0; y < tempArray.length; y++){ //Goes along the temp array and saves old data
                    for(int x = 0; x < tempArray.length; x++){
                        tempArray[x][y] = spreadsheet[x][y]; //Saves tha data.
                    }
                }
            }
            spreadsheet = new double[size][size];//initialises spreadsheet to the new values
            if(tempArray.length > 0){ //This will only be false if tempArray is unitialised. 
                for(int y = 0; y < size; y++){ //Goes through each point of the temp array and carrys over the value from the old values
                    for(int x = 0; x < size; x++){
                        if(x<tempArray.length && y<tempArray.length){ //Chekcs to see if tempArray has a value here.
                            spreadsheet[x][y] = tempArray[x][y]; //if so carry over the value
                        }else{ 
                            spreadsheet[x][y] = 0.00; //if not input the spot with the default
                        }
                        
                    }
                }
            }else{ //If temp array is not initialised
                for(int y = 0; y < size; y++){ 
                    for(int x = 0; x < size; x++){
                        
                        spreadsheet[x][y] = 0.00; //Set every point to 0.00
                    
                        
                    }
                }
            }
    }
   
    public static void inputData(int xIndex, int yIndex, double value, double[][] spreadsheet){
        /*
         * This method goes to a position of the users choice and replaces
         * its current value with one of the users creation.
         */    
        spreadsheet[xIndex][yIndex] = value; //Replaces the value at the given point of the spreadsheet.
    }
    
    public static double sumTotal(double[][] spreadsheet) {
       /* 
       * This method adds all of the double values for the whole array
       * and returns the value.
       */
        double sum = 0;
       for(int rowCount = 0; rowCount < spreadsheet.length; rowCount++){ //Goes through every row and sums up each row together.
           sum += sumRow(rowCount, spreadsheet);
       }
        
       return sum;
    }
    
    public static double sumRow(int targetRow,double[][] spreadsheet) {
        /* 
         * This method adds all of the double values on a given row of the array
         * and returns the value.
         */
        double sum = 0;
        for(int x = 0; x < spreadsheet.length; x++){
            sum += spreadsheet[x][targetRow]; //This line adds the values at every point on the row.
        }

        return sum;
    }
    
    public static double sumCol(int targetCol, double[][] spreadsheet) {
        /* 
         * This method adds all of the double values on a given column of the array
         * and returns the value.
         */
        double sum = 0;
        for(int y = 0; y < spreadsheet.length; y++){
            sum += spreadsheet[targetCol][y]; //This line add the values at every point in the collumn to the sum. 
        }
            
        return sum;
    }
    
    public static double rowAve(int targetRow,double[][] spreadsheet) {
        /*
         * This method reuses the sumRow method to take the sum of the target
         * row and divide it by the given size global variable.
         */
        double sum = sumRow(targetRow, spreadsheet); //Uses the row sum method to find the sum
        double average = sum/spreadsheet.length; //divide by number of factors
        return average; //return the result
        
    }
    
    public static double colAve(int targetCol, double[][] spreadsheet) {
        /*
        * This method reuses the sumRow method to take the sum of the target
        * column and divide it by the given size global variable.
        */
        double sum = sumCol(targetCol, spreadsheet); //Runs sumCol to sum the collumn
        double average = sum/spreadsheet.length; //divides sum by the length of the array
        return average;
    }
    
    public static double average(int size, double[][] spreadsheet) {
        /*
        * This method reuses the sumTotal method to take the sum of the entire
        * array  and divide it by the given size global variable.
        */
        double sum = sumTotal(spreadsheet); //Runs the sumTotal() method, summing the whole array
        int factors = size*size; //The amount of factors is the the length of collums by length of rows, or size*size.
        double average = sum/factors; //Divides sum by the amount of factors of the array
        return average; 
    
    }
    

    public static void printSpreadsheet(double[][] spreadsheet) {
        /*
         * This method prints the spreadsheet in the format of [value], going
         * through each row and collumn and printing each and every value.
         */
        DecimalFormat spreadsheetFormat = new DecimalFormat("|,##0.00|"); //This special format shows trailing 0's up to 2 decimal points
    
        
        for(int y = 0; y < spreadsheet.length; y++){
            for(int x = 0; x < spreadsheet.length; x++){
                System.out.printf(spreadsheetFormat.format(spreadsheet[x][y]));
            }
            System.out.println();
        }
      
   
    }
}


