class GreedyRobot:
    def __init__(self): #Creates two points and prints off the number of paths by calling search.
        robotPosition = Point()
        goal = Point()
        print("Number of Paths: " + str(self.search(robotPosition.getX(),robotPosition.getY(), "", goal.getX(), goal.getY())))

    def search(self,xPosition, yPosition, path, goalX, goalY): #Prints the paths and returns the # of paths
        returnValue = 0
        if(yPosition > goalY): #Go South
            returnValue += self.search(xPosition, yPosition-1, str(path)+str("S"), goalX, goalY)
        elif(yPosition < goalY): #Go North
            returnValue += self.search(xPosition, yPosition+1, str(path)+str("N"), goalX, goalY)
        if(xPosition > goalX): #Go West
            returnValue += self.search(xPosition-1, yPosition, str(path)+str("W"), goalX, goalY)
        elif(xPosition < goalX): #Go East  
            returnValue += self.search(xPosition+1, yPosition, str(path)+str("E"), goalX, goalY)
        if(returnValue == 0): #Base case.
                print(path)
                returnValue = 1   
        return returnValue                
        
class Point: #Saves the starting point position of the robot and the goal.
    def __init__(self):
        self.__locationX = int(input("X Position"))
        self.__locationY = int(input("Y Position"))

    __locationX: int
    __locationY: int
    
    def getX(self): #Gets X
        return self.__locationX
    
    def getY(self): #Gets Y
        return self.__locationY


GreedyRobot()