import numpy as np
import cv2

# loads the classifier
faceCascade = cv2.CascadeClassifier('Cascades/haarcascade_frontalface_default.xml')

cap = cv2.VideoCapture(0)
cap.set(3,640) # 높이 설정
cap.set(4,480) # 너비 설정

while True:
    ret, img = cap.read()
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY) 
    # camera를 grayscale mode로 로드하고 parameter들을 전달
    faces = faceCascade.detectMultiScale(
        gray,
        scaleFactor=1.2,
        minNeighbors=5,     
        minSize=(20, 20) #최소 사각형의 크기
    )
    #얼굴을 표시. (x,y) 는 좌표, w,h는 각각 너비와 높이
    for (x,y,w,h) in faces:
        cv2.rectangle(img,(x,y),(x+w,y+h),(255,0,0),2)
        roi_gray = gray[y:y+h, x:x+w]
        roi_color = img[y:y+h, x:x+w]
        
    cv2.imshow('video',img)

    k = cv2.waitKey(30) & 0xff
    if k == 27: # 'ESC' 를 눌러 종료
        break

cap.release()
cv2.destroyAllWindows()
