#Linearly map values

def map_values(minVal, maxVal, count):
	list = []
	slope = (maxVal - minVal)/(count)
	for i in range(count + 1):
		list.append(minVal + slope * i)

	return list 