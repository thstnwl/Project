< PC 카메라 영상에 나타나는 사람을 인식하여 정보 표시 >
- Implementing one of face recognition algorithms

알고리즘 과정

1. OpenCV에서 제공하는 Haar Cascade Classifier를 사용해 영상에서 얼굴을 검출한 뒤, 이미지를 캡쳐해 dataset 생성
2. OpenCV 패키지에 포함된 인식기 LBPH를 얼굴 recognizer로 사용하고, data set에서 인식되는 얼굴과 id를 반환하며 recognizer를 훈련시키고, yml파일로 저장
3. 훈련된 인식기를 불러와 현재 캠에서 인식되는 얼굴의 id를 예측
