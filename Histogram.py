import cv2 as cv
import matplotlib.image as mpimg
from matplotlib import pyplot as plt
import numpy as np

Row = 2
Col = 3
fig = plt.figure(figsize=(10,5))

Raw_img = cv.imread('D:\轉移\Lane-Tracking-Img/original_exposure.jpg')
Gray = cv.cvtColor(Raw_img,cv.COLOR_BGR2GRAY)

fig.add_subplot(Row, Col, 1)
plt.imshow(Gray, cmap='gray')
plt.axis('off')
plt.title("Gray image", fontsize=15)

Equalized = cv.equalizeHist(Gray)
fig.add_subplot(Row, Col, 2)
plt.imshow(Equalized, cmap='gray')
plt.axis('off')
plt.title("Histogram equalization", fontsize=15)

clahe_obj = cv.createCLAHE(clipLimit=2.0, tileGridSize=(8,8))
Clahe = clahe_obj.apply(Gray)
fig.add_subplot(Row, Col, 3)
plt.imshow(Clahe, cmap='gray')
plt.axis('off')
plt.title("Adaptive histogram equalization", fontsize=15)

fig.add_subplot(Row, Col, 4)
plt.hist(Gray.ravel(), 256, [0, 256])
plt.title("Histogram - gray image", fontsize=15)

fig.add_subplot(Row, Col, 5)
plt.hist(Equalized.ravel(), 256, [0, 256])
plt.title("Histogram - Histogram equalization", fontsize=15)

fig.add_subplot(Row, Col, 6)
plt.hist(Clahe.ravel(), 256, [0, 256])
plt.title("Histogram - Adaptive histogram equalization", fontsize=15)

plt.show()