#Map vlaues based on a second order function

import FirstOrder, math

def map_values(minVal, maxVal, count, curvature = 1.0):
	rangeMod = math.sqrt((maxVal - minVal)/abs(curvature))

	if curvature == 0:
		return FirstOrder.map_values(minVal, maxVal, count)
	elif curvature > 0:
		centerX = 0.0
		centerY = 0.0
	else:
		centerX = rangeMod
		centerY = minVal

	list = []
	rangeMod /= count
	print rangeMod * count
	for i in range(count + 1):
		list.append((abs(curvature) * (i*rangeMod - centerX)**2 + centerY))

	if curvature < 0:
		list.reverse()
	return list