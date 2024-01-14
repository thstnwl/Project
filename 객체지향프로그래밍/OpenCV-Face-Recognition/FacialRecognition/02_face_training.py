import cv2
import numpy as np
from PIL import Image
import os

# 이미지 데이터베이스 경로
path = 'dataset'

recognizer = cv2.face.LBPHFaceRecognizer_create()
detector = cv2.CascadeClassifier("haarcascade_frontalface_default.xml");

# 이미지와 레이블 데이터를 가져오는 함수
def getImagesAndLabels(path):

    imagePaths = [os.path.join(path,f) for f in os.listdir(path)]     
    faceSamples=[]
    ids = []

    for imagePath in imagePaths:

        PIL_img = Image.open(imagePath).convert('L') #  grayscale로 변환
        img_numpy = np.array(PIL_img,'uint8')

        id = int(os.path.split(imagePath)[-1].split(".")[1])
        faces = detector.detectMultiScale(img_numpy)

        for (x,y,w,h) in faces:
            faceSamples.append(img_numpy[y:y+h,x:x+w])
            ids.append(id)

    return faceSamples,ids

print ("\n [INFO] Training faces. It will take a few seconds. Wait ...")
faces,ids = getImagesAndLabels(path)
recognizer.train(faces, np.array(ids))

# 모델을 trainer/trainer.yml에 저장
recognizer.write('trainer/trainer.yml')

# 훈련된 얼굴 수를 print하고 종료
print("\n [INFO] {0} faces trained. Exiting Program".format(len(np.unique(ids))))


