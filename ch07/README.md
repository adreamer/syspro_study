##mtcp
producer가 벡터 입출력으로 스레드 갯수만큼 read하여 consumer 스레드에 버퍼 분배
destination file은 메모리 매핑으로 열고 consumer가 공유된 메모리에 쓰기함

![mtcp](https://user-images.githubusercontent.com/1107765/162577963-05938acf-5290-46dd-b6a8-fef6d3d6a1ac.png)

하나의 파일 출력 fd에 offset만 바꿔가며 write하기 때문인지
벡터 입출력만으로 copy 하는 것에 비해 성능적인 메리트는 없음
