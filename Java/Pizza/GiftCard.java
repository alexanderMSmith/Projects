/* GiftCard.java
 * CSS161
 * 
 * Skeleton file for a basic giftcard class; useful to set, report, and
 * manage deductions
 * 
 */


public class GiftCard {
    //todo: class-level data goes here
    
    private double balance = 0.0;
    
    
    // Default constructor
    public GiftCard() { //Makes default 
        balance = 10.0;
    }
    
    // Constructor
    public GiftCard(double value) { //Takes input during construction
        if(value > 0){ //Is the input valid?
            balance = value;
        }else{
            System.out.println("Error, cannot set to a negative balance.");
        }
    }
    
    public double report(){
        System.out.println(balance); //Prints balance
        return balance;
    }
    
    public void setBalance(double newBalance){
        if(newBalance > 0){ //Checks to see if new balance is valid.
            balance = newBalance;
        }else{
            System.out.println("Error, cannot set to a negative balance.");
        }
    }

    //an example method that needs instance data to be declared first
    public void resetToZero() { 
        balance = 0;
        System.out.println("Reset to zero: " + balance + "\n");
    }
    
    public void deduct(double amount){ //Deducts from card value
        if((balance - amount) > 0){ //Is this a valid transaction?
            balance = balance - amount;
        }else{
            System.out.println("Error, cannot deduct to a negative balance.");
        }
    }
    
    public static void main(String[] args) { 
        GiftCard card1 = new GiftCard();
        
        card1.setBalance(50);
        
        System.out.print("card1 value is :");
        card1.report();
        
        GiftCard card2 = new GiftCard();
        
        card2.setBalance(100);
        System.out.print("card2 value is :");
        card2.report();
        
        
        
        System.out.println("After deducting $101, card2's new balance is :");
        card2.deduct(101);
        card2.report();
        
        card1.deduct(12.50);
        System.out.println(" After deducting $12.50, card1's new balance is :");
        card1.report();
        
        card1.resetToZero();
        card1.report();
        card2.resetToZero();
        card2.report();
        
        // User defined constructor
        GiftCard card3 = new GiftCard(5000);
        System.out.println("\nSetting the new balance to 7500.99 ");
        card3.setBalance(7500.99);
       
        
    }

}
