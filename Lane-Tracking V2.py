import cv2 as cv
import numpy as np
import matplotlib.pyplot as plt


def curve(image):
    Xs = []
    Row = image.shape[0]
    Col = image.shape[1]
    count = 0
    Xmax = 0
    Xmin = 640
    Selected_pixels = []
    Output = np.zeros_like(image)
    for col in range(Col):
        for row in range(Row):
            pixels = image[row, col]
            if (pixels > 0):
                count = count+1
                Selected_pixels.append(col)  # weird    
    
    return Selected_pixels
    
"""
    for pixels in range(count):
        if (Selected_pixels[pixels][0] > Xmax):
            Xmax = Selected_pixels[pixels][0]
        if (Selected_pixels[pixels][0] < Xmin):
            Xmin = Selected_pixels[pixels][0]


    Mid = (Xmax+Xmin)/2

    temp1 = 0
    temp2 = 0

    Output = np.zeros_like(image)##########################
    for pixels in range(count):
        if (Selected_pixels[pixels][0] <= Mid):
            Left_line.append(Selected_pixels[pixels][1])
            temp1 = temp1 + 1
        else:
            Right_line.append(Selected_pixels[pixels][1])
            # Right_line.append([Selected_pixels[pixels][0],Selected_pixels[pixels][1]])
            temp2 = temp2 + 1

    return Left_line, Right_line
"""

def Final(image,pixels):
    Output = np.zeros_like(image)
    line_param = np.polyfit(pixels, pixels, 1)
    print(np.poly1d(line_param))
    A = line_param[0]
    B = line_param[1]
 
    for x in range(640):
        y = int(A*pixels[x]+B)
        curve = cv.circle(Output, (y, x), 1, (255, 255, 255), 1)
        print("point ", x, " : ", x, y)
    print(A,B)
    return curve

    # print(A*leftPix[0]**2)   
  


Img = cv.imread("test_img1.png")
gray = cv.cvtColor(Img, cv.COLOR_BGR2GRAY )
_, Thr = cv.threshold(gray, 150, 255, cv.THRESH_BINARY)
LanePix = curve(Thr)
fitted_curve_img = Final(Thr, LanePix)

cv.imshow("Result", fitted_curve_img)
cv.imshow("Origianl", Img)
cv.waitKey(0)
