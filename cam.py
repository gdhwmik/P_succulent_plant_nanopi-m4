import cv2
import numpy as np

image = cv2.imread("lena256rgb.jpg")
cv2.imshow("Normal", image)
cv2.waitKey(0)

# Convert BGR to Gray
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
cv2.imshow("Gray", gray)
cv2.waitKey(0)

# Threshold the gray image to binary image
# ...
ret, binary = cv2.threshold(gray, 127, 255, cv2.THRESH_BINARY)
cv2.imshow("Binary", binary)
cv2.waitKey(0)


cv2.destroyAllWindows()
