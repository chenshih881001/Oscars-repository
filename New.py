import cv2 as cv
import numpy as np
from matplotlib import pyplot as plt

vidcap = cv.VideoCapture('test_vid.mp4')
start, src_img = vidcap.read()

top_left = (250, 380)
top_right = (400, 380)
buttom_left = (70, 470)
buttom_right = (538, 470)
Points1 = np.float32([top_left, buttom_left, top_right, buttom_right])
Points2 = np.float32([[0, 0], [0, 480], [640, 0], [640, 480]])

def curve(image):
    Row = image.shape[0]
    Col = image.shape[1]
    count = 0
    Xmax = 0
    Xmin = 640
    Selected_pixels = []
    Left_line = []
    Right_line = []
    Output = np.zeros_like(image)
    for col in range(Col):
        for row in range(Row):
            pixels = image[row, col]
            if (pixels > 0):
                count = count+1
                Selected_pixels.append([col, row])  # weird
                curve = cv.circle(Output, (col, row), 1, (255, 255, 255), 1)
    
    
    
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

    #return Left_line, Right_line
    return curve

def Final(image, leftPix, rightPix):
    Output = np.zeros_like(image)
    # Height = image.shape[0]
    right_line_param = np.polyfit(rightPix, rightPix, 2)
    A = right_line_param[0]
    B = right_line_param[1]
    C = right_line_param[2]
    #print(A, B, C)
    for ry in rightPix:
        rx = int(A*rightPix[ry]**2+B*rightPix[ry]+C)
        right_curve = cv.circle(Output, (rx, ry), 1, (255, 255, 255), 1)
        #print("point ", ry, " : ", rx, ry)
    return right_curve
    # print(A*leftPix[0]**2)


# while start:
# start, src_img = vidcap.read()
# frame = cv.resize(src_img, (640, 480))
frame = cv.imread('test_img.png')
gray = cv.cvtColor(frame, cv.COLOR_BGR2GRAY )
_, Thr = cv.threshold(gray, 150, 255, cv.THRESH_BINARY)
matrix = cv.getPerspectiveTransform(Points1, Points2)
transformed_img = cv.warpPerspective(Thr, matrix, (640, 480))

LanePix = curve(transformed_img)
#LeftPix = LanePix[0]
#RightPix = LanePix[1]
#fitted_curve_img = curve(transformed_img, LeftPix, RightPix)


cv.imshow("Result", LanePix)
cv.waitKey(0)

# if cv.waitKey(1) == ord('q'):
# break
