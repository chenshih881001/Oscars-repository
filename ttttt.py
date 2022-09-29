import cv2 as cv
import numpy as np

Raw_Img = cv.imread('D:\轉移\Lane-Tracking-Img\Road-image.jpg')
Height, Width = Raw_Img.shape[0],Raw_Img.shape[1]
Gray_decom = np.zeros_like(Raw_Img)
for i in range(Height):
    for j in range(Width):
        pix_val = Raw_Img[i,j]
        new_pix_val = max(pix_val)
        Gray_decom[i,j]=new_pix_val

cv.imshow("Original",Raw_Img)
cv.imshow("Gray_decom",Gray_decom)
cv.waitKey(0)