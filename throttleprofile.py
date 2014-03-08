# throttle profiles; first order, second order, and inverted second order

import math
import numpy
import pylab as pl
from decimal import *

class ThrottleData(self, x, y):
    def __init__(self):
        self.x = x
        self.y = y
        self.xData = [0]
        self.yData = [0]
        self.throttleDict = {}
        self.throttleDict[0] = 0
        self.applyFunction() # must have the f defined before
        
    def applyFunction(self, f)
        for i in range(x):
            m = i+1
            n = f(m)
            self.xData.append(m)
            self.yData.append(n)
            self.throttleDict[m] = n
            
    def getAllValues(self):
        return [zip(xData, yData)]

    def findValues(self, args):
        # find the y value for a specific x value
        return self.throttleDict[x]

    def plotAll(self, order, color):
        pl.plot(self.xData,self.yData, color) # have color be defined
        pl.title("Throttle Profile %s order" %order)
        pl.ylabel("throttle pass")
        pl.xlabel(" ")
        pl.show

class Linear(ThrottleData):
    def __init__(self):
        ThrottleData.__init__
        self.slope = float(self.y)/self.x
        self.f = lambda k: float(k)
    
        
        
        
        
            
        
