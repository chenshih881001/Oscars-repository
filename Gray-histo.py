import cv2 as cv
import matplotlib.image as mpimg
from matplotlib import pyplot as plt
import numpy as np

Raw_Img = plt.imread('D:\轉移\Lane-Tracking-Img/tttt.jpg')
Test = plt.imread('D:\轉移\Lane-Tracking-Img/tttt.jpg')
R, G, B = Raw_Img[:,:,0], Raw_Img[:,:,1], Raw_Img[:,:,2]
R1, G1, B1 = Test[:,:,0], Test[:,:,1], Test[:,:,2]


Row = 2
Col = 5

fig = plt.figure(figsize=(10,5))

Gray_weighted_avg = 0.2989 * R + 0.5870 * G + 0.1140 * B
fig.add_subplot(Row, Col, 1)
plt.imshow(Gray_weighted_avg, cmap='gray')
plt.axis('off')
plt.title("Weighted average method", fontsize=14)

Height, Width = Raw_Img.shape[0],Raw_Img.shape[1]
Gray_decom_max = np.zeros_like(Raw_Img)
Gray_decom_min = np.zeros_like(Raw_Img)
Gray_desaturation = np.zeros_like(Raw_Img)
for i in range(Height):
    for j in range(Width):
        pix_val = Raw_Img[i,j]
        Max = int(max(pix_val))
        Min = int(min(pix_val))
        Gray_decom_max[i,j] = Max
        Gray_decom_min[i,j] = Min
        Gray_desaturation[i,j] = (Max+Min)/2
fig.add_subplot(Row, Col, 2)
plt.imshow(Gray_decom_max, cmap='gray') 
plt.axis('off')
plt.title("Decomposition method - Maximum", fontsize=14)

fig.add_subplot(Row, Col, 3)
plt.imshow(Gray_decom_min, cmap='gray')
plt.axis('off')
plt.title("Decomposition method - Minimum", fontsize=14)

fig.add_subplot(Row, Col, 4)
plt.imshow(Gray_desaturation, cmap='gray')
plt.axis('off')
plt.title("Desaturation method", fontsize=14)

fig.add_subplot(Row, Col, 4)
plt.imshow(Gray_desaturation, cmap='gray')
plt.axis('off')
plt.title("Desaturation method", fontsize=14)


fig.add_subplot(Row, Col, 5)
plt.hist(Gray_weighted_avg.ravel(), 256, [0, 256])

fig.add_subplot(Row, Col, 6)
plt.hist(Gray_decom_max.ravel(), 256, [0, 256])

fig.add_subplot(Row, Col, 7)
plt.hist(Gray_decom_min.ravel(), 256, [0, 256])

fig.add_subplot(Row, Col, 8)
plt.hist(Gray_desaturation.ravel(), 256, [0, 256])

plt.show()
#cv.imshow('Original',Raw_Img)
#cv.waitKey(0)