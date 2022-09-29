from turtle import clone
import cv2 as cv
import numpy as np
import matplotlib.pyplot as plt
from operator import itemgetter
from glob import glob
import sys
import math

def PT(image, Height):
    top_left = (700, 820)
    top_right = (900, 820)
    buttom_left = (250, Height)
    buttom_right = (1200, Height)
    Points1 = np.float32([top_left, buttom_left, top_right, buttom_right])
    Points2 = np.float32([[0, 0], [0, 640], [480, 0], [480, 640]])
    matrix = cv.getPerspectiveTransform(Points1, Points2)
    transformed_img = cv.warpPerspective(image, matrix, (480, 640))
    return transformed_img


Raw_Img = cv.imread('C:\\Users\\test\\Desktop\\Lane-Tracking-Img\\original_exposure.jpg')
Gray_Img = cv.cvtColor(Raw_Img,cv.COLOR_BGR2GRAY)
Blur_Img = cv.GaussianBlur(Gray_Img,(5,5),0)
Hist_Img = cv.equalizeHist(Blur_Img)
_, Thr = cv.threshold(Hist_Img, 150, 255, cv.THRESH_BINARY)
sobel = cv.Sobel(src=Thr, ddepth=cv.CV_64F, dx=1, dy=1, ksize=5)
Canny_edge = cv.Canny(image=Thr, threshold1=400, threshold2=450)



Height = Raw_Img.shape[0]  
result_Sobel = PT(Raw_Img, Height)
result_Canny = PT(Canny_edge, Height)######################
Clone = np.zeros_like(result_Canny)
lines = cv.HoughLines(result_Canny, 1, np.pi / 180, 30, 0, 0, 0, np.pi)
for line in lines:
    rho,theta = line[0]
    a = np.cos(theta)
    b = np.sin(theta)
    x0 = a*rho
    y0 = b*rho
    x1 = int(x0 + 1000*(-b))
    y1 = int(y0 + 1000*(a))
    x2 = int(x0 - 1000*(-b))
    y2 = int(y0 - 1000*(a))
    cv.line(Clone,(x1,y1),(x2,y2),[255, 0, 0, 255])
cv.imshow('clone', Clone)
cv.waitKey(0)

'''
Img_resize = cv.resize(Canny_edge, (640, 480))  
cv.imshow("Canny edge detection", Img_resize)
cv.imshow("CAnny edge detection & Perspective transform", result_Canny)
'''






