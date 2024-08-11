from typing import Type


class catalan:
    def __init__(self,input): #Runs the function when the class is called
        try:
            check_int = isinstance(input,int)
            if(check_int):
                print(catalan.catalanCalculation(input)) #Prints out the result
            else:
                raise TypeError()
        except TypeError:
            print("Invalid input, please input an integer.")

    def catalanCalculation(input):
        res = 0 #Saved result
        if (input <= 1): #Base case
            res = 1 
        else:
            for i in range(input): #Go through the for loop
                res = res + catalan.catalanCalculation(i) * catalan.catalanCalculation(input-i-1) #Catalan Formula
        return res

#Driver series
catalan(4)
catalan(5)
catalan(1)
catalan(3)
catalan(-1)
catalan(10)
catalan("e")
catalan(5.3)
