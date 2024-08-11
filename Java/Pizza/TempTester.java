
/**
 * Write a description of class TempTester here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class TempTester
{
    public static void main(String[] args){
        Temprature temp = new Temprature(32.0, 'F');
        
        System.out.println(temp.toString());
        
        temp.setBoth('C', 513.0);
        
        System.out.println(temp.toString());
        
        System.out.println(temp.getTempF());
        
        temp.setScale('F');
        
        System.out.println(temp.getTempC());
        
        temp.setTemp(21421.0);
        
        System.out.println(temp.getTempF());
        
        System.out.println(temp.compare(1251));
        
    }
}
