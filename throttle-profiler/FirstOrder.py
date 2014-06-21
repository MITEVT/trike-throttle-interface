#Linearly map values

def map_values(minVal, maxVal, count):
	
	slope = (maxVal - minVal)/(count)
	list = [minVal + slope * i for i in range(count + 1)]
	return list 