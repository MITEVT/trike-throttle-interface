# throttle profiles; first order, second order, and inverted second order

###################### TO USE THIS ####################

# Call function lin, quad or invertQuad on the x and y coordinates,
# and STORE it as a variable.
# Automatically, a list of all the x and y values of the throttle profile will appear.
# To see a plot, just use var.plot() where var is the variable you stored the function call.
# If there are a lot of numbers, you can also look for specific x and y pairs,
# by using findValue(), which takes an x value outputs corresponding y value
# or using findValueY(), which takes a y value outputs the x value of the closest-matching y value 

import math
import numpy
import pylab as pl
from decimal import *

class ThrottleProf:
    def __init__(self, xCoord, yCoord, f):
        self.x = xCoord
        self.y = yCoord
        self.xData = [0]
        self.yData = [0]
        self.throttleDict = {}
        self.throttleDict[0] = 0
        self.applyFunction(f) 
        
    def applyFunction(self, f):
        for i in range(self.x):
            func = f
            m = i+1
            n = func(m) # f defined in subclasses
            self.xData.append(m)
            self.yData.append(n)
            self.throttleDict[m] = n
            
    def getAllValues(self):
        return  zip(self.xData, self.yData)
    
    def plot(self):
        pl.plot(self.xData,self.yData)
        pl.title("Throttle Profile")
        pl.ylabel("throttle pass")
        pl.xlabel(" ")
        pl.show()

    def findValue(self, xInput):
        if xInput not in self.xData:
            print "error, that x value not in domain."
        else:
            return (xInput, self.throttleDict[xInput])

    def findValueY(self, yInput):
        def findX(thing):
            diffs = {}
            d = [] 
            print d
            for i in self.throttleDict:
                diff = float(abs(thing-self.throttleDict[i]))
                d.append(diff)
                diffs[diff] = i
            xValue = diffs[min(d)]
            return (xValue, self.throttleDict[xValue])
        return findX(yInput)           
       
def lin(xCoord, yCoord):
    slope = float(yCoord)/float(xCoord)
    f = lambda k: float(k)*slope
    linData = ThrottleProf(xCoord, yCoord, f)
    print linData.getAllValues()
    return linData

def quad(xCoord, yCoord):
    stretch = float(yCoord)/(float(xCoord)**2)
    f = lambda k: float(k)**2*stretch
    quadData = ThrottleProf(xCoord, yCoord, f)
    print quadData.getAllValues()
    return quadData

def invertQuad(xCoord, yCoord):
    up = yCoord
    right = xCoord
    stretch = -float(yCoord)/(float(xCoord)**2)
    f = lambda k: stretch*(k-right)**2 + up
    invertQuadData = ThrottleProf(xCoord, yCoord, f)
    print invertQuadData.getAllValues()
    return invertQuadData
     
    
        
        
    
        
        
        
        
            
        
