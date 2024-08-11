
/**
 * Write a description of class Temprature here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class Temprature
{

    private double temp; //Temp as in temprature;
    private char scale; //Celsius or Fahrenheit.

    /**
     * Constructor for objects of class Temprature
     */
    public Temprature()
    {
        // initialise instance variables
        temp = 0;
        scale = 'F';
    }
    
    public Temprature(double temprature, char type){
    
        temp = temprature;
        if( type == 'C' || type == 'c'){
            scale = 'C';
        }else{
            scale = 'F';
        }
    }

    public double getTempF(){
        if(scale == 'F'){
            return temp;
        }else{
            return (9* (temp)/5) + 32;
        }
        
        
    }
    
    public double getTempC(){
        if(scale == 'C'){
            return temp;
        }else{
            return 5 * (temp-32)/9;
        }
    }
    
    public void setTemp(double newTemp){
        temp = newTemp;
    }
    
    public void setScale(char newScale){
        if( newScale == 'C' || newScale == 'c'){
            scale = 'C';
        }else{
            scale = 'F';
        }
    }
    
    public void setBoth(char newScale, double newTemp){
        if( newScale == 'C' || newScale == 'c'){
            scale = 'C';
        }else{
            scale = 'F';
        }
        temp = newTemp;
    }
    
    
    public int compare(double comparedTo){
        if(comparedTo > temp){
            return 1;
        }else if(comparedTo < temp){
            return -1;
        }else{
            return 0;
        }
    }
    
    public String toString(){
        return temp + " " + scale;
    }
    
    
}
