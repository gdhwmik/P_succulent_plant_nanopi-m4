import cv2
import numpy as np
import sys

cap = cv2.VideoCapture(0)
# Capture frame-by-frame

def nothing(x):
    pass

# Creating a window for later use
cv2.namedWindow('hsv_demo',cv2.WINDOW_NORMAL)
cv2.namedWindow('hsv_demo1',cv2.WINDOW_NORMAL)
# Starting with 100's to prevent error while masking
h, s, v = 100, 100, 100

# Creating track bar
cv2.createTrackbar('hl', 'hsv_demo1', 0,   179, nothing)
cv2.createTrackbar('hu', 'hsv_demo1', 179, 179, nothing)
cv2.createTrackbar('sl', 'hsv_demo1', 0,   255, nothing)
cv2.createTrackbar('su', 'hsv_demo1', 255, 255, nothing)
cv2.createTrackbar('vl', 'hsv_demo1', 0,   255, nothing)
cv2.createTrackbar('vu', 'hsv_demo1', 255, 255, nothing)
cv2.createTrackbar('ksize', 'hsv_demo', 0, 10, nothing)
cv2.createTrackbar('evalue', 'hsv_demo', 0, 10, nothing)
cv2.createTrackbar('dvalue', 'hsv_demo', 0, 10, nothing)


while True:
   
    # get info from track bar and appy to result
    hl = cv2.getTrackbarPos('hl', 'hsv_demo1')
    hu = cv2.getTrackbarPos('hu', 'hsv_demo1')
    sl = cv2.getTrackbarPos('sl', 'hsv_demo1')
    su = cv2.getTrackbarPos('su', 'hsv_demo1')
    vl = cv2.getTrackbarPos('vl', 'hsv_demo1')
    vu = cv2.getTrackbarPos('vu', 'hsv_demo1')
    
    # Capture frame-by-frame
    ret, frame = cap.read()

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    ksize  = cv2.getTrackbarPos('ksize', 'hsv_demo')
    evalue  = cv2.getTrackbarPos('evalue', 'hsv_demo')
    dvalue  = cv2.getTrackbarPos('dvalue', 'hsv_demo')
        
    kernel = np.ones((3,3), np.uint8)
    
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    lower = np.array([hl, sl, vl])
    upper = np.array([hu, su, vu])
    mask = cv2.inRange(hsv, lower, upper)
    mask1 = cv2.GaussianBlur(mask, (2*ksize+1, 2*ksize+1), 0)
    mask1  = cv2.erode(mask1, kernel, iterations=evalue)
    maskl  = cv2.dilate(mask1, kernel, iterations=dvalue)
    result = cv2.bitwise_and(frame, frame, mask=maskl)
    

    
    # Display the resulting frame
#    cv2.namedWindow("hsv_demo",0);

    cv2.imshow("hsv_demo", result)

    if cv2.waitKey(1) & 0xFF == ord("q"):
        break

# When everything is done, release the capture
cap.release()
cv2.destroyAllWindows()
