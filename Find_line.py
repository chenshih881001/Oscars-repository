import cv2 as cv
import numpy as np
import matplotlib as plt


################################
def PT(image):
    top_left = (200, 200)
    top_right = (400, 200)
    buttom_left = (150, 330)
    buttom_right = (500, 330)
    Points1 = np.float32([top_left, buttom_left, top_right, buttom_right])
    Points2 = np.float32([[0, 0], [0, 640], [480, 0], [480, 640]])
    matrix = cv.getPerspectiveTransform(Points1, Points2)
    transformed_img = cv.warpPerspective(image, matrix, (480, 640))
    return transformed_img

################################

Raw_Img = cv.imread('D:\轉移\Lane-Tracking-Img/Capture.PNG')
Gray_Img = cv.cvtColor(Raw_Img, cv.COLOR_BGR2GRAY)
Blur_Img = cv.GaussianBlur(Gray_Img, (5, 5), 0)
Hist_Img = cv.equalizeHist(Blur_Img)
_, Thr = cv.threshold(Hist_Img, 220, 255, cv.THRESH_BINARY)
#sobel = cv.Sobel(src=Thr, ddepth=cv.CV_64F, dx=1, dy=1, ksize=5)
Canny_edge = cv.Canny(image=Thr, threshold1=400, threshold2=450)

Raw_PT = PT(Raw_Img)
Canny_PT = PT(Canny_edge)

################################

#Image = cv.imread('D:\轉移\Lane-Tracking-Img/artificial.PNG')
#Gray = cv.cvtColor(Image, cv.COLOR_BGR2GRAY)


Height = Canny_PT.shape[0]
Width = Canny_PT.shape[1]

Selected_pixels = []
R_line = []
L_line = []
R = 0
L = 0

for y in range(Height):
    Max = 0
    Min = Width
    Avg = 0
    count = 0
    for x in range(Width):
        pix = Canny_PT[y,x]
        if(pix>230):                #threshold value for pixels
            if(x<=Min):             #get minX
                Min = pix
            if(x>=Max):             #get maxX
                Max= pix
    Avg = (Max+Min)/2
    if(pix<=Avg):                   #classify R_line & L_line
        L_line.append([y,x])
        L = L + 1
    else:
        R_line.append([y,x])
        R = R + 1

clone = np.zeros_like(Canny_PT)
for i in range(L):
    print(L_line[i])
    #cv.circle(clone,L_line[i], 1, (255,255,255), -1)
#print(Selected_pixels[i])
cv.imshow("Test Input", Canny_PT)
cv.imshow("Test Output", clone)
cv.waitKey(0)