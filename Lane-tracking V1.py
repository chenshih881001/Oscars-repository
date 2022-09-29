import cv2 
import numpy as np
import matplotlib.pyplot as plt

def canny(image):
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY )
    blur = cv2.GaussianBlur(gray, (5, 5), 0)
    canny = cv2.Canny(blur, 50, 150)
    return canny

def Mask(image):
    height = image.shape[0]                                         #identify the height of the image
    polygons = np.array([[(500,height),(1250,height),(900,450)]])   #point out the vertexes in the region of interest
    mask = np.zeros_like(image)                                     #generate an array of 0 with the same shape and type as a given image
    cv2.fillPoly(mask, polygons, 255)                               #fill the region of interest with white color
    masked_image = cv2.bitwise_and(image, mask)                     #carry out bitwise addtion of the image and the mask                     
    return masked_image  
                                               #return the cropped image
def coordinates(image,line_parameters):
    slope , intercept = line_parameters
    y1 = image.shape[0]
    y2 = int(y1*(3/5))
    x1 = int((y1-intercept)/slope)
    x2 = int((y2-intercept)/slope)
    return np.array([x1,y1,x2,y2])

def average_slope_intercept(image, lines):
    left_edge = []
    right_edge = []
    for line in lines:
        x1, y1, x2, y2 = lines.reshape(4)                     #turn a 2D array into a 1D array
        parameters = np.polyfit((x1,x2), (y1,y2), 1)         #
        slope = parameters[0]
        intercept = parameters[1]
        if slope < 0:
            left_edge.append((slope, intercept))
        else:
            right_edge.append((slope, intercept))
    left_lane_avg = int(np.average(left_edge, axis=0))
    right_lane_avg = int(np.average(right_edge, axis=0))
    left_line = coordinates(image,left_lane_avg)
    right_line = coordinates(image, right_lane_avg)
    return np.array([left_line,right_line])



def LineDisplay(image,lines):
    line_image = np.zeros_like(image)
    if lines is not None:
        for line in lines:
            x1,y1,x2,y2 = line.reshape(4)
            cv2.line(line_image,(x1,y1),(x2,y2),(255,0,0),5)
    return line_image


 
image = cv2.imread('test_img.png')   #read the raw image
lane_image = np.copy(image)            #create a copy of the raw image
canny_img = canny(image)               #generate a canny verion of the original image
cropped_image = Mask(canny_img)        #crop out the region of interest
lines = cv2.HoughLinesP(cropped_image,2, np.pi/180, 100, np.array([]),minLineLength=40, maxLineGap=5) #produce lines

averaged_line = average_slope_intercept(lane_image, lines)  #obtain the average of the existing lines 

Line_img = LineDisplay(lane_image, averaged_line)
Intergrated_img = cv2.addWeighted(Line_img, 0.8, image, 1, 1)
cv2.imshow("result", Intergrated_img)
cv2.waitKey(0)