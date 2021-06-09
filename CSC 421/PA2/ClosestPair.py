import math

class Point:
	def __init__(self, x=0, y=0):
		self.x = int(x)
		self.y = int(y)

	@property
	def x(self):
		return self.__x

	@property
	def y(self):
		return self.__y

class Result:
	def __init__(self, a=Point(), b=Point(), distance=0):
		self.a = a
		self.b = b
		self.distance = float(distance)

	@property
	def a(self):
		return self.__a
	
	@property
	def b(self):
		return self.__b

	@property
	def distance(self):
		return self.__distance

def main():
	# prompt user for path to input
	try:		
		inputFilePath = raw_input("Please enter the path to the input coordinates: ")
		file = open(inputFilePath, "r")
	except:
		print("File not found. Exiting...")
		exit()

	# gather input coordinates	
	points = []	
	lineText = file.readline()
	while (lineText != ""):
		x = lineText.split(" ")[0].strip()
		y = lineText.split(" ")[1].strip()
		points.append(Point(x, y))	
		lineText = file.readline()
	
	# sort points on x coordinate
	points.sort(compareX)
	sortedX = list(points)

	# sort points on y coordinate
	points.sort(compareY)
	sortedY = list(points)

	# find closest pair of points
	result = closestPair(sortedX, sortedY)
	print("The minimum distance is:")
	print(str(result.distance) + ": " + formatPoint(result.a) + "<--->" + formatPoint(result.b))
	
def closestPair(sortedX, sortedY):
	# for small arrays, brute force the distance
	if len(sortedX) <= 3:
		return bruteForce(sortedX)
		
	# determine value of x that evenly splits the problem
	mid = int(len(sortedX) / 2)
	midX = sortedX[mid].x

	# generate left/right arrays sorted by x coordinate
	leftPointsX = sortedX[0:mid]
	rightPointsX = sortedX[mid:len(sortedX)]
	
	# generate left/right arrays sorted by y coordinate
	leftPointsY = []
	rightPointsY = []
	for p in sortedY:
		if p.x < midX:
			leftPointsY.append(p)
		else:
			rightPointsY.append(p)

	# recurse on the left and right subproblems
	leftResult = closestPair(leftPointsX, leftPointsY)
	rightResult = closestPair(rightPointsX, rightPointsY)

	# determine minimum distance from either subproblem
	minResult = leftResult
	if rightResult.distance < leftResult.distance:
		minResult = rightResult

	# gather points that lie close enough to the dividing line
	middlePoints = []
	for p in sortedY:
		if (p.x > (midX - minResult.distance)) and (p.x < (midX + minResult.distance)):
			middlePoints.append(p)

	# determine if any pair of points spanning the dividing line has a minimum distance
	for i in range(0, len(middlePoints) - 1):
		endIndex = i + 7
		if (len(middlePoints) - i) <= 7:
			endIndex = len(middlePoints) - 1

		for j in range(i + 1, endIndex + 1):
			thisDistance = getDistance(middlePoints[i], middlePoints[j])
			if thisDistance < minResult.distance:
				minResult = Result(middlePoints[i], middlePoints[j], thisDistance)
	
	return minResult

def bruteForce(points):
	rtnResult = Result()
	for i in range(0, len(points)):
		for j in range(i + 1, len(points)):
			thisResult = Result(points[i], points[j], getDistance(points[i], points[j]))
			if (rtnResult.distance == 0) or (thisResult.distance < rtnResult.distance):	
				rtnResult = thisResult
	return rtnResult

def getDistance(a, b):
	return math.sqrt(math.pow((b.x - a.x), 2) + math.pow((b.y - a.y), 2))

def formatPoint(p):
	return "(" + str(p.x) + ", " + str(p.y) + ")"

def compareX(a, b):
	if a.x > b.x:
		return 1
	elif a.x < b.x:
		return -1
	else:
		return 0

def compareY(a, b):
	if a.y > b.y:
		return 1
	elif a.y < b.y:
		return -1
	else:
		return 0

if __name__ == "__main__":
	main()	