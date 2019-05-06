import math
#CONSTANTS
CANVAS_WIDTH = 300 #width in px
CANVAS_DIST = 3 #distance of robot base from paper (in cm)
PAPER_WIDTH = 15 #width of paper (in cm)
ARM_ONE = 9.5 #length of the first arm (in cm)
ARM_TWO = 11.5 #length of the second arm (in cm)
HEIGHT_DISPLACE = 3.125 #height of arm one from the ground (in cm)

mid_pixel = CANVAS_WIDTH / 2 #Middle of canvas
pix_cm = PAPER_WIDTH / CANVAS_WIDTH #Ratio of pixel to cm
dist_canvas = CANVAS_DIST
rad_to_deg = 180.0 / 3.14

def calculateFloorAngle(x,  y):
    global a,b,c,floorAngle
    a = abs(x - mid_pixel) * pix_cm
    b = (y * pix_cm) + dist_canvas
    c = math.sqrt(math.pow(a, 2) + math.pow(b, 2))

    temp = math.cos(a/c) * rad_to_deg
    floorAngle = round(temp)

    if x < mid_pixel:
        floorAngle = round(floorAngle)
    else:
        floorAngle = round(180 - floorAngle)
    return floorAngle

def calculateTriangleAngles( x,  y):
    global servoA, servoB, servoC, servoD, g
    servoA = calculateFloorAngle(x, y)
    g = math.sqrt(math.pow(HEIGHT_DISPLACE, 2) + math.pow(c, 2))
    aTone = math.atan(HEIGHT_DISPLACE / c) * rad_to_deg
    aTtwo = getAngleCos(g, ARM_TWO, ARM_ONE)
    servoD = 90 - round(aTone + aTtwo)
    aTthree = math.atan(c / HEIGHT_DISPLACE) * rad_to_deg
    aTfour = getAngleCos(g, ARM_ONE, ARM_TWO)
    servoB = 180 - round(aTthree + aTfour)
    servoC = 180 - round(aTfour + aTtwo)

    if servoA < 0:
        servoA = 0
    if servoB < 0:
        servoB = 0
    if servoC < 0:
        servoC = 0
    if servoD < 0:
        servoD = 0

    return (servoA, servoB, servoC, servoD)

def getAngleCos(a,  b,  c):
    result = (math.pow(a, 2) + math.pow(b, 2) - math.pow(c, 2)) / ( 2 * a * b)
    return math.acos(result) * rad_to_deg
