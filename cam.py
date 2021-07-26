import cv2

cap = cv2.VideoCapture("/dev/video10")
while(True):
  ret, frame = cap.read()

  # 將圖片轉為灰階
  gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

  cv2.imshow('frame', gray)

  if cv2.waitKey(1) & 0xFF == ord('q'):
    break

cap.release()
cv2.destroyAllWindows()


