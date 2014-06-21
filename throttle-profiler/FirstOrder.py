#Linearly map values

def map_values(minVal, maxVal, count, round = 0):
	
	slope = (maxVal - minVal)/(count)
	if not round:
		list = [minVal + slope * i for i in range(count + 1)]
	else:
		list = [int(minVal + slope * i) for i in range(count + 1)]
	return list 