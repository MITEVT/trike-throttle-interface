#Map vlaues based on a second order function

import FirstOrder, math

def map_values(minVal, maxVal, count, round = 0, curvature = 1.0):
	rangeMod = math.sqrt((maxVal - minVal)/abs(curvature))

	if curvature == 0:
		return FirstOrder.map_values(minVal, maxVal, count)
	elif curvature > 0:
		centerX = 0.0
		centerY = 0.0
	else:
		centerX = rangeMod
		centerY = minVal

	rangeMod /= count
	if (not round):
		list = [(abs(curvature) * (i*rangeMod - centerX)**2 + centerY) for i in range(count + 1)];
	else:
		list = [(int(abs(curvature) * (i*rangeMod - centerX)**2 + centerY)) for i in range(count + 1)];

	if curvature < 0:
		list.reverse()
	return list