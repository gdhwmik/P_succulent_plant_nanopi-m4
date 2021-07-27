# USAGE
# python test_detector.py --detector output/stop_sign_detector.svm --testing stop_sign_testing

# import the necessary packages
from imutils import paths
import dlib
import cv2
import numpy
import time
#import argparse


#load finish detector
detector_bears = dlib.simple_object_detector("svm/Bears_Paw.svm")
detector_mesem = dlib.simple_object_detector("svm/Crassula_Mesembrianthoides.svm")
detector_jade = dlib.simple_object_detector("svm/Gollum_Jade.svm")
detector_panda = dlib.simple_object_detector("svm/Panda_Plant.svm")
detector_coop = dlib.simple_object_detector("svm/Haworthia_Cooperi_var.Truncata.svm")

cv2.namedWindow("Oto Video", 0)
cv2.resizeWindow("Oto Video", 1280, 720)

# use opencv open the /dev/video10
cap = cv2.VideoCapture("/dev/video10")
#cap = cv2.VideoCapture(0)
# get/set the inf of vedio,fps and size
fps = cap.get(cv2.CAP_PROP_FPS)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 960)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 720)
fd = open('/sys/class/gpio/gpio50/value','r')


while True:

    ret, image = cap.read()
    value = fd.read

    if (value == 1):
        
        boxes1 = detector_panda(cv2.cvtColor(image, cv2.COLOR_BGR2RGB))
        boxes2 = detector_jade(cv2.cvtColor(image, cv2.COLOR_BGR2RGB))
        boxes3 = detector_mesem(cv2.cvtColor(image, cv2.COLOR_BGR2RGB))
        boxes4 = detector_bears(cv2.cvtColor(image, cv2.COLOR_BGR2RGB))
        boxes5 = detector_coop(cv2.cvtColor(image, cv2.COLOR_BGR2RGB))


        for b in boxes1:
            (x, y, w, h) = (b.left(), b.top(), b.right(), b.bottom())
            cv2.rectangle(image, (x, y), (w, h), (0, 255, 0), 2)
            print(x,y)
            cv2.putText(image, "Panda", ( x+5, y+30 ), cv2.FONT_HERSHEY_COMPLEX,1, (0,0,255), 1, 10)   
            #cv2.waitKey(0)
               
        for b in boxes2:
            (x, y, w, h) = (b.left(), b.top(), b.right(), b.bottom())
            cv2.rectangle(image, (x, y), (w, h), (0, 255, 0), 2)
            print(x,y)
            cv2.putText(image, "Jade", ( x+5, y+30 ), cv2.FONT_HERSHEY_COMPLEX,1, (0,0,255), 1, 10)   
            #cv2.waitKey(0)
               
        for b in boxes3:
            (x, y, w, h) = (b.left(), b.top(), b.right(), b.bottom())
            cv2.rectangle(image, (x, y), (w, h), (0, 255, 0), 2)
            print(x,y)
            cv2.putText(image, "Mesem", ( x+5, y+30 ), cv2.FONT_HERSHEY_COMPLEX,1, (0,0,255), 1, 10)              
            #cv2.waitKey(0)
            
        for b in boxes4:
            (x, y, w, h) = (b.left(), b.top(), b.right(), b.bottom())
            cv2.rectangle(image, (x, y), (w, h), (0, 255, 0), 2)
            print(x,y)
            cv2.putText(image, "Bears", ( x+5, y+30 ), cv2.FONT_HERSHEY_COMPLEX,1, (0,0,255), 1, 10)    
          
        for b in boxes5:
            (x, y, w, h) = (b.left(), b.top(), b.right(), b.bottom())
            cv2.rectangle(image, (x, y), (w, h), (0, 255, 0), 2)
            print(x,y)
            cv2.putText(image, "Coop", ( x+5, y+30 ), cv2.FONT_HERSHEY_COMPLEX,1, (0,0,255), 1, 10)    
        
        cv2.imshow("Oto Video", image) 
        time.sleep(3)  
        
    cv2.imshow("Oto Video", image)  # display this frame
    cv2.waitKey(int(fps))  # delay
#    videoWriter.write(frame)  # write one frame into the output video
    success, frame = cap.read()  # get the next frame of the video   
    if cv2.waitKey(1) & 0xFF == ord("q"):
        break
    
cv2.destroyAllWindows()
fd.close()
cap.release()
videoWriter.releas 
