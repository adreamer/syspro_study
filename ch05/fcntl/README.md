## fcntl 사용해서 exec 후 파일 자동으로 닫게 만들기

![fcntl](https://user-images.githubusercontent.com/1107765/160242023-0d637655-0b5a-46a2-bf14-44ed553a97a1.png)

FD_CLOEXEC가 설정되어 있지 않을 경우 exec 호출뒤에도 4번 fd가 남아있으며 활성화할 경우 4번 fd가 없는 것을 확인
