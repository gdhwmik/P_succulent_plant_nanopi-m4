# -*- coding: utf-8 -*-
# =================================================================
# windows10, PyCharm, anaconda2, python 2.7.13, opencv 2.4.13
# 2017-12-17
# powered by tuzixini
# attention: you might need install the encoder fist, like x264vfw
# =================================================================

import cv2  # import opencv

# use opencv open the /dev/video10
cap = cv2.VideoCapture("/dev/video10")
# get the inf of vedio,fps and size
fps = cap.get(cv2.CAP_PROP_FPS)
size = (int(cap.get(cv2.CAP_PROP_FRAME_WIDTH)),
        int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT)))

# point out how to encode videos
# I420-avi=>cv2.cv.CV_FOURCC('X','2','6','4');
# MP4=>cv2.cv.CV_FOURCC('M', 'J', 'P', 'G')
# The mp4 encoder in my computer do not work,so i just use X264
videoWriter = cv2.VideoWriter('oto_other.avi', cv2.VideoWriter_fourcc('X', '2', '6', '4'), fps, size)
# read one frame from the video
success, frame = cap.read()

while success:
    cv2.imshow("Oto Video", frame)  # display this frame
    cv2.waitKey(int(fps))  # delay
    videoWriter.write(frame)  # write one frame into the output video
    success, frame = cap.read()  # get the next frame of the video
# some process after finish all the program
cv2.destroyAllWindows()     # close all the widows opened inside the program
cap.release        # release the video read/write handler
videoWriter.release
