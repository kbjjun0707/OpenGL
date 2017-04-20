# OpenGL
OpenGL 프로젝트들

glut 윈도우 환경의 GL을 만들 때, 기본적으로 사용할 프로젝트

나름대로 공부한 ray 구현 
ray와 충돌체의 충돌을 통하여 object picking 및 이동

화면의 점 x는 세상좌표(glVertex3f(1.f, 1.f, 1.f)와 같은 좌표)에 
그린 점 X를 이동, 회전, 투영 등의 변형 과정을 거쳐 표시되는 점.
x = viewport * projection matrix * modelview matrix * X 의 과정을 거친다.
