![newls1](https://user-images.githubusercontent.com/1107765/160220154-2659ea7b-66e9-4ef0-bd08-f3bd22fe2713.png)
newls는 ls를 execlp로 실행하는 프로그램이며 root를 owner로 하는 suid 프로그램으로 설정함

![newls2](https://user-images.githubusercontent.com/1107765/160220157-56780f50-c357-4df6-8c1c-3e6c03760ac4.png)
원래 /etc/shadow를 pass 파일로 저장하는 가짜 ls는 권한이 없어서 동작할 수 없음

![newls3](https://user-images.githubusercontent.com/1107765/160220158-c555fada-56b7-41b4-a99c-4b2cce8f74b2.png)
PATH 환경 변수를 변경하여 가짜 ls가 실행될 수 있도록 함

![newls4](https://user-images.githubusercontent.com/1107765/160220159-6299f077-e6a3-4ad7-b8bb-cdae7502f8dc.png)
newls 실행시 pass에 /etc/shadow 파일이 기록되는걸 확인할 수 있음
