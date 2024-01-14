import cv2
import os

cam = cv2.VideoCapture(0)
cam.set(3, 640) # 너비 설정
cam.set(4, 480) # 높이 설정

face_detector = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')

# 사람 얼굴 마다 숫자로 ID를 입력
face_id = input('\n enter user id end press <return> ==>  ')

print("\n [INFO] Initializing face capture. Look the camera and wait ...")
# 얼굴 카운트를 초기화한다
count = 0

while(True):
    ret, img = cam.read()
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    faces = face_detector.detectMultiScale(gray, 1.3, 5)

    for (x,y,w,h) in faces:
        cv2.rectangle(img, (x,y), (x+w,y+h), (255,0,0), 2)     
        count += 1

        # 만들어둔 dataset 폴더에 사진이 저장된다
        cv2.imwrite("dataset/User." + str(face_id) + '.' + str(count) + ".jpg", gray[y:y+h,x:x+w])
        cv2.imshow('image', img)

    k = cv2.waitKey(100) & 0xff # 'ESC'를 눌러 종료한다
    if k == 27:
        break
    elif count >= 30: # 30장의 얼굴 샘플을 캡쳐하고 비디오를 중지 
         break

# 정리
print("\n [INFO] Exiting Program and cleanup stuff")
cam.release()
cv2.destroyAllWindows()


